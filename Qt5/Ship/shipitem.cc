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

void
GDW_RPG_Ship_Initialize()
{
  // Q_INIT_RESOURCE(ship);
}

using namespace GDW::RPG;

ShipItem::Initialize ShipItem::Initializer;

ShipItem*
ShipItem::Create(ObjectItem* parent)
{
  return new ShipItem(Ship::New(), parent);
}

ShipItem*
ShipItem::Unpack(const QJsonObject& json, ObjectItem* parent)
{
  Ship* unit = new Ship(json);
  ShipItem* item = new ShipItem(unit, parent);

  return item;
}

ShipItem::ShipItem(Ship* ship, ObjectItem* parent)
  : ObjectItem(ship,
                   parent == nullptr ? ShipModel::Model()->RootItem()
                                     : parent)
{
  if(parent == nullptr)
    parent = Model()->RootItem();

  parent->InsertChild(this);
}

ShipForm*
ShipItem::GetForm(QUndoStack* undoStack)
{
  return new ShipForm(GetObjectPtr(), undoStack);
}

Ship*
ShipItem::GetObjectPtr()
{
  return static_cast<Ship*>(ObjectItem::GetObjectPtr());
}

const Ship*
ShipItem::GetObjectPtr() const
{
  return static_cast<const Ship*>(ObjectItem::GetObjectPtr());
}

ShipModel*
ShipItem::Model() const
{
  return ShipModel::Model();
}
