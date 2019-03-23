#include "unit.hh"


namespace GDW
{
  namespace RPG
  {
    const QString
    Unit::JSON_TYPE = "__GDW_RPG_Ship__";

    Unit::Unit(const QJsonObject& json)
      : Object (json)
    {}

    Unit*
    Unit::New()
    {
      static const QJsonObject object
      {
        {"__GDW_RPG_Type__", JSON_TYPE},
        {PROP_NAME, "[Name]"}
      };

      return new Unit(object);
    }


    const QString Unit::PROP_NAME = "name";

    QString
    Unit::Name() const
    {
      return GetStringFor(PROP_NAME);
    }

    void
    Unit::Name(const QString& value)
    {
      SetStringFor(PROP_NAME, value);
    }
  };
};
