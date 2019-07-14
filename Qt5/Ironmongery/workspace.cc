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
#include <QProgressDialog>
#if defined(QT_PRINTSUPPORT_LIB)
#include <QtPrintSupport/qtprintsupportglobal.h>
#if QT_CONFIG(printer)
#if QT_CONFIG(printdialog)
#include <QPrintDialog>
#endif // QT_CONFIG(printdialog)
#include <QPrinter>
#if QT_CONFIG(printpreviewdialog)
#include <QPrintPreviewDialog>
#endif // QT_CONFIG(printpreviewdialog)
#endif // QT_CONFIG(printer)
#endif // QT_PRINTSUPPORT_LIB

#include "ruleset.hh"
#include "commands.hh"
#include "workspace.hh"
#include "prefsdialog.hh"
#include "weapondialog.hh"

#include "objectitem.hh"
#include "shipitem.hh"
#include "unititem.hh"
#include "vehicleitem.hh"
#include "weaponitem.hh"

#include <chrono>

using namespace GDW::RPG;

using namespace std::chrono;

Workspace::Workspace(QWidget* parent)
  : QMainWindow(parent),
    mRuleSet(Ruleset::Current()), mLoadOnStart(true)
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
  actions[0]->setIcon(QIcon("://icons/16x16/edit-undo.png"));
  actions[1]->setIcon(QIcon("://icons/16x16/edit-redo.png"));
  mUi.menuEdit->insertActions(mUi.action_Placeholder, actions);
  mUi.menuEdit->removeAction(mUi.action_Placeholder);

  struct ModelView {
      QTreeView* view;
      std::function<ObjectModel*()> model;
  } mvMap[] = {
  {mUi.vehiclesTreeView, VehicleModel::Model},
  {mUi.weaponsTreeView,  WeaponModel ::Model},
  {mUi.shipTreeView,     ShipModel   ::Model},
  {mUi.unitTreeView,     UnitModel   ::Model}};

  for(ModelView mv: mvMap) {
    //    QSortFilterProxyModel* proxyModel = new QSortFilterProxyModel(this);
    //    proxyModel->setSourceModel(mv.model());
    //    mv.view->setModel(proxyModel);
    mv.view->setModel(mv.model());
  }

  CurrentFile(QString());
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
  connect(&mUndoStack, &QUndoStack::cleanChanged, this, &Workspace::DocumentWasModified);

  if(mLoadOnStart)
    LoadFile(":/Default.gro");

  UpdateActions();
}

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
void Workspace::New()
{
  if (MaybeSave()) {
    Unselect();
    GetCurrentTreeView().selectionModel()->clearSelection();
    // textEdit->clear();
    mUndoStack.setClean();
    mUi.objectForm->hide();

    for (int i = 0; i < mUi.tabWidget->count(); ++i) {
      QTreeView* view =
          static_cast<QTreeView*>(mUi.tabWidget->widget(i)->layout()->itemAt(0)->widget());

      //      QAbstractProxyModel* proxy =
      //          static_cast<QAbstractProxyModel*>(view->model());

      ObjectModel* model =
          static_cast<ObjectModel*>(view->model()); //proxy->sourceModel());

      model->Reset();
    }

    CurrentFile(QString());
    UpdateActions();
  }
}

void
Workspace::Open()
{
  if (MaybeSave()) {
    QString fileName =
        QFileDialog::getOpenFileName(this, tr("Load Vehicles"), ".",
                                     tr("GDW RPG Object files (*.json *.grv *.gro)"));
    if (!fileName.isEmpty()) {
      New();
      LoadFile(fileName);
      UpdateActions();
    }
  }
}

void
Workspace::ExportPDF()
{
  QString fileName =
      QFileDialog::getSaveFileName(this, tr("Export PDF"), ".",
                                   tr("SVG Image (*.pdf)"));
  if (!fileName.isEmpty()) {
    QFile file(fileName);
    if (!file.open(QFile::ReadWrite | QFile::Text)) {
      QString message =
          tr("Cannot read file %1:\n%2.").arg(QDir::toNativeSeparators(fileName),
                                              file.errorString());
      QMessageBox::warning(this,
                           QCoreApplication::organizationName()
                           + " "
                           + QCoreApplication::applicationName(),
                           message);
      return;
    }

#ifndef QT_NO_CURSOR
    QApplication::setOverrideCursor(Qt::WaitCursor);
#endif

    milliseconds start =
        duration_cast<milliseconds>(system_clock::now().time_since_epoch());

    QTreeView& view = GetCurrentTreeView();
    ObjectModel* model =
        static_cast<ObjectModel*>(view.model());

    model->WritePdf(view.currentIndex(), file);
    file.close();

    milliseconds stop =
        duration_cast<milliseconds>(system_clock::now().time_since_epoch());

    milliseconds time = stop - start;

#ifndef QT_NO_CURSOR
    QApplication::restoreOverrideCursor();
#endif

    statusBar()->showMessage(tr("PDF exported")
                             + ": "
                             + QString::number(time.count())
                             + " ms.", 5000);
  }
}

