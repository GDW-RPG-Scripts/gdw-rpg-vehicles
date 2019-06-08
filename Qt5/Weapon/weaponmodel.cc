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

#include "weaponmodel.hh"
#include "weaponitem.hh"

using namespace GDW::RPG;

WeaponModel*
WeaponModel::Model()
{
  static WeaponModel MODEL;
  return &MODEL;
}

WeaponModel::WeaponModel(QObject* parent)
  : ObjectModel(parent)
{}

const QList<QVariant>&
WeaponModel::RootData() const
{
  static const QList<QVariant> rootData =
  {
    tr("Munition type")
  };
  return rootData;
}

bool
WeaponModel::InsertObject(int position)
{
  return InsertChild(WeaponTreeItem::Create(), RootItem(), position);
}

ObjectTreeItem*
WeaponModel::InsertObject(ObjectTreeItem* parent) const
{
  return WeaponTreeItem::Create(parent);
}

ObjectTreeItem*
WeaponModel::Unpack(const QJsonObject& json, ObjectTreeItem* parent)
{
  if(parent == nullptr)
    parent = RootItem();

  WeaponTreeItem* item = WeaponTreeItem::Unpack(json, parent);
  InsertChild(item, parent);

  return item;
}
