/**
 * GDW RPG Vehicles, a vehicle database for Traveller and other GDW derived RPGs.
 *
 * Copyright (C) 2018-2019 Michael N. Henry
 *
 * This file is part of GDW RPG Vehicles.
 *
 * GDW RPG Vehicles is free software: you can redistribute it and/or modify it under the terms of the
 * GNU General Public License as published by the Free Software Foundation, either version 2 of the
 * License, or (at your option) any later version.
 *
 * GDW RPG Vehicles is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY;
 * without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 *
 * See the GNU General Public License for more details. You should have received a copy of the GNU
 * General Public License along with GDW RPG Vehicles. if(not, see <http://www.gnu.org/licenses/>.
 */

#include "vehicle.hh"

#include "mustache.hh"
#include "weapon.hh"

#include <QJsonArray>
#include <QJsonDocument>
#include <QLocale>
#include <QSettings>

#include <cmath>

using namespace GDW::RPG;

const QString
Vehicle::JSON_TYPE = "__GDW_RPG_Vehicle__";

Vehicle::Vehicle(const QJsonObject& json, Object* parent)
  : Object(json, parent)
{}

Vehicle::Vehicle(const Vehicle& vehicle, Object* parent)
  : Object(vehicle, parent)
{}

Vehicle::~Vehicle()
{}

Vehicle*
Vehicle::New(Object* parent)
{
  static const QJsonObject exemplar
  {
    {"__GDW_RPG_Type__", JSON_TYPE},
    {PROP_NAME, "[Name]"}, {PROP_TYPE, "[Type]"}, {PROP_NATIONALITY, "[Nationality]"} //,
    //    {PROP_TRMOV,   QJsonValue(QJsonValue::Double)}, {PROP_CCMOV, QJsonValue(QJsonValue::Double)}, {PROP_FCAP, QJsonValue(QJsonValue::Double)}, {PROP_FCONS, QJsonValue(QJsonValue::Double)}, {PROP_SUSP, ""},
    //    {PROP_TF,      QJsonValue(QJsonValue::Double)}, {PROP_TS,    QJsonValue(QJsonValue::Double)}, {PROP_TR,   QJsonValue(QJsonValue::Double)}, {PROP_HF,    QJsonValue(QJsonValue::Double)}, {PROP_HS,  QJsonValue(QJsonValue::Double)}, {PROP_HR, QJsonValue(QJsonValue::Double)},
    //    {PROP_WEAPONS, QJsonArray()},
    //    {PROP_WEIGHT,  QJsonValue(QJsonValue::Double)}, {PROP_LOAD,  QJsonValue(QJsonValue::Double)}, {PROP_CREW, QJsonValue(QJsonValue::Double)}, {PROP_PSGR,  QJsonValue(QJsonValue::Double)}, {PROP_MNT, QJsonValue(QJsonValue::Double)},
    //    {PROP_PRICE,   QJsonValue(QJsonValue::Double)}, {PROP_RF,    QJsonValue(QJsonValue::Double)}, {PROP_DECK, QJsonValue(QJsonValue::Double)}, {PROP_BELLY, QJsonValue(QJsonValue::Double)},
    //    {PROP_STAB, ""}, {PROP_FUEL, ""}, {PROP_NIGHT, ""}, {PROP_RAD, ""},
    //    {PROP_X5,   ""}, {PROP_X6,   ""}, {PROP_X7,    ""},
    //    {PROP_X8,   ""},
    //    {PROP_LOCA, ""}
  };

  return new Vehicle(exemplar, parent);
}

Vehicle*
Vehicle::Copy(Object* parent)
{
  return new Vehicle(*this, parent);
}

const Vehicle*
Vehicle::Copy(Object* parent) const
{
  return new Vehicle(*this, parent);
}

QList<QVariant>
Vehicle::ItemData() const
{
  QList<QVariant> data;

  data << Name() << Type() << Nationality();

  return data;
}

