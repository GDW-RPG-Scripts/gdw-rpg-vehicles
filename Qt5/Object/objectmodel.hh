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

#ifndef OBJECTMODEL_HH
#define OBJECTMODEL_HH

#include "object_global.hh"

#include <QAbstractItemModel>

class QFile;
class QMenu;
class QPrinter;
class QPainter;
class QTextStream;
class QUndoStack;

namespace GDW
{
  namespace RPG
  {
    class ObjectItem;

    class OBJECTSHARED_EXPORT ObjectModel : public QAbstractItemModel
    {
        Q_OBJECT

      public:
        ObjectModel(QObject* parent = nullptr);
        ~ObjectModel() override;

        // Public API
        void Export(QJsonArray&) const;
        void Print(QModelIndex, QPrinter&) const;
        void Reset();
        void WritePdf(QModelIndex, QFile&) const;
        void WriteSvg(QModelIndex, QFile&) const;

        virtual ObjectItem* Unpack(const QJsonObject&, ObjectItem*);

        virtual ObjectItem* RootItem() const;

        virtual bool InsertObject(int /*= INT_MAX*/);
        virtual bool RemoveObject(int /*= INT_MAX*/);
        virtual void AddActions(QMenu&, QUndoStack&, const QModelIndex&);

        bool InsertChild(ObjectItem*, ObjectItem*, int = INT_MAX);
        ObjectItem* RemoveChild(ObjectItem*, int = INT_MAX);

        // Mandatory overrides
        QModelIndex index(int row, int column,
                          const QModelIndex& parent = QModelIndex()) const override;
        QModelIndex parent(const QModelIndex& index) const override;
        int rowCount(const QModelIndex& parent = QModelIndex()) const override;
        int columnCount(const QModelIndex& parent = QModelIndex()) const override;
        QVariant data(const QModelIndex& index, int role) const override;

        // Optional overrides
        Qt::ItemFlags flags(const QModelIndex& index) const override;
        QVariant headerData(int section, Qt::Orientation orientation,
                            int role = Qt::DisplayRole) const override;
        bool insertRows(int position, int rows,
                        const QModelIndex& parent = QModelIndex()) override;
        bool removeRows(int position, int rows,
                        const QModelIndex& parent = QModelIndex()) override;
        bool setData(const QModelIndex &index, const QVariant &value,
                     int role = Qt::EditRole) override;

        // Output function
        friend QTextStream& operator<<(QTextStream&, const ObjectModel&);

      signals:

      public slots:

      protected:
        // Extension points
        ObjectItem* ItemFor(const QModelIndex& index) const;

        virtual ObjectItem* InsertObject(ObjectItem*) const = 0;
        virtual const QList<QVariant>& RootData() const = 0;

      private:
        mutable ObjectItem* mRootItem;
    };
  };
};

#endif // OBJECTMODEL_HH
