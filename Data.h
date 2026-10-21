#pragma once

#include <cstring>

#include "TetrominoType.h"

class Data
{
    private:
        int _boardState[20][10] = { {0} };
        int _score = 0;
        int _linesCleared = 0;
        TetrominoType _activePiece = TetrominoType::None;
        TetrominoType _heldPiece = TetrominoType::None;

    public:
        Data() = default;
        Data(const int boardState[20][10], int score, int linesCleared, TetrominoType activePiece, TetrominoType heldPiece)
            : _score(score), _linesCleared(linesCleared), _activePiece(activePiece), _heldPiece(heldPiece)
            {
                std::memcpy(_boardState, boardState, sizeof(_boardState));
            }

        const int* GetBoardState() const;
        int GetScore() const;
        int GetLinesCleared() const;
        TetrominoType GetActivePiece() const;
        TetrominoType GetHeldPiece() const;
};