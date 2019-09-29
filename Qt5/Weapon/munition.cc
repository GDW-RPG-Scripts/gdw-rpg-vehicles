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

#include "weapon.hh"

using namespace GDW::RPG;

const QString
Munition::JSON_TYPE = "__GDW_RPG_Munition__";

Munition::Munition(const QJsonObject& json, Object* parent)
  : Object(json, parent)
{}

Munition::Munition(const Munition& object, Object* parent)
  : Object (object, parent)
{}

Munition::~Munition()
{}

Munition*
Munition::New(Object* parent)
{
  static const QJsonObject munition
  {
    {"__GDW_RPG_Type__", JSON_TYPE},
    {PROP_TYPE, "[Type]"}
  };

  return new Munition(munition, parent);
}

Munition*
Munition::Copy(Object* parent)
{
  return new Munition(*this, parent);
}

const Munition*
Munition::Copy(Object* parent) const
{
  return new Munition(*this, parent);
}

QList<QVariant>
Munition::ItemData() const
{
  QList<QVariant> data = {
    Type()
  };

  return data;
}

void
Munition::ToVariantHash(QVariantHash& hash) const
{
  hash[PROP_TYPE]           = Type();
}


const QString Munition::PROP_TYPE = "type";

QVariant
Munition::Type() const
{
  return GetVariantFor(PROP_TYPE);
}

void
Munition::Type(const QVariant& value)
{
  SetVariantFor(PROP_TYPE, value);
}
