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

UnitTreeItem::Initialize UnitTreeItem::Initializer;

UnitTreeItem*
UnitTreeItem::Create(ObjectTreeItem* parent)
{
  return new UnitTreeItem(Unit::New(), parent);
}

UnitTreeItem*
UnitTreeItem::Unpack(const QJsonObject& json, ObjectTreeItem* parent)
{
  Unit* unit = new Unit(json);
  UnitTreeItem* item = new UnitTreeItem(unit, parent);

  return item;
}

UnitTreeItem::UnitTreeItem(Unit* unit, ObjectTreeItem* parent)
  : ObjectTreeItem(unit,
                   parent == nullptr ? UnitModel::Model()->RootItem()
                                     : parent)
{
  if(parent == nullptr)
    parent = Model()->RootItem();

  parent->InsertChild(this);
}

UnitForm*
UnitTreeItem::GetForm(QUndoStack* undoStack)
{
  return new UnitForm(GetObject(), undoStack);
}

Unit*
UnitTreeItem::GetObject()
{
  return static_cast<Unit*>(ObjectTreeItem::GetObject());
}

const Unit*
UnitTreeItem::GetObject() const
{
  return static_cast<const Unit*>(ObjectTreeItem::GetObject());
}

UnitModel*
UnitTreeItem::Model() const
{
  return UnitModel::Model();
}
