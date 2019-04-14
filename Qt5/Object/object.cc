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

#include "mustache.hh"

#include <QtMath>
#include <QSettings>

#include <cmath>

using namespace GDW::RPG;

const int
Object::RANGE = 120;

const double
Object::STRIKER[RANGE] = {
  0.25,     0.50,     0.75,     1.00,     1.25,     1.50,
  1.75,     2.00,     2.25,     2.50,     2.75,     3.00,
  3.25,     3.54,     3.86,     4.20,     4.59,     5.00,
  5.54,     5.95,     6.48,     7.07,     7.71,     8.41,
  9.17,     10.00,    10.90,    11.90,    13.00,    14.10,
  15.40,    16.80,    18.30,    20.00,    21.80,    23.80,
  25.90,    28.30,    30.80,    33.60,    36.70,    40.00,
  43.60,    47.60,    51.90,    56.60,    61.70,    67.30,
  73.40,    80.00,    87.20,    95.10,    104.00,   113.00,
  123.00,   135.00,   147.00,   160.00,   174.00,   190.00,
  207.00,   226.00,   247.00,   269.00,   293.00,   320.00,
  349.00,   381.00,   415.00,   453.00,   494.00,   538.00,
  587.00,   640.00,   698.00,   761.00,   830.00,   905.00,
  987.00,   1080.00,  1170.00,  1280.00,  1400.00,  1520.00,
  1660.00,  1810.00,  1970.00,  2150.00,  2350.00,  2560.00,
  2790.00,  3040.00,  3320.00,  3620.00,  3950.00,  4310.00,
  4700.00,  5120.00,  5580.00,  6090.00,  6640.00,  7240.00,
  7900.00,  8610.00,  9360.00,  10200.00, 11200.00, 12200.00,
  13300.00, 14500.00, 15800.00, 17200.00, 18800.00, 20500.00,
  22300.00, 24400.00, 26600.00, 29000.00, 31600.00, 34400.00
};

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
  //  if(mJsonObject.isEmpty() ||
  //     !mJsonObject.contains(PROP_TECHLEVEL) ||
  //     !mJsonObject[PROP_TECHLEVEL].isDouble())
  //    mJsonObject.insert(PROP_TECHLEVEL, 0);
}

/*
 * Tech-level
 */
const QString Object::PROP_TECHLEVEL = "tl";

void
Object::TechLevel(const QVariant& variant)
{
  SetVariantFor(PROP_TECHLEVEL, variant);
}

QVariant
Object::TechLevel() const
{
  return mJsonObject[PROP_TECHLEVEL].toVariant();
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

void
Object::ToVariantHash(QVariantHash& hash) const
{
  hash[PROP_TECHLEVEL]   = GetVariantFor(PROP_TECHLEVEL);
}

Mustache::QtVariantContext*
Object::Context(const QVariantHash& hash) const
{
  return new Mustache::QtVariantContext(hash);
}


bool
Object::RemoveIfEmpty(const QString& property, const QVariant& variant)
{
  if(variant.isValid() && variant.toString().isEmpty()) {
    mJsonObject.remove(property);
    return true;
  }

  return false;
}

QVariant
Object::GetVariantFor(const QString& index) const
{
  return mJsonObject[index].toVariant();
}

void
Object::SetVariantFor(const QString& index, const QVariant& variant)
{
  if(!RemoveIfEmpty(index, variant)) {
    mJsonObject[index] = QJsonValue::fromVariant(variant);
  }
}

//    bool ok;
//    double number = variant.toDouble(&ok);
//    if(ok) {
//      SetDoubleFor(property, number);
//    }

//QString
//Object::GetStringFor(const QString& index) const
//{
//  if(!mJsonObject.isEmpty() &&
//     mJsonObject.contains(index) &&
//     mJsonObject[index].isString()) {
//    return mJsonObject[index].toString();
//  }
//  return "";
//}

//void
//Object::SetStringFor(const QString& index, const QString& value)
//{
//  mJsonObject[index] = value;
//}

QVariant
Object::GetDoubleFor(const QString& index,
                     std::function<double(double)> calculate) const
{
  QVariant result;

  bool ok;
  double value = GetVariantFor(index).toDouble(&ok);
  if(ok)
    result = calculate(value);

  return result;
}

void
Object::SetDoubleFor(const QString& index, QVariant variant,
                     std::function<double(double)> calculate)
{
  bool ok;
  double value = variant.toDouble(&ok);
  if(ok)
    SetVariantFor(index, calculate(value));
}

double
Object::ConvertFrom(double value) const
{
  QSettings settings;

  if(settings.value("ruleset", 0).toInt() == 1) {
    return STRIKER[qFloor(value)-1];
  }

  return value;
}

double
Object::Round(double value) const
{
  QSettings settings;

  if(settings.value("ruleset", 0).toInt() == 1) {
    for(int i = 0; i < RANGE; ++i) {
      if(STRIKER[i] > value) {
        value = i;
        break;
      }
    }
  } else if(value > 100) {
    value = std::round(value / 10) * 10;
  } else if (value > 50) {
    value = std::round(value / 5) * 5;
  } else if (value < 1) {
    value = 1;
  }

  return std::round(value);
}
