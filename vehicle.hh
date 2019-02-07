/*
**
**
*/

#ifndef VEHICLE_HH
#define VEHICLE_HH

#include "object.hh"
#include "weapon.hh"

#include <QList>
#include <QString>

namespace GDW
{
  namespace RPG
  {
    class Vehicle : public Object
    {
    public:
      Vehicle(const QJsonObject&);

      virtual void Read(const QJsonObject&);

      /*
  int trmov() const;
  void trmov(int);

  int ccmov() const;
  void ccmov(int);

  int fcap() const;
  void fcap(int);

  int fcons() const;
  void fcons(int);

  QString susp() const;
  void susp(const QString&);

  int tf() const;
  void tf(int);

  int ts() const;
  void ts(int);

  int tr() const;
  void tr(int);

  int hf() const;
  void hf(int);

  int hs() const;
  void hs(int);

  int hr() const;
  void hr(int);
  */
      QList<Weapon*>& Weapons();
      void Weapons(QList<Weapon*>&);
      /*
  int weight() const;
  void weight(int);

  qreal load() const;
  void load(qreal);

  int crew() const;
  void crew(int);

  int psgr() const;
  void psgr(int);

  int mnt() const;
  void mnt(int);

  int price() const;
  void price(int);

  int rf() const;
  void rf(int);

  int deck() const;
  void deck(int);

  int belly() const;
  void belly(int);

  QString stab() const;
  void stab(const QString&);

  QString fuel() const;
  void fuel(const QString&);

  QString night() const;
  void night(const QString&);

  QString rad() const;
  void rad(const QString&);

  QString x5() const;
  void x5(const QString&);

  QString x6() const;
  void x6(const QString&);

  QString x7() const;
  void x7(const QString&);

  QString x8() const;
  void x8(const QString&);

  QString loca() const;
  void local(const QString&);
  */

    protected:
      virtual QString TypeName() const;

    private:
      static const QString JSON_TYPE;

      QList<GDW::RPG::Weapon*> mWeapons;
    };
  };
};

#endif // VEHICLE_HH
