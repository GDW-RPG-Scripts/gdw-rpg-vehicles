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

#include "commands.hh"
#include "workspace.hh"
#include "prefsdialog.hh"

#include "objectitem.hh"
#include "shipitem.hh"
#include "unititem.hh"
#include "vehicleitem.hh"
#include "weaponitem.hh"

// #include "ui_vehicleform.h"
// #include "ui_weaponform.h"


namespace GDW
{
  namespace RPG
  {
    Workspace::Workspace(QWidget* parent) :
      QMainWindow(parent), mRuleSet(0), mLoadOnStart(true)
    {
      ReadSettings();

#ifndef QT_NO_SESSIONMANAGER
      QGuiApplication::setFallbackSessionManagementEnabled(false);
      connect(qApp, &QGuiApplication::commitDataRequest,
              this, &Workspace::CommitData);
#endif

      mUi.setupUi(this);

      QList<QAction*> actions =
      {
        mUndoStack.createUndoAction(this, tr("&Undo")),
        mUndoStack.createRedoAction(this, tr("&Redo"))
      };
      actions[0]->setShortcuts(QKeySequence::Undo);
      actions[1]->setShortcuts(QKeySequence::Redo);
      mUi.menuEdit->insertActions(mUi.action_Placeholder, actions);
      mUi.menuEdit->removeAction(mUi.action_Placeholder);

      mUi.vehiclesTreeView->setModel(VehicleTreeItem ::Model());
      mUi.weaponsTreeView->setModel(WeaponTreeItem::Model());
      mUi.shipTreeView->setModel(ShipTreeItem::Model());
      mUi.unitTreeView->setModel(UnitTreeItem::Model());

      SetCurrentFile(QString());
      setUnifiedTitleAndToolBarOnMac(true);

      // Disable menu actions for unavailable features
#if !QT_CONFIG(printer)
      mUi.action_Print->setEnabled(false);
#endif

#if !QT_CONFIG(clipboard)
      mUi.action_Cut->setEnabled(false);
      mUi.action_Copy->setEnabled(false);
      mUi.action_Paste->setEnabled(false);
#endif

      connect(mUi.menuEdit, &QMenu::aboutToShow, this, &Workspace::UpdateActions);
      // connect(&mVehicleModel, &QAbstractItemModel::rowsRemoved, this, &Workspace::RemoveSelectedItems);
      // connect(mUi.insertItemButton, &QAbstractButton::clicked, this, &MainWindow::AddItem);
      // connect(mUi.action_Cut, &QAction::triggered, this, &MainWindow::RemoveItem);
      // connect(insertChildAction, &QAction::triggered, this, &MainWindow::insertChild);

      if(mLoadOnStart)
        LoadFile(":/Default.gro");

      UpdateActions();
    }

//    QAbstractItemModel*
//    Workspace::Model()
//    {
//      QAbstractItemView* view =
//          static_cast<QAbstractItemView*>(mUi.tabWidget->currentWidget());

//      return view->model();
//    }

    Workspace::~Workspace()
    {}

    //
    // Events
    //

    void Workspace::closeEvent(QCloseEvent* event)
    {
      WriteSettings();

      if (MaybeSave()) {
        event->accept();
      } else {
        event->ignore();
      }
    }

    //
    // Slots
    //
    void
    Workspace::LoadOnStart(int state)
    {
      mLoadOnStart = state;
    }

    void
    Workspace::RuleSet(int state)
    {
      mRuleSet = state;
    }

    void Workspace::New()
    {
      if (MaybeSave()) {
        // textEdit->clear();
        mUndoStack.clear();
        // delete mModel;
        // mUi.vehiclesTreeView->setModel(new VehicleModel);
        mUi.objectForm->hide();
        SetCurrentFile(QString());
      }
    }

    void
    Workspace::Open()
    {
      if (MaybeSave()) {
        QString fileName = QFileDialog::getOpenFileName(this, tr("Load Vehicles"), ".", tr("GDW RPG Object files (*.json *.grv *.gro)"));
        if (!fileName.isEmpty())
          LoadFile(fileName);
      }
    }

