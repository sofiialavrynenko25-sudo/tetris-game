#pragma once

#include "GameEngine.h"

class UserInputManager
{
    private:
        GameEngine& _gameEngine;

    public:
        UserInputManager(GameEngine& gameEngine)
            : _gameEngine(gameEngine) {}

        void ProcessInput(const sf::Event& event);
};