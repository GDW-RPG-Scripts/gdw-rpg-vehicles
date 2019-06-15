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

#include "objectcmd.hh"
#include "objectform.hh"

#include <QDebug>

using namespace GDW::RPG;

//
// Clear Image Command
//
ClearImageCommand::ClearImageCommand(ObjectForm* form, QUndoCommand* parent)
  : QUndoCommand(parent), mObjectForm(form)
{
  setText(QObject::tr("clear image"));
}

void
ClearImageCommand::undo()
{
  qDebug() << "ClearImageCommand::undo()";

  mObjectForm->Read();
}

void
ClearImageCommand::redo()
{
  qDebug() << "ClearImageCommand::redo()";

  mObjectForm->Read();
}

//
// Set Image Command
//
SetImageCommand::SetImageCommand(ObjectForm* form, QUndoCommand* parent)
  : QUndoCommand(parent), mObjectForm(form)
{
  setText(QObject::tr("set image"));
}

void
SetImageCommand::undo()
{
  qDebug() << "SetImageCommand::undo()";

  mObjectForm->Read();
}

void
SetImageCommand::redo()
{
  qDebug() << "SetImageCommand::redo()";

  mObjectForm->Read();
}
