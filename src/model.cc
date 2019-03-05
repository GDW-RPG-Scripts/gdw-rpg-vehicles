/**
 * GDW RPG Vehicles, a vehicle database for Traveller and other GDW derived RPGs.
 *
 * Copyright (C) 2018-2019 Michael N. Henry
 *
 * This file is part of GDW RPG Vehicles.
 *
 * GDW RPG Vehicles is free software: you can redistribute it and/or modify it under the terms of the
 * GNU General Public License as published by the Free Software Foundation, either version 2 of the
 * License, or (at your option) any later version.
 *
 * GDW RPG Vehicles is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY;
 * without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 *
 * See the GNU General Public License for more details. You should have received a copy of the GNU
 * General Public License along with GDW RPG Vehicles. If not, see <http://www.gnu.org/licenses/>.
 */

#include "model.hh"

#include "treeitem.hh"

#include "objectform.hh"

#include "ui_mainwindow.h"

#include <QDebug>
#include <QJsonArray>
#include <QJsonDocument>

#if defined(QT_PRINTSUPPORT_LIB)
#include <QtPrintSupport/qtprintsupportglobal.h>
#if QT_CONFIG(printer)
#if QT_CONFIG(printdialog)
#include <QPrintDialog>
#endif // QT_CONFIG(printdialog)
#include <QPrinter>
#endif // QT_CONFIG(printer)
#endif // QT_PRINTSUPPORT_LIB

namespace GDW
{
  namespace RPG
  {
    TreeModel::TreeModel(QObject* parent)
      : QAbstractItemModel(parent), mCurrentType(0)
    {
      CreateRootItem();
    }

    TreeModel::~TreeModel()
    {
      delete mRootItem;
    }

    void
    TreeModel::CreateRootItem()
    {
      QList<QVariant> rootData;
      rootData << tr("Name") << tr("Type") << tr("Nationality");
      mRootItem = new ObjectTreeItem(rootData);
    }

    void
    TreeModel::SetupModelData(const QJsonDocument& jdoc, ObjectTreeItem* parent)
    {
      if (jdoc.isObject())
        ObjectTreeItem::Unpack(jdoc.object(), parent);
      else if (jdoc.isArray())
        for (int index = 0; index < jdoc.array().count(); ++index)
          ObjectTreeItem::Unpack(jdoc[index].toObject(), parent);
    }

    //
    // Public methods
    //
    //    bool
    //    TreeModel::AddItem(int type, const QModelIndex& index)
    //    {
    //      if(!index.isValid()) {
    //        ObjectTreeItem::Create(type, mRootItem);
    //      } else {
    //        ObjectTreeItem::Create(type, GetItem(index));
    //      }

    //      return true;
    //    }

    void
    TreeModel::CurrentType(int type)
    {
      mCurrentType = type;
    }

    ObjectTreeItem*
    TreeModel::GetItem(const QModelIndex& index) const
    {
      if (index.isValid()) {
        ObjectTreeItem* item =
            static_cast<ObjectTreeItem*>(index.internalPointer());
        if (item)
          return item;
      }
      return mRootItem;
    }

    void
    TreeModel::Import(QFile& file)
    {
      const QByteArray& jba = file.readAll();
      QJsonDocument jdoc = QJsonDocument::fromJson(jba);
      SetupModelData(jdoc, mRootItem);
    }

    void
    TreeModel::Print(QWidget* parent) const
    {
#if QT_CONFIG(printer)
      QPrinter printDev;
#if QT_CONFIG(printdialog)
      QPrintDialog dialog(&printDev, parent);
      if (dialog.exec() == QDialog::Rejected)
        return;
#endif // QT_CONFIG(printdialog)
      //ui->textEdit->print(&printDev);
#endif // QT_CONFIG(printer)
    }


    //
    // Overrides
    //
    int
    TreeModel::columnCount(const QModelIndex& parent) const
    {
      if (parent.isValid())
        return
            static_cast<ObjectTreeItem*>(parent.internalPointer())->ColumnCount();
      else
        return mRootItem->ColumnCount();
    }

    QVariant
    TreeModel::data(const QModelIndex& index, int role) const
    {
      if (!index.isValid())
        return QVariant();

      if (role != Qt::DisplayRole && role != Qt::EditRole)
        return QVariant();

      return GetItem(index)->Data(index.column());
    }

    Qt::ItemFlags
    TreeModel::flags(const QModelIndex& index) const
    {
      if (!index.isValid())
        return nullptr;

      return QAbstractItemModel::flags(index);
      // return Qt::ItemIsEditable | QAbstractItemModel::flags(index);
    }

    QVariant
    TreeModel::headerData(int section,
                          Qt::Orientation orientation,
                          int role) const
    {
      if (orientation == Qt::Horizontal && role == Qt::DisplayRole)
        return mRootItem->Data(section);

      return QVariant();
    }

    QModelIndex
    TreeModel::index(int row, int column, const QModelIndex& parent) const
    {
      if (!hasIndex(row, column, parent))
        return QModelIndex();

      ObjectTreeItem* parentItem = GetItem(parent);

      ObjectTreeItem* childItem = parentItem->Child(row);
      if (childItem)
        return createIndex(row, column, childItem);
      else
        return QModelIndex();
    }

    bool
    TreeModel::insertRows(int position, int rows, const QModelIndex& parent)
    {
      ObjectTreeItem* parentItem = GetItem(parent);

      beginInsertRows(parent, position, position + rows - 1);
      bool success = parentItem->InsertChildren(position, rows, mCurrentType);
      endInsertRows();

      return success;
    }

    QModelIndex
    TreeModel::parent(const QModelIndex& index) const
    {
      if (!index.isValid())
        return QModelIndex();

      ObjectTreeItem* childItem = GetItem(index);
      ObjectTreeItem* parentItem = childItem->ParentItem();

      if (parentItem == mRootItem)
        return QModelIndex();

      return createIndex(parentItem->Row(), 0, parentItem);
    }

    bool
    TreeModel::removeRows(int position, int rows, const QModelIndex& parent)
    {
      ObjectTreeItem* parentItem = GetItem(parent);

      beginRemoveRows(parent, position, position + rows - 1);
      bool success = parentItem->RemoveChildren(position, rows);
      endRemoveRows();

      return success;
    }

    int
    TreeModel::rowCount(const QModelIndex& parent) const
    {
      ObjectTreeItem* parentItem;
      if (parent.column() > 0)
        return 0;

      if (!parent.isValid())
        parentItem = mRootItem;
      else
        parentItem = GetItem(parent);

      return parentItem->ChildCount();
    }

    bool
    TreeModel::setData(const QModelIndex& index,
                       const QVariant& value, int role)
    {
      if (!index.isValid() || role != Qt::EditRole)
        return false;

      ObjectTreeItem* item = GetItem(index);
      bool result = item->SetData(index.column(), value);

      if (result)
        emit dataChanged(index, index, {role});

      return result;
    }

    QTextStream&
    operator<<(QTextStream& ots, const TreeModel& model)
    {
      return ots << *model.mRootItem;
    }
  };
};
