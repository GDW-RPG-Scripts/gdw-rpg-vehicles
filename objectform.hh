#ifndef OBJECTFORM_HH
#define OBJECTFORM_HH

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
    class ObjectForm : public QWidget
    {
        Q_OBJECT

      public:
        explicit ObjectForm(QWidget* parent = nullptr);
        ~ObjectForm();
    };

    class VehicleForm : public ObjectForm
    {
        Q_OBJECT

      public:
        explicit VehicleForm(QWidget* parent = nullptr);
        ~VehicleForm();

      private:
        Ui::VehicleForm* mUi;
    };

    class WeaponForm : public ObjectForm
    {
        Q_OBJECT

      public:
        explicit WeaponForm(QWidget* parent = nullptr);
        ~WeaponForm();

      private:
        Ui::WeaponForm* mUi;
    };
  };
};
#endif // OBJECTFORM_HH
