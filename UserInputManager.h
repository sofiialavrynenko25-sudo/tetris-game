#pragma once

#include <SFML/Graphics.hpp>
#include <map>
#include <memory>

#include "GameEngine.h"
#include "ICommand.h"

class UserInputManager
{
    private:
        GameEngine& _gameEngine;

    public:
        UserInputManager(GameEngine& gameEngine)
            : _gameEngine(gameEngine) {}

        ICommand* ProcessInput(const sf::Event& event);
};