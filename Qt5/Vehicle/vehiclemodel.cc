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

#include "vehiclemodel.hh"
#include "vehicleitem.hh"

using namespace GDW::RPG;

VehicleModel VehicleModel::MODEL;

VehicleModel*
VehicleModel::Model()
{
  return &MODEL;
}

VehicleModel::VehicleModel(QObject* parent)
  : ObjectModel(parent)
{}

const QList<QVariant>&
VehicleModel::RootData() const
{
  static const QList<QVariant> rootData =
  {
    tr("Name"),
    tr("Type"),
    tr("Nationality")
  };
  return rootData;
}

ObjectTreeItem*
VehicleModel::Create(ObjectTreeItem* parent) const
{
  return VehicleTreeItem::Create(parent);
}

ObjectTreeItem*
VehicleModel::Unpack(const QJsonObject& json, ObjectTreeItem* parent)
{
  if(parent == nullptr)
    parent = RootItem();

  VehicleTreeItem* item = VehicleTreeItem::Unpack(json, parent);

//  QModelIndex index = createIndex(rowCount(), 0, item);
//  if(insertRow(rowCount())) // && setData(index, QVariant::fromValue(item)))
//  {
//    dataChanged(createIndex(0,0), index);
//    return item;
//  }

  return parent->AppendChild(item);
}
