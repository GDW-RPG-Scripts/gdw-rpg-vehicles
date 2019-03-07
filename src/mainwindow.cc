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

#include <QtWidgets>
#if defined(QT_PRINTSUPPORT_LIB)
#include <QtPrintSupport/qtprintsupportglobal.h>
#if QT_CONFIG(printer)
#if QT_CONFIG(printdialog)
#include <QPrintDialog>
#endif // QT_CONFIG(printdialog)
#include <QPrinter>
#endif // QT_CONFIG(printer)
#endif // QT_PRINTSUPPORT_LIB

#include "model.hh"
#include "mainwindow.hh"
#include "prefsdialog.hh"
#include "treeitem.hh"
#include "commands.hh"

#include "ui_mainwindow.h"
#include "ui_vehicleform.h"
#include "ui_weaponform.h"


namespace GDW
{
  namespace RPG
  {
    const QString MainWindow::APP_NAME = tr("GDW RPG Vehicles");

    MainWindow::MainWindow(QWidget* parent) :
      QMainWindow(parent),
      mRuleSet(0),
      mLoadOnStart(true),
      mModel(new TreeModel),
      mUi(new Ui::MainWindow)
    {
      ReadSettings();

#ifndef QT_NO_SESSIONMANAGER
      QGuiApplication::setFallbackSessionManagementEnabled(false);
      connect(qApp, &QGuiApplication::commitDataRequest,
              this, &MainWindow::CommitData);
#endif

      mUi->setupUi(this);

      QList<QAction*> actions =
      {
        mUndoStack.createUndoAction(this, tr("&Undo")),
        mUndoStack.createRedoAction(this, tr("&Redo"))
      };
      actions[0]->setShortcuts(QKeySequence::Undo);
      actions[1]->setShortcuts(QKeySequence::Redo);
      mUi->menuEdit->insertActions(mUi->action_Placeholder, actions);
      mUi->menuEdit->removeAction(mUi->action_Placeholder);

      SetCurrentFile(QString());
      setUnifiedTitleAndToolBarOnMac(true);

      // Disable menu actions for unavailable features
#if !QT_CONFIG(printer)
      mUi->action_Print->setEnabled(false);
#endif

#if !QT_CONFIG(clipboard)
      mUi->action_Cut->setEnabled(false);
      mUi->action_Copy->setEnabled(false);
      mUi->action_Paste->setEnabled(false);
#endif

      connect(mModel, &QAbstractItemModel::rowsRemoved, this, &MainWindow::RemoveSelectedItems);
      connect(mUi->menuEdit, &QMenu::aboutToShow, this, &MainWindow::UpdateActions);
      // connect(mUi->insertItemButton, &QAbstractButton::clicked, this, &MainWindow::AddItem);
      // connect(mUi->action_Cut, &QAction::triggered, this, &MainWindow::RemoveItem);
      // connect(insertChildAction, &QAction::triggered, this, &MainWindow::insertChild);

      if(mLoadOnStart)
        LoadFile(":/Default.gro");

      UpdateActions();
    }

    MainWindow::~MainWindow()
    {
      delete mUi;
    }

    //
    // Events
    //

    void MainWindow::closeEvent(QCloseEvent* event)
    {
      if (MaybeSave()) {
        WriteSettings();
        event->accept();
      } else {
        event->ignore();
      }
    }

    //
    // Slots
    //
    void
    MainWindow::LoadOnStart(int state)
    {
      mLoadOnStart = state;
    }

    void
    MainWindow::RuleSet(int state)
    {
      mRuleSet = state;
    }

    void MainWindow::New()
    {
      if (MaybeSave()) {
        // textEdit->clear();
        mUndoStack.clear();
        // delete mModel;
        mUi->vehiclesTreeView->setModel(new TreeModel);
        mUi->objectForm->hide();
        SetCurrentFile(QString());
      }
    }

    void
    MainWindow::Open()
    {
      if (MaybeSave()) {
        QString fileName =
            QFileDialog::getOpenFileName(this, tr("Load Vehicles"), ".", tr("GDW RPG Object files (*.json *.grv *.gro)"));
        if (!fileName.isEmpty())
          LoadFile(fileName);
      }
    }

