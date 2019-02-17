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

      Weapon();
      Weapon(const Weapon&);
      ~Weapon() override;

      Weapon(const QJsonObject&);

      QString Wtyp() const;
      void Wtyp(const QString&);

      QString Wqual() const;
      void Wqual(const QString&);

      double RateOfFire() const;
      void RateOfFire(double);

      double Range() const;
      void Range(double);


      /*
"wtyp": "175 mm HEAT",
"wqual": "C",
"rof": 0.333,
"rng": 400,
"ps": 110,
"pm": 110,
"pl": 110,
"px": 110,
"ammo": 3,
"con": 24,
"bur": 30,
"pran": 0
*/

      static const QString JSON_TYPE;

    private:
      static const QString WTYPE;
      static const QString WQUAL;
      static const QString RATE_OF_FIRE;
      static const QString RANGE;

    };
  };
};

Q_DECLARE_METATYPE(GDW::RPG::Weapon)

#endif // WEAPON_HH
