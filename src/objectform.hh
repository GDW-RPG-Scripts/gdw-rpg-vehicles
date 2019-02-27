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

#ifndef OBJECTFORM_HH
#define OBJECTFORM_HH

#include "vehicle.hh"
#include "weapon.hh"

#include <QWidget>

namespace Ui {
  class ObjectForm;
  class VehicleForm;
  class WeaponForm;
}

namespace GDW
{
  namespace RPG
  {
    class Object;
    class Vehicle;
    class Weapon;

    class ObjectForm : public QWidget
    {
        Q_OBJECT

      public:
        explicit ObjectForm(QWidget* parent = nullptr);
        virtual ~ObjectForm();

        virtual void Read();
        virtual void Write();
        virtual void SetReadOnly(bool);
        virtual QString Title() const;

        bool IsReadOnly() const;

        virtual Object* GetObject();
        virtual const Object* GetObject() const;

      protected:
        void AddSvgFrame(QString, QWidget*);

      private:
        bool mReadOnly;
    };

    class VehicleForm : public ObjectForm
    {
        Q_OBJECT

      public:
        explicit VehicleForm(Vehicle* = nullptr, QWidget* parent = nullptr);
        ~VehicleForm() override;

        void Read() override;
        void Write() override;
        void SetReadOnly(bool) override;
        QString Title() const override;

        Vehicle* GetObject() override;
        const Vehicle* GetObject() const override;

      private:
        Vehicle* mVehicle;
        Ui::VehicleForm* mUi;
    };

    class WeaponForm : public ObjectForm
    {
        Q_OBJECT

      public:
        explicit WeaponForm(Weapon* = nullptr, QWidget* parent = nullptr);
        ~WeaponForm() override;

        void Read() override;
        void Write() override;
        void SetReadOnly(bool) override;
        QString Title() const override;

        Weapon* GetObject() override;
        const Weapon* GetObject() const override;

      private:
        Weapon* mWeapon;
        Ui::WeaponForm* mUi;
    };
  };
};
#endif // OBJECTFORM_HH
