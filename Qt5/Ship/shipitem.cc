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

#include "shipitem.hh"
#include "ship.hh"

namespace GDW
{
  namespace RPG
  {
    ShipModel ShipTreeItem::MODEL;

    ShipModel*
    ShipTreeItem::Model()
    {
      return &MODEL;
    }

    ShipTreeItem*
    ShipTreeItem::Create(ObjectTreeItem* parent)
    {
      return new ShipTreeItem(Ship::New(), parent);
    }

    ShipTreeItem*
    ShipTreeItem::Unpack(const QJsonObject& json, ObjectTreeItem* parent)
    {
      Ship* unit = new Ship(json);
      ShipTreeItem* item = new ShipTreeItem(unit, parent);

      return item;
    }

    ShipTreeItem::ShipTreeItem(Ship* ship, ObjectTreeItem* parent)
      : ObjectTreeItem(ship, parent == nullptr ? MODEL.RootItem() : parent)
    {
      if(parent == nullptr)
        MODEL.RootItem()->AppendChild(this);
    }

    ShipForm*
    ShipTreeItem::GetForm()
    {
      return new ShipForm(GetObject());
    }

    Ship*
    ShipTreeItem::GetObject()
    {
      return static_cast<Ship*>(ObjectTreeItem::GetObject());
    }

    const Ship*
    ShipTreeItem::GetObject() const
    {
      return static_cast<const Ship*>(ObjectTreeItem::GetObject());
    }
  };
};
