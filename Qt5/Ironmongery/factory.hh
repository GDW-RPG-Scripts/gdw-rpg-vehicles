#ifndef FACTORY_HH
#define FACTORY_HH

class QJsonValue;

namespace GDW
{
  namespace RPG
  {
    class ObjectTreeItem;

    class Factory
    {
      public:
        static ObjectTreeItem* Create(int type, ObjectTreeItem* parent);
        static ObjectTreeItem* Unpack(const QJsonValue&,
                                      ObjectTreeItem* parent);
    };
  };
};

#endif // FACTORY_HH
