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
#include "weaponitem.hh"
#include "weapondialog.hh"
#include "objectcmd.hh"

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
  return InsertChild(VehicleTreeItem::Create(), RootItem(), position);
}

ObjectTreeItem*
VehicleModel::InsertObject(ObjectTreeItem* parent) const
{
  return VehicleTreeItem::Create(parent);
}

void
VehicleModel::AddWeapon(QUndoStack& undoStack, const QModelIndex& index)
{
  VehicleTreeItem* vti =
      static_cast<VehicleTreeItem*>(index.internalPointer());

  WeaponDialog dialog;

  if(dialog.exec() != QDialog::Accepted) {
    return;
  }

  QModelIndex weaponIndex = dialog.Selected();
  if(weaponIndex.isValid()) {
    WeaponTreeItem* wti =
        static_cast<WeaponTreeItem*>(weaponIndex.internalPointer());

    undoStack.push(new AddChildItemCommand(vti, wti));
  }
}

void
VehicleModel::AddActions(QMenu& menu, QUndoStack& undoStack,
                         const QModelIndex& index)
{
  QAction* action_AddWeapon = new QAction(tr("Add weapon..."));

  connect(action_AddWeapon, &QAction::triggered, this,
          [&, this]() { this->AddWeapon(undoStack, index); });

  menu.addAction(action_AddWeapon);
}

ObjectTreeItem*
VehicleModel::Unpack(const QJsonObject& json, ObjectTreeItem* parent)
{
  if(parent == nullptr)
    parent = RootItem();

  //  int row = rowCount();
  //  QModelIndex index = createIndex(parent->Row(), 0, parent);
  //  beginInsertRows(index, row, row);
  VehicleTreeItem* item = VehicleTreeItem::Unpack(json, parent);
  InsertChild(item, parent);
  //  endInsertRows();

  return item;
}