void
Vehicle::RefreshDependencies()
{
  QList<Object*> list;
  for(Weapon* weapon: mWeapons)
    list.append(weapon);
  SetObjectsFor(PROP_WEAPONS, list);
}

void
Vehicle::ToVariantHash(QVariantHash& hash) const
{
  Object::ToVariantHash(hash);

  hash[PROP_NAME]        = Name();
  hash[PROP_TYPE]        = Type();
  hash[PROP_NATIONALITY] = Nationality();
  hash[PROP_TRMOV]       = TravelMove();
  hash[PROP_CCMOV]       = CombatMove();
  hash[PROP_FCAP]        = FuelCapacity();
  hash[PROP_FCONS]       = FuelConsumption();
  hash[PROP_SUSP]        = Suspension();
  hash[PROP_TF]          = TurretFront();
  hash[PROP_TS]          = TurretSides();
  hash[PROP_TR]          = TurretRear();
  hash[PROP_HF]          = HullFront();
  hash[PROP_HS]          = HullSides();
  hash[PROP_HR]          = HullRear();

  QVariantList list;
  for(Weapon* weapon: Weapons()) {
    QVariantHash w_hash;
    weapon->ToVariantHash(w_hash);
    list << w_hash;
  }

  hash[PROP_WEAPONS]      = list;
  hash[PROP_MASS]         = Mass();
  hash[PROP_LOAD]         = Load();
  hash[PROP_CREW]         = Crew();
  hash[PROP_PSGR]         = Passengers();
  hash[PROP_MNT]          = Maintenance();
  hash[PROP_COST]         = Cost();
  hash[PROP_RF]           = Rf();
  hash[PROP_FIRECONTROL]  = FireControl();
  hash[PROP_DECK]         = Deck();
  hash[PROP_BELLY]        = Belly();
  hash[PROP_STAB]         = Stabilization();
  hash[PROP_FUEL]         = FuelTypes();
  hash[PROP_NIGHT]        = NightVision();
  hash[PROP_RAD]          = NBC();
  hash[PROP_SKILL]        = Skill();
  hash[PROP_AGILITY]      = Agility();
  hash[PROP_HULL]         = Hull();
  hash[PROP_STRUCTURE]    = Structure();
  hash[PROP_OPENCLOSED]   = OpenClosed();
  hash[PROP_X8]           = X8();
  //  hash[PROP_X8]           = LineBreakText(X8().toString(), 140);
  hash[PROP_LOCA]         = HitLocations();
  {
    QByteArray value = SideViewImage().toByteArray();
    hash[PROP_SIDEVIEW_IMG] =
        value.isEmpty()
        ? ""
        : qUncompress(QByteArray::fromBase64(value));
  }
  {
    QByteArray value = TopDownImage().toByteArray();
    hash[PROP_TOPDOWN_IMG]  =
        value.isEmpty()
        ? ""
        : qUncompress(QByteArray::fromBase64(value));
  }

  // Additional asset box
  {
    QString assets;

    QString fuelTypes = FuelTypes().toString();
    if(!fuelTypes.isEmpty())
      assets += tr("Runs on ") + fuelTypes + ".<tbreak/>";

    QString stabilization = Stabilization().toString();
    if(!stabilization.isEmpty())
      assets += stabilization + tr(" stabilization.<tbreak/>");

    QString nightVision = NightVision().toString();
    if(!nightVision.isEmpty())
      assets += tr("Night vision: ") + nightVision + ".<tbreak/>";

    QString nbc = NBC().toString();
    if(!nbc.isEmpty())
      assets += tr("Radiation ") + nbc.toLower() + ".<tbreak/>";

    hash["assets"]          = assets;
    // hash["assets"]         = LineBreakText(paragraph, 100, 8);
  }

  bool ok;

  // Speed
  QString speed;
  double road = TravelMove().toDouble(&ok);
  if(ok) {
    speed += QString::number(std::round(road / 5 * 3.6 / 1.3));
  }
  double country = CombatMove().toDouble(&ok);
  if(ok) {
    speed += " / ";
    speed += QString::number(std::floor(country / 5 * 3.6 / 1.3));
  }
  hash["speed"]          = speed;

  // Range
  QString range;
  double fcap  = FuelCapacity().toDouble(&ok);
  if(ok) {
    double fcons = FuelConsumption().toDouble(&ok);
    if(ok) {
      double trmov = TravelMove().toDouble(&ok);
      if(ok) {
        range = QString::number(std::floor(trmov * fcap / fcons));
      }
      double ccmov = CombatMove().toDouble(&ok);
      if(ok) {
        range += " / ";
        range += QString::number(std::floor(ccmov * fcap / fcons));
      }
    }
  }

  hash["range"]          = range;

  // Crew and passengers
  QString positions(" C ");
  double crew = Crew().toDouble(&ok);
  if(ok) {
    if(crew > 1) positions += " D ";
    if(crew > 2) positions += " G ";
    if(crew > 3) positions += " L ";
    if(crew > 4) positions += " R ";
    if(crew > 5) positions += " X ";
  }

  double psgr = Passengers().toDouble(&ok);
  if(ok && psgr > 0) {
    if(psgr + crew > 15) {
      positions += " + " + QString::number(psgr) + " T ";
    } else {
      for(int i = 0; i < psgr; ++i) {
        positions += " T ";
      }
    }
  }

  hash["psgr?"]          = psgr > 0;
  hash["positions"]      = positions;

  // Mass-related variables
  double mass = Mass(Mode::Edit).toDouble(&ok);
  if(ok) {
    double shipping = std::round(mass / 1.3);
    hash["shipping"]       = QString::number(shipping) + "dT";
    hash["spacesused"]     = QString::number(shipping * 2);
  }
}

