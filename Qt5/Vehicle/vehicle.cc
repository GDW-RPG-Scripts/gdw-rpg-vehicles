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

#include "vehicle.hh"

#include <QJsonArray>
#include <QJsonDocument>

using namespace GDW::RPG;

const QString
Vehicle::JSON_TYPE = "__GDW_RPG_Vehicle__";

Vehicle::Vehicle()
{}

Vehicle::Vehicle(const Vehicle& vehicle)
  : Object(vehicle)
{}

Vehicle::~Vehicle()
{
  // qDeleteAll(mWeapons);
}

Vehicle::Vehicle(const QJsonObject& json)
  : Object(json)
{
  if(json.contains(PROP_WEAPONS))
  {
    mWeapons = Weapon::Load(json[PROP_WEAPONS]);
  }
}

Vehicle*
Vehicle::New()
{
  static const QJsonObject vehicle
  {
    {"__GDW_RPG_Type__", JSON_TYPE},
    {PROP_NAME, "[Name]"}, {PROP_TYPE, "[Type]"}, {PROP_NATIONALITY, "[NAtionality]"},
    {PROP_TRMOV,   QJsonValue(QJsonValue::Double)}, {PROP_CCMOV, QJsonValue(QJsonValue::Double)}, {PROP_FCAP, QJsonValue(QJsonValue::Double)}, {PROP_FCONS, QJsonValue(QJsonValue::Double)}, {PROP_SUSP, ""},
    {PROP_TF,      QJsonValue(QJsonValue::Double)}, {PROP_TS,    QJsonValue(QJsonValue::Double)}, {PROP_TR,   QJsonValue(QJsonValue::Double)}, {PROP_HF,    QJsonValue(QJsonValue::Double)}, {PROP_HS,  QJsonValue(QJsonValue::Double)}, {PROP_HR, QJsonValue(QJsonValue::Double)},
    {PROP_WEAPONS, QJsonArray()},
    {PROP_WEIGHT,  QJsonValue(QJsonValue::Double)}, {PROP_LOAD,  QJsonValue(QJsonValue::Double)}, {PROP_CREW, QJsonValue(QJsonValue::Double)}, {PROP_PSGR,  QJsonValue(QJsonValue::Double)}, {PROP_MNT, QJsonValue(QJsonValue::Double)},
    {PROP_PRICE,   QJsonValue(QJsonValue::Double)}, {PROP_RF,    QJsonValue(QJsonValue::Double)}, {PROP_DECK, QJsonValue(QJsonValue::Double)}, {PROP_BELLY, QJsonValue(QJsonValue::Double)},
    {PROP_STAB, ""}, {PROP_FUEL, ""}, {PROP_NIGHT, ""}, {PROP_RAD, ""},
    {PROP_X5,   ""}, {PROP_X6,   ""}, {PROP_X7,    ""},
    {PROP_X8,   ""},
    {PROP_LOCA, ""}
  };

  return new Vehicle(vehicle);
}

Vehicle*
Vehicle::Copy()
{
  return new Vehicle(*this);
}

const Vehicle*
Vehicle::Copy() const
{
  return new Vehicle(*this);
}

QList<QVariant>
Vehicle::ItemData() const
{
  QList<QVariant> data;

  data << Name() << Type() << Nationality();

  return data;
}

/*
     * Name
     */
const QString Vehicle::PROP_NAME = "name";

QString
Vehicle::Name() const
{
  return GetStringFor(PROP_NAME);
}

void
Vehicle::Name(const QString& value)
{
  SetStringFor(PROP_NAME, value);
}


/*
     * Type
     */
const QString Vehicle::PROP_TYPE = "typ";

QString
Vehicle::Type() const
{
  return GetStringFor(PROP_TYPE);
}

void
Vehicle::Type(const QString& value)
{
  SetStringFor(PROP_TYPE, value);
}


/*
     * Nationality
     */
const QString Vehicle::PROP_NATIONALITY = "nat";

QString
Vehicle::Nationality() const
{
  return GetStringFor(PROP_NATIONALITY);
}

void
Vehicle::Nationality(const QString& value)
{
  SetStringFor(PROP_NATIONALITY, value);
}


/*
     * Trmov
     */
const QString Vehicle::PROP_TRMOV = "trmov";

