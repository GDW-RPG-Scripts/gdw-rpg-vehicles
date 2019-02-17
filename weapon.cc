/*
**
**
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


    const QString Weapon::WTYPE = "wtyp";

    QString
    Weapon::Wtyp() const
    {
      return GetStringFor(WTYPE);
    }

    void
    Weapon::Wtyp(const QString& wtyp)
    {
      SetStringFor(WTYPE, wtyp);
    }

    const QString Weapon::WQUAL = "wqual";

    QString
    Weapon::Wqual() const
    {
      return GetStringFor(WQUAL);
    }

    void
    Weapon::Wqual(const QString& wqual)
    {
      SetStringFor(WQUAL, wqual);
    }

    const QString Weapon::RATE_OF_FIRE = "rof";

    double
    Weapon::RateOfFire() const
    {
      return GetDoubleFor(RATE_OF_FIRE);
    }

    void
    Weapon::RateOfFire(double rof)
    {
      SetDoubleFor(RATE_OF_FIRE, rof);
    }

    const QString Weapon::RANGE = "rng";

    double
    Weapon::Range() const
    {
      return GetDoubleFor(RANGE);
    }

    void
    Weapon::Range(double rng)
    {
      SetDoubleFor(RANGE, rng);
    }


    QList<Weapon*>
    Weapon::Load(const QJsonValue& json)
    {
      QList<Weapon*> result;

      if(json.isNull())
        {
          return result;
        }
      else if (json.isObject()) {
          result.append(new Weapon(json.toObject()));
        }
      else if (json.isArray()) {
          QJsonArray ja = json.toArray();
          for (int i = 0; i < ja.size(); ++i)
            {
              result.append(new Weapon(ja[i].toObject()));
            }
        }

      return result;
    }
  };
};
