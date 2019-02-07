/*
**
**
*/
#ifndef TREEITEM_HH
#define TREEITEM_HH

#include "vehicle.hh"
#include "weapon.hh"

#include <QList>
#include <QVariant>

namespace GDW
{
  namespace RPG
  {
    class ObjectTreeItem
    {
    public:
      explicit ObjectTreeItem(const QList<QVariant> &data, ObjectTreeItem *parentItem = 0);
      virtual ~ObjectTreeItem();
      virtual QVariant data(int column, int role) const;

      const QFontMetrics& FontMetrics() const;

    protected:
      ObjectTreeItem(Object*, int, const QFontMetrics&);

      virtual Object& GetObject();
      virtual const Object& GetObject() const;

    private:
      Object* mObject;
      QFontMetrics mFontMetrics;
    };

    class VehicleTreeItem : public ObjectTreeItem
    {
    public:
      static void Load(const QJsonDocument&, QTree*);

    protected:
      VehicleTreeItem(Vehicle*, const QFontMetrics&);

      virtual Vehicle& GetObject();
      virtual const Vehicle& GetObject() const;

    private:
      static const int TYPE;

      static void addVehicle(const QJsonObject&, QTree*);
    };

    class WeaponTreeItem : public ObjectTreeItem
    {
    public:
      WeaponTreeItem(Weapon*, const QFontMetrics&);

    protected:
      virtual Weapon& GetObject();
      virtual const Weapon& GetObject() const;

    private:
      static const int TYPE;
    };
  };
};

#endif // TREEITEM_HH