double
Vehicle::Trmov() const
{
  return GetDoubleFor(PROP_TRMOV);
}

void
Vehicle::Trmov(double value)
{
  SetDoubleFor(PROP_TRMOV, value);
}


/*
     * Ccmov
     */
const QString Vehicle::PROP_CCMOV = "ccmov";

double
Vehicle::Ccmov() const
{
  return GetDoubleFor(PROP_CCMOV);
}

void
Vehicle::Ccmov(double value)
{
  SetDoubleFor(PROP_CCMOV, value);
}


/*
     * Fcap
     */
const QString Vehicle::PROP_FCAP = "fcap";

double
Vehicle::Fcap() const
{
  return GetDoubleFor(PROP_FCAP);
}

void
Vehicle::Fcap(double value)
{
  SetDoubleFor(PROP_FCAP, value);
}


/*
     * Fcons
     */
const QString Vehicle::PROP_FCONS = "fcons";

double
Vehicle::Fcons() const
{
  return GetDoubleFor(PROP_FCONS);
}

void
Vehicle::Fcons(double value)
{
  SetDoubleFor(PROP_FCONS, value);
}


/*
     * Susp
     */
const QString Vehicle::PROP_SUSP = "susp";

QString
Vehicle::Susp() const
{
  return GetStringFor(PROP_SUSP);
}

void
Vehicle::Susp(const QString& value)
{
  SetStringFor(PROP_SUSP, value);
}


/*
     * Tf
     */
const QString Vehicle::PROP_TF = "tf";

double
Vehicle::Tf() const
{
  return GetDoubleFor(PROP_TF);
}

void
Vehicle::Tf(double value)
{
  SetDoubleFor(PROP_TF, value);
}


/*
     * Ts
     */
const QString Vehicle::PROP_TS = "ts";

double
Vehicle::Ts() const
{
  return GetDoubleFor(PROP_TS);
}

void
Vehicle::Ts(double value)
{
  SetDoubleFor(PROP_TS, value);
}


/*
     * Tr
     */
const QString Vehicle::PROP_TR = "tr";

double
Vehicle::Tr() const
{
  return GetDoubleFor(PROP_TR);
}

void
Vehicle::Tr(double value)
{
  SetDoubleFor(PROP_TR, value);
}


/*
     * Hf
     */
const QString Vehicle::PROP_HF = "hf";

double
Vehicle::Hf() const
{
  return GetDoubleFor(PROP_HF);
}

void
Vehicle::Hf(double value)
{
  SetDoubleFor(PROP_HF, value);
}


/*
     * Hs
     */
const QString Vehicle::PROP_HS = "hs";

double
Vehicle::Hs() const
{
  return GetDoubleFor(PROP_HS);
}

void
Vehicle::Hs(double value)
{
  SetDoubleFor(PROP_HS, value);
}


/*
     * Hr
     */
const QString Vehicle::PROP_HR = "hr";

double
Vehicle::Hr() const
{
  return GetDoubleFor(PROP_HR);
}

void
Vehicle::Hr(double value)
{
  SetDoubleFor(PROP_HR, value);
}


/*
     * Weapons
     */
const QString Vehicle::PROP_WEAPONS = "weap";

QList<Weapon*>
Vehicle::Weapons()
{
  return mWeapons;
}

void
Vehicle::Weapons(QList<Weapon*>& weapons)
{
  mWeapons = weapons;
}


/*
     * Weight
     */
const QString Vehicle::PROP_WEIGHT = "weight";

double
Vehicle::Weight() const
{
  return GetDoubleFor(PROP_WEIGHT);
}

void
Vehicle::Weight(double value)
{
  SetDoubleFor(PROP_WEIGHT, value);
}


/*
     * Load
     */
const QString Vehicle::PROP_LOAD = "load";

double
Vehicle::Load() const
{
  return GetDoubleFor(PROP_HR);
}

void
Vehicle::Load(double value)
{
  SetDoubleFor(PROP_HR, value);
}


/*
     * Crew
     */
const QString Vehicle::PROP_CREW = "crew";

double
Vehicle::Crew() const
{
  return GetDoubleFor(PROP_CREW);
}

void
Vehicle::Crew(double value)
{
  SetDoubleFor(PROP_CREW, value);
}