Mustache::QtVariantContext*
Vehicle::Context(const QVariantHash& hash) const
{
  class CounterContext : public Mustache::QtVariantContext
  {
    public:
      int mNumber;
      int mYCoord;
      int mIncrement;

      CounterContext(int start, int increment, const QVariantHash& map)
        : Mustache::QtVariantContext(map),
          mNumber(1), mYCoord(start), mIncrement(increment)
      {}

      virtual bool canEval(const QString& key) const {
        return key == "counter";
      }

      virtual QString eval(const QString& key, const QString& _template, Mustache::Renderer* renderer) {
        if(key == "counter") {
          mNumber += 1;
          mYCoord += mIncrement;
        }
        return renderer->render(_template, this);
      }

      virtual QString stringValue(const QString& key) const {
        if(key == "number") {
          return QString::number(mNumber);
        } else if(key == "y_coord") {
          return QString::number(mYCoord);
        } else {
          return Mustache::QtVariantContext::stringValue(key);
        }
      }
  };

  return new CounterContext(63, 11, hash);
}


qreal
Vehicle::Divisor() const
{
  static const qreal FACTOR[] = {
    1.0, 2.0, 2.0, 2.16666, 5.4
  };

  QSettings settings;
  int ruleset = settings.value("ruleset", 0).toInt();

  return FACTOR[ruleset];
}

/*
 * Name
 */
const QString Vehicle::PROP_NAME = "name";

QVariant
Vehicle::Name() const
{
  return GetVariantFor(PROP_NAME);
}

void
Vehicle::Name(const QVariant& variant)
{
  SetVariantFor(PROP_NAME, variant);
}


/*
 * Type
 */
const QString Vehicle::PROP_TYPE = "typ";

QVariant
Vehicle::Type() const
{
  return GetVariantFor(PROP_TYPE);
}

void
Vehicle::Type(const QVariant& variant)
{
  SetVariantFor(PROP_TYPE, variant);
}


/*
 * Nationality
 */
const QString Vehicle::PROP_NATIONALITY = "nat";

QVariant
Vehicle::Nationality() const
{
  return GetVariantFor(PROP_NATIONALITY);
}

