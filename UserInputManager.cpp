#include "UserInputManager.h"

ICommand* UserInputManager::ProcessInput(const sf::Event& event)
{
    return _gameEngine.GetState().HandleInput(event);
}