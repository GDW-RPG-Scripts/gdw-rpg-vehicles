#ifndef UNIT_HH
#define UNIT_HH

#include "unit_global.hh"

#include "object.hh"

namespace GDW
{
  namespace RPG
  {
    class UNITSHARED_EXPORT Unit : public Object
    {

      public:
        Unit(const QJsonObject&);
        static Unit* New();


        QString Name() const;
        void Name(const QString&);

        static const QString JSON_TYPE;

      private:
        static const QString PROP_NAME;
    };
  };
};

#endif // UNIT_HH
