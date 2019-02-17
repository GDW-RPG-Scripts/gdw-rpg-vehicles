#include "objectform.hh"

#include "ui_vehicleform.h"
#include "ui_weaponform.h"

namespace GDW
{
  namespace RPG
  {
    ObjectForm::ObjectForm(QWidget* parent) :
      QWidget(parent)
    {}

    ObjectForm::~ObjectForm()
    {}

    VehicleForm::VehicleForm(QWidget* parent) :
      ObjectForm(parent),
      mUi(new Ui::VehicleForm)
    {
      mUi->setupUi(this);
    }

    VehicleForm::~VehicleForm()
    {
      delete mUi;
    }

    WeaponForm::WeaponForm(QWidget* parent) :
      ObjectForm(parent),
      mUi(new Ui::WeaponForm)
    {
      mUi->setupUi(this);
    }

    WeaponForm::~WeaponForm()
    {
      delete mUi;
    }
  };
};
