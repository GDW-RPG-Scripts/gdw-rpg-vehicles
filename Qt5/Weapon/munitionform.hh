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

#ifndef MUNITIONFORM_HH
#define MUNITIONFORM_HH

#include "weapon_global.hh"

#include "objectform.hh"

#include "munition.hh"

namespace Ui {
  class MunitionForm;
}

namespace GDW
{
  namespace RPG
  {
    class WEAPONSHARED_EXPORT MunitionForm : public ObjectForm
    {
        Q_OBJECT

      public:
        explicit MunitionForm(Munition* = nullptr, QUndoStack* = nullptr, QWidget *parent = nullptr);
        ~MunitionForm();

        Munition* Read(Mode = Mode::Display, Object* = nullptr) override;
        Munition* Write() override;
        void SetReadOnly(bool) override;
        QString Title() const override;

        Munition* GetObjectPtr() override;
        const Munition* GetObjectPtr() const override;

        Ui::MunitionForm* getUi() const;

      private:
        Munition* mMunition;
        Ui::MunitionForm* mUi;
    };
  };
};

#endif // MUNITIONFORM_HH
