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

#ifndef SHIPFORM_HH
#define SHIPFORM_HH

#include "ship_global.hh"

#include "objectform.hh"

#include "ship.hh"

namespace Ui {
  class ShipForm;
}

namespace GDW
{
  namespace RPG
  {
    class Ship;

    class SHIPSHARED_EXPORT ShipForm : public ObjectForm
    {
        Q_OBJECT

      public:
        explicit ShipForm(Ship* = nullptr, QUndoStack* = nullptr, QWidget* parent = nullptr);
        ~ShipForm();

        Ship* Read(Mode = Mode::Display, Object* = nullptr) override;
        Ship* Write() override;
        void SetReadOnly(bool) override;
        QString Title() const override;

        Ship* GetObject() override;
        const Ship* GetObject() const override;

      private:
        Ship* mShip;
        Ui::ShipForm *mUi;
    };
  };
};

#endif // SHIPFORM_HH
