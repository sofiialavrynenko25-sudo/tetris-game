#include "Position.h"

int Position::GetX() const
{
    return _x;
}

int Position::GetY() const
{
    return _y;
}

void Position::SetX(int newX)
{
    _x = newX;
}

void Position::SetY(int newY)
{
    _y = newY;
}