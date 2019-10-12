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

#include "vehicleform.hh"
#include "ui_vehicleform.h"

#include "objectcmd.hh"

#include <QtWidgets>
#include <QHBoxLayout>
#include <QSvgWidget>

#include <QDoubleValidator>
#include <QRegExpValidator>

using namespace GDW::RPG;

VehicleForm::VehicleForm(Vehicle* vehicle, QUndoStack* undoStack, QWidget* parent)
  : ObjectForm(parent, undoStack), mVehicle(vehicle), mUi(new Ui::VehicleForm)
{
  mUi->setupUi(this);

  //AddSvgFrame(mVehicle->Type(), mUi->svgFrame);
  Read();

  // mUi-> travelMoveLineEdit->setValidator(new QIntValidator(0, 1000000, this));
  // mUi->  techLevelLineEdit->setValidator(new QDoubleValidator(1, 33, 1, mUi->techLevelLineEdit));
  mUi-> suspensionLineEdit->setValidator(new QRegExpValidator(QRegExp("[AGTW]\\d+"), mUi->suspensionLineEdit));
}

VehicleForm::~VehicleForm()
{
  delete mUi;
}

void
VehicleForm::ShowSideViewMenu(const QPoint& position)
{
  QPoint offset(0, QFontMetrics(QAction().font()).height());

  QMenu menu(this);
  menu.addAction(tr("Set side-view image..."), this, &VehicleForm::SetSideViewImage);
  menu.addAction(tr("Clear side-view image"), this, &VehicleForm::ClearSideViewImage);
  menu.exec(mUi->sideViewFrame->mapToGlobal(position + offset));
}

void
VehicleForm::ShowTopDownMenu(const QPoint& position)
{
  QPoint offset(0, QFontMetrics(QAction().font()).height());

  QMenu menu(this);
  menu.addAction(tr("Set top-down image..."), this, &VehicleForm::SetTopDownImage);
  menu.addAction(tr("Clear top-down image"), this, &VehicleForm::ClearTopDownImage);
  menu.exec(mUi->topDownFrame->mapToGlobal(position + offset));
}

void
VehicleForm::ClearSideViewImage()
{
  mVehicle->SideViewImage("");

  UndoStack()->push(new ClearImageCommand(this));
}

void
VehicleForm::ClearTopDownImage()
{
  mVehicle->TopDownImage("");

  UndoStack()->push(new ClearImageCommand(this));
}

void
VehicleForm::SetTopDownImage()
{
  qDebug() << "VehicleForm::SetTopDownImage()";

  QByteArray svg = GetSvgFragment(tr("Select Top-Down Image"));

  if(!svg.isEmpty())
    mVehicle->TopDownImage(svg);

  UndoStack()->push(new SetImageCommand(this));
}

void
VehicleForm::SetSideViewImage()
{
  qDebug() << "VehicleForm::SetSideViewImage()";

  QByteArray svg = GetSvgFragment(tr("Select Side-View Image"));

  if(!svg.isEmpty())
    mVehicle->SideViewImage(svg);

  UndoStack()->push(new SetImageCommand(this));
}

