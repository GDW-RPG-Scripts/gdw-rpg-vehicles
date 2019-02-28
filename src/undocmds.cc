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

#include "undocmds.hh"

#include <QDebug>

namespace GDW
{
  namespace RPG
  {
    /*
 * Undo Commit Object
 */
    UndoCommitObject::UndoCommitObject()
    {
      //  mUi->objectForm->GetObject()->Copy();
      //  QModelIndex index = mUi->vehiclesTreeView->currentIndex();
      //  ObjectTreeItem* item =
      //      static_cast<ObjectTreeItem*>(index.internalPointer());
      //  item->Copy();
    }

    void
    UndoCommitObject::undo()
    {
      qDebug() << "UndoCommitObject::undo()";
    }

    void
    UndoCommitObject::redo()
    {
      qDebug() << "UndoCommitObject::redo()";
    }

    /*
 * Undo Commit Object
 */
    UndoRemoveObject::UndoRemoveObject(const QModelIndex& index, QAbstractItemModel* model)
      : mIndex(index), mModel(model)
    {}

    void
    UndoRemoveObject::undo()
    {
      qDebug() << "UndoRemoveObject::undo()";
      mModel->insertRow(mIndex.row(), mIndex.parent());
    }

    void
    UndoRemoveObject::redo()
    {
      qDebug() << "UndoRemoveObject::redo()";
      mModel->removeRow(mIndex.row(), mIndex.parent());
    }
  };
};
