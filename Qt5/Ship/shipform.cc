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

#include "shipform.hh"
#include "ui_shipform.h"

namespace GDW
{
  namespace RPG
  {
    ShipForm::ShipForm(Ship* ship, QWidget *parent)
      : ObjectForm(parent), mShip(ship), mUi(new Ui::ShipForm)
    {
      mUi->setupUi(this);

      Read();
    }

    ShipForm::~ShipForm()
    {
      delete mUi;
    }

    void
    ShipForm::Read()
    {
      ObjectForm::Read();
    }

    void
    ShipForm::Write()
    {
      ObjectForm::Write();

      SetReadOnly(true);
    }

    void
    ShipForm::SetReadOnly(bool value)
    {
      ObjectForm::SetReadOnly(value);
    }

    QString
    ShipForm::Title() const
    {

      return tr("Unit");
    }

    Ship*
    ShipForm::GetObject()
    {
      return mShip;
    }

    const Ship*
    ShipForm::GetObject() const
    {
      return mShip;
    }
  };
};
