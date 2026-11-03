#include "UserInputManager.h"

ICommand* UserInputManager::ProcessInput(const sf::Event& event, GameState state)
{
    const auto* keyPressed = event.getIf<sf::Event::KeyPressed>();

    if (keyPressed == nullptr)
    {
        return nullptr;
    }

    auto gameState = _connections.find(state);

    if (gameState == _connections.end())
    {
        return nullptr;
    }

    auto command = gameState -> second.find(keyPressed -> code);

    if (command == gameState -> second.end())
    {
        return nullptr;
    }

    return command -> second.get();
}