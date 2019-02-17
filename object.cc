#include "object.hh"

#include "exception.hh"


namespace GDW
{
  namespace RPG
  {
    Object::Object()
    {}

    Object::Object(const Object& object)
      : mJsonObject(object.mJsonObject)
    {}

    Object::~Object()
    {}

    Object::Object(const QJsonObject& json)
      : mJsonObject(json)
    {}

//    void
//    Object::Read(const QJsonObject& json)
//    {
//      mJsonObject = json;

//      TypeCheck();
//    }

//    void
//    Object::Write(QJsonObject& json) const
//    {
//      json = mJsonObject;
//    }

    void
    Object::Print(int /*indentation*/) const
    {}

    QVariant
    Object::GetVariantFor(const QString& index) const
    {
      static const QVariant INVALID;

      if(mJsonObject.contains(index))
        return mJsonObject[index];

      return INVALID;
    }

    QString
    Object::GetStringFor(const QString& index) const
    {
      if(!mJsonObject.isEmpty() &&
         mJsonObject.contains(index) &&
         mJsonObject[index].isString())
        return mJsonObject[index].toString();

      return "";
    }

    void
    Object::SetStringFor(const QString& index, const QString& value)
    {
      mJsonObject[index] = value;
    }

    double
    Object::GetDoubleFor(const QString& index) const
    {
      if(!mJsonObject.isEmpty() &&
         mJsonObject.contains(index) &&
         mJsonObject[index].isDouble())
        return mJsonObject[index].toDouble();

      return 0.0;
    }

    void
    Object::SetDoubleFor(const QString& index, double value)
    {
      mJsonObject[index] = value;
    }
  };
};
