/*
**
**
*/

#include "treeitem.hh"

#include <QJsonArray>
#include <QJsonDocument>
#include <QDebug>

const int GDW::RPG::VehicleTreeItem::TYPE = 1001;
const int GDW::RPG::WeaponTreeItem::TYPE = 1002;

GDW::RPG::ObjectTreeItem::~ObjectTreeItem()
{
  delete mObject;
}

GDW::RPG::ObjectTreeItem::ObjectTreeItem(Object* object, int type, const QFontMetrics& fontMetrics)
  : mObject(object), mFontMetrics(fontMetrics)
{
  setChildIndicatorPolicy(DontShowIndicatorWhenChildless);
}

GDW::RPG::Object&
GDW::RPG::ObjectTreeItem::GetObject()
{
  return *mObject;
}

const GDW::RPG::Object&
GDW::RPG::ObjectTreeItem::GetObject() const
{
  return *mObject;
}

const QFontMetrics&
GDW::RPG::ObjectTreeItem::FontMetrics() const
{
  return mFontMetrics;
}

QVariant
GDW::RPG::ObjectTreeItem::data(int column, int role) const
{
  QString textArray[] = {
    mObject->Name(),
    mObject->Type(),
    mObject->Nationality()
  };
  QString text = textArray[column];

  QSize sizeHint = FontMetrics().boundingRect(text).size();

  QVariant result[] = {
    text,
    QVariant(),
    text,
    mObject->Name(),
    mObject->Name(),
    mObject->Name(),
    QVariant(),
    0x0101,
    QVariant(),
    QVariant(),
    QVariant(),
    text,
    text,
    sizeHint,
    0
  };

  qDebug() << "Object::data("
           << column
           << ", "
           << role
           << ") = "
           << sizeHint
           << ": "
           << result->toString();

  return result[role];
}

void
GDW::RPG::VehicleTreeItem::addVehicle(const QJsonObject& json, QTree* tree)
{
  GDW::RPG::Vehicle* v =
      new GDW::RPG::Vehicle(json);
  VehicleTreeItem* vtwi =
      new VehicleTreeItem(v, tree->fontMetrics());
  if(!v->Weapons().isEmpty()) {
      QMutableListIterator<GDW::RPG::Weapon*> qli(v->Weapons());
      while (qli.hasNext()) {
          WeaponTreeItem* wtwi = new WeaponTreeItem(qli.next(), tree->fontMetrics());
          vtwi->addChild(wtwi);
        }
    }
  tree->addTopLevelItem(vtwi);
}

void
GDW::RPG::VehicleTreeItem::Load(const QJsonDocument& jdoc, QTree* tree)
{
  if(jdoc.isNull())
    {
      return;
    }
  else if(jdoc.isObject())
    {
      addVehicle(jdoc.object(), tree);
    }
  else if (jdoc.isArray())
    {
      QJsonArray ja = jdoc.array();
      for (int i = 0; i < ja.size(); ++i)
        {
          addVehicle(ja[i].toObject(), tree);
        }
    }

  tree->setEnabled(true);
}

GDW::RPG::VehicleTreeItem::VehicleTreeItem(Vehicle* vehicle, const QFontMetrics& fontMetrics)
  : ObjectTreeItem(vehicle, TYPE, fontMetrics)
{}

GDW::RPG::Vehicle&
GDW::RPG::VehicleTreeItem::GetObject()
{
  return static_cast<GDW::RPG::Vehicle&>(ObjectTreeItem::GetObject());
}

const GDW::RPG::Vehicle&
GDW::RPG::VehicleTreeItem::GetObject() const
{
  return static_cast<const GDW::RPG::Vehicle&>(ObjectTreeItem::GetObject());
}

GDW::RPG::WeaponTreeItem::WeaponTreeItem(Weapon* weapon, const QFontMetrics& fontMetrics)
  : ObjectTreeItem(weapon, TYPE, fontMetrics)
{}

GDW::RPG::Weapon&
GDW::RPG::WeaponTreeItem::GetObject()
{
  return static_cast<GDW::RPG::Weapon&>(ObjectTreeItem::GetObject());
}

const GDW::RPG::Weapon&
GDW::RPG::WeaponTreeItem::GetObject() const
{
  return static_cast<const GDW::RPG::Weapon&>(ObjectTreeItem::GetObject());
}
