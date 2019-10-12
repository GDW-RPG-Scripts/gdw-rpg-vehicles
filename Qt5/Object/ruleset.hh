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

#ifndef RULESET_HH
#define RULESET_HH

#include "object_global.hh"

#include <QCoreApplication>
#include <QMap>

namespace GDW
{
  namespace RPG
  {
    class OBJECTSHARED_EXPORT Ruleset
    {
        Q_DECLARE_TR_FUNCTIONS(Ruleset)

      public:
        static const QString T2K_TNE;
        static const QString STRIKER;
        static const QString ARMOR;
        static const QString MGT2;
        static const QString CEPHEUS;

        static QString Current();
        static void ToVariantHash(QVariantHash& hash);

        static const QMap<QString, QString> MAP;
    };
  };
};

#endif // RULESET_HH
