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

#include "treeitem.hh"

#include "objectform.hh"

#include "vehicle.hh"
#include "weapon.hh"

#include "ui_mainwindow.h"

#include <QDebug>
#include <QGroupBox>
#include <QJsonArray>
#include <QJsonDocument>
#include <QStackedWidget>
#include <QVBoxLayout>

namespace GDW
{
  namespace RPG
  {
    ObjectTreeItem::ObjectTreeItem(QList<QVariant>& data, ObjectTreeItem* parent)
      : mItemData(data), mParentItem(parent)
    {}

    ObjectTreeItem::~ObjectTreeItem()
    {
      qDeleteAll(mChildItems);
    }

    ObjectTreeItem*
    ObjectTreeItem::AppendChild(ObjectTreeItem* item)
    {
      mChildItems.append(item);

      return item;
    }

    ObjectTreeItem*
    ObjectTreeItem::Child(int row)
    {
      return mChildItems.value(row);
    }

    int
    ObjectTreeItem::ChildCount() const
    {
      return mChildItems.count();
    }

    int
    ObjectTreeItem::ColumnCount() const
    {
      return mItemData.count();
    }

    QVariant
    ObjectTreeItem::Data(int column) const
    {
      return mItemData.value(column);
    }

    ObjectTreeItem*
    ObjectTreeItem::ParentItem()
    {
      return mParentItem;
    }

    int
    ObjectTreeItem::Row() const
    {
      if (mParentItem)
        return mParentItem->mChildItems.indexOf(const_cast<ObjectTreeItem*>(this));

      return 0;
    }

    typedef std::function<ObjectTreeItem*(const QJsonObject&, ObjectTreeItem*)> ObjectTreeUnpackFunction;
    typedef QHash<const QString, ObjectTreeUnpackFunction> ObjectTreeUnpackMap;

    ObjectTreeItem*
    ObjectTreeItem::Unpack(const QJsonValue& json, ObjectTreeItem* parent)
    {
      static const QString GDW_RPG_TYPE = "__GDW_RPG_Type__";
      static const ObjectTreeUnpackMap OBJECT_TREE_UNPACK_MAP =
      {
        { Vehicle::JSON_TYPE, VehicleTreeItem::Unpack },
        {  Weapon::JSON_TYPE,  WeaponTreeItem::Unpack }
      };

      if(json.isObject())
      {
        QJsonObject obj = json.toObject();
        if (obj.contains(GDW_RPG_TYPE) && obj[GDW_RPG_TYPE].isString())
        {
          const QString type = obj[GDW_RPG_TYPE].toString();

          if(OBJECT_TREE_UNPACK_MAP.contains(type))
          {
            ObjectTreeUnpackFunction unpack = OBJECT_TREE_UNPACK_MAP[type];
            ObjectTreeItem* item = unpack(obj, parent);

            return parent->AppendChild(item);
          }
        }
      }

      return nullptr;
    }

    QTextStream&
    operator<<(QTextStream& ots, const ObjectTreeItem& item)
    {
      QJsonArray jarr;

      for (int i = 0; i < item.mChildItems.size(); ++i) {
        Object* obj = item.mChildItems.at(i)->GetObject();
        QJsonValue jv(*obj);
        jarr.append(jv);
      }

      QJsonDocument jdoc(jarr);
      return ots << jdoc.toJson(QJsonDocument::Compact);
    }

    void
    ObjectTreeItem::Select(Ui::MainWindow* mainWindow, ObjectForm* objectForm)
    {
      QGroupBox* objectGroupBox = mainWindow->objectGroupBox;
      QLayout* layout = objectGroupBox->layout();

      if(layout != nullptr) {
        QLayoutItem* child;
        while ((child = layout->takeAt(0)) != nullptr)  {
          QWidget* widget = child->widget();
          if(widget != nullptr)
            widget->hide();
        }
        delete layout;
      }

      mainWindow->objectForm = objectForm;

      QVBoxLayout* verticalLayout = new QVBoxLayout(objectGroupBox);
      objectForm->setParent(objectGroupBox);
      objectForm->setObjectName(QString::fromUtf8("objectWidget"));

      verticalLayout->addWidget(objectForm);
      verticalLayout->addItem(mainWindow->objectButtonsLayout);

      objectGroupBox->setTitle(objectForm->Title() + ": "); // + mWeapon->Wtyp());
      objectGroupBox->setLayout(verticalLayout);
      objectGroupBox->update();
    }

