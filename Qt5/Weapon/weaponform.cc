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

WeaponForm::WeaponForm(Weapon* weapon, QUndoStack* undoStack, QWidget* parent)
  : ObjectForm(parent, undoStack), mWeapon(weapon), mUi(new Ui::WeaponForm)
{
  mUi->setupUi(this);

  //AddSvgFrame("WEP", mUi->svgFrame);
  Read();
}

WeaponForm::~WeaponForm()
{
  delete mUi;
}


Weapon*
WeaponForm::Read(Mode mode, Object* object)
{
  Weapon* original = mWeapon;

  if(object) {
    mWeapon = static_cast<Weapon*>(object);
  }

  ObjectForm::Read();

  mUi->techLevelLineEdit->setText(mWeapon-> TechLevel()    .toString());

  mUi->     wtypLineEdit->setText(mWeapon->      Wtyp()    .toString());
  mUi->    wqualLineEdit->setText(mWeapon->     Wqual()    .toString());
  mUi->      rofLineEdit->setText(mWeapon->RateOfFire()    .toString());
  mUi->      rngLineEdit->setText(mWeapon->     Range()    .toString());
  mUi->       psLineEdit->setText(mWeapon->        Ps()    .toString());
  mUi->       pmLineEdit->setText(mWeapon->        Pm()    .toString());
  mUi->       plLineEdit->setText(mWeapon->        Pl()    .toString());
  mUi->       pxLineEdit->setText(mWeapon->        Px()    .toString());
  mUi->     ammoLineEdit->setText(mWeapon->      Ammo()    .toString());
  mUi->      conLineEdit->setText(mWeapon->Concussion()    .toString());
  mUi->      burLineEdit->setText(mWeapon->     Burst(mode).toString());
  mUi->     pranLineEdit->setText(mWeapon->      Pran()    .toString());

  AddSvgFrame(mWeapon->SideViewImage(), mUi->svgFrame);

  return original;
}

Weapon*
WeaponForm::Write()
{
  Weapon* original = mWeapon->Copy();

  ObjectForm::Write();

  mWeapon-> TechLevel(mUi->  techLevelLineEdit->text());

  mWeapon->      Wtyp(mUi->       wtypLineEdit->text());
  mWeapon->     Wqual(mUi->      wqualLineEdit->text());
  mWeapon->RateOfFire(mUi->        rofLineEdit->text());
  mWeapon->     Range(mUi->        rngLineEdit->text());
  mWeapon->        Ps(mUi->         psLineEdit->text());
  mWeapon->        Pm(mUi->         pmLineEdit->text());
  mWeapon->        Pl(mUi->         plLineEdit->text());
  mWeapon->        Px(mUi->         pxLineEdit->text());
  mWeapon->      Ammo(mUi->       ammoLineEdit->text());
  mWeapon->Concussion(mUi->        conLineEdit->text());
  mWeapon->     Burst(mUi->        burLineEdit->text());
  mWeapon->      Pran(mUi->       pranLineEdit->text());

  SetReadOnly(true);

  return original;
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
