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

#include "vehicle_global.hh"

#include "object.hh"
#include "weapon.hh"

#include <QList>
#include <QString>

namespace Mustache
{
  class QtVariantContext;
};

namespace GDW
{
  namespace RPG
  {
    class VEHICLESHARED_EXPORT VehicleReference : public ObjectReference
    {};

    class VEHICLESHARED_EXPORT Vehicle : public Object
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
        void ToVariantHash(QVariantHash&) const override;
        Mustache::QtVariantContext* Context(const QVariantHash&) const override;


        QVariant Name() const;
        void Name(const QVariant&);

        QVariant Type() const;
        void Type(const QVariant&);

        QVariant Nationality() const;
        void Nationality(const QVariant&);

        QVariant TravelMove() const;
        void TravelMove(const QVariant&);

        QVariant CombatMove() const;
        void CombatMove(const QVariant&);

        QVariant FuelCapacity() const;
        void FuelCapacity(const QVariant&);

        QVariant FuelConsumption() const;
        void FuelConsumption(const QVariant&);

        QVariant Suspension() const;
        void Suspension(const QVariant&);

        QVariant TurretFront() const;
        void TurretFront(const QVariant&);

        QVariant TurretSides() const;
        void TurretSides(const QVariant&);

        QVariant TurretRear() const;
        void TurretRear(const QVariant&);

        QVariant HullFront() const;
        void HullFront(const QVariant&);

        QVariant HullSides() const;
        void HullSides(const QVariant&);

        QVariant HullRear() const;
        void HullRear(const QVariant&);

        QList<Weapon*> Weapons() const;
        void Weapons(QList<Weapon*>&);

        QVariant Weight() const;
        void Weight(const QVariant&);

        QVariant Load() const;
        void Load(const QVariant&);

        QVariant Crew() const;
        void Crew(const QVariant&);

        QVariant Passengers() const;
        void Passengers(const QVariant&);

        QVariant Maintenance() const;
        void Maintenance(const QVariant&);

        QVariant Price() const;
        void Price(const QVariant&);

        QVariant Rf() const;
        void Rf(const QVariant&);

        QVariant Deck(Mode = Mode::Standard) const;
        void Deck(const QVariant&);

        QVariant Belly(Mode = Mode::Standard) const;
        void Belly(const QVariant&);

        QVariant Stabilization() const;
        void Stabilization(const QVariant&);

        QVariant FuelTypes() const;
        void FuelTypes(const QVariant&);

        QVariant NightVision() const;
        void NightVision(const QVariant&);

        QVariant NBC() const;
        void NBC(const QVariant&);

        QVariant X5() const;
        void X5(const QVariant&);

        QVariant X6() const;
        void X6(const QVariant&);

        QVariant X7() const;
        void X7(const QVariant&);

        QVariant X8() const;
        void X8(const QVariant&);

        QVariant HitLocations() const;
        void HitLocations(const QVariant&);

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

        qreal Divisor() const;

        QList<Weapon*> mWeapons;
    };
  };
};

// Q_DECLARE_METATYPE(GDW::RPG::Vehicle)

#endif // VEHICLE_HH
