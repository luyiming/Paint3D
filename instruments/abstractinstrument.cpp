#include "abstractinstrument.h"

AbstractInstrument::AbstractInstrument(QObject *parent) : QObject(parent)
{

}

void AbstractInstrument::makeUndoCommand(DrawingBoard &board)
{
//    board.pushUndoCommand(new UndoCommand(board.getImage(), board));
}
