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

#ifndef MAINWINDOW_HH
#define MAINWINDOW_HH

#include "factory.hh"

#include "ui_workspace.h"


#include <QMainWindow>
#include <QUndoStack>

class QAction;
class QMenu;
class QPlainTextEdit;
class QSessionManager;
class QTreeView;
class QUndoCommand;

namespace Ui {
  class Workspace;
  class VehicleForm;
  class WeaponForm;
}

namespace GDW
{
  namespace RPG
  {
    class VehicleModel;

    class Workspace : public QMainWindow
    {
        Q_OBJECT

      public:
        explicit Workspace(QWidget* parent = nullptr);
        ~Workspace() override;

        void LoadFile(const QString& fileName);

      public slots:
        void LoadOnStart(int);
        void RuleSet(int);
        void UpdateActions();

      protected:
        void closeEvent(QCloseEvent* event) override;

      private slots:
        void New();
        void Open();
        void Prefs();
        bool Save();
        bool SaveAs();
        void Redo();
        void Undo();
        void About();
        void DocumentWasModified();
#ifndef QT_NO_SESSIONMANAGER
        void CommitData(QSessionManager&);
#endif

        void InsertItem();
        void CurrentType(int);
        void EditItem();
        void ItemClicked(const QModelIndex&);
        void PrintItem();
        void RemoveSelectedItems();
        void SaveItem();

        void AddWeapon();
        void ShowVehiclesMenu(const QPoint&);
        void ShowWeaponsMenu(const QPoint&);

      private:
        void ReadSettings();
        void WriteSettings();
        bool IsModified();
        bool MaybeSave();
        bool SaveFile(const QString& fileName);
        const QString& CurrentFile() const;
        void CurrentFile(const QString& fileName);
        //QAbstractItemModel* Model();
        QTreeView& GetCurrentTreeView();
        void ResizeViewColumns();

        void ClearObjectGroupBox();
        void Select(ObjectForm*);
        void Unselect();

        int mRuleSet;
        bool mLoadOnStart;

        Factory mFactory;

        QString mCurrentFile;
        QUndoStack mUndoStack;
        Ui::Workspace mUi;

        // QPlainTextEdit* textEdit;
    };
  };
};
#endif // MAINWINDOW_HH
