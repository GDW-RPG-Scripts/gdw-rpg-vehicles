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
    class VEHICLESHARED_EXPORT Vehicle : public Object
    {
        Q_OBJECT

      public:
        Vehicle(const QJsonObject& = QJsonObject(), Object* = nullptr);
        Vehicle(const Vehicle&, Object* = nullptr);
        ~Vehicle() override;

        static Vehicle* New(Object* = nullptr);

        Vehicle* Copy(Object* = nullptr) override;
        const Vehicle* Copy(Object* = nullptr) const override;

        void InsertChild(Object*, int = INT_MAX) override;
        Object* RemoveChild(int) override;

        QList<QVariant> ItemData() const override;
        void ToVariantHash(QVariantHash&) const override;
        Mustache::QtVariantContext* Context(const QVariantHash&) const override;
        void RefreshDependencies() override;


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

        void AddWeapon(Weapon*, int = INT_MAX);
        QList<Weapon*> Weapons() const;
        void Weapons(QList<Weapon*>&);

        QVariant Mass(Mode = Mode::Display) const;
        void Mass(const QVariant&);

        QVariant Load(Mode = Mode::Display) const;
        void Load(const QVariant&);

        QVariant Crew() const;
        void Crew(const QVariant&);

        QVariant Passengers() const;
        void Passengers(const QVariant&);

        QVariant Maintenance() const;
        void Maintenance(const QVariant&);

        QVariant Cost(Mode = Mode::Display) const;
        void Cost(const QVariant&);

        QVariant Rf() const;
        void Rf(const QVariant&);

        QVariant Deck(Mode = Mode::Display) const;
        void Deck(const QVariant&);

        QVariant Belly(Mode = Mode::Display) const;
        void Belly(const QVariant&);

        QVariant Stabilization() const;
        void Stabilization(const QVariant&);

        QVariant FuelTypes() const;
        void FuelTypes(const QVariant&);

        QVariant NightVision() const;
        void NightVision(const QVariant&);

        QVariant NBC() const;
        void NBC(const QVariant&);

        QVariant Skill() const;
        void Skill(const QVariant&);

        QVariant Agility() const;
        void Agility(const QVariant&);

        QVariant Hull() const;
        void Hull(const QVariant&);

        QVariant Structure() const;
        void Structure(const QVariant&);

        QVariant OpenClosed() const;
        void OpenClosed(const QVariant&);

        QVariant X8() const;
        void X8(const QVariant&);

        QVariant HitLocations() const;
        void HitLocations(const QVariant&);

        QVariant TopDownImage() const;
        void TopDownImage(const QVariant&);

        QVariant SideViewImage() const;
        void SideViewImage(const QVariant&);


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
        static const QString PROP_MASS;
        static const QString PROP_LOAD;
        static const QString PROP_CREW;
        static const QString PROP_PSGR;
        static const QString PROP_MNT;
        static const QString PROP_COST;
        static const QString PROP_RF;
        static const QString PROP_DECK;
        static const QString PROP_BELLY;
        static const QString PROP_STAB;
        static const QString PROP_FUEL;
        static const QString PROP_NIGHT;
        static const QString PROP_RAD;
        static const QString PROP_SKILL;
        static const QString PROP_AGILITY;
        static const QString PROP_HULL;
        static const QString PROP_STRUCTURE;
        static const QString PROP_OPENCLOSED;
        static const QString PROP_X8;
        static const QString PROP_LOCA;
        static const QString PROP_TOPDOWN_IMG;
        static const QString PROP_SIDEVIEW_IMG;

        qreal Divisor() const;

        QList<Weapon*> mWeapons;
    };
  };
};

// Q_DECLARE_METATYPE(GDW::RPG::Vehicle)

#endif // VEHICLE_HH
