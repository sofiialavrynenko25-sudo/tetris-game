#include "Board.h"

void Board::PlacePiece(Tetromino piece)
{
    const int* shape = piece.GetShape();

    int startX = piece.GetPosition().GetX();
    int startY = piece.GetPosition().GetY();

    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            if (shape[i * 4 + j] == 1)
            {
                int boardColumn = startX + j;
                int boardRow = startY + i;

                if (boardColumn >= 0 && boardColumn < WIDTH && 
                    boardRow >= 0 && boardRow < HEIGHT)

                {
                    _grid[boardRow][boardColumn] = 1;
                }
            }
        }
    }
}

std::vector<int> Board::CheckFullRows()
{
    std::vector<int> fullRows = {};
    int sum = 0;

    for (int i = 0; i < HEIGHT; i++)
    {
        sum = 0;

        for (int j = 0; j < WIDTH; j++)
        {
            sum += _grid[i][j];
        }
        
        if (sum == 10)
        {
            fullRows.push_back(i);
        }
    }

    return fullRows;
}

void Board::ClearRow(int row)
{
    for (int i = row; i > 0; i--)
    {
        for (int j = 0; j < WIDTH; j++)
        {
            _grid[i][j] = _grid[i - 1][j];
        }
    }

    for (int j = 0; j < WIDTH; j++)
    {
        _grid[0][j] = 0;
    }
}

void Board::TriggerBomb(Position center)
{
    int centerX = center.GetX();
    int centerY = center.GetY();

    for (int i = centerY - 1; i < centerY; i++)
    {
        for (int j = centerX - 1; j < centerX; j++)
        {
            if (i >= 0 && i < HEIGHT &&
                j >= 0 && j <WIDTH)
            {
                _grid[i][j] = 0;
            }
        }
    }
}

void Board::ClearAll()
{
    for (int i = 0; i < HEIGHT; i++)
    {
        for (int j = 0; j < WIDTH; j++)

        {
            _grid[i][j] = 0;
        }
    }
}

int Board::GetWidth() const
{
    return WIDTH;
}

int Board::GetHeight() const
{
    return HEIGHT;
}