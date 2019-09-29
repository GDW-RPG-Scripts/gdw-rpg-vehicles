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

#include "munitionform.hh"
#include "ui_munitionform.h"

#include "munition.hh"

using namespace GDW::RPG;

MunitionForm::MunitionForm(Munition* munition, QUndoStack* undoStack, QWidget *parent) :
  ObjectForm(parent, undoStack), mMunition(munition), mUi(new Ui::MunitionForm)
{
  mUi->setupUi(this);

  Read();
}

MunitionForm::~MunitionForm()
{
  delete mUi;
}

Munition*
MunitionForm::Read(Mode mode, Object* object)
{
  Munition* original = mMunition;

  if(object) {
    mMunition = static_cast<Munition*>(object);
  }

  ObjectForm::Read();

  mUi->munitionTypeLineEdit->setText(mMunition->   Type()    .toString());

  return original;
}

Munition*
MunitionForm::Write()
{
  Munition* original = mMunition->Copy();

  ObjectForm::Write();

  mMunition->       Type(mUi->munitionTypeLineEdit->text());

  SetReadOnly(true);

  return original;
}

void
MunitionForm::SetReadOnly(bool value)
{
  ObjectForm::SetReadOnly(value);

  mUi->munitionTypeLineEdit->setReadOnly(value);
}

QString
MunitionForm::Title() const
{
  return tr("Munition");
}

Munition*
MunitionForm::GetObject()
{
  return mMunition;
}

const Munition*
MunitionForm::GetObject() const
{
  return mMunition;
}
