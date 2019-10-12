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

#include "munitionitem.hh"

#include "munition.hh"
#include "munitionform.hh"
#include "weaponform.hh"
#include "weaponitem.hh"

using namespace GDW::RPG;

MunitionItem*
MunitionItem::Create(ObjectItem* parent)
{
  return new MunitionItem(Munition::New(parent->GetObjectPtr()), parent);
}

MunitionItem::MunitionItem(Munition* munition, ObjectItem* parent)
  : ObjectItem(munition, parent)
{}

MunitionItem::MunitionItem(const MunitionItem& item)
  : ObjectItem(item)
{}

MunitionItem::~MunitionItem()
{}

MunitionItem*
MunitionItem::Copy() const
{
  return new MunitionItem(*this);
}

ObjectForm*
MunitionItem::GetForm(QUndoStack* undoStack)
{
  WeaponItem* weapon =
      static_cast<WeaponItem*>(parent());
  WeaponForm* weaponForm = weapon->GetForm(undoStack);
  weaponForm->SetMunitionForm(new MunitionForm(GetObjectPtr()));
  return weaponForm;
}

Munition*
MunitionItem::GetObjectPtr()
{
  return static_cast<Munition*>(ObjectItem::GetObjectPtr());
}

const Munition*
MunitionItem::GetObjectPtr() const
{
  return static_cast<const Munition*>(ObjectItem::GetObjectPtr());
}