    void
    ObjectTreeItem::Edit()
    {}

    Object*
    ObjectTreeItem::GetObject()
    {
      return nullptr;
    }

    const Object*
    ObjectTreeItem::GetObject() const
    {
      return nullptr;
    }

    QDebug&
    operator<<(QDebug& debug, const ObjectTreeItem& item)
    {
      return item.Debug(debug);
    }

    QDebug&
    ObjectTreeItem::Debug(QDebug& debug) const
    {
      return debug;
    }


    /*
     * Vehicle
     */
    VehicleTreeItem*
    VehicleTreeItem::Unpack(const QJsonObject& json, ObjectTreeItem* parent)
    {
      Vehicle* vehicle = new Vehicle(json);

      QList<QVariant> vehicleData;

      vehicleData << vehicle->Name()
                  << vehicle->Type()
                  << vehicle->Nationality();

      VehicleTreeItem* vti = new VehicleTreeItem(vehicleData, parent, vehicle);

      QList<Weapon*> weapons = vehicle->Weapons();
      for (int i = 0; i < weapons.size(); ++i)
      {
        QList<QVariant> weaponData;

        weaponData << weapons[i]->Wtyp();
        // << weapons[i]->Range()
        // << weapons[i]->RateOfFire();

        vti->AppendChild(new WeaponTreeItem(weaponData, vti, weapons[i]));
      }

      return vti;
    }

    VehicleTreeItem::VehicleTreeItem(QList<QVariant>& data, ObjectTreeItem* parent, Vehicle* vehicle) //, const QFontMetrics& fontMetrics)
      : ObjectTreeItem(data, parent), mVehicle(vehicle)
    {}

    VehicleTreeItem::~VehicleTreeItem()
    {}

    void
    VehicleTreeItem::Select(Ui::MainWindow* mainWindow, ObjectForm*)
    {
      ObjectTreeItem::Select(mainWindow, new VehicleForm(mVehicle));
    }

    Object*
    VehicleTreeItem::GetObject()
    {
      return mVehicle;
    }

    const Object*
    VehicleTreeItem::GetObject() const
    {
      return mVehicle;
    }

    QDebug&
    VehicleTreeItem::Debug(QDebug& debug) const
    {
      debug.nospace() << "Vehicle: ";

      return debug;
    }


    /*
     * Weapon
     */
    WeaponTreeItem*
    WeaponTreeItem::Unpack(const QJsonObject& json, ObjectTreeItem* parent)
    {
      Weapon* weapon = new Weapon(json);

      QList<QVariant> data;

      data << weapon->Wtyp();
      // << weapon->Range()
      // << weapon->RateOfFire();

      WeaponTreeItem* wti = new WeaponTreeItem(data, parent, weapon);

      return wti;
    }

    WeaponTreeItem::WeaponTreeItem(QList<QVariant>& data, ObjectTreeItem* parent, Weapon* weapon) //, const QFontMetrics& fontMetrics)
      : ObjectTreeItem(data, parent), mWeapon(weapon)
    {}

    WeaponTreeItem::~WeaponTreeItem()
    {}

    void
    WeaponTreeItem::Select(Ui::MainWindow* mainWindow, ObjectForm*)
    {
      ObjectTreeItem::Select(mainWindow, new WeaponForm(mWeapon));
    }

    Object*
    WeaponTreeItem::GetObject()
    {
      return mWeapon;
    }

    const Object*
    WeaponTreeItem::GetObject() const
    {
      return mWeapon;
    }

    QDebug&
    WeaponTreeItem::Debug(QDebug& debug) const
    {
      debug.nospace() << "Weapon: ";

      return debug;
    }
  };
};
