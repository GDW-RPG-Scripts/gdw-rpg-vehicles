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
