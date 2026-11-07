#pragma once

#include <map>
#include <memory>
#include <SFML/Graphics.hpp>

#include "IGameState.h"
#include "ICommand.h"

class BaseState : public IGameState 
{
    protected: 
        std::map<sf::Keyboard::Key, std::unique_ptr<ICommand>> _connections;

    public:
        ICommand* HandleInput(const sf::Event& event) override;
};

class MenuState : public BaseState
{
    public:
        MenuState();
        void Update(GameEngine& gameEngine, float time) override;
        GameState GetId() const override;
};

class PlayingState : public BaseState
{
    public:
        PlayingState();
        void Update(GameEngine& gameEngine, float time) override;
        GameState GetId() const override;
};

class PausedState : public BaseState
{
    public:
        PausedState();
        void Update(GameEngine& gameEngine, float time) override;
        GameState GetId() const override;
};

class GameOverState : public BaseState
{
    public:
        GameOverState();
        void Update(GameEngine& gameEngine, float time) override;
        GameState GetId() const override;
};