void
Vehicle::Nationality(const QVariant& variant)
{
  SetVariantFor(PROP_NATIONALITY, variant);
}


/*
 * Trmov
 */
const QString Vehicle::PROP_TRMOV = "trmov";

QVariant
Vehicle::TravelMove() const
{
  return GetVariantFor(PROP_TRMOV);
}

void
Vehicle::TravelMove(const QVariant& variant)
{
  SetVariantFor(PROP_TRMOV, variant);
}


/*
 * Ccmov
 */
const QString Vehicle::PROP_CCMOV = "ccmove";

QVariant
Vehicle::CombatMove() const
{
  return GetVariantFor(PROP_CCMOV);
}

void
Vehicle::CombatMove(const QVariant& variant)
{
  SetVariantFor(PROP_CCMOV, variant);
}


/*
 * Fcap
 */
const QString Vehicle::PROP_FCAP = "fcap";

QVariant
Vehicle::FuelCapacity() const
{
  return GetDoubleFor(PROP_FCAP);
}

void
Vehicle::FuelCapacity(const QVariant& variant)
{
  SetDoubleFor(PROP_FCAP, variant);
}


/*
 * Fcons
 */
const QString Vehicle::PROP_FCONS = "fcons";

QVariant
Vehicle::FuelConsumption() const
{
  return GetVariantFor(PROP_FCONS);
}

void
Vehicle::FuelConsumption(const QVariant& variant)
{
  SetVariantFor(PROP_FCONS, variant);
}


/*
 * Susp
 */
const QString Vehicle::PROP_SUSP = "susp";

QVariant
Vehicle::Suspension() const
{
  QString value = GetVariantFor(PROP_SUSP).toString();
  QChar type = value[0];

  bool ok;
  double number = value.mid(1).toDouble(&ok);
  if(ok) {
    value = type;
    value += QString::number(Round(number / Divisor()));
  }

  return value;
}

void
Vehicle::Suspension(const QVariant& variant)
{
  if(RemoveIfEmpty(PROP_SUSP, variant))
    return;

  bool ok;
  QString value = variant.toString();
  double number = value.mid(1).toDouble(&ok);
  if(ok) {
    value = value[0];
    value += QString::number(ConvertFrom(number));
    SetVariantFor(PROP_SUSP, value);
  }
}


/*
 * Tf
 */
const QString Vehicle::PROP_TF = "tf";

QVariant
Vehicle::TurretFront() const
{
  auto lambda = [this](double value) -> double {
    return Round(value / Divisor());
  };

  return GetDoubleFor(PROP_TF, lambda);
}

void
Vehicle::TurretFront(const QVariant& variant)
{
  auto lambda = [this](double value) -> double {
    return ConvertFrom(value);
  };

  SetDoubleFor(PROP_TF, variant, lambda);
}


/*
 * Ts
 */
const QString Vehicle::PROP_TS = "ts";

QVariant
Vehicle::TurretSides() const
{
  auto lambda = [this](double value) -> double {
    return Round(value / Divisor());
  };

  return GetDoubleFor(PROP_TS, lambda);
}

void
Vehicle::TurretSides(const QVariant& variant)
{
  auto lambda = [this](double value) -> double {
    return ConvertFrom(value);
  };

  SetDoubleFor(PROP_TS, variant, lambda);
}


/*
 * Tr
 */
const QString Vehicle::PROP_TR = "tr";

QVariant
Vehicle::TurretRear() const
{
  auto lambda = [this](double value) -> double {
    return Round(value / Divisor());
  };

  return GetDoubleFor(PROP_TR, lambda);
}

void
Vehicle::TurretRear(const QVariant& variant)
{
  auto lambda = [this](double value) -> double {
    return ConvertFrom(value);
  };

  SetDoubleFor(PROP_TR, variant, lambda);
}


/*
 * Hf
 */
const QString Vehicle::PROP_HF = "hf";

