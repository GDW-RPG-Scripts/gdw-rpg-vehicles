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

#ifndef UNITITEM_HH
#define UNITITEM_HH

#include "unit_global.hh"

#include "objectitem.hh"

#include "unit.hh"
#include "unitform.hh"
#include "unitmodel.hh"

extern void GDW_RPG_Unit_Initialize();

namespace GDW
{
  namespace RPG
  {
    class UNITSHARED_EXPORT UnitItem : public ObjectItem
    {
        Q_OBJECT

      public:
        static UnitItem* Create(ObjectItem* parent = nullptr);
        static UnitItem* Unpack(const QJsonObject&,
                                    ObjectItem* parent);

        UnitForm* GetForm(QUndoStack*) override;

        UnitItem();

      protected:
        explicit UnitItem(Unit*, ObjectItem* parent = nullptr);

        Unit* GetObjectPtr() override;
        const Unit* GetObjectPtr() const override;

        UnitModel* Model() const override;

      private:
        static class Initialize {
          public:
            Initialize() { GDW_RPG_Unit_Initialize(); }
        } Initializer;
    };
  };
};

// Q_DECLARE_METATYPE(GDW::RPG::UnitTreeItem)

#endif // UNITITEM_HH
