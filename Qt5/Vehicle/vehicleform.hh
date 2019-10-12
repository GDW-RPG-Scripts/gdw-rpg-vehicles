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

#ifndef VEHICLEFORM_HH
#define VEHICLEFORM_HH

#include "vehicle_global.hh"

#include "objectform.hh"

#include "vehicle.hh"

class QUndoStack;

namespace Ui {
  class VehicleForm;
}

namespace GDW
{
  namespace RPG
  {
    class VEHICLESHARED_EXPORT VehicleForm : public ObjectForm
    {
        Q_OBJECT

      public:
        explicit VehicleForm(Vehicle* = nullptr, QUndoStack* = nullptr, QWidget* parent = nullptr);
        ~VehicleForm() override;

        Vehicle* Read(Mode = Mode::Display, Object* = nullptr) override;
        Vehicle* Write() override;
        void SetReadOnly(bool) override;
        QString Title() const override;

        Vehicle* GetObjectPtr() override;
        const Vehicle* GetObjectPtr() const override;

      private slots:
        void ShowSideViewMenu(const QPoint&);
        void ShowTopDownMenu(const QPoint&);
        void SetTopDownImage();
        void SetSideViewImage();
        void ClearTopDownImage();
        void ClearSideViewImage();

      private:
        Vehicle* mVehicle;
        Ui::VehicleForm* mUi;
    };
  };
};
#endif // VEHICLEFORM_HH
