/*
**
**
*/

#include "model.hh"

#include "treeitem.hh"

#include "objectform.hh"

#include <QJsonArray>
#include <QJsonDocument>

namespace GDW
{
  namespace RPG
  {
    TreeModel::TreeModel(const QByteArray& jba, QObject* parent)
      : QAbstractItemModel(parent)
    {
      QList<QVariant> rootData;
      rootData << "Name" << "Type" << "Nationality";
      mRootItem = new ObjectTreeItem(rootData);

      QJsonDocument jdoc = QJsonDocument::fromJson(jba);
      SetupModelData(mRootItem, jdoc);
    }

    TreeModel::~TreeModel()
    {
      delete mRootItem;
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
  };
};