void
Workspace::ExportSVG()
{
  QString fileName =
      QFileDialog::getSaveFileName(this, tr("Export SVG"), ".",
                                   tr("SVG Image (*.svg)"));
  if (!fileName.isEmpty()) {
    QFile file(fileName);
    if (!file.open(QFile::ReadWrite | QFile::Text)) {
      QString message =
          tr("Cannot read file %1:\n%2.").arg(QDir::toNativeSeparators(fileName),
                                              file.errorString());
      QMessageBox::warning(this,
                           QCoreApplication::organizationName()
                           + " "
                           + QCoreApplication::applicationName(),
                           message);
      return;
    }

#ifndef QT_NO_CURSOR
    QApplication::setOverrideCursor(Qt::WaitCursor);
#endif

    milliseconds start =
        duration_cast<milliseconds>(system_clock::now().time_since_epoch());

    QTreeView& view = GetCurrentTreeView();
    ObjectModel* model =
        static_cast<ObjectModel*>(view.model());

    model->WriteSvg(view.currentIndex(), file);
    file.close();

    milliseconds stop =
        duration_cast<milliseconds>(system_clock::now().time_since_epoch());

    milliseconds time = stop - start;

#ifndef QT_NO_CURSOR
    QApplication::restoreOverrideCursor();
#endif

    statusBar()->showMessage(tr("SVG exported")
                             + ": "
                             + QString::number(time.count())
                             + " ms.", 5000);
  }
}

void
Workspace::Import()
{
  QString fileName =
      QFileDialog::getOpenFileName(this, tr("Import Vehicles"), ".",
                                   tr("GDW RPG Object files (*.json *.grv *.gro)"));
  if (!fileName.isEmpty()) {
    LoadFile(fileName);
    setWindowModified(true);
  }
}

void
Workspace::Prefs()
{
  PrefsDialog dialog(mLoadOnStart, mRuleSet, this);

  if(dialog.exec() != PrefsDialog::Accepted) {
    return;
  }

  QSettings settings;

  QString dialogRuleset = dialog.Ruleset();
  if(mRuleSet != dialogRuleset) {
    mRuleSet = dialogRuleset;
    settings.setValue("ruleset", dialogRuleset);

    ClearObjectGroupBox();
    ItemClicked(GetCurrentTreeView().currentIndex());
  }

  bool dialogLoadOnStart = dialog.LoadOnStart();
  if(dialogLoadOnStart != mLoadOnStart) {
    mLoadOnStart = dialogLoadOnStart;
    settings.setValue("loadOnStart", dialogRuleset);
  }
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
                                   tr("GDW RPG Object files (*.gro);; "
                                      "GDW RPG Vehicles files (*.grv);; "
                                      "JSON Files (*.json)"));

  if(fileName.isEmpty())
    return false;

  return SaveFile(fileName);
}

void
Workspace::About()
{
  // qDebug() << "Workspace::About()";
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
  QItemSelectionModel* itemSelectionModel = view.selectionModel();
  QModelIndex index = itemSelectionModel->currentIndex();

  ObjectModel* model =
      static_cast<ObjectModel*>(view.model());
  mUndoStack.push(new InsertItemCommand(index, model));

  if(!index.isValid()) {
    index = index.siblingAtRow(0);
  }

  itemSelectionModel->select(index,
                             QItemSelectionModel::ClearAndSelect |
                             QItemSelectionModel::Rows);

  view.update();
}

void
Workspace::CurrentType(int)
{
  UpdateActions();
}

