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

#ifndef MUNITIONITEM_HH
#define MUNITIONITEM_HH

#include "weapon_global.hh"

#include "munition.hh"
#include "objectitem.hh"

namespace GDW
{
  namespace RPG
  {
    class Munition;

    class WEAPONSHARED_EXPORT MunitionItem : public ObjectItem
    {
        Q_OBJECT

      public:
        static MunitionItem* Create(ObjectItem* parent = nullptr);

        MunitionItem(Munition*, ObjectItem*);
        ~MunitionItem() override;

        MunitionItem* Copy() const override;

        ObjectForm* GetForm(QUndoStack*) override;

        Munition* GetObject() override;
        const Munition* GetObject() const override;

      protected:
        MunitionItem(const MunitionItem&);
    };
  };
};

#endif // MUNITIONITEM_HH
