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

WeaponTreeItem::Initialize WeaponTreeItem::Initializer;

WeaponTreeItem*
WeaponTreeItem::Create(ObjectTreeItem* parent)
{
  return new WeaponTreeItem(Weapon::New(), parent);
}

WeaponTreeItem*
WeaponTreeItem::Unpack(const QJsonObject& json, ObjectTreeItem* parent)
{
  Weapon* weapon = new Weapon(json);
  return new WeaponTreeItem(weapon, parent);
}

WeaponTreeItem::WeaponTreeItem(Weapon* weapon, ObjectTreeItem* parent)
  : ObjectTreeItem(weapon, parent)
{}

WeaponTreeItem::WeaponTreeItem(const WeaponTreeItem& item)
  : ObjectTreeItem(item)
{}

WeaponTreeItem::~WeaponTreeItem()
{}

WeaponTreeItem*
WeaponTreeItem::Copy() const
{
  return new WeaponTreeItem(*this);
}

WeaponForm*
WeaponTreeItem::GetForm(QUndoStack* undoStack)
{
  return new WeaponForm(GetObject(), undoStack);
}

//    void
//    WeaponTreeItem::Select(Ui::Workspace& ui, ObjectForm*)
//    {
//      ObjectTreeItem::Select(ui, new WeaponForm(GetObject()));
//    }

Weapon*
WeaponTreeItem::GetObject()
{
  return static_cast<Weapon*>(ObjectTreeItem::GetObject());
}

const Weapon*
WeaponTreeItem::GetObject() const
{
  return static_cast<const Weapon*>(ObjectTreeItem::GetObject());
}

WeaponModel*
WeaponTreeItem::Model() const
{
  return WeaponModel::Model();
}
