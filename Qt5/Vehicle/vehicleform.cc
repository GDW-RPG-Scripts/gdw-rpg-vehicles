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

#include <QDoubleValidator>
#include <QRegExpValidator>

using namespace GDW::RPG;

VehicleForm::VehicleForm(Vehicle* vehicle, QWidget* parent) :
  ObjectForm(parent), mVehicle(vehicle), mUi(new Ui::VehicleForm)
{
  mUi->setupUi(this);

  AddSvgFrame(mVehicle->Type(), mUi->svgFrame);
  Read();

  // mUi-> travelMoveLineEdit->setValidator(new QIntValidator(0, 1000000, this));
  // mUi->  techLevelLineEdit->setValidator(new QDoubleValidator(1, 33, 1, mUi->techLevelLineEdit));
  mUi-> suspensionLineEdit->setValidator(new QRegExpValidator(QRegExp("[AGTW]\\d+"), mUi->suspensionLineEdit));
}

VehicleForm::~VehicleForm()
{
  delete mUi;
}

Vehicle*
VehicleForm::Read(Mode mode, Object* object)
{
  Vehicle* original = mVehicle;

  if(object) {
    mVehicle = static_cast<Vehicle*>(object);
  }

  ObjectForm::Read();

  mUi->  techLevelLineEdit->setText(mVehicle->TechLevel()      .toString());

  mUi->       nameLineEdit->setText(mVehicle->Name()           .toString());
  mUi->       typeLineEdit->setText(mVehicle->Type()           .toString());
  mUi->nationalityLineEdit->setText(mVehicle->Nationality()    .toString());
  mUi-> travelMoveLineEdit->setText(mVehicle->TravelMove()     .toString());
  mUi-> combatMoveLineEdit->setText(mVehicle->CombatMove()     .toString());
  mUi->       fcapLineEdit->setText(mVehicle->FuelCapacity()   .toString());
  mUi->      fconsLineEdit->setText(mVehicle->FuelConsumption().toString());
  mUi-> suspensionLineEdit->setText(mVehicle->Suspension()     .toString());
  mUi->         tfLineEdit->setText(mVehicle->TurretFront()    .toString());
  mUi->         tsLineEdit->setText(mVehicle->TurretSides()    .toString());
  mUi->         trLineEdit->setText(mVehicle->TurretRear()     .toString());
  mUi->         hfLineEdit->setText(mVehicle->HullFront()      .toString());
  mUi->         hsLineEdit->setText(mVehicle->HullSides()      .toString());
  mUi->         hrLineEdit->setText(mVehicle->HullRear()       .toString());
  mUi->     weightLineEdit->setText(mVehicle->Weight()         .toString());
  mUi->       loadLineEdit->setText(mVehicle->Load()           .toString());
  mUi->       crewLineEdit->setText(mVehicle->Crew()           .toString());
  mUi->  passengerLineEdit->setText(mVehicle->Passengers()     .toString());
  mUi->maintenanceLineEdit->setText(mVehicle->Maintenance()    .toString());
  mUi->      priceLineEdit->setText(mVehicle->Price()          .toString());
  mUi->         rFLineEdit->setText(mVehicle->Rf()             .toString());
  mUi->       deckLineEdit->setText(mVehicle->Deck(mode)        .toString());
  mUi->      bellyLineEdit->setText(mVehicle->Belly(mode)       .toString());
  mUi->       stabLineEdit->setText(mVehicle->Stabilization()  .toString());
  mUi->   fuelTypeLineEdit->setText(mVehicle->FuelTypes()      .toString());
  mUi->      nightLineEdit->setText(mVehicle->NightVision()    .toString());
  mUi->        radLineEdit->setText(mVehicle->NBC()            .toString());
  mUi->         x5LineEdit->setText(mVehicle->X5()             .toString());
  mUi->         x6LineEdit->setText(mVehicle->X6()             .toString());
  mUi->         x7LineEdit->setText(mVehicle->X7()             .toString());
  mUi->         x8TextEdit->setPlainText(mVehicle->X8()        .toString());
  mUi->       locaLineEdit->setText(mVehicle->HitLocations()   .toString());

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
  mVehicle->         Weight(mUi->     weightLineEdit->text());
  mVehicle->           Load(mUi->       loadLineEdit->text());
  mVehicle->           Crew(mUi->       crewLineEdit->text());
  mVehicle->     Passengers(mUi->  passengerLineEdit->text());
  mVehicle->    Maintenance(mUi->maintenanceLineEdit->text());
  mVehicle->          Price(mUi->      priceLineEdit->text());
  mVehicle->             Rf(mUi->         rFLineEdit->text());
  mVehicle->           Deck(mUi->       deckLineEdit->text());
  mVehicle->          Belly(mUi->      bellyLineEdit->text());
  mVehicle->  Stabilization(mUi->       stabLineEdit->text());
  mVehicle->      FuelTypes(mUi->   fuelTypeLineEdit->text());
  mVehicle->    NightVision(mUi->      nightLineEdit->text());
  mVehicle->            NBC(mUi->        radLineEdit->text());
  mVehicle->             X5(mUi->         x5LineEdit->text());
  mVehicle->             X6(mUi->         x6LineEdit->text());
  mVehicle->             X7(mUi->         x7LineEdit->text());
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
  mUi->     weightLineEdit->setReadOnly(value);
  mUi->       loadLineEdit->setReadOnly(value);
  mUi->       crewLineEdit->setReadOnly(value);
  mUi->  passengerLineEdit->setReadOnly(value);
  mUi->maintenanceLineEdit->setReadOnly(value);
  mUi->      priceLineEdit->setReadOnly(value);
  mUi->         rFLineEdit->setReadOnly(value);
  mUi->       deckLineEdit->setReadOnly(value);
  mUi->      bellyLineEdit->setReadOnly(value);
  mUi->       stabLineEdit->setReadOnly(value);
  mUi->   fuelTypeLineEdit->setReadOnly(value);
  mUi->      nightLineEdit->setReadOnly(value);
  mUi->        radLineEdit->setReadOnly(value);
  mUi->         x5LineEdit->setReadOnly(value);
  mUi->         x6LineEdit->setReadOnly(value);
  mUi->         x7LineEdit->setReadOnly(value);
  mUi->         x8TextEdit->setReadOnly(value);
  mUi->       locaLineEdit->setReadOnly(value);
}

QString
VehicleForm::Title() const
{

  return tr("Vehicle");
}

Vehicle*
VehicleForm::GetObject()
{
  return mVehicle;
}

const Vehicle*
VehicleForm::GetObject() const
{
  return mVehicle;
}
