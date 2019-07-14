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

void
GDW_RPG_Vehicle_Initialize()
{
  Q_INIT_RESOURCE(vehicle);
}

using namespace GDW::RPG;

VehicleItem::Initialize VehicleItem::Initializer;

VehicleItem*
VehicleItem::Create(ObjectItem* parent)
{
  return new VehicleItem(Vehicle::New(), parent);
}

VehicleItem*
VehicleItem::Unpack(const QJsonObject& json, ObjectItem* parent)
{
  Vehicle* vehicle = new Vehicle(json);
  VehicleItem* vti = new VehicleItem(vehicle, parent);

  QList<Weapon*> list;// = vehicle->Weapons();
  const QString PROP_WEAPONS = "weap";
  if(json.contains(PROP_WEAPONS)) {
    list = Weapon::Load(json[PROP_WEAPONS], vehicle);
  }

  for(Weapon* weapon: list) {
    VehicleModel::Model()->InsertChild(new WeaponItem(weapon, vti), vti);
  }

  return vti;
}

VehicleItem::VehicleItem(Vehicle* vehicle, ObjectItem* parent)
  : ObjectItem(vehicle, parent)
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
VehicleItem::GetForm(QUndoStack* undoStack)
{
  return new VehicleForm(GetObject(), undoStack);
}

Vehicle*
VehicleItem::GetObject()
{
  return static_cast<Vehicle*>(ObjectItem::GetObject());
}

const Vehicle*
VehicleItem::GetObject() const
{
  return static_cast<const Vehicle*>(ObjectItem::GetObject());
}

VehicleModel*
VehicleItem::Model() const
{
  return VehicleModel::Model();
}

QByteArray
VehicleItem::Template() const
{
  QFile file(":/vehicle.svg");

  if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
    return "";

  return file.readAll();
}
