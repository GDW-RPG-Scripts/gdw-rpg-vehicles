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

#include "unitmodel.hh"
#include "unititem.hh"

using namespace GDW::RPG;

UnitModel UnitModel::MODEL;

UnitModel*
UnitModel::Model()
{
  return &MODEL;
}

UnitModel::UnitModel(QObject* parent)
  : ObjectModel(parent)
{}

const QList<QVariant>&
UnitModel::RootData() const
{
  static QList<QVariant> rootData =
  {
    tr("Name")
  };
  return rootData;
}

ObjectTreeItem*
UnitModel::Create(ObjectTreeItem* parent) const
{
  return UnitTreeItem::Create(parent);
}

ObjectTreeItem*
UnitModel::Unpack(const QJsonObject& json, ObjectTreeItem* parent)
{
  UnitTreeItem* item = UnitTreeItem::Unpack(json, parent);
  return item;
}
