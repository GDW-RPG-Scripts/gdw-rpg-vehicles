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

#ifndef WEAPON_HH
#define WEAPON_HH

#include "weapon_global.hh"

#include "object.hh"

namespace GDW
{
  namespace RPG
  {
    class WEAPONSHARED_EXPORT Weapon : public Object
    {
        Q_OBJECT

      public:
        static QList<Weapon*> Load(const QJsonValue&,
                                   Object* = nullptr);

        Weapon(const QJsonObject& = QJsonObject(),
               Object* = nullptr);
        Weapon(const Weapon&, Object* = nullptr);
        ~Weapon() override;

        static Weapon* New();

        Weapon* Copy(Object* = nullptr) override;
        const Weapon* Copy(Object* = nullptr) const override;

        QList<QVariant> ItemData() const override;
        void ToVariantHash(QVariantHash&) const override;


        QVariant Wtyp() const;
        void Wtyp(const QVariant&);

        QVariant Wqual() const;
        void Wqual(const QVariant&);

        QVariant RateOfFire() const;
        void RateOfFire(const QVariant&);

        QVariant Range() const;
        void Range(const QVariant&);

        QVariant Ps() const;
        void Ps(const QVariant&);

        QVariant Pm() const;
        void Pm(const QVariant&);

        QVariant Pl() const;
        void Pl(const QVariant&);

        QVariant Px() const;
        void Px(const QVariant&);

        QVariant Ammo() const;
        void Ammo(const QVariant&);

        QVariant Concussion() const;
        void Concussion(const QVariant&);

        QVariant Burst(Mode = Mode::Display) const;
        void Burst(const QVariant&);

        QVariant Pran() const;
        void Pran(const QVariant&);

        QVariant Description() const;
        void Description(const QVariant&);

        QVariant SideViewImage() const;
        void SideViewImage(const QVariant&);

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
        static const QString PROP_DESCRIPTION;
        static const QString PROP_SIDEVIEW_IMG;

    };
  };
};

#endif // WEAPON_HH
