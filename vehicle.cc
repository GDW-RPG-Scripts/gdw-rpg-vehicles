#include "vehicle.hh"

const QString
GDW::RPG::Vehicle::JSON_TYPE = "__GDW_RPG_Vehicle__";

QString
GDW::RPG::Vehicle::TypeName() const
{
  return JSON_TYPE;
}

GDW::RPG::Vehicle::Vehicle(const QJsonObject& json)
  : Object(json)
{
  if(json.contains("weap"))
    {
      mWeapons = Weapon::Load(json["weap"]);
    }
}

void
GDW::RPG::Vehicle::Read(const QJsonObject& json)
{
  Object::Read(json);
}

QList<GDW::RPG::Weapon*>&
GDW::RPG::Vehicle::Weapons()
{
  return mWeapons;
}

void
GDW::RPG::Vehicle::Weapons(QList<GDW::RPG::Weapon*>& weapons)
{
  mWeapons = weapons;
}
