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

#ifndef MUNITION_HH
#define MUNITION_HH

#include "weapon_global.hh"

#include "object.hh"

namespace GDW
{
  namespace RPG
  {
    class Weapon;

    class WEAPONSHARED_EXPORT Munition : public Object
    {
      public:
        Munition(const QJsonObject& = QJsonObject(),
                 Object* = nullptr);
        Munition(const Munition&, Object* = nullptr);
        ~Munition() override;

        static Munition* New(Object* = nullptr);

        Munition* Copy(Object* = nullptr) override;
        const Munition* Copy(Object* = nullptr) const override;

        QList<QVariant> ItemData() const override;
        void ToVariantHash(QVariantHash&) const override;


        QVariant Type() const;
        void Type(const QVariant&);


        static const QString JSON_TYPE;

      private:
        static const QString PROP_TYPE;
    };
  };
};

#endif // MUNITION_HH
