/*
**
**
*/

#include "weapon.hh"

#include <QJsonArray>


const QString
GDW::RPG::Weapon::JSON_TYPE = "__GDW_RPG_Weapon__";

QString
GDW::RPG::Weapon::TypeName() const
{
  return JSON_TYPE;
}

QList<GDW::RPG::Weapon*>
GDW::RPG::Weapon::Load(const QJsonValue& json)
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

GDW::RPG::Weapon::Weapon(const QJsonObject& json)
  : Object(json)
{}
