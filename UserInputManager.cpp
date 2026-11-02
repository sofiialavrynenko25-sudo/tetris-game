#include "UserInputManager.h"

void UserInputManager::ProcessInput(const sf::Event& event)
{
    const auto* keyPressed = event.getIf<sf::Event::KeyPressed>();

    if (keyPressed == nullptr)
    {
        return;
    }

    sf::Keyboard::Key key = keyPressed -> code;
    GameState state = _gameEngine.GetState();

    if (state == GameState::Menu)
    {
        if (key == sf::Keyboard::Key::Enter)
        {
            _gameEngine.ResetGame();
        }
        else if (key == sf::Keyboard::Key::L)
        {
            _gameEngine.LoadGame();
        }
    }
    else if (state == GameState::Playing)
    {
        Tetromino active = _gameEngine.GetActivePiece();
        Position activePosition = active.GetPosition();

        int x = activePosition.GetX();
        int y = activePosition.GetY();

        if (key == sf::Keyboard::Key::A)
        {
            _gameEngine.MovePiece(x - 1, y);
        }
        else if (key == sf::Keyboard::Key::D)
        {
            _gameEngine.MovePiece(x + 1, y);
        }
        else if (key == sf::Keyboard::Key::Space)
        {
            _gameEngine.HardDrop();
        }
        else if (key == sf::Keyboard::Key::H)
        {
            _gameEngine.HoldPiece();
        }
        else if (key == sf::Keyboard::Key::Left)
        {
            _gameEngine.RotatePieceLeft();
        }
        else if (key == sf::Keyboard::Key::Right)
        {
            _gameEngine.RotatePieceRight(); 
        }
        else if (key == sf::Keyboard::Key::P)
        {
            _gameEngine.PauseGame();
        }
    }
    else if (state == GameState::Paused)
    {
        if (key == sf::Keyboard::Key::P)
        {
            _gameEngine.ResumeGame();
        }
        else if (key == sf::Keyboard::Key::S)
        {
            _gameEngine.SaveGame();
        }
        else if (key == sf::Keyboard::Key::L)
        {
            _gameEngine.LoadGame();
        }
        else if (key == sf::Keyboard::Key::M)
        {
            _gameEngine.GoToMenu();
        }
    }
    else if (state == GameState::GameOver)
    {
        if (key == sf::Keyboard::Key::R)
        {
            _gameEngine.ResetGame();
        }
        else if (key == sf::Keyboard::Key::M)
        {
            _gameEngine.GoToMenu();
        }
    }
}