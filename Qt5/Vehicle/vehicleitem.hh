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

#include <QList>
#include <QVariant>

class QStackedWidget;
class QTextStream;

namespace Ui {
  class Workspace;
}

namespace GDW
{
  namespace RPG
  {
    class VEHICLESHARED_EXPORT VehicleTreeItem : public ObjectTreeItem
    {
      public:
        static VehicleTreeItem* Create(ObjectTreeItem* parent = nullptr);
        static VehicleTreeItem* Unpack(const QJsonObject&,
                                       ObjectTreeItem* parent);

        VehicleForm* GetForm() override;
        // void Select(Ui::Workspace&, ObjectForm* = nullptr) override;

        QDebug& Debug(QDebug&) const override;

      protected:
        VehicleTreeItem(Vehicle*, ObjectTreeItem* parent);
        ~VehicleTreeItem() override;

        Vehicle* GetObject() override;
        const Vehicle* GetObject() const override;

        //      private:
        //        Vehicle* mVehicle;
    };
  };
};

#endif // VEHICLETREEITEM_HH
