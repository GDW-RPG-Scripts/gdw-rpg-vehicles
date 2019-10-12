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

#ifndef OBJECTTREEITEM_HH
#define OBJECTTREEITEM_HH

#include "object_global.hh"

#include <QList>
#include <QVariant>

class QFile;
class QJsonArray;
class QStackedWidget;
class QTextStream;
class QUndoStack;

namespace Ui {
  class Workspace;
}

extern void GDW_RPG_Object_Initialize();

namespace GDW
{
  namespace RPG
  {
    class Object;
    class ObjectForm;
    class ObjectModel;

    class OBJECTSHARED_EXPORT ObjectItem : public QObject
    {
        Q_OBJECT

      public:
        ObjectItem();
        ObjectItem(const ObjectItem&);
        ObjectItem(Object*, ObjectItem* parent = nullptr);
        ObjectItem(const QList<QVariant>&,
                       ObjectItem* parent = nullptr);
        virtual ~ObjectItem();

        virtual ObjectItem* Copy() const;

        void Export(QJsonArray&) const;
        void RenderPage(QPaintDevice&) const;
        void WriteSvg(QFile&) const;

        virtual QByteArray Template() const;

        QModelIndex Index() const;
        virtual ObjectModel* Model() const;

        virtual bool InsertChild(ObjectItem*, int = INT_MAX);
        ObjectItem* RemoveChild(int);
        ObjectItem* Child(int row);
        int ChildCount() const;

        int ColumnCount() const;
        virtual QVariant Data(int column) const;
        virtual bool SetData(int column, const QVariant&);
        int Row() const;
        ObjectItem* ParentItem() const;

        void RefreshItemData();

        virtual ObjectForm* GetForm(QUndoStack*);
        virtual Object* GetObjectPtr();
        virtual const Object* GetObjectPtr() const;

      signals:

      public slots:

      protected:

      private:
        friend QTextStream& operator<<(QTextStream&, const ObjectItem&);

        QString RenderSvg() const;

        Object* mObject;
        QList<ObjectItem*> mChildItems;
        QList<QVariant> mItemData;

      private:
        static class Initialize {
          public:
            Initialize() { GDW_RPG_Object_Initialize(); }
        } Initializer;
    };
  };
};

// Q_DECLARE_METATYPE(GDW::RPG::ObjectTreeItem)

#endif // OBJECTTREEITEM_HH
