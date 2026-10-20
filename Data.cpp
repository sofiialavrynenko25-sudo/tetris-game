#include "Data.h"

const int* Data::GetBoardState() const
{
    return &_boardState[0][0];
}

int Data::GetScore() const
{
    return _score;
}

int Data::GetLinesCleared() const
{
    return _linesCleared;
}

TetrominoType Data::GetActivePiece() const
{
    return _activePiece;
}

TetrominoType Data::GetHeldPiece() const
{
    return _heldPiece;
}