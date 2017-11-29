#include "abstractinstrument.h"
#include "../undocommand.h"
#include "../drawingboard.h"

AbstractInstrument::AbstractInstrument(QObject *parent) : QObject(parent)
{

}

void AbstractInstrument::makeUndoCommand(DrawingBoard &board)
{
    board.pushUndoCommand(new UndoCommand(board.getImage(), board));
}
