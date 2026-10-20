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
    return {};
}

void Board::ClearRow(int row)
{

}

void Board::TriggerBomb(Position center)
{

}

void Board::ClearAll()
{

}

int Board::GetWidth() const
{
    return WIDTH;
}

int Board::GetHeight() const
{
    return HEIGHT;
}