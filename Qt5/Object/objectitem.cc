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

#include "objectitem.hh"
#include "object.hh"
#include "objectform.hh"

#include "mustache.hh"

#include <QDebug>
#include <QGroupBox>
#include <QJsonArray>
#include <QJsonDocument>
#include <QPainter>
#include <QSettings>
#include <QStackedWidget>
#include <QSvgRenderer>
#include <QVBoxLayout>

using namespace GDW::RPG;

ObjectTreeItem::ObjectTreeItem(Object* object, ObjectTreeItem* parent)
  : mObject(object), mItemData(object->ItemData()), mParentItem(parent)
{}

ObjectTreeItem::ObjectTreeItem(const QList<QVariant>& data, ObjectTreeItem* parent)
  : mObject(nullptr), mItemData(data), mParentItem(parent)
{}

ObjectTreeItem::~ObjectTreeItem()
{
  if(mObject != nullptr)
    delete mObject;

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

bool
ObjectTreeItem::SetData(int column, const QVariant& value)
{
  if (column < 0 || column >= mItemData.size())
    return false;

  mItemData[column] = value;
  return true;
}

bool
ObjectTreeItem::InsertChildren(int position, int count, // int type,
                               ObjectTreeItem* item)
{
  if (position < 0 || position > mChildItems.size())
    return false;

  for (int row = 0; row < count; ++row) {
    mChildItems.insert(position, item);
  }

  return true;
}

bool
ObjectTreeItem::RemoveChildren(int position, int count)
{
  if (position < 0 || position + count > mChildItems.size())
    return false;

  for (int row = 0; row < count; ++row)
    delete mChildItems.takeAt(position);

  return true;
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

void
ObjectTreeItem::Export(QJsonArray& jarr) const
{
  for (int i = 0; i < mChildItems.size(); ++i) {
    Object* obj = mChildItems.at(i)->GetObject();
    QJsonValue jv(*obj);
    jarr.append(jv);
  }
}

QTextStream&
GDW::RPG::operator<<(QTextStream& ots, const ObjectTreeItem& item)
{
  QJsonArray jarr;

  item.Export(jarr);
  return ots << QJsonDocument(jarr).toJson(QJsonDocument::Compact);
}

ObjectForm*
ObjectTreeItem::GetForm()
{
  return nullptr;
}

void
ObjectTreeItem::RefreshItemData()
{
  if(mObject)
    mItemData = mObject->ItemData();
}

Object*
ObjectTreeItem::GetObject()
{
  return mObject;
}

const Object*
ObjectTreeItem::GetObject() const
{
  return mObject;
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

QByteArray
ObjectTreeItem::Template() const
{
  return "";
}

void
ObjectTreeItem::RenderPage(QPaintDevice& device) const
{
  QVariantHash map = GetObject()->ToVariantHash();

  Mustache::Renderer renderer;
  Mustache::QtVariantContext* context = GetObject()->Context(map);

  QXmlStreamReader reader(renderer.render(Template(), context));
  QSvgRenderer svg(&reader);
  QPainter painter(&device);

  svg.render(&painter);
}
