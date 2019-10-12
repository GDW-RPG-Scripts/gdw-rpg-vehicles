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

#ifndef VEHICLETREEITEM_HH
#define VEHICLETREEITEM_HH

#include "vehicle_global.hh"

#include "objectitem.hh"

#include "vehicle.hh"
#include "vehicleform.hh"
#include "vehiclemodel.hh"

extern void GDW_RPG_Vehicle_Initialize();

namespace GDW
{
  namespace RPG
  {
    class WeaponItem;

    class VEHICLESHARED_EXPORT VehicleItem : public ObjectItem
    {
        Q_OBJECT

      public:
        static VehicleItem* Create(ObjectItem* parent = nullptr);
        static VehicleItem* Unpack(const QJsonObject&, ObjectItem* parent);

        // bool InsertChild(ObjectTreeItem*, int = INT_MAX) override;

        VehicleForm* GetForm(QUndoStack*) override;
        QByteArray Template() const override;

      protected:
        explicit VehicleItem(Vehicle*, ObjectItem* parent);

        Vehicle* GetObjectPtr() override;
        const Vehicle* GetObjectPtr() const override;

        VehicleModel* Model() const override;

      private:
        static class Initialize {
          public:
            Initialize() { GDW_RPG_Vehicle_Initialize(); }
        } Initializer;
    };
  };
};

#endif // VEHICLETREEITEM_HH
