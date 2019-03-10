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

#include "objectform.hh"

#include "vehicle.hh"
#include "weapon.hh"

#include "ui_vehicleform.h"
#include "ui_weaponform.h"

#include <QDebug>
#include <QDoubleValidator>
#include <QIntValidator>
#include <QSvgWidget>


namespace GDW
{
  namespace RPG
  {
    ObjectForm::ObjectForm(QWidget* parent) :
      QWidget(parent), mReadOnly(true)
    {}

    ObjectForm::~ObjectForm()
    {}

    void
    ObjectForm::Read()
    {}

    void
    ObjectForm::Write()
    {}

    bool
    ObjectForm::IsReadOnly() const
    {
      return mReadOnly;
    }

    void
    ObjectForm::SetReadOnly(bool value)
    {
      mReadOnly = value;
    }

    QString
    ObjectForm::Title() const
    {
      return "";
    }

    Object*
    ObjectForm::GetObject()
    {
      return nullptr;
    }

    const Object*
    ObjectForm::GetObject() const
    {
      return nullptr;
    }

    void
    ObjectForm::AddSvgFrame(QString name, QWidget* parent)
    {
      QHBoxLayout* hbox = new QHBoxLayout(parent);
      hbox->setContentsMargins(2,2,2,2);
      QSvgWidget* svg = new QSvgWidget(":/images/" + name +".svg", parent); // + mWeapon->Wtyp() +
      hbox->addWidget(svg);
      parent->setLayout(hbox);
    }


    /*
     * VehicleForm
     */
    VehicleForm::VehicleForm(Vehicle* vehicle, QWidget* parent) :
      ObjectForm(parent), mVehicle(vehicle), mUi(new Ui::VehicleForm)
    {
      mUi->setupUi(this);

      AddSvgFrame(mVehicle->Type(), mUi->svgFrame);
      Read();

      mUi->      trmovLineEdit->setValidator(new QIntValidator(0, 1000000, this));
    }

    VehicleForm::~VehicleForm()
    {
      delete mUi;
    }

    void
    VehicleForm::Read()
    {
      ObjectForm::Read();

      mUi->  techLevelLineEdit->setText(QString::number(mVehicle->TechLevel()));

      mUi->       nameLineEdit->setText(                mVehicle->Name());
      mUi->       typeLineEdit->setText(                mVehicle->Type());
      mUi->nationalityLineEdit->setText(                mVehicle->Nationality());
      mUi->      trmovLineEdit->setText(QString::number(mVehicle->Trmov()));
      mUi->      ccmovLineEdit->setText(QString::number(mVehicle->Ccmov()));
      mUi->       fcapLineEdit->setText(QString::number(mVehicle->Fcap()));
      mUi->      fconsLineEdit->setText(QString::number(mVehicle->Fcons()));
      mUi->       suspLineEdit->setText(                mVehicle->Susp());
      mUi->         tfLineEdit->setText(QString::number(mVehicle->Tf()));
      mUi->         tsLineEdit->setText(QString::number(mVehicle->Ts()));
      mUi->         trLineEdit->setText(QString::number(mVehicle->Tr()));
      mUi->         hfLineEdit->setText(QString::number(mVehicle->Hf()));
      mUi->         hsLineEdit->setText(QString::number(mVehicle->Hs()));
      mUi->         hrLineEdit->setText(QString::number(mVehicle->Hr()));
      mUi->     weightLineEdit->setText(QString::number(mVehicle->Weight()));
      mUi->       loadLineEdit->setText(QString::number(mVehicle->Load()));
      mUi->       crewLineEdit->setText(QString::number(mVehicle->Crew()));
      mUi->  passengerLineEdit->setText(QString::number(mVehicle->Psgr()));
      mUi->    mountedLineEdit->setText(QString::number(mVehicle->Mnt()));
      mUi->      priceLineEdit->setText(QString::number(mVehicle->Price()));
      mUi->         rFLineEdit->setText(QString::number(mVehicle->Rf()));
      mUi->       deckLineEdit->setText(QString::number(mVehicle->Deck()));
      mUi->      bellyLineEdit->setText(QString::number(mVehicle->Belly()));
      mUi->       stabLineEdit->setText(                mVehicle->Stab());
      mUi->       fuelLineEdit->setText(                mVehicle->Fuel());
      mUi->      nightLineEdit->setText(                mVehicle->Night());
      mUi->        radLineEdit->setText(                mVehicle->Rad());
      mUi->         x5LineEdit->setText(                mVehicle->X5());
      mUi->         x6LineEdit->setText(                mVehicle->X6());
      mUi->         x7LineEdit->setText(                mVehicle->X7());
      mUi->         x8TextEdit->setPlainText(           mVehicle->X8());
      mUi->       locaLineEdit->setText(                mVehicle->Loca());
    }

