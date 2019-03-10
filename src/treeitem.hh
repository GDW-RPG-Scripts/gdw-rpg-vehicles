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

#ifndef TREEITEM_HH
#define TREEITEM_HH

#include "objectform.hh"

#include "vehicle.hh"
#include "weapon.hh"

#include <QList>
#include <QVariant>

class QStackedWidget;
class QTextStream;

namespace Ui {
  class MainWindow;
}

namespace GDW
{
  namespace RPG
  {
    class Object;

    class ObjectTreeItem
    {
      public:
        static ObjectTreeItem* Create(int type, ObjectTreeItem* parent);
        static ObjectTreeItem* Unpack(const QJsonValue&,
                                      ObjectTreeItem* parent);

        ObjectTreeItem(Object*, ObjectTreeItem* parent = nullptr);
        ObjectTreeItem(QList<QVariant>&,
                       ObjectTreeItem* parent = nullptr);
        virtual ~ObjectTreeItem();

        ObjectTreeItem* AppendChild(ObjectTreeItem* child);
        bool InsertChildren(int, int, int type);
        bool RemoveChildren(int, int);

        ObjectTreeItem* Child(int row);
        int ChildCount() const;
        int ColumnCount() const;
        virtual QVariant Data(int column) const;
        virtual bool SetData(int column, const QVariant&);
        int Row() const;
        ObjectTreeItem* ParentItem();

        void RefreshItemData();
        virtual void Select(Ui::MainWindow&, ObjectForm* = nullptr);
        virtual void Unselect(Ui::MainWindow&, ObjectForm* = nullptr);

        virtual QDebug& Debug(QDebug&) const;

        friend QTextStream& operator<<(QTextStream&, const ObjectTreeItem&);

      protected:
        virtual Object* GetObject();
        virtual const Object* GetObject() const;

      private:
        void ClearObjectGroupBox(Ui::MainWindow&);

        Object* mObject;
        QList<ObjectTreeItem*> mChildItems;
        QList<QVariant> mItemData;
        ObjectTreeItem* mParentItem;
    };

    class VehicleTreeItem : public ObjectTreeItem
    {
      public:
        static VehicleTreeItem* Create(ObjectTreeItem* parent = nullptr);
        static VehicleTreeItem* Unpack(const QJsonObject&,
                                       ObjectTreeItem* parent);

        void Select(Ui::MainWindow&, ObjectForm* = nullptr) override;

        QDebug& Debug(QDebug&) const override;

      protected:
        VehicleTreeItem(Vehicle*, ObjectTreeItem* parent);
        ~VehicleTreeItem() override;

        Vehicle* GetObject() override;
        const Vehicle* GetObject() const override;

        //      private:
        //        Vehicle* mVehicle;
    };

    class WeaponTreeItem : public ObjectTreeItem
    {
      public:
        static WeaponTreeItem* Create(ObjectTreeItem* parent = nullptr);
        static WeaponTreeItem* Unpack(const QJsonObject&,
                                      ObjectTreeItem* parent);

        WeaponTreeItem(Weapon*, ObjectTreeItem* parent);
        ~WeaponTreeItem() override;

        void Select(Ui::MainWindow&, ObjectForm* = nullptr) override;

      protected:
        Weapon* GetObject() override;
        const Weapon* GetObject() const override;

        QDebug& Debug(QDebug&) const override;

        //      private:
        //        Weapon* mWeapon;
    };

    QDebug& operator<<(QDebug&, const ObjectTreeItem&);
  };
};

#endif // TREEITEM_HH