    void
    Workspace::Prefs()
    {
      PrefsDialog dialog(this);
      dialog.exec();
    }

    bool
    Workspace::Save()
    {
      if (mCurrentFile.isEmpty()) {
        return SaveAs();
      } else {
        return SaveFile(mCurrentFile);
      }
    }

    bool Workspace::SaveAs()
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
    Workspace::About()
    {
      // qDebug() << "MainWindow::About()";
      const QString text =
          tr("GDW RPG Vehicles – Vehicle database and card printing software "
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

      QMessageBox::about(this,
                         tr("About") + " " +
                         QCoreApplication::organizationName() + " " +
                         QCoreApplication::applicationName(), text);
    }

    void
    Workspace::InsertItem()
    {
      QTreeView& view = GetCurrentTreeView();

      // if(treeView.model() == nullptr)
      //   treeView.setModel(&mVehicleModel);

      QItemSelectionModel* itemSelectionModel = view.selectionModel();
      QModelIndex index = itemSelectionModel->currentIndex();

      ObjectModel* model =
          static_cast<ObjectModel*>(view.model());
      mUndoStack.push(new InsertItemCommand(index, model));

      UpdateActions();

      view.update();

      //      for (int column = mModel.columnCount(index.parent())-1; column >= 0 ; --column) {
      //        QModelIndex child =
      //            mModel.index(index.row()+1, column, index.parent());
      //        mModel.setData(child, QVariant("[No data]"), Qt::EditRole);
      //      }
    }

    void
    Workspace::CurrentType(int type)
    {
      // mCurrentType = type;
      // mModel.CurrentType(type);
      UpdateActions();
    }

    void
    Workspace::EditItem()
    {
      if(mUi.objectForm->IsReadOnly()) {
        mUi.editItemButton->setText(tr("&Cancel"));
        mUi.      okButton->setEnabled(true);
        mUi.    objectForm->SetReadOnly(false);
      } else {
        mUi.editItemButton->setText(tr("&Edit"));
        mUi.      okButton->setEnabled(false);
        mUi.    objectForm->SetReadOnly(true);
        mUi.    objectForm->Read();
      }
    }

    void
    Workspace::RemoveSelectedItems()
    {
      QTreeView& view = GetCurrentTreeView();

      while(view.selectionModel()->hasSelection()) {
        QModelIndex index =
            view.selectionModel()->selectedRows().takeAt(0);
        //ObjectTreeItem* oti =
        //     static_cast<ObjectTreeItem*>(index.internalPointer());
        // oti->Unselect(mUi);
        Unselect();
        ObjectModel* model =
            static_cast<ObjectModel*>(view.model());
        mUndoStack.push(new RemoveItemCommand(index, model));
      }

      UpdateActions();
    }

    void
    Workspace::PrintItem()
    {
      QTreeView& view = GetCurrentTreeView();
      ObjectModel* model =
          static_cast<ObjectModel*>(view.model());
      model->Print(this);
    }

    void
    Workspace::Redo()
    {
      mUndoStack.redo();
    }

    void
    Workspace::Undo()
    {
      mUndoStack.undo();
    }

    void
    Workspace::DocumentWasModified()
    {
      setWindowModified(IsModified());
      // setWindowModified(textEdit->document()->isModified());
    }

    // typedef std::function<void(ObjectTreeItem*, Ui::Workspace&, ObjectForm*)>
    // ObjectTreeSelector;

    void
    Workspace::ItemClicked(const QModelIndex& index)
    {
      ObjectTreeItem* oti =
          static_cast<ObjectTreeItem*>(index.internalPointer());

      if(GetCurrentTreeView().selectionModel()->isSelected(index))
        return Select(oti->GetForm());

      Unselect();
    }

    void
    Workspace::ClearObjectGroupBox()
    {
      QLayout* layout = mUi.objectGroupBox->layout();

      if(layout != nullptr) {
        QLayoutItem* child;
        while ((child = layout->takeAt(0)) != nullptr)  {
          QWidget* widget = child->widget();
          if(widget != nullptr)
            widget->hide();
        }
        delete layout;
      }
    }

    void
    Workspace::Select(ObjectForm* objectForm)
    {
      ClearObjectGroupBox();

      mUi.objectForm = objectForm;

      QGroupBox* objectGroupBox = mUi.objectGroupBox;
      objectForm->setParent(objectGroupBox);
      objectForm->setObjectName(QString::fromUtf8("objectWidget"));

      QVBoxLayout* verticalLayout = new QVBoxLayout(objectGroupBox);
      verticalLayout->addWidget(objectForm);
      verticalLayout->addItem(mUi.objectButtonsLayout);

      objectGroupBox->setLayout(verticalLayout);
      objectGroupBox->setTitle(objectForm->Title() + ": "); // + mWeapon->Wtyp());
      objectGroupBox->update();

      mUi.     action_Copy->setEnabled(true);
      mUi.      action_Cut->setEnabled(true);
      mUi.    action_Print->setEnabled(true);
      mUi.  editItemButton->setEnabled(true);
      mUi.  editItemButton->setText(QObject::tr("Edit"));
      mUi.        okButton->setEnabled(false);
      mUi.     printButton->setEnabled(true);
      mUi.removeItemButton->setEnabled(true);
    }

    void
    Workspace::Unselect()
    {
      ClearObjectGroupBox();

      mUi.     action_Copy->setEnabled(false);
      mUi.      action_Cut->setEnabled(false);
      mUi.    action_Print->setEnabled(false);
      mUi.  editItemButton->setEnabled(false);
      mUi.  editItemButton->setText(QObject::tr("Edit"));
      mUi.        okButton->setEnabled(false);
      mUi.     printButton->setEnabled(false);
      mUi.removeItemButton->setEnabled(false);
    }

    void
    Workspace::SaveItem()
    {
      // mUndoStack.push(new InsertItemCommand());
      mUi.    objectForm->Write();
      mUi.editItemButton->setText(tr("Edit"));
      mUi.      okButton->setEnabled(false);

      QTreeView& view = GetCurrentTreeView();
      QModelIndex index = view.currentIndex();
      ObjectTreeItem* oti =
          static_cast<ObjectTreeItem*>(index.internalPointer());
      oti->RefreshItemData();
      view.selectionModel()->select(index,
                                    QItemSelectionModel::SelectCurrent |
                                    QItemSelectionModel::Rows);
      view.activateWindow();
    }

#ifndef QT_NO_SESSIONMANAGER
    void Workspace::CommitData(QSessionManager& manager)
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
    Workspace::AddWeapon()
    {
      qDebug() << "MainWindow::AddWeapon";
      QModelIndex index =
          mUi.vehiclesTreeView->selectionModel()->currentIndex();

      ObjectTreeItem* oti =
          static_cast<ObjectTreeItem*>(index.internalPointer());

      WeaponTreeItem* weaponItem = WeaponTreeItem::Create(oti);

      oti->AppendChild(weaponItem);
      // mModel.
    }

    void
    Workspace::ShowVehiclesMenu(const QPoint& position)
    {
      QAction action(tr("Add weapon"), this);
      QFontMetrics fontMetric(action.font());
      QPoint offset(0, fontMetric.height());

      connect(&action, &QAction::triggered, this, &Workspace::AddWeapon);

      QMenu menu(this);
      menu.addAction(&action);
      menu.exec(mUi.vehiclesTreeView->mapToGlobal(position + offset));
    }

    void
    Workspace::ShowWeaponsMenu(const QPoint& position)
    {
      qDebug() << "MainWindow::ShowWeaponsMenu(const QPoint& " << position << ")";
    }

    //
    // Methods
    //

    void
    Workspace::ReadSettings()
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
    Workspace::WriteSettings()
    {
      QSettings settings;
      settings.setValue("geometry", saveGeometry());
      settings.setValue("loadOnStart", mLoadOnStart);
      settings.setValue("ruleset", mRuleSet);
    }

    bool
    Workspace::IsModified()
    {
      return !mUndoStack.isClean();
    }

    bool
    Workspace::MaybeSave()
    {
      if(!IsModified())
        return true;

      // if(/* DISABLES CODE */ (true))
      //  return true;
      //  if (!textEdit->document()->isModified())
      //    return true;

      const QMessageBox::StandardButton ret
          = QMessageBox::warning(this,
                                 QCoreApplication::organizationName() + " " +
                                 QCoreApplication::applicationName(),
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
    Workspace::LoadFile(const QString& fileName)
    {
      QFile file(fileName);
      if (!file.open(QFile::ReadOnly | QFile::Text)) {
        QString message =
            tr("Cannot read file %1:\n%2.").arg(QDir::toNativeSeparators(fileName),
                                                file.errorString());
        QMessageBox::warning(this,
                             QCoreApplication::organizationName() + " " +
                             QCoreApplication::applicationName(),
                             message);
        return;
      }

#ifndef QT_NO_CURSOR
      QApplication::setOverrideCursor(Qt::WaitCursor);
#endif

      // textEdit->setPlainText(in.readAll());
      mFactory.Import(mUi, file);

#ifndef QT_NO_CURSOR
      QApplication::restoreOverrideCursor();
#endif

      SetCurrentFile(fileName);
      UpdateActions();
      mUi.action_Save->setEnabled(true);
      mUi.action_SaveAs->setEnabled(true);
      statusBar()->showMessage(tr("Objects loaded"), 2000);
    }

    bool
    Workspace::SaveFile(const QString& fileName)
    {
      QFile file(fileName);
      if (!file.open(QFile::WriteOnly | QFile::Text)) {
        QMessageBox::warning(this,
                             QCoreApplication::organizationName() + " " +
                             QCoreApplication::applicationName(),
                             tr("Cannot write file %1:\n%2.")
                             .arg(QDir::toNativeSeparators(fileName),
                                  file.errorString()));
        return false;
      }

      QTextStream out(&file);

#ifndef QT_NO_CURSOR
      QApplication::setOverrideCursor(Qt::WaitCursor);
#endif
      out << mFactory;
      // out << mVehicleModel;
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
    Workspace::SetCurrentFile(const QString& fileName)
    {
      QFileInfo info(mCurrentFile = fileName);
      QString title(info.fileName());
      title += info.fileName().isEmpty() ? "" : " - ";
      setWindowTitle(title +
                     QCoreApplication::organizationName() + " " +
                     QCoreApplication::applicationName());
    }

    void
    Workspace::UpdateActions()
    {
      QTreeView& view = GetCurrentTreeView();
      QItemSelectionModel* selectionModel = view.selectionModel();

      mUi.action_Save->setEnabled(!mUndoStack.isClean());
      mUi.action_SaveAs->setEnabled(true);

      bool hasSelection =
          selectionModel != nullptr && !selectionModel->selection().isEmpty();

      int currentIndex = mUi.tabWidget->currentIndex();
      mUi.action_AddVehicle->setEnabled(currentIndex == 0);
      mUi. action_AddWeapon->setEnabled(currentIndex == 1 || hasSelection);
      mUi.       action_Cut->setEnabled(hasSelection);
      mUi.      action_Copy->setEnabled(hasSelection);
      mUi. removeItemButton->setEnabled(hasSelection);

      if(hasSelection) {
        connect(selectionModel, &QItemSelectionModel::selectionChanged,
                this, &Workspace::UpdateActions);
      }

      bool hasCurrent =
          selectionModel != nullptr && selectionModel->currentIndex().isValid();
      mUi.insertItemButton->setEnabled(true); // hasCurrent);
      if (hasCurrent) {
        view.closePersistentEditor(selectionModel->currentIndex());
      }
    }

    QTreeView&
    Workspace::GetCurrentTreeView()
    {
      static QTreeView* objectView[] =
      {
        mUi.vehiclesTreeView, mUi.weaponsTreeView,
        mUi.shipTreeView, mUi.unitTreeView
      };

      return *objectView[mUi.tabWidget->currentIndex()];
    }
  };
};