    void
    VehicleForm::Write()
    {
      ObjectForm::Write();

      mVehicle->  TechLevel(mUi->  techLevelLineEdit->text().toDouble());

      mVehicle->       Name(mUi->       nameLineEdit->text());
      mVehicle->       Type(mUi->       typeLineEdit->text());
      mVehicle->Nationality(mUi->nationalityLineEdit->text());
      mVehicle->      Trmov(mUi->      trmovLineEdit->text().toDouble());
      mVehicle->      Ccmov(mUi->      ccmovLineEdit->text().toDouble());
      mVehicle->       Fcap(mUi->       fcapLineEdit->text().toDouble());
      mVehicle->      Fcons(mUi->      fconsLineEdit->text().toDouble());
      mVehicle->       Susp(mUi->       suspLineEdit->text());
      mVehicle->         Tf(mUi->         tfLineEdit->text().toDouble());
      mVehicle->         Ts(mUi->         tsLineEdit->text().toDouble());
      mVehicle->         Tr(mUi->         trLineEdit->text().toDouble());
      mVehicle->         Hf(mUi->         hfLineEdit->text().toDouble());
      mVehicle->         Hs(mUi->         hsLineEdit->text().toDouble());
      mVehicle->         Hr(mUi->         hrLineEdit->text().toDouble());
      mVehicle->     Weight(mUi->     weightLineEdit->text().toDouble());
      mVehicle->       Load(mUi->       loadLineEdit->text().toDouble());
      mVehicle->       Crew(mUi->       crewLineEdit->text().toDouble());
      mVehicle->       Psgr(mUi->  passengerLineEdit->text().toDouble());
      mVehicle->        Mnt(mUi->    mountedLineEdit->text().toDouble());
      mVehicle->      Price(mUi->      priceLineEdit->text().toDouble());
      mVehicle->         Rf(mUi->         rFLineEdit->text().toDouble());
      mVehicle->       Deck(mUi->       deckLineEdit->text().toDouble());
      mVehicle->      Belly(mUi->      bellyLineEdit->text().toDouble());
      mVehicle->       Stab(mUi->       stabLineEdit->text());
      mVehicle->       Fuel(mUi->       fuelLineEdit->text());
      mVehicle->      Night(mUi->      nightLineEdit->text());
      mVehicle->        Rad(mUi->        radLineEdit->text());
      mVehicle->         X5(mUi->         x5LineEdit->text());
      mVehicle->         X6(mUi->         x6LineEdit->text());
      mVehicle->         X7(mUi->         x7LineEdit->text());
      mVehicle->          X8(mUi->        x8TextEdit->toPlainText());
      mVehicle->       Loca(mUi->       locaLineEdit->text());

      SetReadOnly(true);
    }

    void
    VehicleForm::SetReadOnly(bool value)
    {
      ObjectForm::SetReadOnly(value);

      mUi->  techLevelLineEdit->setReadOnly(value);

      mUi->       nameLineEdit->setReadOnly(value);
      mUi->       typeLineEdit->setReadOnly(value);
      mUi->nationalityLineEdit->setReadOnly(value);
      mUi->      trmovLineEdit->setReadOnly(value);
      mUi->      ccmovLineEdit->setReadOnly(value);
      mUi->       fcapLineEdit->setReadOnly(value);
      mUi->      fconsLineEdit->setReadOnly(value);
      mUi->       suspLineEdit->setReadOnly(value);
      mUi->         tfLineEdit->setReadOnly(value);
      mUi->         tsLineEdit->setReadOnly(value);
      mUi->         trLineEdit->setReadOnly(value);
      mUi->         hfLineEdit->setReadOnly(value);
      mUi->         hsLineEdit->setReadOnly(value);
      mUi->         hrLineEdit->setReadOnly(value);
      mUi->     weightLineEdit->setReadOnly(value);
      mUi->       loadLineEdit->setReadOnly(value);
      mUi->       crewLineEdit->setReadOnly(value);
      mUi->  passengerLineEdit->setReadOnly(value);
      mUi->    mountedLineEdit->setReadOnly(value);
      mUi->      priceLineEdit->setReadOnly(value);
      mUi->         rFLineEdit->setReadOnly(value);
      mUi->       deckLineEdit->setReadOnly(value);
      mUi->      bellyLineEdit->setReadOnly(value);
      mUi->       stabLineEdit->setReadOnly(value);
      mUi->       fuelLineEdit->setReadOnly(value);
      mUi->      nightLineEdit->setReadOnly(value);
      mUi->        radLineEdit->setReadOnly(value);
      mUi->         x5LineEdit->setReadOnly(value);
      mUi->         x6LineEdit->setReadOnly(value);
      mUi->         x7LineEdit->setReadOnly(value);
      mUi->         x8TextEdit->setReadOnly(value);
      mUi->       locaLineEdit->setReadOnly(value);
    }

