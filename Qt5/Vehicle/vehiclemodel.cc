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

#include "objectcmd.hh"
#include "weaponitem.hh"
#include "weapondialog.hh"

#include <QMenu>

class QUndoStack;

using namespace GDW::RPG;

VehicleModel*
VehicleModel::Model()
{
  static VehicleModel MODEL;
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

bool
VehicleModel::InsertObject(int position)
{
  return InsertChild(VehicleItem::Create(), RootItem(), position);
}

ObjectItem*
VehicleModel::InsertObject(ObjectItem* parent) const
{
  return VehicleItem::Create(parent);
}

void
VehicleModel::AddWeapon(QUndoStack& undoStack, const QModelIndex& index)
{
  VehicleItem* vti =
      static_cast<VehicleItem*>(index.internalPointer());

  WeaponDialog dialog;

  if(dialog.exec() != QDialog::Accepted) {
    return;
  }

  QModelIndex weaponIndex = dialog.Selected();
  if(weaponIndex.isValid()) {
    WeaponItem* wti =
        static_cast<WeaponItem*>(weaponIndex.internalPointer());

    undoStack.push(new AddChildItemCommand(vti, wti));
  }
}

void
VehicleModel::AddItemActions(QMenu& menu, QUndoStack& undoStack,
                         const QModelIndex& index)
{
  menu.addAction(QIcon("://icons/16x16/list-add.png"),
                 tr("Add Vehicle Weapon..."), this,
                 [&, this]() {
    AddWeapon(undoStack, index);
  });
}

void
VehicleModel::AddViewActions(QMenu& menu, QUndoStack& undoStack,
                         const QModelIndex& index)
{
  menu.addAction(QIcon("://icons/16x16/list-add.png"),
                 tr("Insert New Vehicle..."), this,
                 [&, this]() {
    undoStack.push(new InsertItemCommand(index, this));
  });
}

ObjectItem*
VehicleModel::Unpack(const QJsonObject& json, ObjectItem* parent)
{
  if(parent == nullptr)
    parent = RootItem();

  //  int row = rowCount();
  //  QModelIndex index = createIndex(parent->Row(), 0, parent);
  //  beginInsertRows(index, row, row);
  VehicleItem* item = VehicleItem::Unpack(json, parent);
  InsertChild(item, parent);
  //  endInsertRows();

  return item;
}
