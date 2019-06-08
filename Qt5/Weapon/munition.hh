#ifndef MUNITION_HH
#define MUNITION_HH

#include "weapon_global.hh"

#include "object.hh"

namespace GDW
{
  namespace RPG
  {
    class WEAPONSHARED_EXPORT Munition : public Object
    {
      public:
        Munition();
        Munition(const Munition&);
        ~Munition() override;

        Munition(const QJsonObject&);

        static const QString JSON_TYPE;

      private:
    };
  };
};

#endif // MUNITION_HH
