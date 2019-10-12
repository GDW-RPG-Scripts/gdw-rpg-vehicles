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

#ifndef SHIPTITEM_HH
#define SHIPTITEM_HH

#include "ship_global.hh"

#include "objectitem.hh"

#include "ship.hh"
#include "shipform.hh"
#include "shipmodel.hh"

extern void GDW_RPG_Ship_Initialize();

namespace GDW
{
  namespace RPG
  {
    class SHIPSHARED_EXPORT ShipItem : public ObjectItem
    {
        Q_OBJECT

      public:
        static ShipItem* Create(ObjectItem* parent = nullptr);
        static ShipItem* Unpack(const QJsonObject&,
                                    ObjectItem* parent);

        ShipForm* GetForm(QUndoStack*) override;

        ShipItem();

      protected:
        explicit ShipItem(Ship*, ObjectItem* parent = nullptr);

        Ship* GetObjectPtr() override;
        const Ship* GetObjectPtr() const override;

        ShipModel* Model() const override;

      private:
        static class Initialize {
          public:
            Initialize() { GDW_RPG_Ship_Initialize(); }
        } Initializer;
    };
  };
};

#endif // SHIPTITEM_HH
