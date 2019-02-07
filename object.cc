#include "object.hh"

#include "exception.hh"


GDW::RPG::Object::~Object()
{}

GDW::RPG::Object::Object(const QJsonObject& json)
  : mJsonObject(json)
{}

void
GDW::RPG::Object::TypeCheck() const
{
  QString typeName = TypeName();

  if(!mJsonObject.contains(typeName) ||
     !mJsonObject[typeName].isBool() ||
     !mJsonObject[typeName].toBool())
  {
    throw InvalidTypeException();
  }
}

void
GDW::RPG::Object::Read(const QJsonObject& json)
{
  mJsonObject = json;

  TypeCheck();
}

void
GDW::RPG::Object::Write(QJsonObject& json) const
{
  json = mJsonObject;
}

void
GDW::RPG::Object::Print(int /*indentation*/) const
{}

QVariant
GDW::RPG::Object::GetVariantFor(const QString& index) const
{
  if(mJsonObject.contains(index))
    return mJsonObject[index];

  return QVariant();
}

QString
GDW::RPG::Object::GetStringFor(const QString& index) const
{
  if(!mJsonObject.isEmpty() &&
     mJsonObject.contains(index) &&
     mJsonObject[index].isString())
    return mJsonObject[index].toString();

  return "";
}

QString
GDW::RPG::Object::Name() const
{
  return GetStringFor("name");
}

void
GDW::RPG::Object::Name(const QString& name)
{
  mJsonObject["name"] = name;
}

QString
GDW::RPG::Object::Type() const
{
  return GetStringFor("typ");
}

void
GDW::RPG::Object::Type(const QString& type)
{
  mJsonObject["typ"] = type;
}

QString
GDW::RPG::Object::Nationality() const
{
  return GetStringFor("nat");
}

void
GDW::RPG::Object::Nationality(const QString& nationality)
{
  mJsonObject["nat"] = nationality;
}


