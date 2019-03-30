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

#include "prefsdialog.hh"
#include "workspace.hh"

#include <QtWidgets>

using namespace GDW::RPG;

PrefsDialog::PrefsDialog(Workspace* parent)
  : QDialog(parent), mRuleGroup(new QButtonGroup)
{
  QSettings settings;
  QVBoxLayout* dialogLayout = new QVBoxLayout;

  //
  QGroupBox* startBox = new QGroupBox(tr("Startup behavior") + ":", this);
  QVBoxLayout* startBoxLayout = new QVBoxLayout;

  QCheckBox* checkbox =
      new QCheckBox(tr("Load default database on startup") + ".", this);
  checkbox->setChecked(settings.value("loadOnStart", true).toBool());
  connect(checkbox, SIGNAL(stateChanged(int)), parent, SLOT(LoadOnStart(int)));

  startBoxLayout->addWidget(checkbox);
  startBox->setLayout(startBoxLayout);
  dialogLayout->addWidget(startBox);

  //
  QGroupBox* ruleBox = new QGroupBox(tr("Ruleset") + ":", this);
  QVBoxLayout* ruleBoxLayout = new QVBoxLayout;

  QList<QRadioButton*> ruleSet =
  {
    new QRadioButton(tr("Twilight 2000 (2.2) and TNE rules") + ".", this),
    new QRadioButton(tr("Striker I rules") + ".", this),
    new QRadioButton(tr("Actual armor equivalent in centimeters of steel (cm)") + ".", this),
    new QRadioButton(tr("Mongoose T2E vehicle rules") + ".", this),
    new QRadioButton(tr("Cepheus vehicle rules") + ".", this),
    new QRadioButton(tr("Armor calculator") + ".", this)
  };

  ruleSet[settings.value("ruleset", 0).toInt()]->setChecked(true);

  for(int i = 0; i < ruleSet.count(); ++i) {
    ruleBoxLayout->addWidget(ruleSet[i]);
    mRuleGroup->addButton(ruleSet[i], i);
  }
  connect(mRuleGroup, SIGNAL(buttonReleased(int)), parent, SLOT(RuleSet(int)));

  ruleBox->setLayout(ruleBoxLayout);
  dialogLayout->addWidget(ruleBox);

  QDialogButtonBox* buttonBox = new QDialogButtonBox(QDialogButtonBox::Ok, this);
  connect(buttonBox, &QDialogButtonBox::accepted, this, &QDialog::accept);
  dialogLayout->addWidget(buttonBox);

  setWindowTitle(tr("Preferences"));
  setLayout(dialogLayout);
}

PrefsDialog::~PrefsDialog()
{
  delete mRuleGroup;
}