void
Workspace::EditItem()
{
  if(mUi.objectForm->IsReadOnly()) {
    mUi.editItemButton->setText(tr("&Cancel"));
    mUi.      okButton->setEnabled(true);
    mUi.    objectForm->SetReadOnly(false);
    mUi.    objectForm->Read(Mode::Edit);
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
  QItemSelectionModel* selectionModel = view.selectionModel();
  QModelIndexList indexList = selectionModel->selectedRows();
  for(QModelIndex index: indexList) {
    Unselect();
    mUndoStack.push(new RemoveItemCommand(index));
  }
}

void
Workspace::PrintItem()
{
#if defined(QT_PRINTSUPPORT_LIB) && QT_CONFIG(printdialog)
  QPrinter printer(QPrinter::HighResolution);
  QFileInfo fileInfo(CurrentFile());
  printer.setDocName(fileInfo.baseName());

  QPrintDialog dialog(&printer, this);
  if (dialog.exec() != QDialog::Accepted)
    return;

  QTreeView& view = GetCurrentTreeView();
  ObjectModel* model =
      static_cast<ObjectModel*>(view.model());

  model->Print(view.currentIndex(), printer);
#endif
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
Workspace::DocumentWasModified(bool isClean)
{
  setWindowModified(!isClean);
  UpdateActions();
}

void
Workspace::ItemClicked(const QModelIndex& index)
{
  ObjectItem* oti =
      static_cast<ObjectItem*>(index.internalPointer());

  if(GetCurrentTreeView().selectionModel()->isSelected(index))
    return Select(oti->GetForm(&mUndoStack));

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

  mUi.     action_Copy    ->setEnabled(true);
  mUi.      action_Cut    ->setEnabled(true);
  mUi.    action_ExportPdf->setEnabled(true);
  // mUi.    action_ExportSvg->setEnabled(true);
  mUi.    action_Print    ->setEnabled(true);
  mUi.  editItemButton    ->setEnabled(true);
  mUi.  editItemButton    ->setText(QObject::tr("Edit"));
  mUi.        okButton    ->setEnabled(false);
  mUi.     printButton    ->setEnabled(true);
  mUi.removeItemButton    ->setEnabled(true);
}

void
Workspace::Unselect()
{
  ClearObjectGroupBox();

  mUi.     action_Copy    ->setEnabled(false);
  mUi.      action_Cut    ->setEnabled(false);
  mUi.    action_ExportPdf->setEnabled(false);
  // mUi.    action_ExportSvg->setEnabled(false);
  mUi.    action_Print    ->setEnabled(false);
  mUi.  editItemButton    ->setEnabled(false);
  mUi.  editItemButton    ->setText(QObject::tr("Edit"));
  mUi.        okButton    ->setEnabled(false);
  mUi.     printButton    ->setEnabled(false);
  mUi.removeItemButton    ->setEnabled(false);
}

void
Workspace::SaveItem()
{
  mUndoStack.push(new UpdateItemCommand(mUi.objectForm));
  mUi.objectForm->Read();

  mUi.editItemButton->setText(tr("Edit"));
  mUi.      okButton->setEnabled(false);

  QTreeView& view = GetCurrentTreeView();
  QModelIndex index = view.currentIndex();
  ObjectItem* oti =
      static_cast<ObjectItem*>(index.internalPointer());
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
Workspace::AddMunition()
{
  qDebug() << "Workspace::AddMunition";
  QModelIndex index =
      mUi.weaponsTreeView->selectionModel()->currentIndex();

  ObjectItem* oti =
      static_cast<ObjectItem*>(index.internalPointer());

}

void
Workspace::AddWeapon()
{
  qDebug() << "Workspace::AddWeapon";
  QModelIndex vehicleIndex =
      mUi.vehiclesTreeView->selectionModel()->currentIndex();

  VehicleItem* vti =
      static_cast<VehicleItem*>(vehicleIndex.internalPointer());

  WeaponDialog dialog(this);

  if(dialog.exec() != PrefsDialog::Accepted) {
    return;
  }

  QModelIndex weaponIndex = dialog.Selected();
  if(weaponIndex.isValid()) {
    WeaponItem* wti =
        static_cast<WeaponItem*>(weaponIndex.internalPointer());

    //mUndoStack.push(new AddChildItemCommand(vti, wti));
  }
}

void
Workspace::ShowContextMenu(const QPoint& position)
{
  QTreeView& view = GetCurrentTreeView();
  QModelIndex index = view.currentIndex();
  ObjectItem* oti =
      static_cast<ObjectItem*>(index.internalPointer());

  QFontMetrics fontMetric(QAction().font());
  QPoint offset(0, fontMetric.height());

  QMenu menu(this);
  oti->Model()->AddActions(menu, mUndoStack, index);
  menu.exec(view.mapToGlobal(position + offset));
}

void
Workspace::ShowVehiclesMenu(const QPoint& position)
{
  QAction action(tr("Add weapon..."), this);

  connect(&action, &QAction::triggered, this, &Workspace::AddWeapon);

  QFontMetrics fontMetric(action.font());
  QPoint offset(0, fontMetric.height());

  QMenu menu(this);
  menu.addAction(&action);
  menu.exec(mUi.vehiclesTreeView->mapToGlobal(position + offset));
}

void
Workspace::ShowWeaponsMenu(const QPoint& position)
{
  QAction action(tr("Add munition..."), this);

  connect(&action, &QAction::triggered, this, &Workspace::AddMunition);

  QFontMetrics fontMetric(action.font());
  QPoint offset(0, fontMetric.height());

  QMenu menu(this);
  menu.addAction(&action);
  menu.exec(mUi.weaponsTreeView->mapToGlobal(position + offset));
}

//
// Methods
//

void
Workspace::ReadSettings()
{
  QSettings settings;

  mLoadOnStart = settings.value("loadOnStart", mLoadOnStart).toBool();
  mRuleSet = settings.value("ruleset", mRuleSet).toString();

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
  return isWindowModified();
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
Workspace::ResizeViewColumns()
{
  struct ModelViewMap {
      std::function<ObjectModel*()> GetModel;
      QTreeView* View;
  };

  static const ModelViewMap MODEL_VIEW_MAP[] = {
    { VehicleModel::Model, mUi.vehiclesTreeView },
    { WeaponModel ::Model, mUi. weaponsTreeView },
    { ShipModel   ::Model, mUi.    shipTreeView },
    { UnitModel   ::Model, mUi.    unitTreeView }
  };

  for(ModelViewMap map: MODEL_VIEW_MAP) {
    ObjectModel* model = map.GetModel();
    for (int column = 0; column < model->columnCount(); ++column) {
      map.View->resizeColumnToContents(column);
      //map.View->;
    }
  }
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
                         QCoreApplication::organizationName()
                         + " "
                         + QCoreApplication::applicationName(),
                         message);
    return;
  }

#ifndef QT_NO_CURSOR
  QApplication::setOverrideCursor(Qt::WaitCursor);
#endif

  milliseconds start =
      duration_cast<milliseconds>(system_clock::now().time_since_epoch());

  // textEdit->setPlainText(in.readAll());
  mFactory.Import(file);
  file.close();

  ResizeViewColumns();

  milliseconds stop =
      duration_cast<milliseconds>(system_clock::now().time_since_epoch());

  milliseconds time = stop - start;

#ifndef QT_NO_CURSOR
  QApplication::restoreOverrideCursor();
#endif

  CurrentFile(fileName);
  UpdateActions();
  mUi.action_Save->setEnabled(true);
  mUi.action_SaveAs->setEnabled(true);
  statusBar()->showMessage(tr("Objects loaded")
                           + ": "
                           + QString::number(time.count())
                           + " ms.", 5000);
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

#ifndef QT_NO_CURSOR
  QApplication::restoreOverrideCursor();
#endif

  mUndoStack.setClean();
  CurrentFile(fileName);
  statusBar()->showMessage(tr("File saved") + ".", 2000);
  return true;
}

const QString&
Workspace::CurrentFile() const
{
  return mCurrentFile;
}

void
Workspace::CurrentFile(const QString& fileName)
{
  QFileInfo info(mCurrentFile = fileName);
  QString title(info.fileName());
  title += info.fileName().isEmpty() ? "" : "[*] - ";
  setWindowTitle(title
                 + QCoreApplication::organizationName()
                 + " "
                 + QCoreApplication::applicationName()
                 );
}

void
Workspace::UpdateActions()
{
  QTreeView& view = GetCurrentTreeView();
  QItemSelectionModel* selectionModel = view.selectionModel();

  mUi.action_Save->setEnabled(IsModified() /*!mUndoStack.isClean()*/);
  mUi.action_SaveAs->setEnabled(true);

  bool hasSelection =
      selectionModel != nullptr && !selectionModel->selection().isEmpty();

  int currentIndex = mUi.tabWidget->currentIndex();
  mUi.action_AddObject->setEnabled(currentIndex == 0);
  mUi.action_AddWeapon->setEnabled(currentIndex == 1 || hasSelection);
  mUi.      action_Cut->setEnabled(hasSelection);
  mUi.     action_Copy->setEnabled(hasSelection);
  mUi.removeItemButton->setEnabled(hasSelection);

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
