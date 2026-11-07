#include "RenderingEngine.h"

void RenderingEngine::DrawBoard()
{
    Board board = _gameEngine.GetBoard();
    const int* boardGrid = board.GetGrid();

    for (int i = 0; i < board.GetHeight(); i++)
    {
        for (int j = 0; j < board.GetWidth(); j++)
        {
            if (boardGrid[i * 10 + j] != 0)
            {
                sf::RectangleShape cell(sf::Vector2f(static_cast<float>(CELL_SIZE - 1), static_cast<float>(CELL_SIZE - 1)));
                cell.setPosition(sf::Vector2f(static_cast<float>(j * CELL_SIZE), static_cast<float>(i * CELL_SIZE)));

                cell.setFillColor(sf::Color::Blue);

                _window.draw(cell);
            }
        }
    }
}

void RenderingEngine::DrawPiece()
{
    Tetromino piece = _gameEngine.GetActivePiece();

    if (piece.GetType() == TetrominoType::None)
    {
        return;
    }

    const int* shape = piece.GetShape();
    Position position = piece.GetPosition();

    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            if (shape[i *4 + j] == 1)
            {
                int boardX = position.GetX() + j;
                int boardY = position.GetY() + i;

                sf::RectangleShape cell(sf::Vector2f(static_cast<float>(CELL_SIZE - 1), static_cast<float>(CELL_SIZE - 1)));
                cell.setPosition(sf::Vector2f(static_cast<float>(boardX * CELL_SIZE), static_cast<float>(boardY * CELL_SIZE)));

                if (piece.GetIsBomb())
                {
                    cell.setFillColor(sf::Color::Red);
                }
                else
                {
                    cell.setFillColor(sf::Color::Green);
                }

                _window.draw(cell);
            }
        }
    }
}

void RenderingEngine::DrawGameOver()
{
    if (!_gameEngine.CheckGameOver())
    {
        return;
    }

    sf::RectangleShape overlay(sf::Vector2f(440.f, 600.f));
    overlay.setFillColor(sf::Color::Black);
    _window.draw(overlay); 

    if (_fontLoaded)
    {
        sf::Text game(_font);
        game.setCharacterSize(50);
        game.setFillColor(sf::Color::Red);
        game.setString("GAME");
        game.setPosition(sf::Vector2f(220.f, 100.f));

        _window.draw(game);

        sf::Text over(_font);
        over.setCharacterSize(50);
        over.setFillColor(sf::Color::Red);
        over.setString("OVER");
        over.setPosition(sf::Vector2f(220.f, 180.f));
            
        _window.draw(over);

        sf::Text resume(_font);
        resume.setCharacterSize(20);
        resume.setFillColor(sf::Color::White);
        resume.setString("R to restart");
        resume.setPosition(sf::Vector2f(220.f, 340.f));
            
        _window.draw(resume);

        sf::Text menu(_font);
        menu.setCharacterSize(20);
        menu.setFillColor(sf::Color::White);
        menu.setString("M to go to menu");
        menu.setPosition(sf::Vector2f(220.f, 390.f));
            
        _window.draw(menu);
    }
}

void RenderingEngine::DrawDisplay()
{
    float displayX = 300.f;

    sf::RectangleShape next(sf::Vector2f(100.f, 160.f));
    next.setPosition(sf::Vector2f(displayX + 25.f, 130.f));
    next.setFillColor(sf::Color::Black);
    next.setOutlineColor(sf::Color::White);
    next.setOutlineThickness(2.f);
    _window.draw(next);

    sf::RectangleShape hold(sf::Vector2f(100.f, 90.f));
    hold.setPosition(sf::Vector2f(displayX + 25.f, 440.f));
    hold.setFillColor(sf::Color::Black);
    hold.setOutlineColor(sf::Color::White);
    hold.setOutlineThickness(2.f);
    _window.draw(hold);

    std::queue<Tetromino> nextQueue = _gameEngine.GetNextQueue();
    
    if (!nextQueue.empty())
    {
        Tetromino nextPiece = nextQueue.front();
        const int* shape = nextPiece.GetShape();

        float nextX = displayX + 35.f;
        float nextY = 150.f;

        for (int i = 0; i < 4; i++)
        {
            for (int j = 0; j < 4; j++)
            {
                if (shape[i * 4 + j] == 1)
                {
                    sf::RectangleShape cell(sf::Vector2f(static_cast<float>(CELL_SIZE - 4), static_cast<float>(CELL_SIZE - 4)));
                    cell.setPosition(sf::Vector2f(nextX + (j * (CELL_SIZE - 4)), nextY + (i * (CELL_SIZE - 4))));
                    
                    if (nextPiece.GetIsBomb())
                    {
                        cell.setFillColor(sf::Color::Red);
                    }
                    else
                    {
                        cell.setFillColor(sf::Color::Green);
                    }
                    _window.draw(cell);
                }
            }
        }
    }

    Tetromino heldPiece = _gameEngine.GetHeldPiece();

    if (heldPiece.GetType() != TetrominoType::None)
    {
        const int* shape = heldPiece.GetShape();
        float holdX = displayX + 35.f;
        float holdY = 460.f;

        for (int i = 0; i < 4; i++)
        {
            for (int j = 0; j < 4; j++)
            {
                if (shape[i * 4 + j] == 1)
                {
                    sf::RectangleShape cell(sf::Vector2f(static_cast<float>(CELL_SIZE - 4), static_cast<float>(CELL_SIZE - 4)));
                    cell.setPosition(sf::Vector2f(holdX + (j * (CELL_SIZE - 4)), holdY + (i * (CELL_SIZE - 4))));
                    
                    if (heldPiece.GetIsBomb())
                    {
                        cell.setFillColor(sf::Color::Red);
                    }
                    else
                    {
                        cell.setFillColor(sf::Color::Green);
                    }
                    _window.draw(cell);
                }
            }
        }
    }

    if (_fontLoaded)
    {
        sf::Text title(_font);
        title.setCharacterSize(24);
        title.setFillColor(sf::Color::White);
        title.setString("TETRIS");
        title.setPosition(sf::Vector2f(displayX + 35.f, 40.f));

        _window.draw(title);

        sf::Text score(_font);
        score.setCharacterSize(18);
        score.setFillColor(sf::Color::White);
        score.setString("Score:\n" + std::to_string(_gameEngine.GetCurrScore()));
        score.setPosition(sf::Vector2f(displayX + 30.f, 80.f));

        _window.draw(score);
    }
}

