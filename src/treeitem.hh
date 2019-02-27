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
        static ObjectTreeItem* Unpack(const QJsonValue&,
                                      ObjectTreeItem* parent);

        explicit ObjectTreeItem(QList<QVariant>&,
                                ObjectTreeItem* parent = nullptr);
        virtual ~ObjectTreeItem();

        ObjectTreeItem* AppendChild(ObjectTreeItem* child);

        ObjectTreeItem* Child(int row);
        int ChildCount() const;
        int ColumnCount() const;
        virtual QVariant Data(int column) const;
        int Row() const;
        ObjectTreeItem* ParentItem();

        void Edit();
        virtual void Select(Ui::MainWindow*, ObjectForm* = nullptr);

        virtual QDebug& Debug(QDebug&) const;

        friend QTextStream& operator<<(QTextStream&, const ObjectTreeItem&);

      protected:
        ObjectTreeItem(Object*, ObjectTreeItem*);

        virtual Object* GetObject();
        virtual const Object* GetObject() const;

        QList<QVariant>& ItemData();
        const QList<QVariant>& ItemData() const;

      private:
        QList<ObjectTreeItem*> mChildItems;
        QList<QVariant> mItemData;
        ObjectTreeItem* mParentItem;
    };

    class VehicleTreeItem : public ObjectTreeItem
    {
      public:
        static VehicleTreeItem* Unpack(const QJsonObject&,
                                       ObjectTreeItem* parent);

        void Select(Ui::MainWindow*, ObjectForm* = nullptr) override;

        QDebug& Debug(QDebug&) const override;

      protected:
        VehicleTreeItem(QList<QVariant>&,
                        ObjectTreeItem* parent,
                        Vehicle*);
        ~VehicleTreeItem() override;

        Object* GetObject() override;
        const Object* GetObject() const override;

      private:
        Vehicle* mVehicle;
    };

    class WeaponTreeItem : public ObjectTreeItem
    {
      public:
        static WeaponTreeItem* New();
        static WeaponTreeItem* Unpack(const QJsonObject&,
                                      ObjectTreeItem* parent);

        WeaponTreeItem(QList<QVariant>&,
                       ObjectTreeItem* parent,
                       Weapon*);
        ~WeaponTreeItem() override;

        void Select(Ui::MainWindow*, ObjectForm* = nullptr) override;

      protected:
        Object* GetObject() override;
        const Object* GetObject() const override;

        QDebug& Debug(QDebug&) const override;

      private:
        Weapon* mWeapon;
    };

    QDebug& operator<<(QDebug&, const ObjectTreeItem&);
  };
};

#endif // TREEITEM_HH
