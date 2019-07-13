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

#include "munition.hh"

using namespace GDW::RPG;

const QString
Munition::JSON_TYPE = "__GDW_RPG_Munition__";

Munition::Munition()
{}

Munition::Munition(const Munition& object)
  : Object (object)
{}

Munition::~Munition()
{}

Munition::Munition(const QJsonObject& json)
  : Object (json)
{}

Munition*
Munition::New()
{
  static const QJsonObject weapon
  {
    {"__GDW_RPG_Type__", JSON_TYPE} //,
    // {PROP_WTYP, "[Type]"} //, {PROP_WQUAL, ""},    {PROP_ROF, QJsonValue(QJsonValue::Double)}, {PROP_RNG,  QJsonValue(QJsonValue::Double)},
    //    {PROP_PS,  QJsonValue(QJsonValue::Double)}, {PROP_PM,  QJsonValue(QJsonValue::Double)}, {PROP_PL,   QJsonValue(QJsonValue::Double)}, {PROP_PX, QJsonValue(QJsonValue::Double)}, {PROP_AMMO, QJsonValue(QJsonValue::Double)},
    //    {PROP_CON, QJsonValue(QJsonValue::Double)}, {PROP_BUR, QJsonValue(QJsonValue::Double)}, {PROP_PRAN, QJsonValue(QJsonValue::Double)}
  };

  return new Munition(weapon);
}
