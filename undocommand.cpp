#include "undocommand.h"
#include "drawingboard.h"

UndoCommand::UndoCommand(const QImage *img, DrawingBoard &board, QUndoCommand *parent)
    : QUndoCommand(parent), mPrevImage(*img), mBoard(board)
{
    mCurrImage = mPrevImage;
}

void UndoCommand::undo()
{
//    board.clearSelection();
    mCurrImage = *(mBoard.getImage());
    mBoard.setImage(mPrevImage);
    mBoard.update();
//    mBoard.saveImageChanges();
}

void UndoCommand::redo()
{
    mBoard.setImage(mCurrImage);
    mBoard.update();
//    mBoard.saveImageChanges();
}
