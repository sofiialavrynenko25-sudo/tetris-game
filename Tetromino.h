#pragma once

#include <string>
#include <cstdlib>

#include "TetrominoType.h"
#include "Position.h"

class Tetromino
{
    private:
        TetrominoType _type = TetrominoType::None;
        std::string _color = "";
        Position _position = Position(-1, -1);
        int _shape[4][4] = { {0} };
        bool _isBomb = false;

        void FillShapeGrid(TetrominoType type);

    public:
        Tetromino(TetrominoType type, std::string color, Position position)
            : _type(type), _color(color), _position(position)
            {
                FillShapeGrid(type);
                _isBomb = (rand() % 100 < 10);
            }

        void RotateLeft();
        void RotateRight();
        void Move(int newX, int newY);
};