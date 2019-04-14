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

#ifndef SHIPTITEM_HH
#define SHIPTITEM_HH

#include "ship_global.hh"

#include "objectitem.hh"

#include "ship.hh"
#include "shipform.hh"
#include "shipmodel.hh"

namespace GDW
{
  namespace RPG
  {
    class SHIPSHARED_EXPORT ShipTreeItem : public ObjectTreeItem
    {
      public:
        static ShipTreeItem* Create(ObjectTreeItem* parent = nullptr);
        static ShipTreeItem* Unpack(const QJsonObject&,
                                    ObjectTreeItem* parent);

        ShipForm* GetForm() override;

        ShipTreeItem();

      protected:
        explicit ShipTreeItem(Ship*, ObjectTreeItem* parent = nullptr);

        Ship* GetObject() override;
        const Ship* GetObject() const override;

        ShipModel* Model() const override;
    };
  };
};

#endif // SHIPTITEM_HH
