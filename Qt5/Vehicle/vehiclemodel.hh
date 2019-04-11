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

#ifndef VEHICLEMODEL_HH
#define VEHICLEMODEL_HH

#include "vehicle_global.hh"

#include "objectmodel.hh"

namespace GDW
{
  namespace RPG
  {
    class VehicleTreeItem;

    class VEHICLESHARED_EXPORT VehicleModel : public ObjectModel
    {
        Q_OBJECT

      public:
        static VehicleModel* Model();

        ObjectTreeItem* Unpack(const QJsonObject& json,
                               ObjectTreeItem* parent) override;

      protected:
        ObjectTreeItem* Create(ObjectTreeItem*) const override;
        const QList<QVariant>& RootData() const override;

      private:
        VehicleModel(QObject* parent = nullptr);

        static VehicleModel MODEL;
    };
  };
};

#endif // VEHICLEMODEL_HH
