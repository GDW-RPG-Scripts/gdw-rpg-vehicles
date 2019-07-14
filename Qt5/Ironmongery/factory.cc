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

ObjectItem*
Factory::Create(int type, ObjectItem* parent)
{
  typedef std::function<ObjectItem*(ObjectItem*)> CreateFunction;

  static const CreateFunction CREATE[] = {
    VehicleItem::Create,
    WeaponItem ::Create,
    ShipItem   ::Create,
    UnitItem   ::Create
  };

  return CREATE[type](parent);
}

// typedef std::function<ObjectTreeItem*(const QJsonObject&, ObjectTreeItem*)> ObjectTreeUnpackFunction;
// typedef QHash<const QString, UnpackFunction> UnpackMap;

typedef std::function<ObjectModel*()> ModelFunction;
typedef QHash<const QString, ModelFunction> ModelMap;

ObjectItem*
Factory::Unpack(const QJsonValue& json, ObjectItem*)
{
  static const QString GDW_RPG_TYPE = "__GDW_RPG_Type__";
  static const ModelMap MODEL = {
    { Vehicle::JSON_TYPE, VehicleModel::Model },
    { Weapon ::JSON_TYPE, WeaponModel ::Model },
    { Ship   ::JSON_TYPE, ShipModel   ::Model },
    { Unit   ::JSON_TYPE, UnitModel   ::Model }
  };

  if(json.isObject()) {
    QJsonObject obj = json.toObject();
    if (obj.contains(GDW_RPG_TYPE) && obj[GDW_RPG_TYPE].isString()) {
      const QString type = obj[GDW_RPG_TYPE].toString();

      if(MODEL.contains(type)) {
        ObjectModel* model = MODEL[type]();
        return model->Unpack(obj, model->RootItem());
      }
    }
  }

  return nullptr;
}

QTextStream&
GDW::RPG::operator<<(QTextStream& ots, const Factory&)
{
  static const ModelFunction MODEL[] = {
    VehicleModel::Model,
    WeaponModel ::Model,
    ShipModel   ::Model,
    UnitModel   ::Model
  };

  QJsonArray jarr;

  for(ModelFunction model: MODEL) {
    model()->Export(jarr);
  }

  return ots << QJsonDocument(jarr).toJson(QJsonDocument::Indented);
}
