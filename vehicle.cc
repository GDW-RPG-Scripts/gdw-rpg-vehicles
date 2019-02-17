#include "vehicle.hh"

namespace GDW
{
  namespace RPG
  {
    const QString
    Vehicle::JSON_TYPE = "__GDW_RPG_Vehicle__";

    Vehicle::Vehicle()
    {}

    Vehicle::Vehicle(const Vehicle& vehicle)
      : Object(vehicle)
    {}

    Vehicle::~Vehicle()
    {
      qDeleteAll(mWeapons);
    }

    Vehicle::Vehicle(const QJsonObject& json)
      : Object(json)
    {
      if(json.contains(WEAPONS))
        {
          mWeapons = Weapon::Load(json[WEAPONS]);
        }
    }


    const QString Vehicle::NAME = "name";

    QString
    Vehicle::Name() const
    {
      return GetStringFor(NAME);
    }

    void
    Vehicle::Name(const QString& name)
    {
      SetStringFor(NAME, name);
    }


    const QString Vehicle::TYPE = "typ";

    QString
    Vehicle::Type() const
    {
      return GetStringFor(TYPE);
    }

    void
    Vehicle::Type(const QString& type)
    {
      SetStringFor(TYPE, type);
    }


    const QString Vehicle::NATIONALITY = "nat";

    QString
    Vehicle::Nationality() const
    {
      return GetStringFor(NATIONALITY);
    }

    void
    Vehicle::Nationality(const QString& nationality)
    {
      SetStringFor(NATIONALITY, nationality);
    }


    const QString Vehicle::WEAPONS = "weap";

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
  };
};