Vehicle*
VehicleForm::Read(Mode mode, Object* object)
{
  Vehicle* original = mVehicle;

  if(object) {
    mVehicle = static_cast<Vehicle*>(object);
  }

  ObjectForm::Read();

  mUi->  techLevelLineEdit->setText(mVehicle->      TechLevel()      .toString());

  mUi->       nameLineEdit->setText(mVehicle->           Name()    .toString());
  mUi->       typeLineEdit->setText(mVehicle->           Type()    .toString());
  mUi->nationalityLineEdit->setText(mVehicle->    Nationality()    .toString());
  mUi-> travelMoveLineEdit->setText(mVehicle->     TravelMove()    .toString());
  mUi-> combatMoveLineEdit->setText(mVehicle->     CombatMove()    .toString());
  mUi->       fcapLineEdit->setText(mVehicle->   FuelCapacity()    .toString());
  mUi->      fconsLineEdit->setText(mVehicle->FuelConsumption()    .toString());
  mUi-> suspensionLineEdit->setText(mVehicle->     Suspension()    .toString());
  mUi->         tfLineEdit->setText(mVehicle->    TurretFront()    .toString());
  mUi->         tsLineEdit->setText(mVehicle->    TurretSides()    .toString());
  mUi->         trLineEdit->setText(mVehicle->     TurretRear()    .toString());
  mUi->         hfLineEdit->setText(mVehicle->      HullFront()    .toString());
  mUi->         hsLineEdit->setText(mVehicle->      HullSides()    .toString());
  mUi->         hrLineEdit->setText(mVehicle->       HullRear()    .toString());
  mUi->       massLineEdit->setText(mVehicle->           Mass(mode).toString());
  mUi->       loadLineEdit->setText(mVehicle->           Load(mode).toString());
  mUi->       crewLineEdit->setText(mVehicle->           Crew()    .toString());
  mUi->  passengerLineEdit->setText(mVehicle->     Passengers()    .toString());
  mUi->maintenanceLineEdit->setText(mVehicle->    Maintenance()    .toString());
  mUi->       costLineEdit->setText(mVehicle->           Cost(mode).toString());
  mUi->         rFLineEdit->setText(mVehicle->             Rf()    .toString());
  mUi->fireControlLineEdit->setText(mVehicle->    FireControl(mode).toString());
  mUi->       deckLineEdit->setText(mVehicle->           Deck(mode).toString());
  mUi->      bellyLineEdit->setText(mVehicle->          Belly(mode).toString());
  mUi->       stabLineEdit->setText(mVehicle->  Stabilization()    .toString());
  mUi->   fuelTypeLineEdit->setText(mVehicle->      FuelTypes()    .toString());
  mUi->      nightLineEdit->setText(mVehicle->    NightVision()    .toString());
  mUi->        radLineEdit->setText(mVehicle->            NBC()    .toString());
  mUi->      skillLineEdit->setText(mVehicle->          Skill()    .toString());
  mUi->    agilityLineEdit->setText(mVehicle->        Agility()    .toString());
  mUi->       hullLineEdit->setText(mVehicle->           Hull()    .toString());
  mUi->  structureLineEdit->setText(mVehicle->      Structure()    .toString());
  mUi-> openClosedLineEdit->setText(mVehicle->     OpenClosed()    .toString());
  mUi->         x8TextEdit->setPlainText(mVehicle->        X8()    .toString());
  mUi->       locaLineEdit->setText(mVehicle->   HitLocations()    .toString());

  AddSvgFrame(mVehicle->SideViewImage(), mUi->sideViewFrame);
  AddSvgFrame(mVehicle->TopDownImage(),  mUi->topDownFrame);

  return original;
}