void RenderingEngine::DrawMenu()
{
    if (_gameEngine.GetState().GetId() == GameState::Menu)
    {
        if (_fontLoaded)
        {
            sf::Text menu(_font);
            menu.setCharacterSize(50);
            menu.setFillColor(sf::Color::White);
            menu.setString("TETRIS");
            menu.setPosition(sf::Vector2f(220.f, 100.f));
            
            _window.draw(menu);

            sf::Text bestScore(_font);
            bestScore.setCharacterSize(20);
            bestScore.setFillColor(sf::Color::White);
            bestScore.setString("Best score:");
            bestScore.setPosition(sf::Vector2f(220.f, 200.f));
            
            _window.draw(bestScore);

            sf::Text bestScoreNum(_font);
            bestScoreNum.setCharacterSize(34);
            bestScoreNum.setFillColor(sf::Color::White);
            bestScoreNum.setString(std::to_string(_gameEngine.GetHighScore()));
            bestScoreNum.setPosition(sf::Vector2f(220.f, 240.f));
            
            _window.draw(bestScoreNum);

            sf::Text start(_font);
            start.setCharacterSize(20);
            start.setFillColor(sf::Color::White);
            start.setString("ENTER to start, L to load");
            start.setPosition(sf::Vector2f(220.f, 340.f));
            
            _window.draw(start);
        }
    }
}

void RenderingEngine::DrawPause()
{
    sf::RectangleShape overlay(sf::Vector2f(440.f, 600.f));
    overlay.setFillColor(sf::Color::Black);
    _window.draw(overlay); 

    if (_fontLoaded)
    {
        sf::Text pause(_font);
        pause.setCharacterSize(50);
        pause.setFillColor(sf::Color::White);
        pause.setString("PAUSED");
        pause.setPosition(sf::Vector2f(220.f, 100.f));
            
        _window.draw(pause);

        sf::Text resume(_font);
        resume.setCharacterSize(20);
        resume.setFillColor(sf::Color::White);
        resume.setString("P to resume");
        resume.setPosition(sf::Vector2f(220.f, 200.f));
            
        _window.draw(resume);

        sf::Text saveLoad(_font);
        saveLoad.setCharacterSize(20);
        saveLoad.setFillColor(sf::Color::White);
        saveLoad.setString("S / L to save / load");
        saveLoad.setPosition(sf::Vector2f(220.f, 280.f));
            
        _window.draw(saveLoad);

        sf::Text menu(_font);
        menu.setCharacterSize(20);
        menu.setFillColor(sf::Color::White);
        menu.setString("M to go to menu");
        menu.setPosition(sf::Vector2f(220.f, 360.f));
            
        _window.draw(menu);
    }
}

void RenderingEngine::Clear()
{
    _window.clear(sf::Color::Black);
}

void RenderingEngine::Render()
{
    Clear();

    GameState state = _gameEngine.GetState().GetId();

    if (state == GameState::Menu)
    {
        DrawMenu();
    }
    else
    {
        DrawBoard();
        DrawPiece();
        DrawDisplay();
        DrawGameOver();

        if (state == GameState::Paused)
        {
            DrawPause();
        }
    }

    _window.display();
}