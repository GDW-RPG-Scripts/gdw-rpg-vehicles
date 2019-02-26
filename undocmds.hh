#ifndef UNDOCOMMANDS_HH
#define UNDOCOMMANDS_HH

#include <QUndoCommand>

class UndoCommitObject : public QUndoCommand
{
  public:
    UndoCommitObject();

    void undo() override;
    void redo() override;
};

#endif // UNDOCOMMANDS_HH
