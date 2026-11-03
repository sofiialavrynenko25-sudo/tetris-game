#pragma once

#include "GameEngine.h"

class ICommand
{
    public:
        virtual void Execute(GameEngine& gameEngine) = 0;
        virtual ~ICommand() = default;
};