Vehicle*
VehicleForm::Write()
{
  Vehicle* original = mVehicle->Copy();

  ObjectForm::Write();

  mVehicle->      TechLevel(mUi->  techLevelLineEdit->text());

  mVehicle->           Name(mUi->       nameLineEdit->text());
  mVehicle->           Type(mUi->       typeLineEdit->text());
  mVehicle->    Nationality(mUi->nationalityLineEdit->text());
  mVehicle->     TravelMove(mUi-> travelMoveLineEdit->text());
  mVehicle->     CombatMove(mUi-> combatMoveLineEdit->text());
  mVehicle->   FuelCapacity(mUi->       fcapLineEdit->text());
  mVehicle->FuelConsumption(mUi->      fconsLineEdit->text());
  mVehicle->     Suspension(mUi-> suspensionLineEdit->text());
  mVehicle->    TurretFront(mUi->         tfLineEdit->text());
  mVehicle->    TurretSides(mUi->         tsLineEdit->text());
  mVehicle->     TurretRear(mUi->         trLineEdit->text());
  mVehicle->      HullFront(mUi->         hfLineEdit->text());
  mVehicle->      HullSides(mUi->         hsLineEdit->text());
  mVehicle->       HullRear(mUi->         hrLineEdit->text());
  mVehicle->           Mass(mUi->       massLineEdit->text());
  mVehicle->           Load(mUi->       loadLineEdit->text());
  mVehicle->           Crew(mUi->       crewLineEdit->text());
  mVehicle->     Passengers(mUi->  passengerLineEdit->text());
  mVehicle->    Maintenance(mUi->maintenanceLineEdit->text());
  mVehicle->           Cost(mUi->       costLineEdit->text());
  mVehicle->             Rf(mUi->         rFLineEdit->text());
  mVehicle->    FireControl(mUi->fireControlLineEdit->text());
  mVehicle->           Deck(mUi->       deckLineEdit->text());
  mVehicle->          Belly(mUi->      bellyLineEdit->text());
  mVehicle->  Stabilization(mUi->       stabLineEdit->text());
  mVehicle->      FuelTypes(mUi->   fuelTypeLineEdit->text());
  mVehicle->    NightVision(mUi->      nightLineEdit->text());
  mVehicle->            NBC(mUi->        radLineEdit->text());
  mVehicle->          Skill(mUi->      skillLineEdit->text());
  mVehicle->        Agility(mUi->    agilityLineEdit->text());
  mVehicle->           Hull(mUi->       hullLineEdit->text());
  mVehicle->      Structure(mUi->  structureLineEdit->text());
  mVehicle->     OpenClosed(mUi-> openClosedLineEdit->text());
  mVehicle->             X8(mUi->         x8TextEdit->toPlainText());
  mVehicle->   HitLocations(mUi->       locaLineEdit->text());

  SetReadOnly(true);

  return original;
}

void
VehicleForm::SetReadOnly(bool value)
{
  ObjectForm::SetReadOnly(value);

  mUi->  techLevelLineEdit->setReadOnly(value);

  mUi->       nameLineEdit->setReadOnly(value);
  mUi->       typeLineEdit->setReadOnly(value);
  mUi->nationalityLineEdit->setReadOnly(value);
  mUi-> travelMoveLineEdit->setReadOnly(value);
  mUi-> combatMoveLineEdit->setReadOnly(value);
  mUi->       fcapLineEdit->setReadOnly(value);
  mUi->      fconsLineEdit->setReadOnly(value);
  mUi-> suspensionLineEdit->setReadOnly(value);
  mUi->         tfLineEdit->setReadOnly(value);
  mUi->         tsLineEdit->setReadOnly(value);
  mUi->         trLineEdit->setReadOnly(value);
  mUi->         hfLineEdit->setReadOnly(value);
  mUi->         hsLineEdit->setReadOnly(value);
  mUi->         hrLineEdit->setReadOnly(value);
  mUi->       massLineEdit->setReadOnly(value);
  mUi->       loadLineEdit->setReadOnly(value);
  mUi->       crewLineEdit->setReadOnly(value);
  mUi->  passengerLineEdit->setReadOnly(value);
  mUi->maintenanceLineEdit->setReadOnly(value);
  mUi->       costLineEdit->setReadOnly(value);
  mUi->         rFLineEdit->setReadOnly(value);
  mUi->fireControlLineEdit->setReadOnly(value);
  mUi->       deckLineEdit->setReadOnly(value);
  mUi->      bellyLineEdit->setReadOnly(value);
  mUi->       stabLineEdit->setReadOnly(value);
  mUi->   fuelTypeLineEdit->setReadOnly(value);
  mUi->      nightLineEdit->setReadOnly(value);
  mUi->        radLineEdit->setReadOnly(value);
  mUi->      skillLineEdit->setReadOnly(value);
  mUi->       hullLineEdit->setReadOnly(value);
  mUi->    agilityLineEdit->setReadOnly(value);
  mUi->  structureLineEdit->setReadOnly(value);
  mUi-> openClosedLineEdit->setReadOnly(value);
  mUi->         x8TextEdit->setReadOnly(value);
  mUi->       locaLineEdit->setReadOnly(value);
}

QString
VehicleForm::Title() const
{

  return tr("Vehicle");
}

Vehicle*
VehicleForm::GetObjectPtr()
{
  return mVehicle;
}

const Vehicle*
VehicleForm::GetObjectPtr() const
{
  return mVehicle;
}
