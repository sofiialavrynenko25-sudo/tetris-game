#include <SFML/Graphics.hpp>

#include "UserInputManager.h"

void UserInputManager::ProcessInput(const sf::Event& event)
{
    if (const auto* keyPressed = event.getIf<sf::Event::KeyPressed>())
    {
        Position currPosition = _gameEngine.GetActivePiece().GetPosition();

        int currX = currPosition.GetX();
        int currY = currPosition.GetY();

        if (keyPressed -> code == sf::Keyboard::Key::A)
        {
            _gameEngine.MovePiece(currX - 1, currY);
        }
        else if (keyPressed -> code == sf::Keyboard::Key::D)
        {
            _gameEngine.MovePiece(currX + 1, currY);
        }
        else if (keyPressed -> code == sf::Keyboard::Key::Space)
        {
            _gameEngine.HardDrop();
        }
        else if (keyPressed -> code == sf::Keyboard::Key::H)
        {
            _gameEngine.HoldPiece();
        }
        else if (keyPressed -> code == sf::Keyboard::Key::Left)
        {
            _gameEngine.RotatePieceLeft();
        }
        else if (keyPressed -> code == sf::Keyboard::Key::Right)
        {
            _gameEngine.RotatePieceRight();
        }
    }
}