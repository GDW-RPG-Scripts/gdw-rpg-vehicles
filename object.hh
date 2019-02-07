#ifndef OBJECT_HH
#define OBJECT_HH


#include <QJsonObject>
#include <QVariant>

namespace GDW
{
  namespace RPG
  {
    class Object
    {
    public:
      virtual ~Object();

      QString Name() const;
      void Name(const QString&);

      QString Type() const;
      void Type(const QString&);

      QString Nationality() const;
      void Nationality(const QString&);


      virtual void Read(const QJsonObject&);
      virtual void Write(QJsonObject&) const;

      void Print(int indentation = 0) const;


    protected:
      Object(const QJsonObject&);

      virtual QString TypeName() const = 0;

      QString GetStringFor(const QString&) const;
      QVariant GetVariantFor(const QString&) const;


    private:
      void TypeCheck() const;

      QJsonObject mJsonObject;
    };
  };
};

#endif // OBJECT_HH
