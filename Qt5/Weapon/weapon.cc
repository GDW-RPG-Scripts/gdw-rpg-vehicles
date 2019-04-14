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

#include "weapon.hh"

#include <QJsonArray>

using namespace GDW::RPG;

const QString
Weapon::JSON_TYPE = "__GDW_RPG_Weapon__";

Weapon::Weapon()
{}

Weapon::Weapon(const Weapon& weapon)
  : Object(weapon)
{}

Weapon::~Weapon()
{}

Weapon::Weapon(const QJsonObject& json)
  : Object(json)
{}

Weapon*
Weapon::New()
{
  static const QJsonObject weapon
  {
    {"__GDW_RPG_Type__", JSON_TYPE} //,
    //    {PROP_WTYP, "[Type]"}, {PROP_WQUAL, ""},    {PROP_ROF, QJsonValue(QJsonValue::Double)}, {PROP_RNG,  QJsonValue(QJsonValue::Double)},
    //    {PROP_PS,  QJsonValue(QJsonValue::Double)}, {PROP_PM,  QJsonValue(QJsonValue::Double)}, {PROP_PL,   QJsonValue(QJsonValue::Double)}, {PROP_PX, QJsonValue(QJsonValue::Double)}, {PROP_AMMO, QJsonValue(QJsonValue::Double)},
    //    {PROP_CON, QJsonValue(QJsonValue::Double)}, {PROP_BUR, QJsonValue(QJsonValue::Double)}, {PROP_PRAN, QJsonValue(QJsonValue::Double)}
  };

  return new Weapon(weapon);
}

Weapon*
Weapon::Copy()
{
  return new Weapon(*this);
}

const Weapon*
Weapon::Copy() const
{
  return new Weapon(*this);
}

QList<QVariant>
Weapon::ItemData() const
{
  QList<QVariant> data = {
    Wtyp() //,
    // Rng(),
    // Rof()
  };

  return data;
}

void
Weapon::ToVariantHash(QVariantHash& hash) const
{
  bool ok;
  double value;

  hash[PROP_WTYP]  = Wtyp();
  hash[PROP_WQUAL] = Wqual();
  hash[PROP_ROF]   = Rof();
  hash[PROP_RNG]   = Rng();
  hash[PROP_PS]    = Ps();
  hash[PROP_PM]    = Pl();
  hash[PROP_PL]    = Pm();
  hash[PROP_PX]    = Px();
  hash[PROP_AMMO]  = Ammo();
  hash[PROP_CON]   = Con();
  hash[PROP_BUR]   = Bur();
  hash[PROP_PRAN]  = Pran();

  value = Rng().toDouble(&ok) / 2;
  if(ok)
    hash["short"]    = value;

  value = Rng().toDouble(&ok) * 2;
  if(ok)
    hash["long"]     = value;

  value = Rng().toDouble(&ok) * 4;
  if(ok)
    hash["extreme"]  = value;
}


const QString Weapon::PROP_WTYP = "wtyp";

QVariant
Weapon::Wtyp() const
{
  return GetVariantFor(PROP_WTYP);
}

void
Weapon::Wtyp(const QVariant& value)
{
  SetVariantFor(PROP_WTYP, value);
}

const QString Weapon::PROP_WQUAL = "wqual";

QVariant
Weapon::Wqual() const
{
  return GetVariantFor(PROP_WQUAL);
}

void
Weapon::Wqual(const QVariant& value)
{
  SetVariantFor(PROP_WQUAL, value);
}

const QString Weapon::PROP_ROF = "rof";

QVariant
Weapon::Rof() const
{
  return GetVariantFor(PROP_ROF);
}

void
Weapon::Rof(const QVariant& value)
{
  SetVariantFor(PROP_ROF, value);
}


const QString Weapon::PROP_RNG = "rng";

QVariant
Weapon::Rng() const
{
  return GetVariantFor(PROP_RNG);
}

void
Weapon::Rng(const QVariant& value)
{
  SetVariantFor(PROP_RNG, value);
}


const QString Weapon::PROP_PS = "ps";

QVariant
Weapon::Ps() const
{
  return GetVariantFor(PROP_PS);
}

void
Weapon::Ps(const QVariant& value)
{
  SetVariantFor(PROP_PS, value);
}


const QString Weapon::PROP_PM = "pm";

QVariant
Weapon::Pm() const
{
  return GetVariantFor(PROP_PM);
}

void
Weapon::Pm(const QVariant& value)
{
  SetVariantFor(PROP_PM, value);
}


const QString Weapon::PROP_PL = "pl";

QVariant
Weapon::Pl() const
{
  return GetVariantFor(PROP_PL);
}

void
Weapon::Pl(const QVariant& value)
{
  SetVariantFor(PROP_PL, value);
}


const QString Weapon::PROP_PX = "px";

QVariant
Weapon::Px() const
{
  return GetVariantFor(PROP_PX);
}

void
Weapon::Px(const QVariant& value)
{
  SetVariantFor(PROP_PX, value);
}


const QString Weapon::PROP_AMMO = "ammo";

QVariant
Weapon::Ammo() const
{
  return GetVariantFor(PROP_AMMO);
}

void
Weapon::Ammo(const QVariant& value)
{
  SetVariantFor(PROP_AMMO, value);
}


const QString Weapon::PROP_CON = "con";

QVariant
Weapon::Con() const
{
  return GetVariantFor(PROP_CON);
}

void
Weapon::Con(const QVariant& value)
{
  SetVariantFor(PROP_CON, value);
}


const QString Weapon::PROP_BUR = "bur";

QVariant
Weapon::Bur() const
{
  return GetVariantFor(PROP_BUR);
}

void
Weapon::Bur(const QVariant& value)
{
  SetVariantFor(PROP_BUR, value);
}


const QString Weapon::PROP_PRAN = "pran";

QVariant
Weapon::Pran() const
{
  return GetVariantFor(PROP_PRAN);
}

void
Weapon::Pran(const QVariant& value)
{
  SetVariantFor(PROP_PRAN, value);
}


QList<Weapon*>
Weapon::Load(const QJsonValue& json)
{
  QList<Weapon*> result;

  if(json.isNull()) {
    return result;
  } else if (json.isObject()) {
    result.append(new Weapon(json.toObject()));
  } else if (json.isArray()) {
    QJsonArray ja = json.toArray();
    for (int i = 0; i < ja.size(); ++i) {
      result.append(new Weapon(ja[i].toObject()));
    }
  }

  return result;
}
