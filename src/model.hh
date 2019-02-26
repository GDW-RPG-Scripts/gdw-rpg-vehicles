/*
**
**
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

        void AddItem(QString, const QModelIndex&);
        void Import(QFile&);
        void Print(QWidget* = nullptr) const;

        QVariant data(const QModelIndex& index, int role) const override;
        Qt::ItemFlags flags(const QModelIndex& index) const override;
        QVariant headerData(int section, Qt::Orientation orientation,
                            int role = Qt::DisplayRole) const override;
        QModelIndex index(int row, int column,
                          const QModelIndex& parent = QModelIndex()) const override;
        QModelIndex parent(const QModelIndex& index) const override;
        int rowCount(const QModelIndex& parent = QModelIndex()) const override;
        int columnCount(const QModelIndex& parent = QModelIndex()) const override;

        friend QTextStream& operator<<(QTextStream&, const TreeModel&);

      private:
        void CreateRootItem();
        void SetupModelData(ObjectTreeItem* parent,
                            const QJsonDocument&);

        ObjectTreeItem* mRootItem;
    };
  };
};

#endif // MODEL_HH
