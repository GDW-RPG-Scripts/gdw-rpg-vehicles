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

#ifndef OBJECTFORM_HH
#define OBJECTFORM_HH

#include "object_global.hh"

#include "object.hh"

#include <QWidget>

namespace GDW
{
  namespace RPG
  {
    class OBJECTSHARED_EXPORT ObjectForm : public QWidget
    {
        Q_OBJECT

      public:
        explicit ObjectForm(QWidget* parent = nullptr);
        virtual ~ObjectForm();

        virtual Object* Read(Mode = Mode::Display, Object* = nullptr);
        virtual Object* Write();
        virtual void SetReadOnly(bool);
        virtual QString Title() const;

        bool IsReadOnly() const;

        virtual Object* GetObject();
        virtual const Object* GetObject() const;

      protected:
        void AddSvgFrame(const QVariant&, QWidget*);

      private:
        bool mReadOnly;
    };
  };
};
#endif // OBJECTFORM_HH
