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

#include "weapon_global.hh"

#include "objectitem.hh"

#include "weapon.hh"
#include "weaponform.hh"
#include "weaponmodel.hh"

#include <QList>
#include <QVariant>

namespace Ui {
  class VehicleForm;
}

namespace GDW
{
  namespace RPG
  {
    class WEAPONSHARED_EXPORT WeaponTreeItem : public ObjectTreeItem
    {
      public:
        static WeaponTreeItem* Create(ObjectTreeItem* parent = nullptr);
        static WeaponTreeItem* Unpack(const QJsonObject&,
                                      ObjectTreeItem* parent);

        WeaponTreeItem(Weapon*, ObjectTreeItem* parent);
        ~WeaponTreeItem() override;

        WeaponForm* GetForm() override;
        // void Select(Ui::Workspace&, ObjectForm* = nullptr) override;

      protected:
        Weapon* GetObject() override;
        const Weapon* GetObject() const override;

        WeaponModel* Model() const override;

        QDebug& Debug(QDebug&) const override;
    };
  };
};

#endif // TREEITEM_HH
