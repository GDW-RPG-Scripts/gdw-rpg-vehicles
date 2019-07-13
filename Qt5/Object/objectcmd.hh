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

#ifndef OBJECTCMD_HH
#define OBJECTCMD_HH

#include <QUndoCommand>

namespace GDW
{
  namespace RPG
  {
    class ObjectForm;
    class ObjectTreeItem;

    class AddChildItemCommand : public QUndoCommand
    {
      public:
        AddChildItemCommand(ObjectTreeItem*, ObjectTreeItem*,
                            QUndoCommand* parent = nullptr);

        void undo() override;
        void redo() override;

      private:
        ObjectTreeItem* mParentItem;
        ObjectTreeItem* mChildItem;
    };

    class ClearImageCommand : public QUndoCommand
    {
      public:
        ClearImageCommand(ObjectForm*, QUndoCommand* parent = nullptr);

        void undo() override;
        void redo() override;

      private:
        ObjectForm* mObjectForm;
    };

    class SetImageCommand : public QUndoCommand
    {
      public:
        SetImageCommand(ObjectForm*, QUndoCommand* parent = nullptr);

        void undo() override;
        void redo() override;

      private:
        ObjectForm* mObjectForm;
    };
  };
};

#endif // OBJECTCMD_HH
