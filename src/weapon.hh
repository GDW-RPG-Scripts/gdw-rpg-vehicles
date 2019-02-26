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
        static Weapon* New();

        Weapon* Copy() override;
        const Weapon* Copy() const override;


        QString Wtyp() const;
        void Wtyp(const QString&);

        QString Wqual() const;
        void Wqual(const QString&);

        double Rof() const;
        void Rof(double);

        double Rng() const;
        void Rng(double);

        double Ps() const;
        void Ps(double);

        double Pm() const;
        void Pm(double);

        double Pl() const;
        void Pl(double);

        double Px() const;
        void Px(double);

        double Ammo() const;
        void Ammo(double);

        double Con() const;
        void Con(double);

        double Bur() const;
        void Bur(double);

        double Pran() const;
        void Pran(double);

        static const QString JSON_TYPE;

      private:
        static const QString PROP_WTYP;
        static const QString PROP_WQUAL;
        static const QString PROP_ROF;
        static const QString PROP_RNG;
        static const QString PROP_PS;
        static const QString PROP_PM;
        static const QString PROP_PL;
        static const QString PROP_PX;
        static const QString PROP_AMMO;
        static const QString PROP_CON;
        static const QString PROP_BUR;
        static const QString PROP_PRAN;

    };
  };
};

Q_DECLARE_METATYPE(GDW::RPG::Weapon)

#endif // WEAPON_HH
