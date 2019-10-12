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

#include "weaponitem.hh"
#include "weaponform.hh"
#include "weapon.hh"

// #include "ui_mainwindow.h"

#include <QDebug>
#include <QGroupBox>
#include <QJsonArray>
#include <QJsonDocument>
#include <QStackedWidget>
#include <QVBoxLayout>

void
GDW_RPG_Weapon_Initialize()
{
  Q_INIT_RESOURCE(weapon);
}

using namespace GDW::RPG;

WeaponItem::Initialize WeaponItem::Initializer;

WeaponItem*
WeaponItem::Create(ObjectItem* parent)
{
  return new WeaponItem(Weapon::New(), parent);
}

WeaponItem*
WeaponItem::Unpack(const QJsonObject& json, ObjectItem* parent)
{
  Weapon* weapon = new Weapon(json);
  return new WeaponItem(weapon, parent);
}

WeaponItem::WeaponItem(Weapon* weapon, ObjectItem* parent)
  : ObjectItem(weapon, parent)
{}

WeaponItem::WeaponItem(const WeaponItem& item)
  : ObjectItem(item)
{}

WeaponItem::~WeaponItem()
{}

WeaponItem*
WeaponItem::Copy() const
{
  return new WeaponItem(*this);
}

WeaponForm*
WeaponItem::GetForm(QUndoStack* undoStack)
{
  return new WeaponForm(GetObjectPtr(), undoStack);
}

//    void
//    WeaponTreeItem::Select(Ui::Workspace& ui, ObjectForm*)
//    {
//      ObjectTreeItem::Select(ui, new WeaponForm(GetObject()));
//    }

Weapon*
WeaponItem::GetObjectPtr()
{
  return static_cast<Weapon*>(ObjectItem::GetObjectPtr());
}

const Weapon*
WeaponItem::GetObjectPtr() const
{
  return static_cast<const Weapon*>(ObjectItem::GetObjectPtr());
}

WeaponModel*
WeaponItem::Model() const
{
  return WeaponModel::Model();
}
