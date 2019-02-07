/*
**
**
*/

#ifndef WEAPON_HH
#define WEAPON_HH

#include "object.hh"

namespace GDW
{
  namespace RPG
  {
    class Weapon : public Object
    {
    public:
      static QList<Weapon*> Load(const QJsonValue&);

      Weapon(const QJsonObject&);

    protected:
      virtual QString TypeName() const;

    private:
      static const QString JSON_TYPE;
    };
  };
};

#endif // WEAPON_HH
