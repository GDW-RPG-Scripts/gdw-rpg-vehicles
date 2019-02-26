/*
**
**
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
      : QAbstractItemModel(parent)
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
      rootData << "Name" << "Type" << "Nationality";
      mRootItem = new ObjectTreeItem(rootData);
    }

    void
    TreeModel::Import(QFile& file)
    {
      const QByteArray& jba = file.readAll();
      QJsonDocument jdoc = QJsonDocument::fromJson(jba);
      SetupModelData(mRootItem, jdoc);
    }

    void
    TreeModel::SetupModelData(ObjectTreeItem* parent, const QJsonDocument& jdoc)
    {
      if (jdoc.isObject())
        ObjectTreeItem::Unpack(jdoc.object(), parent);
      else if (jdoc.isArray())
        for (int index = 0; index < jdoc.array().count(); ++index)
          ObjectTreeItem::Unpack(jdoc[index].toObject(), parent);
    }

    void
    TreeModel::AddItem(QString type, const QModelIndex& index)
    {
      qDebug() << "TreeModel::AddItem(QString"
               << type
               << ", const QModelIndex&"
               << index;

      ObjectTreeItem* parent;

      if(index.internalPointer() == nullptr) {
        CreateRootItem();
        parent = mRootItem;
      } else {
        parent =
            static_cast<ObjectTreeItem*>(index.internalPointer());
      }

      // ObjectTreeItem::Unpack(jdoc.object(), parent);
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

    QVariant
    TreeModel::headerData(int section,
                          Qt::Orientation orientation,
                          int role) const
    {
      if (orientation == Qt::Horizontal && role == Qt::DisplayRole)
        return mRootItem->Data(section);

      return QVariant();
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
        parentItem =
            static_cast<ObjectTreeItem*>(parent.internalPointer());

      return parentItem->ChildCount();
    }

    int
    TreeModel::columnCount(const QModelIndex& parent) const
    {
      if (parent.isValid())
        return static_cast<ObjectTreeItem*>(parent.internalPointer())->ColumnCount();
      else
        return mRootItem->ColumnCount();
    }

    QVariant
    TreeModel::data(const QModelIndex& index, int role) const
    {
      if (!index.isValid())
        return QVariant();

      if (role != Qt::DisplayRole)
        return QVariant();

      ObjectTreeItem* item =
          static_cast<ObjectTreeItem*>(index.internalPointer());

      return item->Data(index.column());
    }

    Qt::ItemFlags
    TreeModel::flags(const QModelIndex& index) const
    {
      if (!index.isValid())
        return nullptr;

      return QAbstractItemModel::flags(index);
    }

    QModelIndex
    TreeModel::index(int row, int column, const QModelIndex& parent) const
    {
      if (!hasIndex(row, column, parent))
        return QModelIndex();

      ObjectTreeItem* parentItem;

      if (!parent.isValid())
        parentItem = mRootItem;
      else
        parentItem = static_cast<ObjectTreeItem*>(parent.internalPointer());

      ObjectTreeItem* childItem = parentItem->Child(row);
      if (childItem)
        return createIndex(row, column, childItem);
      else
        return QModelIndex();
    }

    QModelIndex
    TreeModel::parent(const QModelIndex& index) const
    {
      if (!index.isValid())
        return QModelIndex();

      ObjectTreeItem *childItem =
          static_cast<ObjectTreeItem*>(index.internalPointer());
      ObjectTreeItem *parentItem = childItem->ParentItem();

      if (parentItem == mRootItem)
        return QModelIndex();

      return createIndex(parentItem->Row(), 0, parentItem);
    }

    QTextStream&
    operator<<(QTextStream& ots, const TreeModel& model)
    {
      return ots << *model.mRootItem;
    }
  };
};
