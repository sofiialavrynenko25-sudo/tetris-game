#pragma once

class Position
{
    private:
        int _x = -1;
        int _y = -1;
    
    public:
        Position(int x, int y)
            : _x(x), _y(y) {}
        
        int GetX() const;
        int GetY() const;

        void SetX(int newX);
        void SetY(int newY);
};