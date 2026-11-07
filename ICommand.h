#pragma once

class GameEngine;

class ICommand
{
    public:
        virtual void Execute(GameEngine& gameEngine) = 0;
        virtual ~ICommand() = default;
};