QVariant
Vehicle::HullFront() const
{
  auto lambda = [this](double value) -> double {
    return Round(value / Divisor());
  };

  return GetDoubleFor(PROP_HF, lambda);
}

void
Vehicle::HullFront(const QVariant& variant)
{
  auto lambda = [this](double value) -> double {
    return ConvertFrom(value);
  };

  SetDoubleFor(PROP_HF, variant, lambda);
}


/*
 * Hs
 */
const QString Vehicle::PROP_HS = "hs";

QVariant
Vehicle::HullSides() const
{
  auto lambda = [this](double value) -> double {
    return Round(value / Divisor());
  };

  return GetDoubleFor(PROP_HS, lambda);
}

void
Vehicle::HullSides(const QVariant& variant)
{
  auto lambda = [this](double value) -> double {
    return ConvertFrom(value);
  };

  SetDoubleFor(PROP_HS, variant, lambda);
}


/*
 * Hr
 */
const QString Vehicle::PROP_HR = "hr";

QVariant
Vehicle::HullRear() const
{
  auto lambda = [this](double value) -> double {
    return Round(value / Divisor());
  };

  return GetDoubleFor(PROP_HR, lambda);
}

void
Vehicle::HullRear(const QVariant& variant)
{
  auto lambda = [this](double value) -> double {
    return ConvertFrom(value);
  };

  SetDoubleFor(PROP_HR, variant, lambda);
}


/*
 * Weapons
 */
const QString Vehicle::PROP_WEAPONS = "weap";


void
Vehicle::InsertChild(Object* object, int position)
{
  Weapon* weapon =
      qobject_cast<Weapon*>(object);

  if(weapon)
    AddWeapon(weapon, position);
}

Object*
Vehicle::RemoveChild(int position)
{
  Q_ASSERT(position >= 0 && position < mWeapons.size());
  return mWeapons.takeAt(position);
}

void
Vehicle::AddWeapon(Weapon* weapon, int position)
{
  mWeapons.insert(position, weapon);
  RefreshDependencies();
}

QList<Weapon*>
Vehicle::Weapons() const
{
  return mWeapons;
}

void
Vehicle::Weapons(QList<Weapon*>& weapons)
{
  mWeapons = weapons;
}


/*
 * Weight
 */
const QString Vehicle::PROP_MASS = "mass";

QVariant
Vehicle::Mass(Mode mode) const
{
  QVariant variant;

  if(mode == Mode::Edit)
    return GetDoubleFor(PROP_MASS);

  bool ok;
  double value = GetDoubleFor(PROP_MASS).toDouble(&ok);
  if(ok)
    return QString::number(value) + "t";

  return variant;
}

void
Vehicle::Mass(const QVariant& value)
{
  SetDoubleFor(PROP_MASS, value);
}


/*
 * Load
 */
const QString Vehicle::PROP_LOAD = "load";

QVariant
Vehicle::Load(Mode mode) const
{
  QVariant variant;

  if(mode == Mode::Edit)
    return GetDoubleFor(PROP_LOAD);

  bool ok;
  double value = GetDoubleFor(PROP_LOAD).toDouble(&ok);
  if(ok)
    return QString::number(value) + "t";

  return variant;
}

void
Vehicle::Load(const QVariant& value)
{
  SetDoubleFor(PROP_LOAD, value);
}


/*
 * Crew
 */
const QString Vehicle::PROP_CREW = "crew";

QVariant
Vehicle::Crew() const
{
  return GetDoubleFor(PROP_CREW);
}

void
Vehicle::Crew(const QVariant& value)
{
  SetDoubleFor(PROP_CREW, value);
}


/*
 * Passengers
 */
const QString Vehicle::PROP_PSGR = "psgr";

QVariant
Vehicle::Passengers() const
{
  return GetDoubleFor(PROP_PSGR);
}

void
Vehicle::Passengers(const QVariant& value)
{
  SetDoubleFor(PROP_PSGR, value);
}


