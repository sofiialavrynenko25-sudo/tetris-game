#pragma once

#include <SFML/Graphics.hpp>
#include <map>
#include <memory>

#include "GameEngine.h"
#include "ICommand.h"
#include "Commands.h"

class UserInputManager
{
    private:
        std::map<GameState, std::map<sf::Keyboard::Key, std::unique_ptr<ICommand>>> _connections;

    public:
        UserInputManager()
        {
            _connections[GameState::Menu][sf::Keyboard::Key::Enter] = std::make_unique<StartGameCmd>();
            _connections[GameState::Menu][sf::Keyboard::Key::L] = std::make_unique<LoadGameCmd>();

            _connections[GameState::Playing][sf::Keyboard::Key::A] = std::make_unique<MoveLeftCmd>();
            _connections[GameState::Playing][sf::Keyboard::Key::D] = std::make_unique<MoveRightCmd>();
            _connections[GameState::Playing][sf::Keyboard::Key::Left] = std::make_unique<RotateLeftCmd>();
            _connections[GameState::Playing][sf::Keyboard::Key::Right] = std::make_unique<RotateRightCmd>();
            _connections[GameState::Playing][sf::Keyboard::Key::Space] = std::make_unique<HardDropCmd>();
            _connections[GameState::Playing][sf::Keyboard::Key::H] = std::make_unique<HoldCmd>();
            _connections[GameState::Playing][sf::Keyboard::Key::P] = std::make_unique<PauseCmd>();

            _connections[GameState::Paused][sf::Keyboard::Key::P] = std::make_unique<ResumeCmd>();
            _connections[GameState::Paused][sf::Keyboard::Key::S] = std::make_unique<SaveGameCmd>();
            _connections[GameState::Paused][sf::Keyboard::Key::L] = std::make_unique<LoadGameCmd>();
            _connections[GameState::Paused][sf::Keyboard::Key::M] = std::make_unique<GoToMenuCmd>();

            _connections[GameState::GameOver][sf::Keyboard::Key::R] = std::make_unique<StartGameCmd>();
            _connections[GameState::GameOver][sf::Keyboard::Key::M] = std::make_unique<GoToMenuCmd>();
        }

        ICommand* ProcessInput(const sf::Event& event, GameState state);
};