/*
**
**
*/

#include "treeitem.hh"

#include "ui_mainwindow.h"
#include "ui_vehicleform.h"
#include "ui_weaponform.h"

#include "vehicle.hh"
#include "weapon.hh"

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

    ObjectTreeItem*
    ObjectTreeItem::Unpack(const QJsonValue& json, ObjectTreeItem* parent)
    {
      static const QString GDW_RPG_TYPE = "__GDW_RPG_Type__";
      static const QHash<const QString,std::function<ObjectTreeItem*(const QJsonObject&,ObjectTreeItem*)> >
          TYPE_MAP({{Vehicle::JSON_TYPE, VehicleTreeItem::Unpack},
                    {Weapon::JSON_TYPE, WeaponTreeItem::Unpack}
                   });

      if(json.isObject())
      {
        QJsonObject obj = json.toObject();
        if (obj.contains(GDW_RPG_TYPE) && obj[GDW_RPG_TYPE].isString()) {
          const QString type = obj[GDW_RPG_TYPE].toString();
          if(TYPE_MAP.contains(type)) {
            std::function<ObjectTreeItem*(const QJsonObject&,ObjectTreeItem*)>
                fn = TYPE_MAP[type];
            ObjectTreeItem* item = fn(obj, parent);
            parent->AppendChild(item);
          }
        }
      }

      return nullptr;
    }

    void
    ObjectTreeItem::Display(Ui::MainWindow*)
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
     *
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

        weaponData << weapons[i]->Wtyp()
                   << weapons[i]->Range()
                   << weapons[i]->RateOfFire();

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
    VehicleTreeItem::Display(Ui::MainWindow* mainWindow)
    {
      qDebug() << "VehicleTreeItem::Display(Ui::MainWindow* " << hex << &mainWindow << ")";

      QWidget* wrapper = new QWidget;
      Ui::VehicleForm* ui = new Ui::VehicleForm;
      ui->setupUi(wrapper);

      ui->nameLineEdit->setText(mVehicle->Name());
      ui->typeLineEdit->setText(mVehicle->Type());
      ui->nationalityLineEdit->setText(mVehicle->Nationality());

      QVBoxLayout* hbox = new QVBoxLayout;
      hbox->addWidget(wrapper);
      // hbox->addStretch(1);

      QGroupBox* widget = mainWindow->objectWidget;
      QLayout* layout = widget->layout();
      if(layout != nullptr) {
        delete layout;
      }

      widget->setTitle("Vehicle: " + mVehicle->Name());
      widget->setLayout(hbox);
      widget->update();
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
     *
     */
    WeaponTreeItem*
    WeaponTreeItem::Unpack(const QJsonObject& json, ObjectTreeItem* parent)
    {
      Weapon* weapon = new Weapon(json);

      QList<QVariant> data;

      data << weapon->Wtyp()
           << weapon->Range()
           << weapon->RateOfFire();

      WeaponTreeItem* wti = new WeaponTreeItem(data, parent, weapon);

      return wti;
    }

    WeaponTreeItem::WeaponTreeItem(QList<QVariant>& data, ObjectTreeItem* parent, Weapon* weapon) //, const QFontMetrics& fontMetrics)
      : ObjectTreeItem(data, parent), mWeapon(weapon)
    {}

    WeaponTreeItem::~WeaponTreeItem()
    {}

    void
    WeaponTreeItem::Display(Ui::MainWindow* mainWindow)
    {
      qDebug() << "WeaponTreeItem::Display(Ui::MainWindow* " << &mainWindow << ")";

      QWidget* wrapper = new QWidget;
      Ui::WeaponForm* ui = new Ui::WeaponForm;
      ui->setupUi(wrapper);

      ui->typeLineEdit->setText(mWeapon->Wtyp());

      QVBoxLayout* hbox = new QVBoxLayout;
      hbox->addWidget(wrapper);
      // hbox->addStretch(1);

      QGroupBox* widget = mainWindow->objectWidget;
      QLayout* layout = widget->layout();
      if(layout != nullptr) {
        delete layout;
      }

      widget->setTitle("Weapon: " + mWeapon->Wtyp());
      widget->setLayout(hbox);
      widget->update();
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
