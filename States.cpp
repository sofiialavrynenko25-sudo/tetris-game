#include "States.h"
#include "Commands.h"
#include "GameEngine.h"

ICommand* BaseState::HandleInput(const sf::Event& event)
{
    const auto* keyPressed = event.getIf<sf::Event::KeyPressed>();

    if (keyPressed == nullptr)
    {
        return nullptr;
    }

    auto command = _connections.find(keyPressed -> code);

    if (command == _connections.end())
    {
        return nullptr;
    }

    return command -> second.get();
}

MenuState::MenuState()
{
    _connections[sf::Keyboard::Key::Enter] = std::make_unique<StartGameCmd>();
    _connections[sf::Keyboard::Key::L] = std::make_unique<LoadGameCmd>();
}

void MenuState::Update(GameEngine& gameEngine, float time)
{}

GameState MenuState::GetId() const
{
    return GameState::Menu;
}

PlayingState::PlayingState()
{
    _connections[sf::Keyboard::Key::A] = std::make_unique<MoveLeftCmd>();
    _connections[sf::Keyboard::Key::D] = std::make_unique<MoveRightCmd>();
    _connections[sf::Keyboard::Key::Left] = std::make_unique<RotateLeftCmd>();
    _connections[sf::Keyboard::Key::Right] = std::make_unique<RotateRightCmd>();
    _connections[sf::Keyboard::Key::P] = std::make_unique<PauseCmd>();
    _connections[sf::Keyboard::Key::Space] = std::make_unique<HardDropCmd>();
    _connections[sf::Keyboard::Key::H] = std::make_unique<HoldCmd>();
}

void PlayingState::Update(GameEngine& gameEngine, float time)
{
    gameEngine.ApplyGravity(time);
}

GameState PlayingState::GetId() const
{
    return GameState::Playing;
}

PausedState::PausedState()
{
    _connections[sf::Keyboard::Key::P] = std::make_unique<ResumeCmd>();
    _connections[sf::Keyboard::Key::S] = std::make_unique<SaveGameCmd>();
    _connections[sf::Keyboard::Key::L] = std::make_unique<LoadGameCmd>();
    _connections[sf::Keyboard::Key::M] = std::make_unique<GoToMenuCmd>();
}

void PausedState::Update(GameEngine& gameEngine, float time)
{}

GameState PausedState::GetId() const
{
    return GameState::Paused;
}

GameOverState::GameOverState()
{
    _connections[sf::Keyboard::Key::R] = std::make_unique<StartGameCmd>();
    _connections[sf::Keyboard::Key::M] = std::make_unique<GoToMenuCmd>();
}

void GameOverState::Update(GameEngine& gameEngine, float time)
{}

GameState GameOverState::GetId() const
{
    return GameState::GameOver;
}