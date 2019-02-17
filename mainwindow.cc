/*
**
**
*/

#include <QtWidgets>

#include "model.hh"
#include "mainwindow.hh"
#include "treeitem.hh"

#include "ui_mainwindow.h"
#include "ui_vehicleform.h"
#include "ui_weaponform.h"


namespace GDW
{
  namespace RPG
  {
    MainWindow::MainWindow(QWidget* parent) :
      QMainWindow(parent),
      mMainUi(new Ui::MainWindow),
      mVehicleUi(new Ui::VehicleForm),
      mWeaponUi(new Ui::WeaponForm)
    {

      SetCurrentFile(QString());
      setUnifiedTitleAndToolBarOnMac(true);

      mMainUi->setupUi(this);
//      mVehicleUi->setupUi(mMainUi->vehiclePage);
//      mWeaponUi->setupUi(mMainUi->weaponsPage);
    }

    MainWindow::~MainWindow()
    {
      delete mMainUi;
      delete mVehicleUi;
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
    void MainWindow::NewFile()
    {
      if (MaybeSave()) {
        // textEdit->clear();
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
      if (curFile.isEmpty()) {
        return SaveAs();
      } else {
        return SaveFile(curFile);
      }
    }

    bool MainWindow::SaveAs()
    {
      QFileDialog dialog(this);
      dialog.setWindowModality(Qt::WindowModal);
      dialog.setAcceptMode(QFileDialog::AcceptSave);
      if (dialog.exec() != QDialog::Accepted)
        return false;
      return SaveFile(dialog.selectedFiles().first());
    }

    void
    MainWindow::About()
    {
      qDebug() << "MainWindow::About()";
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
    MainWindow::DocumentWasModified()
    {
      setWindowModified(textEdit->document()->isModified());
    }

    void MainWindow::Display(const QModelIndex& index)
    {
      qDebug() << "Display: " << index;
      ObjectTreeItem* oti =
          static_cast<ObjectTreeItem*>(index.internalPointer());
      oti->Display(mMainUi);
    }

#ifndef QT_NO_SESSIONMANAGER
    void MainWindow::CommitData(QSessionManager& manager)
    {
      if (manager.allowsInteraction()) {
        if (!MaybeSave())
          manager.cancel();
      } else {
        // Non-interactive: save without asking
        if (textEdit->document()->isModified())
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
    MainWindow::MaybeSave()
    {
      if(/* DISABLES CODE */ (true))
        return true;
      //  if (!textEdit->document()->isModified())
      //    return true;

      const QMessageBox::StandardButton ret
          = QMessageBox::warning(this, tr("Application"),
                                 tr("Vehicles have been modified.\n"
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
    MainWindow::LoadFile(const QString &fileName)
    {
      QFile file(fileName);
      if (!file.open(QFile::ReadOnly | QFile::Text)) {
        QMessageBox::warning(this, tr("Application"),
                             tr("Cannot read file %1:\n%2.")
                             .arg(QDir::toNativeSeparators(fileName), file.errorString()));
        return;
      }

      // QTextStream in(&file);
#ifndef QT_NO_CURSOR
      QApplication::setOverrideCursor(Qt::WaitCursor);
#endif

      // textEdit->setPlainText(in.readAll());
      mMainUi->vehiclesTreeView->setModel(new TreeModel(file.readAll()));
      file.close();

      // VehicleTreeWidgetItem::Load(jdoc, ui->treeWidget);

#ifndef QT_NO_CURSOR
      QApplication::restoreOverrideCursor();
#endif

      SetCurrentFile(fileName);
      statusBar()->showMessage(tr("Vehicles loaded"), 2000);
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
      out << textEdit->toPlainText();
#ifndef QT_NO_CURSOR
      QApplication::restoreOverrideCursor();
#endif

      SetCurrentFile(fileName);
      statusBar()->showMessage(tr("File saved"), 2000);
      return true;
    }

    void
    MainWindow::SetCurrentFile(const QString &fileName)
    {
      curFile = fileName;
    }
  };
};
