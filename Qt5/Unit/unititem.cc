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

#include "unititem.hh"

void
GDW_RPG_Unit_Initialize()
{
  // Q_INIT_RESOURCE(unit);
}

using namespace GDW::RPG;

UnitItem::Initialize UnitItem::Initializer;

UnitItem*
UnitItem::Create(ObjectItem* parent)
{
  return new UnitItem(Unit::New(), parent);
}

UnitItem*
UnitItem::Unpack(const QJsonObject& json, ObjectItem* parent)
{
  Unit* unit = new Unit(json);
  UnitItem* item = new UnitItem(unit, parent);

  return item;
}

UnitItem::UnitItem(Unit* unit, ObjectItem* parent)
  : ObjectItem(unit,
                   parent == nullptr ? UnitModel::Model()->RootItem()
                                     : parent)
{
  if(parent == nullptr)
    parent = Model()->RootItem();

  parent->InsertChild(this);
}

UnitForm*
UnitItem::GetForm(QUndoStack* undoStack)
{
  return new UnitForm(GetObject(), undoStack);
}

Unit*
UnitItem::GetObject()
{
  return static_cast<Unit*>(ObjectItem::GetObject());
}

const Unit*
UnitItem::GetObject() const
{
  return static_cast<const Unit*>(ObjectItem::GetObject());
}

UnitModel*
UnitItem::Model() const
{
  return UnitModel::Model();
}
