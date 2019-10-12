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
#include "objectitem.hh"
#include "object.hh"
#include "objectform.hh"
#include "objectmodel.hh"

#include "mustache.hh"

#include <QDebug>
#include <QGroupBox>
#include <QJsonArray>
#include <QJsonDocument>
#include <QPdfWriter>
#include <QPainter>
#include <QSettings>
#include <QStackedWidget>
#include <QSvgRenderer>
#include <QVBoxLayout>

void
GDW_RPG_Object_Initialize()
{
  Q_INIT_RESOURCE(object);
}

using namespace GDW::RPG;

ObjectItem::Initialize ObjectItem::Initializer;

ObjectItem::ObjectItem()
{}

ObjectItem::ObjectItem(Object* object, ObjectItem* parent)
  : QObject(parent),
    mObject(object), mItemData(object->ItemData())
{}

ObjectItem::ObjectItem(const QList<QVariant>& data, ObjectItem* parent)
  : QObject(parent), mObject(nullptr), mItemData(data)
{}

ObjectItem::ObjectItem(const ObjectItem& item)
  : QObject(item.parent()),
    mObject(item.mObject->Copy()), mItemData(item.mItemData)
{}

ObjectItem::~ObjectItem()
{
  //  if(mObject != nullptr)
  //    delete mObject;

  // qDeleteAll(mChildItems);
}

ObjectItem*
ObjectItem::Copy() const
{
  return nullptr;
}

ObjectItem*
ObjectItem::Child(int row)
{
  return mChildItems.value(row);
}

int
ObjectItem::ChildCount() const
{
  return mChildItems.count();
}

int
ObjectItem::ColumnCount() const
{
  return mItemData.count();
}

QVariant
ObjectItem::Data(int column) const
{
  return mItemData.value(column);
}

bool
ObjectItem::SetData(int column, const QVariant& variant)
{
  if (column < 0 || column > mItemData.size())
    return false;

  if(variant.canConvert<ObjectItem*>()) {
    ObjectItem* oti = variant.value<ObjectItem*>();
    mObject = oti->GetObjectPtr();
    mItemData = mObject->ItemData();
    return true;
  }

  return false;
}

bool
ObjectItem::InsertChild(ObjectItem* item, int position)
{
  if(item)
    item->setParent(this);

  mChildItems.insert(position, item);

  // Not necessary since the basic objects come with their
  // children already:
  if(mObject)
    mObject->InsertChild(item->GetObjectPtr(), position);

  return true;
}

ObjectItem*
ObjectItem::RemoveChild(int position)
{
  ObjectItem* item = nullptr;

  if(position >= 0 && position < mChildItems.size()) {
    item = mChildItems.takeAt(position);
    item->setParent(nullptr);

    if(mObject)
      mObject->RemoveChild(position);
  }

  return item;
}

ObjectItem*
ObjectItem::ParentItem() const
{
  return static_cast<ObjectItem*>(parent());
  //return qobject_cast<ObjectTreeItem*>(parent());
}

int
ObjectItem::Row() const
{
  ObjectItem* parent = ParentItem();

  if (parent)
    return parent->mChildItems.indexOf(const_cast<ObjectItem*>(this));

  return 0;
}

QModelIndex
ObjectItem::Index() const
{
  if(parent() == nullptr) {
    return QModelIndex();
  }

  return Model()->index(Row(), 0, ParentItem()->Index());
}

void
ObjectItem::Export(QJsonArray& jarr) const
{
  for (int i = 0; i < mChildItems.size(); ++i) {
    Object* obj = mChildItems.at(i)->GetObjectPtr();
    QJsonValue jv(*obj);
    jarr.append(jv);
  }
}

QTextStream&
GDW::RPG::operator<<(QTextStream& ots, const ObjectItem& item)
{
  QJsonArray jarr;

  item.Export(jarr);
  return ots << QJsonDocument(jarr).toJson(QJsonDocument::Compact);
}

ObjectForm*
ObjectItem::GetForm(QUndoStack*)
{
  return nullptr;
}

void
ObjectItem::RefreshItemData()
{
  if(mObject)
    mItemData = mObject->ItemData();
}

Object*
ObjectItem::GetObjectPtr()
{
  return mObject;
}

const Object*
ObjectItem::GetObjectPtr() const
{
  return mObject;
}

ObjectModel*
ObjectItem::Model() const
{
  return nullptr;
}

QByteArray
ObjectItem::Template() const
{
  return "";
}

QString
ObjectItem::RenderSvg() const
{
  QVariantHash hash;

  Ruleset::ToVariantHash(hash);
  GetObjectPtr()->ToVariantHash(hash);

  Mustache::Renderer renderer;
  Mustache::QtVariantContext* context = GetObjectPtr()->Context(hash);

  return renderer.render(Template(), context);
}

void
ObjectItem::RenderPage(QPaintDevice& device) const
{
  QXmlStreamReader reader(RenderSvg().toUtf8());
  QSvgRenderer svg(&reader);
  QPainter painter(&device);

  svg.render(&painter);
}

void
ObjectItem::WriteSvg(QFile& file) const
{
  file.write(RenderSvg().toUtf8());
}
