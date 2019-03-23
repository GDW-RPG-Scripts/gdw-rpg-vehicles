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

#ifndef OBJECTTREEITEM_HH
#define OBJECTTREEITEM_HH

#include "object_global.hh"

#include <QList>
#include <QVariant>

class QStackedWidget;
class QTextStream;

namespace Ui {
  class Workspace;
}

namespace GDW
{
  namespace RPG
  {
    class Object;
    class ObjectForm;

    class OBJECTSHARED_EXPORT ObjectTreeItem
    {
      public:
        ObjectTreeItem(Object*, ObjectTreeItem* parent = nullptr);
        ObjectTreeItem(const QList<QVariant>&,
                       ObjectTreeItem* parent = nullptr);
        virtual ~ObjectTreeItem();

        ObjectTreeItem* AppendChild(ObjectTreeItem* child);
        bool InsertChildren(int, int, /*int type,*/ ObjectTreeItem* = nullptr);
        bool RemoveChildren(int, int);

        ObjectTreeItem* Child(int row);
        int ChildCount() const;
        int ColumnCount() const;
        virtual QVariant Data(int column) const;
        virtual bool SetData(int column, const QVariant&);
        int Row() const;
        ObjectTreeItem* ParentItem();

        void RefreshItemData();

        virtual ObjectForm* GetForm();
        // virtual void Select(Ui::Workspace&, ObjectForm* = nullptr);
        // virtual void Unselect(Ui::Workspace&, ObjectForm* = nullptr);

        virtual QDebug& Debug(QDebug&) const;

        friend QTextStream& operator<<(QTextStream&, const ObjectTreeItem&);

      signals:

      public slots:

      protected:
        virtual Object* GetObject();
        virtual const Object* GetObject() const;

      private:
        // void ClearObjectGroupBox(Ui::Workspace&);

        Object* mObject;
        QList<ObjectTreeItem*> mChildItems;
        QList<QVariant> mItemData;
        ObjectTreeItem* mParentItem;
    };

    QDebug& operator<<(QDebug&, const ObjectTreeItem&);
  };
};

#endif // OBJECTTREEITEM_HH
