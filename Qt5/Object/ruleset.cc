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

#include "ruleset.hh"

#include <QDebug>
#include <QSettings>

using namespace GDW::RPG;

const QString Ruleset::T2K_TNE ("t2k_tne");
const QString Ruleset::STRIKER ("striker");
const QString Ruleset::ARMOR   ("armor");
const QString Ruleset::MGT2    ("mgt2");
const QString Ruleset::CEPHEUS ("cepheus");

const QMap<QString, QString> Ruleset::MAP = {
  {T2K_TNE, QObject::tr("Twilight 2000 (2.2) and TNE")},
  {STRIKER, QObject::tr("Striker I")},
  {ARMOR,   QObject::tr("Armor equivalent (cm)")},
  {MGT2,    QObject::tr("Mongoose Traveller 2nd Ed.")},
  {CEPHEUS, QObject::tr("Cepheus Engine")}
};

QString
Ruleset::Current() {
  return QSettings().value("ruleset", T2K_TNE).toString();
}

void
Ruleset::ToVariantHash(QVariantHash& hash) {
  QString current = Current();

  hash["ruleset"] = MAP[current];

  QMap<QString, QString>::const_iterator i;
  for(i = MAP.cbegin(); i != MAP.cend(); ++i) {
    hash[i.key() + "?"] = i.key() == current;
  }
}
