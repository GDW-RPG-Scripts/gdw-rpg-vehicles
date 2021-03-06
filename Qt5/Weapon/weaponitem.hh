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

#ifndef WEAPONITEM_HH
#define WEAPONITEM_HH

#include "weapon_global.hh"

#include "objectitem.hh"

#include "weapon.hh"
#include "weaponform.hh"
#include "weaponmodel.hh"

#include "munitionmodel.hh"

#include <QList>
#include <QVariant>

namespace Ui {
  class VehicleForm;
}

extern void GDW_RPG_Weapon_Initialize();

namespace GDW
{
  namespace RPG
  {
    class WEAPONSHARED_EXPORT WeaponItem : public ObjectItem
    {
        Q_OBJECT

      public:
        static WeaponItem* Create(ObjectItem* parent = nullptr);
        static WeaponItem* Unpack(const QJsonObject&,
                                      ObjectItem* parent);

        WeaponItem(Weapon*, ObjectItem* parent);
        ~WeaponItem() override;

        WeaponItem* Copy() const override;

        WeaponForm* GetForm(QUndoStack*) override;
        // void Select(Ui::Workspace&, ObjectForm* = nullptr) override;

        Weapon* GetObject() override;
        const Weapon* GetObject() const override;

      protected:
        WeaponItem(const WeaponItem&);

        WeaponModel* Model() const override;

      private:
        static class Initialize {
          public:
            Initialize() { GDW_RPG_Weapon_Initialize(); }
        } Initializer;
    };
  };
};

#endif // WEAPONITEM_HH
