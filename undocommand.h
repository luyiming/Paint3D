#ifndef UNDOCOMMAND_H
#define UNDOCOMMAND_H

#include <QUndoCommand>
#include <QImage>

class DrawingBoard;

class UndoCommand : public QUndoCommand
{
public:
    UndoCommand(const QImage* img, DrawingBoard &board, QUndoCommand *parent = 0);

    virtual void undo();
    virtual void redo();

private:
    QImage mPrevImage;
    QImage mCurrImage;
    DrawingBoard& mBoard;
};
#endif // UNDOCOMMAND_H