/*
 * Mnt
 */
const QString Vehicle::PROP_MNT = "mnt";

QVariant
Vehicle::Maintenance() const
{
  return GetDoubleFor(PROP_MNT);
}

void
Vehicle::Maintenance(const QVariant& value)
{
  SetDoubleFor(PROP_MNT, value);
}


/*
 * Price
 */
const QString Vehicle::PROP_COST = "cost";

QVariant
Vehicle::Cost(Mode mode) const
{
  QVariant variant = GetDoubleFor(PROP_COST);

  if(mode == Mode::Display) {
    QLocale locale("en_US"); // = QLocale::system();
    bool ok;
    double value = variant.toDouble(&ok);
    if(ok) {
      if(value < 1000000)
        variant = locale.toCurrencyString(value, "Cr", 0);
      else {
        variant = locale.toCurrencyString(value/1000000, "MCr", 2);
      }
    }
  }

  return variant;
}

void
Vehicle::Cost(const QVariant& value)
{
  SetDoubleFor(PROP_COST, value);
}


/*
 * Rf
 */
const QString Vehicle::PROP_RF = "rf";

QVariant
Vehicle::Rf() const
{
  return GetDoubleFor(PROP_RF);
}

void
Vehicle::Rf(const QVariant& value)
{
  SetDoubleFor(PROP_RF, value);
}


/*
 * FireControl
 */
const QString Vehicle::PROP_FIRECONTROL = "fc";

QVariant
Vehicle::FireControl(Mode mode) const
{
  QVariant variant;

  if(mode == Mode::Edit)
    return GetDoubleFor(PROP_FIRECONTROL);

  bool ok;
  double value = GetDoubleFor(PROP_FIRECONTROL).toDouble(&ok);
  if(ok)
    return (value > 0 ? "+" : "") + QString::number(value);

  return variant;
}

void
Vehicle::FireControl(const QVariant& value)
{
  SetDoubleFor(PROP_FIRECONTROL, value);
}


/*
 * Deck
 */
const QString Vehicle::PROP_DECK = "deck";

QVariant
Vehicle::Deck(Mode mode) const
{
  auto lambda = [this](double value) -> double {
    return Round(value / Divisor());
  };

  QVariant result = GetDoubleFor(PROP_DECK, lambda);

  if(mode == Mode::Display && !result.isValid()) {
    auto alternate = [this](double value) -> double {
      return Round(value / 2 / Divisor());
    };

    result = GetDoubleFor(PROP_HR, alternate);
  }

  return result;
}

void
Vehicle::Deck(const QVariant& variant)
{
  auto lambda = [this](double value) -> double {
    return ConvertFrom(value * Divisor());
  };

  SetDoubleFor(PROP_DECK, variant, lambda);
}


/*
 * Belly
 */
const QString Vehicle::PROP_BELLY = "belly";

QVariant
Vehicle::Belly(Mode mode) const
{
  auto lambda = [this](double value) -> double {
    return Round(value / Divisor());
  };

  QVariant result = GetDoubleFor(PROP_BELLY, lambda);

  if(mode == Mode::Display && !result.isValid()) {
    auto alternate = [this](double value) -> double {
      return Round(value / 2 / Divisor());
    };

    result = GetDoubleFor(PROP_HR, alternate);
  }

  return result;
}

void
Vehicle::Belly(const QVariant& variant)
{
  auto lambda = [this](double value) -> double {
    return ConvertFrom(value * Divisor());
  };

  SetDoubleFor(PROP_BELLY, variant, lambda);
}


/*
 * Stabilization
 */
const QString Vehicle::PROP_STAB = "stab";

QVariant
Vehicle::Stabilization() const
{
  return GetVariantFor(PROP_STAB);
}

void
Vehicle::Stabilization(const QVariant& value)
{
  SetVariantFor(PROP_STAB, value);
}


/*
 * Fuel Types
 */
