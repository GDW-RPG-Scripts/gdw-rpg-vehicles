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

#include "object.hh"

#include "exception.hh"


using namespace GDW::RPG;

Object::Object()
{}

Object::Object(const Object& object)
  : mJsonObject(object.mJsonObject)
{}

Object::~Object()
{}

Object::Object(const QJsonObject& json)
  : mJsonObject(json)
{
  if(mJsonObject.isEmpty() ||
     !mJsonObject.contains(PROP_TECHLEVEL) ||
     !mJsonObject[PROP_TECHLEVEL].isDouble())
    mJsonObject.insert(PROP_TECHLEVEL, 0);
}

/*
     * Tech-level
     */
const QString Object::PROP_TECHLEVEL = "tl";

void
Object::TechLevel(double value)
{
  SetDoubleFor(PROP_TECHLEVEL, value);
}

double
Object::TechLevel() const
{
  return GetDoubleFor(PROP_TECHLEVEL);
}

Object*
Object::Copy()
{
  return nullptr;
}

const Object*
Object::Copy() const
{
  return nullptr;
}

QList<QVariant>
Object::ItemData() const
{
  return QList<QVariant>();
}

Object::operator const QJsonObject&() const
{
  return mJsonObject;
}

QVariantHash
Object::ToVariantHash() const
{
  return mJsonObject.toVariantHash();
}


QVariant
Object::GetVariantFor(const QString& index) const
{
  static const QVariant INVALID;

  if(mJsonObject.contains(index))
    return mJsonObject[index];

  return INVALID;
}

QString
Object::GetStringFor(const QString& index) const
{
  if(!mJsonObject.isEmpty() &&
     mJsonObject.contains(index) &&
     mJsonObject[index].isString())
    return mJsonObject[index].toString();

  return "";
}

void
Object::SetStringFor(const QString& index, const QString& value)
{
  mJsonObject[index] = value;
}

double
Object::GetDoubleFor(const QString& index) const
{
  if(!mJsonObject.isEmpty() &&
     mJsonObject.contains(index) &&
     mJsonObject[index].isDouble())
    return mJsonObject[index].toDouble();

  return 0;
}

void
Object::SetDoubleFor(const QString& index, double value)
{
  mJsonObject[index] = value;
}
