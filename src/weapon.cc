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

namespace GDW
{
  namespace RPG
  {
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
        {"__GDW_RPG_Type__", JSON_TYPE},
        {PROP_WTYP, ""}, {PROP_WQUAL, ""},          {PROP_ROF, QJsonValue(QJsonValue::Double)}, {PROP_RNG,  QJsonValue(QJsonValue::Double)},
        {PROP_PS,  QJsonValue(QJsonValue::Double)}, {PROP_PM,  QJsonValue(QJsonValue::Double)}, {PROP_PL,   QJsonValue(QJsonValue::Double)}, {PROP_PX, QJsonValue(QJsonValue::Double)}, {PROP_AMMO, QJsonValue(QJsonValue::Double)},
        {PROP_CON, QJsonValue(QJsonValue::Double)}, {PROP_BUR, QJsonValue(QJsonValue::Double)}, {PROP_PRAN, QJsonValue(QJsonValue::Double)}
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
      QList<QVariant> data;

      data << Wtyp();
      //   << Range()
      //   << RateOfFire();

      return data;
    }


    const QString Weapon::PROP_WTYP = "wtyp";

    QString
    Weapon::Wtyp() const
    {
      return GetStringFor(PROP_WTYP);
    }

    void
    Weapon::Wtyp(const QString& value)
    {
      SetStringFor(PROP_WTYP, value);
    }

    const QString Weapon::PROP_WQUAL = "wqual";

    QString
    Weapon::Wqual() const
    {
      return GetStringFor(PROP_WQUAL);
    }

    void
    Weapon::Wqual(const QString& value)
    {
      SetStringFor(PROP_WQUAL, value);
    }

    const QString Weapon::PROP_ROF = "rof";

    double
    Weapon::Rof() const
    {
      return GetDoubleFor(PROP_ROF);
    }

    void
    Weapon::Rof(double value)
    {
      SetDoubleFor(PROP_ROF, value);
    }


    const QString Weapon::PROP_RNG = "rng";

    double
    Weapon::Rng() const
    {
      return GetDoubleFor(PROP_RNG);
    }

    void
    Weapon::Rng(double value)
    {
      SetDoubleFor(PROP_RNG, value);
    }


    const QString Weapon::PROP_PS = "ps";

    double
    Weapon::Ps() const
    {
      return GetDoubleFor(PROP_PS);
    }

    void
    Weapon::Ps(double value)
    {
      SetDoubleFor(PROP_PS, value);
    }


    const QString Weapon::PROP_PM = "pm";

    double
    Weapon::Pm() const
    {
      return GetDoubleFor(PROP_PM);
    }

    void
    Weapon::Pm(double value)
    {
      SetDoubleFor(PROP_PM, value);
    }


    const QString Weapon::PROP_PL = "pl";

    double
    Weapon::Pl() const
    {
      return GetDoubleFor(PROP_PL);
    }

    void
    Weapon::Pl(double value)
    {
      SetDoubleFor(PROP_PL, value);
    }


    const QString Weapon::PROP_PX = "px";

    double
    Weapon::Px() const
    {
      return GetDoubleFor(PROP_PX);
    }

    void
    Weapon::Px(double value)
    {
      SetDoubleFor(PROP_PX, value);
    }


    const QString Weapon::PROP_AMMO = "ammo";

    double
    Weapon::Ammo() const
    {
      return GetDoubleFor(PROP_AMMO);
    }

    void
    Weapon::Ammo(double value)
    {
      SetDoubleFor(PROP_AMMO, value);
    }


    const QString Weapon::PROP_CON = "con";

    double
    Weapon::Con() const
    {
      return GetDoubleFor(PROP_CON);
    }

    void
    Weapon::Con(double value)
    {
      SetDoubleFor(PROP_CON, value);
    }


    const QString Weapon::PROP_BUR = "bur";

    double
    Weapon::Bur() const
    {
      return GetDoubleFor(PROP_BUR);
    }

    void
    Weapon::Bur(double value)
    {
      SetDoubleFor(PROP_BUR, value);
    }


    const QString Weapon::PROP_PRAN = "pran";

    double
    Weapon::Pran() const
    {
      return GetDoubleFor(PROP_PRAN);
    }

    void
    Weapon::Pran(double value)
    {
      SetDoubleFor(PROP_PRAN, value);
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
  };
};
