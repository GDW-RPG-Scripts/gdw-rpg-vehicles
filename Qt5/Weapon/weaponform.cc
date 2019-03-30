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

#include "weaponform.hh"
#include "weapon.hh"
#include "ui_weaponform.h"

using namespace GDW::RPG;

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
