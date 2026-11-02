#pragma once

#include <SFML/Graphics.hpp>

#include "GameEngine.h"

class RenderingEngine
{
    private:
        GameEngine& _gameEngine;
        sf::RenderWindow& _window;
        sf::Font _font;
        bool _fontLoaded = false;

        const int CELL_SIZE = 30;

        void DrawBoard();
        void DrawPiece();
        void DrawGameOver();
        void DrawDisplay();
        void DrawMenu();
        void DrawPause();
        void Clear();

    public:
        RenderingEngine(sf::RenderWindow& window, GameEngine& gameEngine)
            : _window(window), _gameEngine(gameEngine) 
        {
            if (_font.openFromFile("/System/Library/Fonts/Supplemental/Times New Roman.ttf"))
            {
                _fontLoaded = true;
            }
            else
            {
                _fontLoaded = false;
                std::printf("error!\n");
            }
        }

        void Render();
};