    void
    MainWindow::Prefs()
    {
      PrefsDialog dialog(this);
      dialog.exec();
    }

    bool
    MainWindow::Save()
    {
      if (mCurrentFile.isEmpty()) {
        return SaveAs();
      } else {
        return SaveFile(mCurrentFile);
      }
    }

    bool MainWindow::SaveAs()
    {
      QString fileName =
          QFileDialog::getSaveFileName(this, tr("Save File"),
                                       tr("Untitled"),
                                       tr("GDW RPG Object files (*.gro);; GDW RPG Vehicles files (*.grv);; JSON Files (*.json)"));

      if(fileName.isEmpty())
        return false;

      return SaveFile(fileName);

      //      QFileDialog dialog(this);
      //      dialog.setWindowModality(Qt::WindowModal);
      //      dialog.setAcceptMode(QFileDialog::AcceptSave);
      //      if (dialog.exec() != QDialog::Accepted)
      //        return false;
      //      return SaveFile(dialog.selectedFiles().first());
    }

    void
    MainWindow::About()
    {
      // qDebug() << "MainWindow::About()";
      const QString text = tr(
                             "GDW RPG Vehicles – Vehicle database and card printing software "
                             "for 2d6 Sci-fi and other RPGs.\n\n"
                             "Copyright © 2018-2019 by Michael N. Henry\n\n"
                             "This program is free software: you can redistribute it and/or "
                             "modify it under the terms of the GNU General Public License as "
                             "published by the Free Software Foundation, either version 3 of "
                             "the License, or (at your option) any later version.\n\n"
                             "Based on the original GDW RPG Vehicles QBasic software written "
                             "by Peter Kreft.\n\n"
                             "Artwork by Ian Stead and others.\n\n"
                             "The Traveller game in all forms is owned by Far Future "
                             "Enterprises. Copyright 1977 - 2008 Far Future Enterprises.");

      QMessageBox::about(this, tr("About") + " " + APP_NAME, text);
    }

    void
    MainWindow::InsertItem()
    {
      QTreeView* treeView = GetCurrentTreeView();

      if(treeView->model() == nullptr)
        treeView->setModel(mModel);

      QItemSelectionModel* itemSelectionModel = treeView->selectionModel();
      QModelIndex index = itemSelectionModel->currentIndex();

      mUndoStack.push(new InsertItemCommand(index, mModel));

      UpdateActions();

      treeView->update();

      //      for (int column = mModel->columnCount(index.parent())-1; column >= 0 ; --column) {
      //        QModelIndex child =
      //            mModel->index(index.row()+1, column, index.parent());
      //        mModel->setData(child, QVariant("[No data]"), Qt::EditRole);
      //      }
    }

    void
    MainWindow::CurrentType(int type)
    {
      mModel->CurrentType(type);
    }

    void
    MainWindow::EditItem()
    {
      if(mUi->objectForm->IsReadOnly()) {
        mUi->editItemButton->setText(tr("&Cancel"));
        mUi->  okButton->setEnabled(true);
        mUi->objectForm->SetReadOnly(false);
      } else {
        mUi->editItemButton->setText(tr("&Edit"));
        mUi->  okButton->setEnabled(false);
        mUi->objectForm->SetReadOnly(true);
        mUi->objectForm->Read();
      }
    }

    void
    MainWindow::RemoveSelectedItems()
    {
      QTreeView* view = GetCurrentTreeView();

      while(view->selectionModel()->hasSelection()) {
        QModelIndex index =
            view->selectionModel()->selectedRows().takeAt(0);

        ObjectTreeItem* oti =
            static_cast<ObjectTreeItem*>(index.internalPointer());
        oti->Unselect(mUi);

        mUndoStack.push(new RemoveItemCommand(index, mModel));
      }

      UpdateActions();
    }

    void
    MainWindow::PrintItem()
    {
      mModel->Print(this);
    }

    void
    MainWindow::Redo()
    {
      mUndoStack.redo();
    }

    void
    MainWindow::Undo()
    {
      mUndoStack.undo();
    }

