#ifndef SHIP_HH
#define SHIP_HH

#include "ship_global.hh"

#include "object.hh"

namespace GDW
{
  namespace RPG
  {
    class SHIPSHARED_EXPORT Ship : public Object
    {

      public:
        Ship(const QJsonObject&);
        static Ship* New();


        QString Name() const;
        void Name(const QString&);

        static const QString JSON_TYPE;

      private:
        static const QString PROP_NAME;
    };
  };
};

#endif // SHIP_HH
