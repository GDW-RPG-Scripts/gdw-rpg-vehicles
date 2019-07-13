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
 * General Public License along with GDW RPG Vehicles. If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef OBJECT_HH
#define OBJECT_HH

#include "object_global.hh"


#include <QJsonObject>
#include <QVariant>

namespace Mustache
{
  class QtVariantContext;
};

namespace GDW
{
  namespace RPG
  {
    enum class Mode { Display, Edit };

    class OBJECTSHARED_EXPORT Object : public QObject
    {
        Q_OBJECT

      public:
        Object(const QJsonObject& = QJsonObject(), Object* = nullptr);
        Object(const Object&, Object* = nullptr);
        virtual ~Object();

        virtual Object* Copy(Object* = nullptr);
        virtual const Object* Copy(Object* = nullptr) const;

        virtual void InsertChild(Object*, int = INT_MAX);
        virtual Object* RemoveChild(int);

        void TechLevel(const QVariant&);
        QVariant TechLevel() const;

        operator const QJsonObject&();
        virtual void ToVariantHash(QVariantHash&) const;
        virtual Mustache::QtVariantContext* Context(const QVariantHash&) const;

        virtual QList<QVariant> ItemData() const;

      protected:
        virtual void RefreshDependencies();

        bool RemoveIfEmpty(const QString&, const QVariant&);

        QVariant GetVariantFor(const QString&) const;
        void SetVariantFor(const QString&, const QVariant&);

        QVariant GetDoubleFor(const QString&,
                              std::function<double(double)> = [](double value) { return value; }) const;
        void SetDoubleFor(const QString&, QVariant,
                          std::function<double(double)> = [](double value) { return value; });

        void SetObjectsFor(const QString&, QList<Object*>&);

        double ConvertFrom(double) const;
        double Round(double) const;

        QVariant UnpackSvg(const QVariant&) const;
        QVariant UnpackMultiValue(const QVariant&) const;

        QString LineBreakText(QString, int, double = 0.0) const;

      private:
        static const QString PROP_TECHLEVEL;

        static const int RANGE;
        static const double STRIKER[];

        QJsonObject mJsonObject;
    };
  };
};

// Q_DECLARE_METATYPE(GDW::RPG::Object)

#endif // OBJECT_HH
