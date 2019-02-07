#include "model.hh"

GDW::RPG::TreeModel::TreeModel(QObject* parent)
  : QAbstractItemModel(parent)
{
  QList<QVariant> rootData;
  rootData << "Name" << "Type" << "Nationality";
  setupModelData(data.split(QString("\n")), rootItem);
}

void
GDW::RPG::TreeModel::setupModelData(const QStringList &lines, TreeItem *parent)
{
}