    void
    MainWindow::DocumentWasModified()
    {
      setWindowModified(IsModified());
      // setWindowModified(textEdit->document()->isModified());
    }

    typedef std::function<void(ObjectTreeItem*, Ui::MainWindow*, ObjectForm*)>
    ObjectTreeSelector;

    void
    MainWindow::ItemClicked(const QModelIndex& index)
    {
      static const ObjectTreeSelector SELECTION[] =
      {
        &ObjectTreeItem::Unselect,
        &ObjectTreeItem::Select
      };

      QTreeView* view = GetCurrentTreeView();

      ObjectTreeSelector selector =
          SELECTION[view->selectionModel()->isSelected(index)];

      ObjectTreeItem* oti =
          static_cast<ObjectTreeItem*>(index.internalPointer());

      selector(oti, mUi, nullptr);
    }

    void
    MainWindow::SaveItem()
    {
      // mUndoStack.push(new InsertItemCommand());
      mUi->    objectForm->Write();
      mUi->editItemButton->setText(tr("Edit"));
      mUi->      okButton->setEnabled(false);

      QTreeView* view = GetCurrentTreeView();
      QModelIndex index = view->currentIndex();
      ObjectTreeItem* oti =
          static_cast<ObjectTreeItem*>(index.internalPointer());
      oti->RefreshItemData();
      view->selectionModel()->select(index,
                                     QItemSelectionModel::SelectCurrent |
                                     QItemSelectionModel::Rows);
      view->activateWindow();
    }

#ifndef QT_NO_SESSIONMANAGER
    void MainWindow::CommitData(QSessionManager& manager)
    {
      if (manager.allowsInteraction()) {
        if (!MaybeSave())
          manager.cancel();
      } else {
        // Non-interactive: save without asking
        // if (textEdit->document()->isModified())
        if (IsModified())
          Save();
      }
    }
#endif

    void
    MainWindow::AddWeapon()
    {
      qDebug() << "MainWindow::AddWeapon";
      QModelIndex index =
          mUi->vehiclesTreeView->selectionModel()->currentIndex();

      ObjectTreeItem* oti =
          static_cast<ObjectTreeItem*>(index.internalPointer());

      WeaponTreeItem* weaponItem = WeaponTreeItem::Create(oti);

      oti->AppendChild(weaponItem);
      mModel->
    }

    void
    MainWindow::ShowVehiclesMenu(const QPoint& position)
    {
      QAction action(tr("Add weapon"), this);
      QFontMetrics fontMetric(action.font());
      QPoint offset(0, fontMetric.height());

      connect(&action, &QAction::triggered, this, &MainWindow::AddWeapon);

      QMenu menu(this);
      menu.addAction(&action);
      menu.exec(mUi->vehiclesTreeView->mapToGlobal(position + offset));
    }

    void
    MainWindow::ShowWeaponsMenu(const QPoint& position)
    {
      qDebug() << "MainWindow::ShowWeaponsMenu(const QPoint& " << position << ")";
    }

    //
    // Methods
    //

    void
    MainWindow::ReadSettings()
    {
      QSettings settings;

      mLoadOnStart = settings.value("loadOnStart", mLoadOnStart).toBool();
      mRuleSet = settings.value("ruleset", mRuleSet).toInt();

      const QByteArray geometry = settings.value("geometry", QByteArray()).toByteArray();
      if (geometry.isEmpty()) {
        const QRect availableGeometry = QApplication::desktop()->availableGeometry(this);
        resize(availableGeometry.width() / 3, availableGeometry.height() / 2);
        move((availableGeometry.width() - width()) / 2,
             (availableGeometry.height() - height()) / 2);
      } else {
        restoreGeometry(geometry);
      }
    }

    void
    MainWindow::WriteSettings()
    {
      QSettings settings;
      settings.setValue("geometry", saveGeometry());
      settings.setValue("loadOnStart", mLoadOnStart);
      settings.setValue("ruleset", mRuleSet);
    }

    bool
    MainWindow::IsModified()
    {
      return !mUndoStack.isClean();
    }

