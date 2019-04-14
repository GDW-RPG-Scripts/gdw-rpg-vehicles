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

#include "objectform.hh"

// #include <QDebug>
// #include <QDoubleValidator>
#include <QHBoxLayout>
// #include <QIntValidator>
#include <QSvgWidget>

using namespace GDW::RPG;

ObjectForm::ObjectForm(QWidget* parent) :
  QWidget(parent), mReadOnly(true)
{}

ObjectForm::~ObjectForm()
{}

Object*
ObjectForm::Read(Mode, Object*)
{
  return nullptr;
}

Object*
ObjectForm::Write()
{
  return nullptr;
}

bool
ObjectForm::IsReadOnly() const
{
  return mReadOnly;
}

void
ObjectForm::SetReadOnly(bool value)
{
  mReadOnly = value;
}

QString
ObjectForm::Title() const
{
  return "";
}

Object*
ObjectForm::GetObject()
{
  return nullptr;
}

const Object*
ObjectForm::GetObject() const
{
  return nullptr;
}

void
ObjectForm::AddSvgFrame(const QVariant& name, QWidget* parent)
{
  QHBoxLayout* hbox = new QHBoxLayout(parent);
  hbox->setContentsMargins(2,2,2,2);
  QSvgWidget* svg =
      new QSvgWidget(":/images/" + name.toString() +".svg", parent); // + mWeapon->Wtyp() +
  hbox->addWidget(svg);
  parent->setLayout(hbox);
}
