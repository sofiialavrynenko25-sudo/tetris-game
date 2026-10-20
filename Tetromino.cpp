#include "TetrominoType.h"
#include "Position.h"
#include "Tetromino.h"

void Tetromino::FillShapeGrid(TetrominoType type)
{
    switch (type)
    {
        case TetrominoType::I:
        {
            _shape[1][0] = 1;
            _shape[1][1] = 1;
            _shape[1][2] = 1;
            _shape[1][3] = 1;
            break;
        }

        case TetrominoType::L:
        {
            _shape[1][0] = 1;
            _shape[1][1] = 1;
            _shape[1][2] = 1;
            _shape[2][2] = 1;
            break;
        }

        case TetrominoType::J:
        {
            _shape[2][0] = 1;
            _shape[2][1] = 1;
            _shape[2][2] = 1;
            _shape[1][2] = 1;
            break;
        }

        case TetrominoType::S:
        {
            _shape[1][1] = 1;
            _shape[2][1] = 1;
            _shape[0][3] = 1;
            _shape[1][3] = 1;
            break;
        }

        case TetrominoType::Z:
        {
            _shape[0][1] = 1;
            _shape[1][1] = 1;
            _shape[1][2] = 1;
            _shape[2][2] = 1;
            break;
        }

        case TetrominoType::O:
        {
            _shape[1][1] = 1;
            _shape[2][1] = 1;
            _shape[1][2] = 1;
            _shape[2][2] = 1;
            break;
        }

        case TetrominoType::T:
        {
            _shape[0][1] = 1;
            _shape[1][1] = 1;
            _shape[2][1] = 1;
            _shape[1][2] = 1;
            break;
        }

        default:
            break;
    }
}

void Tetromino::RotateLeft()
{
    int tempShape[4][4] = { {0} };

    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            tempShape[3 - j][i] = _shape[i][j];
        }
    }

    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            _shape[i][j] = tempShape[i][j];
        }
    }
}

void Tetromino::RotateRight()
{
    int tempShape[4][4] = { {0} };

    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            tempShape[j][3 - i] = _shape[i][j];
        }
    }

    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            _shape[i][j] = tempShape[i][j];
        }
    }
}

void Tetromino::Move(int newX, int newY)
{
    _position.SetX(newX);
    _position.SetY(newY);
}