/*
     * Psgr
     */
const QString Vehicle::PROP_PSGR = "psgr";

double
Vehicle::Psgr() const
{
  return GetDoubleFor(PROP_PSGR);
}

void
Vehicle::Psgr(double value)
{
  SetDoubleFor(PROP_PSGR, value);
}


/*
     * Mnt
     */
const QString Vehicle::PROP_MNT = "mnt";

double
Vehicle::Mnt() const
{
  return GetDoubleFor(PROP_MNT);
}

void
Vehicle::Mnt(double value)
{
  SetDoubleFor(PROP_MNT, value);
}


/*
     * Price
     */
const QString Vehicle::PROP_PRICE = "price";

double
Vehicle::Price() const
{
  return GetDoubleFor(PROP_PRICE);
}

void
Vehicle::Price(double value)
{
  SetDoubleFor(PROP_PRICE, value);
}


/*
     * Rf
     */
const QString Vehicle::PROP_RF = "rf";

double
Vehicle::Rf() const
{
  return GetDoubleFor(PROP_RF);
}

void
Vehicle::Rf(double value)
{
  SetDoubleFor(PROP_RF, value);
}


/*
     * Deck
     */
const QString Vehicle::PROP_DECK = "deck";

double
Vehicle::Deck() const
{
  return GetDoubleFor(PROP_DECK);
}

void
Vehicle::Deck(double value)
{
  SetDoubleFor(PROP_DECK, value);
}


/*
     * Belly
     */
const QString Vehicle::PROP_BELLY = "belly";

double
Vehicle::Belly() const
{
  return GetDoubleFor(PROP_BELLY);
}

void
Vehicle::Belly(double value)
{
  SetDoubleFor(PROP_BELLY, value);
}


/*
     * Stab
     */
const QString Vehicle::PROP_STAB = "stab";

QString
Vehicle::Stab() const
{
  return GetStringFor(PROP_STAB);
}

void
Vehicle::Stab(const QString& value)
{
  SetStringFor(PROP_STAB, value);
}


/*
     * Fuel
     */
const QString Vehicle::PROP_FUEL = "fuel";

QString
Vehicle::Fuel() const
{
  return GetStringFor(PROP_FUEL);
}

void
Vehicle::Fuel(const QString& value)
{
  SetStringFor(PROP_FUEL, value);
}


/*
     * Night
     */
const QString Vehicle::PROP_NIGHT = "night";

QString
Vehicle::Night() const
{
  return GetStringFor(PROP_NIGHT);
}

void
Vehicle::Night(const QString& value)
{
  SetStringFor(PROP_NIGHT, value);
}


/*
     * Rad
     */
const QString Vehicle::PROP_RAD = "rad";

QString
Vehicle::Rad() const
{
  return GetStringFor(PROP_RAD);
}

void
Vehicle::Rad(const QString& value)
{
  SetStringFor(PROP_RAD, value);
}


/*
     * X5
     */
const QString Vehicle::PROP_X5 = "x5";

QString
Vehicle::X5() const
{
  return GetStringFor(PROP_X5);
}

void
Vehicle::X5(const QString& value)
{
  SetStringFor(PROP_X5, value);
}


/*
     * X6
     */
const QString Vehicle::PROP_X6 = "x6";

QString
Vehicle::X6() const
{
  return GetStringFor(PROP_X6);
}

void
Vehicle::X6(const QString& value)
{
  SetStringFor(PROP_X6, value);
}


/*
     * X7
     */
const QString Vehicle::PROP_X7 = "x7";

QString
Vehicle::X7() const
{
  return GetStringFor(PROP_X7);
}

void
Vehicle::X7(const QString& value)
{
  SetStringFor(PROP_X7, value);
}


/*
     * X8
     */
const QString Vehicle::PROP_X8 = "x8";

QString
Vehicle::X8() const
{
  return GetStringFor(PROP_X8);
}

void
Vehicle::X8(const QString& value)
{
  SetStringFor(PROP_X8, value);
}


/*
 * Loca
 */
const QString Vehicle::PROP_LOCA = "loca";

QString
Vehicle::Loca() const
{
  return GetStringFor(PROP_LOCA);
}

void
Vehicle::Loca(const QString& value)
{
  SetStringFor(PROP_LOCA, value);
}