    QString
    VehicleForm::Title() const
    {

      return tr("Vehicle");
    }

    Vehicle*
    VehicleForm::GetObject()
    {
      return mVehicle;
    }

    const Vehicle*
    VehicleForm::GetObject() const
    {
      return mVehicle;
    }


    /*
     * WepaonForm
     */
    WeaponForm::WeaponForm(Weapon* weapon, QWidget* parent) :
      ObjectForm(parent), mWeapon(weapon), mUi(new Ui::WeaponForm)
    {
      mUi->setupUi(this);

      AddSvgFrame("WEP", mUi->svgFrame);
      Read();
    }

    WeaponForm::~WeaponForm()
    {
      delete mUi;
    }


    void WeaponForm::Read()
    {
      ObjectForm::Read();

      mUi->techLevelLineEdit->setText(QString::number(mWeapon->TechLevel()));

      mUi->     wtypLineEdit->setText(                mWeapon->     Wtyp());
      mUi->    wqualLineEdit->setText(                mWeapon->    Wqual());
      mUi->      rofLineEdit->setText(QString::number(mWeapon->      Rof()));
      mUi->      rngLineEdit->setText(QString::number(mWeapon->      Rng()));
      mUi->       psLineEdit->setText(QString::number(mWeapon->       Ps()));
      mUi->       pmLineEdit->setText(QString::number(mWeapon->       Pm()));
      mUi->       plLineEdit->setText(QString::number(mWeapon->       Pl()));
      mUi->       pxLineEdit->setText(QString::number(mWeapon->       Px()));
      mUi->     ammoLineEdit->setText(QString::number(mWeapon->     Ammo()));
      mUi->      conLineEdit->setText(QString::number(mWeapon->      Con()));
      mUi->      burLineEdit->setText(QString::number(mWeapon->      Bur()));
      mUi->     pranLineEdit->setText(QString::number(mWeapon->     Pran()));
    }

    void
    WeaponForm::Write()
    {
      ObjectForm::Write();

      mWeapon->TechLevel(mUi->  techLevelLineEdit->text().toDouble());

      mWeapon->     Wtyp(mUi->       wtypLineEdit->text()           );
      mWeapon->    Wqual(mUi->      wqualLineEdit->text()           );
      mWeapon->      Rof(mUi->        rofLineEdit->text().toDouble());
      mWeapon->      Rng(mUi->        rngLineEdit->text().toDouble());
      mWeapon->       Ps(mUi->         psLineEdit->text().toDouble());
      mWeapon->       Pm(mUi->         pmLineEdit->text().toDouble());
      mWeapon->       Pl(mUi->         plLineEdit->text().toDouble());
      mWeapon->       Px(mUi->         pxLineEdit->text().toDouble());
      mWeapon->     Ammo(mUi->       ammoLineEdit->text().toDouble());
      mWeapon->      Con(mUi->        conLineEdit->text().toDouble());
      mWeapon->      Bur(mUi->        burLineEdit->text().toDouble());
      mWeapon->     Pran(mUi->       pranLineEdit->text().toDouble());

      SetReadOnly(true);
    }

    void
    WeaponForm::SetReadOnly(bool value)
    {
      ObjectForm::SetReadOnly(value);

      mUi->  techLevelLineEdit->setReadOnly(value);

      mUi->       wtypLineEdit->setReadOnly(value);
      mUi->      wqualLineEdit->setReadOnly(value);
      mUi->        rofLineEdit->setReadOnly(value);
      mUi->        rngLineEdit->setReadOnly(value);
      mUi->         psLineEdit->setReadOnly(value);
      mUi->         pmLineEdit->setReadOnly(value);
      mUi->         plLineEdit->setReadOnly(value);
      mUi->         pxLineEdit->setReadOnly(value);
      mUi->       ammoLineEdit->setReadOnly(value);
      mUi->        conLineEdit->setReadOnly(value);
      mUi->        burLineEdit->setReadOnly(value);
      mUi->       pranLineEdit->setReadOnly(value);
    }

    QString
    WeaponForm::Title() const
    {
      return tr("Weapon");
    }

    Weapon*
    WeaponForm::GetObject()
    {
      return mWeapon;
    }

    const Weapon*
    WeaponForm::GetObject() const
    {
      return mWeapon;
    }
  };
};
