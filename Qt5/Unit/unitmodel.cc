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

#include "objectcmd.hh"

#include <QMenu>

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

ObjectItem*
UnitModel::InsertObject(ObjectItem* parent) const
{
  return UnitItem::Create(parent);
}

void
UnitModel::AddItemActions(QMenu& menu, QUndoStack& undoStack,
                         const QModelIndex& index)
{
  menu.addAction(QIcon("://icons/16x16/list-add.png"),
                 tr("Add Unit Child..."), this,
                 [&, this]() { ; });
}

void
UnitModel::AddViewActions(QMenu& menu, QUndoStack& undoStack,
                         const QModelIndex& index)
{
  menu.addAction(QIcon("://icons/16x16/list-add.png"),
                 tr("Insert New Unit..."), this,
                 [&, this]() {
    undoStack.push(new InsertItemCommand(index, this));
  });
}

ObjectItem*
UnitModel::Unpack(const QJsonObject& json, ObjectItem* parent)
{
  UnitItem* item = UnitItem::Unpack(json, parent);
  return item;
}
