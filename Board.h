#pragma once

#include <vector>

#include "Tetromino.h"
#include "Position.h"

class Board
{
    private:
        static const int WIDTH = 10;
        static const int HEIGHT = 20;
        int _grid[HEIGHT][WIDTH] = { {0} };

    public:
        Board() = default;
        void PlacePiece(Tetromino piece);
        std::vector<int> CheckFullRows();
        void ClearRow(int row);
        void TriggerBomb(Position center);
        void ClearAll();

        int GetWidth() const;
        int GetHeight() const;
};