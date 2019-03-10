#include "factory.hh"

#include "vehicleitem.hh"
#include "weaponitem.hh"

namespace GDW
{
  namespace RPG
  {
    typedef std::function<ObjectTreeItem*(ObjectTreeItem*)> ObjectTreeCreateFunction;

    ObjectTreeItem*
    Factory::Create(int type, ObjectTreeItem* parent)
    {
      static const ObjectTreeCreateFunction OBJECT_TREE_NEW[] =
      {
        VehicleTreeItem::Create,
        WeaponTreeItem::Create
      };

      ObjectTreeCreateFunction create = OBJECT_TREE_NEW[type];
      return create(parent);
    }

    typedef std::function<ObjectTreeItem*(const QJsonObject&, ObjectTreeItem*)> ObjectTreeUnpackFunction;
    typedef QHash<const QString, ObjectTreeUnpackFunction> ObjectTreeUnpackMap;

    ObjectTreeItem*
    Factory::Unpack(const QJsonValue& json, ObjectTreeItem* parent)
    {
      static const QString GDW_RPG_TYPE = "__GDW_RPG_Type__";
      static const ObjectTreeUnpackMap OBJECT_TREE_UNPACK_MAP =
      {
        { Vehicle::JSON_TYPE, VehicleTreeItem::Unpack },
        {  Weapon::JSON_TYPE,  WeaponTreeItem::Unpack }
      };

      if(json.isObject())
      {
        QJsonObject obj = json.toObject();
        if (obj.contains(GDW_RPG_TYPE) && obj[GDW_RPG_TYPE].isString())
        {
          const QString type = obj[GDW_RPG_TYPE].toString();

          if(OBJECT_TREE_UNPACK_MAP.contains(type))
          {
            ObjectTreeUnpackFunction unpack = OBJECT_TREE_UNPACK_MAP[type];
            ObjectTreeItem* item = unpack(obj, parent);

            return parent->AppendChild(item);
          }
        }
      }

      return nullptr;
    }
  };
};
