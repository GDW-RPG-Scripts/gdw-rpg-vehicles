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
      Object();
      Object(const Object&);
      virtual ~Object();


//      virtual void Read(const QJsonObject&);
//      virtual void Write(QJsonObject&) const;

      void Print(int indentation = 0) const;


    protected:
      Object(const QJsonObject&);

      QString GetStringFor(const QString&) const;
      void SetStringFor(const QString&, const QString&);
      double GetDoubleFor(const QString&) const;
      void SetDoubleFor(const QString&, double);

      QVariant GetVariantFor(const QString&) const;

    private:
      QJsonObject mJsonObject;

    };
  };
};

// Q_DECLARE_METATYPE(GDW::RPG::Object)

#endif // OBJECT_HH
