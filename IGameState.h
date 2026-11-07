#pragma once

#include <SFML/Graphics.hpp>

#include "GameState.h"

class ICommand;
class GameEngine;

class IGameState
{
    public:
        virtual void Update(GameEngine& engine, float time) = 0;
        virtual ICommand* HandleInput(const sf::Event& event) = 0;
        virtual GameState GetId() const = 0;
        virtual ~IGameState() = default;
};