const QString Vehicle::PROP_FUEL = "fuel";

QVariant
Vehicle::FuelTypes() const
{
  return GetVariantFor(PROP_FUEL);
}

void
Vehicle::FuelTypes(const QVariant& value)
{
  SetVariantFor(PROP_FUEL, value);
}


/*
 * Night Vision
 */
const QString Vehicle::PROP_NIGHT = "night";

QVariant
Vehicle::NightVision() const
{
  return GetVariantFor(PROP_NIGHT);
}

void
Vehicle::NightVision(const QVariant& value)
{
  SetVariantFor(PROP_NIGHT, value);
}


/*
 * Rad
 */
const QString Vehicle::PROP_RAD = "rad";

QVariant
Vehicle::NBC() const
{
  return GetVariantFor(PROP_RAD);
}

void
Vehicle::NBC(const QVariant& value)
{
  SetVariantFor(PROP_RAD, value);
}


/*
 * Skill
 */
const QString Vehicle::PROP_SKILL = "skill";

QVariant
Vehicle::Skill() const
{
  return GetVariantFor(PROP_SKILL);
}

void
Vehicle::Skill(const QVariant& value)
{
  SetVariantFor(PROP_SKILL, value);
}


/*
 * Agility
 */
const QString Vehicle::PROP_AGILITY = "agility";

QVariant
Vehicle::Agility() const
{
  return GetVariantFor(PROP_AGILITY);
}

void
Vehicle::Agility(const QVariant& value)
{
  SetVariantFor(PROP_AGILITY, value);
}


/*
 * Hull
 */
const QString Vehicle::PROP_HULL = "hull";

QVariant
Vehicle::Hull() const
{
  return GetVariantFor(PROP_HULL);
}

void
Vehicle::Hull(const QVariant& value)
{
  SetVariantFor(PROP_HULL, value);
}


/*
 * Structure
 */
const QString Vehicle::PROP_STRUCTURE = "structure";

QVariant
Vehicle::Structure() const
{
  return GetVariantFor(PROP_STRUCTURE);
}

void
Vehicle::Structure(const QVariant& value)
{
  SetVariantFor(PROP_STRUCTURE, value);
}


/*
 * OpenClosed
 */
const QString Vehicle::PROP_OPENCLOSED = "openclosed";

QVariant
Vehicle::OpenClosed() const
{
  return GetVariantFor(PROP_OPENCLOSED);
}

void
Vehicle::OpenClosed(const QVariant& value)
{
  SetVariantFor(PROP_OPENCLOSED, value);
}


/*
 * X8
 */
const QString Vehicle::PROP_X8 = "x8";

QVariant
Vehicle::X8() const
{
  return GetVariantFor(PROP_X8);
}

void
Vehicle::X8(const QVariant& value)
{
  SetVariantFor(PROP_X8, value);
}


/*
 * TopDownImage
 */
const QString Vehicle::PROP_TOPDOWN_IMG = "topdown";

QVariant
Vehicle::TopDownImage() const
{
  return GetVariantFor(PROP_TOPDOWN_IMG);
}

void
Vehicle::TopDownImage(const QVariant& value)
{
  SetVariantFor(PROP_TOPDOWN_IMG, value);
}


/*
 * SideViewImage
 */
const QString Vehicle::PROP_SIDEVIEW_IMG = "sideview";

QVariant
Vehicle::SideViewImage() const
{
  return GetVariantFor(PROP_SIDEVIEW_IMG);
}

void
Vehicle::SideViewImage(const QVariant& value)
{
  SetVariantFor(PROP_SIDEVIEW_IMG, value);
}


/*
 * Additional Hit Location
 */
const QString Vehicle::PROP_LOCA = "loca";

QVariant
Vehicle::HitLocations() const
{
  return GetVariantFor(PROP_LOCA);
}

void
Vehicle::HitLocations(const QVariant& value)
{
  SetVariantFor(PROP_LOCA, value);
}
