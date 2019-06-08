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

#include "vehicleitem.hh"
#include "vehicleform.hh"
#include "weaponitem.hh"

#include "vehicle.hh"
#include "weapon.hh"

#include <QDebug>
#include <QGroupBox>
#include <QJsonArray>
#include <QJsonDocument>
#include <QStackedWidget>
#include <QVBoxLayout>

using namespace GDW::RPG;

class QPaintDevice;

VehicleTreeItem*
VehicleTreeItem::Create(ObjectTreeItem* parent)
{
  return new VehicleTreeItem(Vehicle::New(), parent);
}

VehicleTreeItem*
VehicleTreeItem::Unpack(const QJsonObject& json, ObjectTreeItem* parent)
{
  Vehicle* vehicle = new Vehicle(json);
  VehicleTreeItem* vti = new VehicleTreeItem(vehicle, parent);

  QList<Weapon*> list = vehicle->Weapons();
  for(Weapon* weapon: list) {
    VehicleModel::Model()->InsertChild(new WeaponTreeItem(weapon, vti), vti);
  }

  return vti;
}

VehicleTreeItem::VehicleTreeItem(Vehicle* vehicle, ObjectTreeItem* parent)
  : ObjectTreeItem(vehicle, parent)
{}

//bool
//VehicleTreeItem::InsertChild(ObjectTreeItem* item, int position)
//{
//  if(!item)
//    return false;

//  Weapon* weapon =
//      qobject_cast<Weapon*>(item->GetObject());

//  if(!weapon)
//    return false;

//  ObjectTreeItem::InsertChild(item, position);
//  GetObject()->AddWeapon(weapon);

//  return true;
//}

VehicleForm*
VehicleTreeItem::GetForm()
{
  return new VehicleForm(GetObject());
}

Vehicle*
VehicleTreeItem::GetObject()
{
  return static_cast<Vehicle*>(ObjectTreeItem::GetObject());
}

const Vehicle*
VehicleTreeItem::GetObject() const
{
  return static_cast<const Vehicle*>(ObjectTreeItem::GetObject());
}

VehicleModel*
VehicleTreeItem::Model() const
{
  return VehicleModel::Model();
}

QByteArray
VehicleTreeItem::Template() const
{
  QFile file(":/vehicle.svg");

  if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
    return "";

  return file.readAll();
}