    bool
    MainWindow::MaybeSave()
    {
      if(!IsModified())
        return true;

      // if(/* DISABLES CODE */ (true))
      //  return true;
      //  if (!textEdit->document()->isModified())
      //    return true;

      const QMessageBox::StandardButton ret
          = QMessageBox::warning(this, APP_NAME,
                                 tr("Objects have been modified.\n"
                                    "Do you want to save your changes?"),
                                 QMessageBox::Save | QMessageBox::Discard | QMessageBox::Cancel);
      switch (ret) {
        case QMessageBox::Save:
          return Save();
        case QMessageBox::Cancel:
          return false;
        default:
          break;
      }

      return true;
    }

    void
    MainWindow::LoadFile(const QString& fileName)
    {
      QFile file(fileName);
      if (!file.open(QFile::ReadOnly | QFile::Text)) {
        QString message =
            tr("Cannot read file %1:\n%2.").arg(QDir::toNativeSeparators(fileName),
                                                file.errorString());
        QMessageBox::warning(this, APP_NAME, message);
        return;
      }

#ifndef QT_NO_CURSOR
      QApplication::setOverrideCursor(Qt::WaitCursor);
#endif

      // textEdit->setPlainText(in.readAll());
      mModel->Import(file);
      mUi->vehiclesTreeView->setModel(mModel);
      for (int column = 0; column < mModel->columnCount(); ++column)
        mUi->vehiclesTreeView->resizeColumnToContents(column);
      file.close();

#ifndef QT_NO_CURSOR
      QApplication::restoreOverrideCursor();
#endif

      SetCurrentFile(fileName);
      UpdateActions();
      mUi->action_Save->setEnabled(true);
      mUi->action_SaveAs->setEnabled(true);
      statusBar()->showMessage(tr("Objects loaded"), 2000);
    }

    bool
    MainWindow::SaveFile(const QString& fileName)
    {
      QFile file(fileName);
      if (!file.open(QFile::WriteOnly | QFile::Text)) {
        QMessageBox::warning(this, APP_NAME,
                             tr("Cannot write file %1:\n%2.")
                             .arg(QDir::toNativeSeparators(fileName),
                                  file.errorString()));
        return false;
      }

      QTextStream out(&file);

#ifndef QT_NO_CURSOR
      QApplication::setOverrideCursor(Qt::WaitCursor);
#endif
      out << *mModel;
      // out << textEdit->toPlainText();
#ifndef QT_NO_CURSOR
      QApplication::restoreOverrideCursor();
#endif

      mUndoStack.setClean();
      SetCurrentFile(fileName);
      statusBar()->showMessage(tr("File saved"), 2000);
      return true;
    }

    void
    MainWindow::SetCurrentFile(const QString& fileName)
    {
      QFileInfo info(mCurrentFile = fileName);
      QString title(info.fileName());
      title += info.fileName().isEmpty() ? "" : " - ";
      setWindowTitle(title +
                     QCoreApplication::organizationName() + " " +
                     QCoreApplication::applicationName());
    }

    void
    MainWindow::UpdateActions()
    {
      QTreeView* view = GetCurrentTreeView();
      QItemSelectionModel* selectionModel = view->selectionModel();

      if(selectionModel == nullptr)
        return;

      mUi->action_Save->setEnabled(!mUndoStack.isClean());
      mUi->action_SaveAs->setEnabled(true);

      bool hasSelection = !selectionModel->selection().isEmpty();
      mUi->action_Cut->setEnabled(hasSelection);
      mUi->action_Copy->setEnabled(hasSelection);
      mUi->removeItemButton->setEnabled(hasSelection);
      if(hasSelection) {
        connect(selectionModel, &QItemSelectionModel::selectionChanged,
                this, &MainWindow::UpdateActions);
      }

      bool hasCurrent = selectionModel->currentIndex().isValid();
      mUi->insertItemButton->setEnabled(true); // hasCurrent);
      if (hasCurrent) {
        view->closePersistentEditor(selectionModel->currentIndex());
      }
    }

    QTreeView*
    MainWindow::GetCurrentTreeView()
    {
      static QTreeView* objectView[] =
      {
        mUi->vehiclesTreeView, mUi->weaponsTreeView
      };

      return objectView[mUi->tabWidget->currentIndex()];
    }
  };
};
