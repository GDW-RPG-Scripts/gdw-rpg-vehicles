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

#include <QModelIndex>
#include <QUndoCommand>

namespace GDW
{
  namespace RPG
  {
    class Object;
    class ObjectForm;
    class ObjectModel;
    class ObjectItem;

    class InsertItemCommand : public QUndoCommand
    {
      public:
        InsertItemCommand(const QModelIndex&, ObjectModel*,
                          QUndoCommand* parent = nullptr);

        void undo() override;
        void redo() override;

      private:
        int mRow;
        bool mInserted;
        QModelIndex mParent;
        ObjectModel* mModel;
    };

    class RemoveItemCommand : public QUndoCommand
    {
      public:
        RemoveItemCommand(const QModelIndex&,
                          QUndoCommand* parent = nullptr);

        void undo() override;
        void redo() override;

      private:
        int mRow;
        ObjectItem* mParent;
        ObjectModel* mModel;
        ObjectItem* mRemovedItem;
    };

    class UpdateItemCommand : public QUndoCommand
    {
      public:
        UpdateItemCommand(ObjectForm*, QUndoCommand* parent = nullptr);
        ~UpdateItemCommand();

        void undo() override;
        void redo() override;

      private:
        Object* mObject;
        ObjectForm* mObjectForm;
    };

    class AddChildItemCommand : public QUndoCommand
    {
      public:
        AddChildItemCommand(ObjectItem*, ObjectItem*,
                            QUndoCommand* parent = nullptr);

        void undo() override;
        void redo() override;

      private:
        ObjectItem* mParentItem;
        ObjectItem* mChildItem;
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
