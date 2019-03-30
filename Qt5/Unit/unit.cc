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

#include "unit.hh"

using namespace GDW::RPG;

const QString
Unit::JSON_TYPE = "__GDW_RPG_Ship__";

Unit::Unit(const QJsonObject& json)
  : Object (json)
{}

Unit*
Unit::New()
{
  static const QJsonObject object
  {
    {"__GDW_RPG_Type__", JSON_TYPE},
    {PROP_NAME, "[Name]"}
  };

  return new Unit(object);
}


const QString Unit::PROP_NAME = "name";

QString
Unit::Name() const
{
  return GetStringFor(PROP_NAME);
}

void
Unit::Name(const QString& value)
{
  SetStringFor(PROP_NAME, value);
}
