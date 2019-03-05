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

#ifndef MODEL_HH
#define MODEL_HH

#include <QAbstractItemModel>
#include <QModelIndex>
#include <QVariant>


class QFile;
class QTextStream;

namespace Ui {
  class MainWindow;
}

namespace GDW
{
  namespace RPG
  {
    class ObjectTreeItem;

    class TreeModel : public QAbstractItemModel
    {
        Q_OBJECT

      public:
        TreeModel(QObject* parent = nullptr);
        ~TreeModel() override;

        QVariant data(const QModelIndex& index, int role) const override;
        QVariant headerData(int section, Qt::Orientation orientation,
                            int role = Qt::DisplayRole) const override;

        QModelIndex index(int row, int column,
                          const QModelIndex& parent = QModelIndex()) const override;
        QModelIndex parent(const QModelIndex& index) const override;

        int rowCount(const QModelIndex& parent = QModelIndex()) const override;
        int columnCount(const QModelIndex& parent = QModelIndex()) const override;

        Qt::ItemFlags flags(const QModelIndex& index) const override;
        bool setData(const QModelIndex &index, const QVariant &value,
                     int role = Qt::EditRole) override;

        bool insertRows(int position, int rows,
                        const QModelIndex& parent = QModelIndex()) override;
        bool removeRows(int position, int rows,
                        const QModelIndex& parent = QModelIndex()) override;

        // bool AddItem(int, const QModelIndex& = QModelIndex());
        void CurrentType(int);
        ObjectTreeItem* GetItem(const QModelIndex& index) const;
        void Import(QFile&);
        void Print(QWidget* = nullptr) const;

        friend QTextStream& operator<<(QTextStream&, const TreeModel&);

      private:
        void CreateRootItem();
        void SetupModelData(const QJsonDocument&, ObjectTreeItem* parent = nullptr);

        int mCurrentType;
        ObjectTreeItem* mRootItem;
    };
  };
};

#endif // MODEL_HH
