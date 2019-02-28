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

#ifndef VEHICLE_HH
#define VEHICLE_HH

#include "object.hh"
#include "weapon.hh"

#include <QList>
#include <QString>

namespace GDW
{
  namespace RPG
  {
    class Vehicle : public Object
    {
      public:

        Vehicle();
        Vehicle(const Vehicle&);
        ~Vehicle() override;

        Vehicle(const QJsonObject&);
        static Vehicle* New();

        Vehicle* Copy() override;
        const Vehicle* Copy() const override;

        QList<QVariant> ItemData() const override;


        QString Name() const;
        void Name(const QString&);

        QString Type() const;
        void Type(const QString&);

        QString Nationality() const;
        void Nationality(const QString&);

        double Trmov() const;
        void Trmov(double);

        double Ccmov() const;
        void Ccmov(double);

        double Fcap() const;
        void Fcap(double);

        double Fcons() const;
        void Fcons(double);

        QString Susp() const;
        void Susp(const QString&);

        double Tf() const;
        void Tf(double);

        double Ts() const;
        void Ts(double);

        double Tr() const;
        void Tr(double);

        double Hf() const;
        void Hf(double);

        double Hs() const;
        void Hs(double);

        double Hr() const;
        void Hr(double);

        QList<Weapon*> Weapons();
        void Weapons(QList<Weapon*>&);

        double Weight() const;
        void Weight(double);

        double Load() const;
        void Load(double);

        double Crew() const;
        void Crew(double);

        double Psgr() const;
        void Psgr(double);

        double Mnt() const;
        void Mnt(double);

        double Price() const;
        void Price(double);

        double Rf() const;
        void Rf(double);

        double Deck() const;
        void Deck(double);

        double Belly() const;
        void Belly(double);

        QString Stab() const;
        void Stab(const QString&);

        QString Fuel() const;
        void Fuel(const QString&);

        QString Night() const;
        void Night(const QString&);

        QString Rad() const;
        void Rad(const QString&);

        QString X5() const;
        void X5(const QString&);

        QString X6() const;
        void X6(const QString&);

        QString X7() const;
        void X7(const QString&);

        QString X8() const;
        void X8(const QString&);

        QString Loca() const;
        void Loca(const QString&);

        // virtual void Read(const QJsonObject&) override;

        static const QString JSON_TYPE;

      private:
        static const QString PROP_NAME;
        static const QString PROP_TYPE;
        static const QString PROP_NATIONALITY;
        static const QString PROP_TRMOV;
        static const QString PROP_CCMOV;
        static const QString PROP_FCAP;
        static const QString PROP_FCONS;
        static const QString PROP_SUSP;
        static const QString PROP_TF;
        static const QString PROP_TS;
        static const QString PROP_TR;
        static const QString PROP_HF;
        static const QString PROP_HS;
        static const QString PROP_HR;
        static const QString PROP_WEAPONS;
        static const QString PROP_WEIGHT;
        static const QString PROP_LOAD;
        static const QString PROP_CREW;
        static const QString PROP_PSGR;
        static const QString PROP_MNT;
        static const QString PROP_PRICE;
        static const QString PROP_RF;
        static const QString PROP_DECK;
        static const QString PROP_BELLY;
        static const QString PROP_STAB;
        static const QString PROP_FUEL;
        static const QString PROP_NIGHT;
        static const QString PROP_RAD;
        static const QString PROP_X5;
        static const QString PROP_X6;
        static const QString PROP_X7;
        static const QString PROP_X8;
        static const QString PROP_LOCA;

        QList<Weapon*> mWeapons;
    };
  };
};

Q_DECLARE_METATYPE(GDW::RPG::Vehicle)

#endif // VEHICLE_HH
