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

#ifndef UNITFORM_HH
#define UNITFORM_HH

#include "unit_global.hh"

#include "objectform.hh"

#include "unit.hh"

namespace Ui {
  class UnitForm;
}

namespace GDW
{
  namespace RPG
  {
    class Unit;

    class UNITSHARED_EXPORT UnitForm : public ObjectForm
    {
        Q_OBJECT

      public:
        explicit UnitForm(Unit* = nullptr, QWidget *parent = nullptr);
        ~UnitForm() override;

        void Read() override;
        void Write() override;
        void SetReadOnly(bool) override;
        QString Title() const override;

        Unit* GetObject() override;
        const Unit* GetObject() const override;

      private:
        Unit* mUnit;
        Ui::UnitForm *mUi;
    };
  };
};
#endif // UNITFORM_HH
