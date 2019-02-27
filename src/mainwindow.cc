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
#include "treeitem.hh"
#include "undocmds.hh"

#include "ui_mainwindow.h"
#include "ui_vehicleform.h"
#include "ui_weaponform.h"


namespace GDW
{
  namespace RPG
  {
    MainWindow::MainWindow(QWidget* parent) :
      QMainWindow(parent),
      mModel(new TreeModel),
      mUi(new Ui::MainWindow)
    {
      SetCurrentFile(QString());
      setUnifiedTitleAndToolBarOnMac(true);

      mUi->setupUi(this);

      // Disable menu actions for unavailable features
#if !QT_CONFIG(printer)
      mUi->action_Print->setEnabled(false);
#endif

#if !QT_CONFIG(clipboard)
      mUi->action_Cut->setEnabled(false);
      mUi->action_Copy->setEnabled(false);
      mUi->action_Paste->setEnabled(false);
#endif
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
                                       "Untitled",
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
      QMessageBox::about(this, tr("About GDW RPG Vehicles"),
                         tr("<b>GDW RPG Vehicles</b> – Vehicle card printing database for 2d6 "
                            "Sci-fi and other RPGs.\n"
                            "Copyright (C) 2018-2019 by Michael N. Henry\n\n"
                            "This program is free software: you can redistribute it and/or modify "
                            "it under the terms of the GNU General Public License as published by "
                            "the Free Software Foundation, either version 3 of the License, or"
                            "(at your option) any later version.\n\n"
                            "The Traveller game in all forms is owned by Far Future Enterprises. "
                            "Copyright 1977 - 2008 Far Future Enterprises."));
    }

    void
    MainWindow::AddItem()
    {
      QString type =
          mUi->tabWidget->tabText(mUi->tabWidget->currentIndex());

      QTreeView* tv =
          static_cast<QTreeView*>(mUi->tabWidget->currentWidget());

      mModel->AddItem(type, tv->currentIndex());
    }

    void
    MainWindow::EditItem()
    {
      if(mUi->objectForm->IsReadOnly()) {
        mUi->editButton->setText(tr("Cancel"));
        mUi->  okButton->setEnabled(true);
        mUi->objectForm->SetReadOnly(false);
      } else {
        mUi->editButton->setText(tr("Edit"));
        mUi->  okButton->setEnabled(false);
        mUi->objectForm->SetReadOnly(true);
        mUi->objectForm->Read();
      }
    }

    void
    MainWindow::PrintItem()
    {
      qDebug() << "MainWindow::Print()";

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
      setWindowModified(isModified());
      // setWindowModified(textEdit->document()->isModified());
    }

    void MainWindow::SelectItem(const QModelIndex& index)
    {
      ObjectTreeItem* oti =
          static_cast<ObjectTreeItem*>(index.internalPointer());

      oti->Select(mUi);

      mUi->  editButton->setEnabled(true);
      mUi->  editButton->setText(tr("Edit"));
      mUi->    okButton->setEnabled(false);
      mUi-> printButton->setEnabled(true);
      mUi->deleteButton->setEnabled(true);
      mUi->action_Print->setEnabled(true);
    }

    void
    MainWindow::SaveItem()
    {
      mUndoStack.push(new UndoCommitObject());
      mUi->objectForm->Write();
      mUi->editButton->setText(tr("Edit"));
      mUi->  okButton->setEnabled(false);
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
        if (isModified())
          Save();
      }
    }
#endif

    //
    // Methods
    //

    void
    MainWindow::ReadSettings()
    {
      QSettings settings(QCoreApplication::organizationName(), QCoreApplication::applicationName());
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
      QSettings settings(QCoreApplication::organizationName(), QCoreApplication::applicationName());
      settings.setValue("geometry", saveGeometry());
    }

    bool
    MainWindow::isModified()
    {
      return !mUndoStack.isClean();
    }

    bool
    MainWindow::MaybeSave()
    {
      if(!isModified())
        return true;

      // if(/* DISABLES CODE */ (true))
      //  return true;
      //  if (!textEdit->document()->isModified())
      //    return true;

      const QMessageBox::StandardButton ret
          = QMessageBox::warning(this, tr("Application"),
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
        QMessageBox::warning(this, tr("Application"), message);
        return;
      }

#ifndef QT_NO_CURSOR
      QApplication::setOverrideCursor(Qt::WaitCursor);
#endif

      // textEdit->setPlainText(in.readAll());
      mModel->Import(file);
      mUi->vehiclesTreeView->setModel(mModel);
      file.close();

#ifndef QT_NO_CURSOR
      QApplication::restoreOverrideCursor();
#endif

      SetCurrentFile(fileName);
      mUi->action_Save->setEnabled(true);
      mUi->action_SaveAs->setEnabled(true);
      statusBar()->showMessage(tr("Objects loaded"), 2000);
    }

    bool
    MainWindow::SaveFile(const QString& fileName)
    {
      QFile file(fileName);
      if (!file.open(QFile::WriteOnly | QFile::Text)) {
        QMessageBox::warning(this, tr("Application"),
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
      setWindowTitle(info.fileName() + " - GDW RPG Vehicles");
    }
  };
};
