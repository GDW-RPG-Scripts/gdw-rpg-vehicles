#include "undocmds.hh"

#include <QDebug>

UndoCommitObject::UndoCommitObject()
{
  //  mUi->objectForm->GetObject()->Copy();
  //  QModelIndex index = mUi->vehiclesTreeView->currentIndex();
  //  ObjectTreeItem* item =
  //      static_cast<ObjectTreeItem*>(index.internalPointer());
  //  item->Copy();
}

void
UndoCommitObject::undo()
{
  qDebug() << "UndoCommitObject::undo()";
}

void
UndoCommitObject::redo()
{
  qDebug() << "UndoCommitObject::redo()";
}
