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

#include "ruleset.hh"
#include "prefsdialog.hh"
#include "workspace.hh"

#include <QtWidgets>

using namespace GDW::RPG;

PrefsDialog::PrefsDialog(bool loadOnStart, const QString& ruleset, Workspace* parent)
  : QDialog(parent), mLoadOnStart(loadOnStart), mRuleset(ruleset),
    mRuleGroup(new QButtonGroup)
{
  QVBoxLayout* dialogLayout = new QVBoxLayout;

  //
  QGroupBox* startBox = new QGroupBox(tr("Startup behavior") + ":", this);
  QVBoxLayout* startBoxLayout = new QVBoxLayout;

  QCheckBox* checkbox =
      new QCheckBox(tr("Load default database on startup") + ".", this);
  checkbox->setChecked(mLoadOnStart);
  connect(checkbox, QOverload<int>::of(&QCheckBox::stateChanged),
          this, QOverload<bool>::of(&PrefsDialog::LoadOnStart));

  startBoxLayout->addWidget(checkbox);
  startBox->setLayout(startBoxLayout);
  dialogLayout->addWidget(startBox);

  //
  QGroupBox* ruleBox = new QGroupBox(tr("Ruleset") + ":", this);
  QVBoxLayout* ruleBoxLayout = new QVBoxLayout;

  QMap<QString, QRadioButton*> ruleSet;
  QMap<QString, QString>::const_iterator i;
  for (i = Ruleset::MAP.cbegin(); i != Ruleset::MAP.cend(); ++i) {
    uint hash = qHash(i.key());
    QRadioButton* button = new QRadioButton(i.value());
    if(i.key() == mRuleset)
      button->setChecked(true);
    ruleBoxLayout->addWidget(button);
    mRuleGroup->addButton(button, hash);
    ruleSet[i.key()] = button;
    mRuleMap[hash] = i.key();
  }

//  QList<QRadioButton*> ruleSet =
//  {
//    new QRadioButton(tr("Twilight 2000 (2.2) and TNE rules") + ".", this),
//    new QRadioButton(tr("Striker I rules") + ".", this),
//    new QRadioButton(tr("Actual armor equivalent in centimeters of steel (cm)") + ".", this),
//    new QRadioButton(tr("Mongoose T2E vehicle rules") + ".", this),
//    new QRadioButton(tr("Cepheus vehicle rules") + ".", this),
//    new QRadioButton(tr("Armor calculator") + ".", this)
//  };

//  ruleSet[mRuleset]->setChecked(true);

//  for(int i = 0; i < ruleSet.count(); ++i) {
//    ruleBoxLayout->addWidget(ruleSet[i]);
//    mRuleGroup->addButton(ruleSet[i], i);
//  }

  connect(mRuleGroup, QOverload<int>::of(&QButtonGroup::buttonClicked),
          this, QOverload<uint>::of(&PrefsDialog::Ruleset));

  ruleBox->setLayout(ruleBoxLayout);
  dialogLayout->addWidget(ruleBox);

  QDialogButtonBox* buttonBox =
      new QDialogButtonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel, this);
  connect(buttonBox, &QDialogButtonBox::accepted, this, &QDialog::accept);
  connect(buttonBox, &QDialogButtonBox::rejected, this, &QDialog::reject);
  dialogLayout->addWidget(buttonBox);

  setWindowTitle(tr("Preferences"));
  setLayout(dialogLayout);
}

PrefsDialog::~PrefsDialog()
{
  delete mRuleGroup;
}

QString
PrefsDialog::Ruleset() const
{
  return mRuleset;
}

void
PrefsDialog::Ruleset(uint ruleset)
{
  mRuleset = mRuleMap[ruleset];
}

void
PrefsDialog::Ruleset(const QString& ruleset)
{
  mRuleset = ruleset;
}

bool
PrefsDialog::LoadOnStart() const
{
  return mLoadOnStart;
}

void
PrefsDialog::LoadOnStart(bool loadOnStart)
{
  mLoadOnStart = loadOnStart;
}
