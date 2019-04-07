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

#include "factory.hh"

#include "shipitem.hh"
#include "unititem.hh"
#include "vehicleitem.hh"
#include "weaponitem.hh"
#include "objectmodel.hh"

#include "ui_workspace.h"

#include <QFile>
#include <QJsonArray>
#include <QJsonDocument>
#include <QTextStream>

using namespace GDW::RPG;

Factory::Factory()
{}

void
Factory::Import(QFile& file)
{
  const QByteArray& jba = file.readAll();
  QJsonDocument jdoc = QJsonDocument::fromJson(jba);

  if (jdoc.isObject())
    Unpack(jdoc.object());
  else if (jdoc.isArray())
    for (int index = 0; index < jdoc.array().count(); ++index)
      Unpack(jdoc[index].toObject());
}

ObjectTreeItem*
Factory::Create(int type, ObjectTreeItem* parent)
{
  typedef std::function<ObjectTreeItem*(ObjectTreeItem*)> CreateFunction;

  static const CreateFunction CREATE[] = {
    VehicleTreeItem::Create,
    WeaponTreeItem ::Create,
    ShipTreeItem   ::Create,
    UnitTreeItem   ::Create
  };

  return CREATE[type](parent);
}

typedef std::function<ObjectTreeItem*(const QJsonObject&, ObjectTreeItem*)> ObjectTreeUnpackFunction;
typedef QHash<const QString, ObjectTreeUnpackFunction> ObjectTreeUnpackMap;

ObjectTreeItem*
Factory::Unpack(const QJsonValue& json, ObjectTreeItem* parent)
{
  static const QString GDW_RPG_TYPE = "__GDW_RPG_Type__";
  static const ObjectTreeUnpackMap UNPACK = {
    { Vehicle::JSON_TYPE, VehicleTreeItem::Unpack },
    { Weapon ::JSON_TYPE, WeaponTreeItem ::Unpack },
    { Ship   ::JSON_TYPE, ShipTreeItem   ::Unpack },
    { Unit   ::JSON_TYPE, UnitTreeItem   ::Unpack }
  };

  if(json.isObject()) {
    QJsonObject obj = json.toObject();
    if (obj.contains(GDW_RPG_TYPE) && obj[GDW_RPG_TYPE].isString()) {
      const QString type = obj[GDW_RPG_TYPE].toString();

      if(UNPACK.contains(type)) {
        return UNPACK[type](obj, parent);
      }
    }
  }

  return nullptr;
}

QTextStream&
GDW::RPG::operator<<(QTextStream& ots, const Factory& factory)
{
  typedef std::function<ObjectModel*()> ModelFunction;

  static const ModelFunction MODEL[] = {
    VehicleTreeItem::Model,
    WeaponTreeItem ::Model,
    ShipTreeItem   ::Model,
    UnitTreeItem   ::Model
  };

  QJsonArray jarr;

  for(ModelFunction model: MODEL) {
    model()->Export(jarr);
  }

  return ots << QJsonDocument(jarr).toJson(QJsonDocument::Compact);
}
