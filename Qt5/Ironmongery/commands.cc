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

#include "commands.hh"

#include "vehiclemodel.hh"
#include "objectform.hh"
#include "objectitem.hh"

#include <QObject>
#include <QDebug>

using namespace GDW::RPG;

//
// Add Item Command
//
AddChildItemCommand::AddChildItemCommand(ObjectTreeItem* parentItem,
                                         ObjectTreeItem* childItem,
                                         QUndoCommand* parent)
  : QUndoCommand(parent),
    mParentItem(parentItem), mChildItem(childItem->Copy())
{
  setText(QObject::tr("child add"));
}

void
AddChildItemCommand::undo()
{
  qDebug() << "AddItemCommand::undo()";

  mParentItem->Model()->RemoveChild(mParentItem, mChildItem->Row());
}

void
AddChildItemCommand::redo()
{
  qDebug() << "AddItemCommand::redo()";

  mParentItem->Model()->InsertChild(mChildItem, mParentItem);
}

//
// Insert Item Command
//
InsertItemCommand::InsertItemCommand(const QModelIndex& index,
                                     ObjectModel* model,
                                     QUndoCommand* parent)
  : QUndoCommand(parent),
    mRow(index.row()+1),
    mInserted(false),
    mParent(index.parent()),
    mModel(model)
{
  setText(QObject::tr("insert"));
}

void
InsertItemCommand::undo()
{
  qDebug() << "InsertItemCommand::undo()";

  if(mInserted)
    mModel->RemoveObject(mRow);
}

void
InsertItemCommand::redo()
{
  qDebug() << "InsertItemCommand::redo()";

  mInserted = mModel->InsertObject(mRow);
}

//
// Remove Item Command
//
RemoveItemCommand::RemoveItemCommand(const QModelIndex& index,
                                     QUndoCommand* parent)
  : QUndoCommand(parent),
    mRow(index.row()),
    mParent(static_cast<ObjectTreeItem*>(index.parent().internalPointer())),
    mRemovedItem(nullptr)
{
  setText(QObject::tr("remove"));

  const ObjectModel* model =
      static_cast<const ObjectModel*>(index.model());

  if(model)
    mModel = const_cast<ObjectModel*>(model); // Kludge
}

void
RemoveItemCommand::undo()
{
  qDebug() << "RemoveItemCommand::undo()";

  if(mRemovedItem)
    mModel->InsertChild(mRemovedItem, mParent, mRow);
}

void
RemoveItemCommand::redo()
{
  qDebug() << "RemoveItemCommand::redo()";

  mRemovedItem =
      mModel->RemoveChild(mParent, mRow);
}


//
// Update Item Command
//
UpdateItemCommand::UpdateItemCommand(ObjectForm* form, QUndoCommand* parent)
  : QUndoCommand(parent), mObject(nullptr), mObjectForm(form)
{
  setText(QObject::tr("update"));
}

UpdateItemCommand::~UpdateItemCommand()
{
  qDebug() << "UpdateItemCommand::~UpdateItemCommand()";

  //  if(mObject)
  //    delete mObject;
}

void
UpdateItemCommand::undo()
{
  qDebug() << "UpdateItemCommand::undo()";

  mObject = mObjectForm->Read(Mode::Display, mObject);
}

void
UpdateItemCommand::redo()
{
  qDebug() << "UpdateItemCommand::redo()";

  if(mObject) {
    mObject = mObjectForm->Read(Mode::Display, mObject);
  } else {
    mObject = mObjectForm->Write();
  }
}
