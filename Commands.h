#pragma once

#include "ICommand.h"

class MoveLeftCmd : public ICommand
{
    public:
        void Execute(GameEngine& gameEngine) override;
};

class MoveRightCmd : public ICommand
{
    public:
        void Execute(GameEngine& gameEngine) override;
};

class RotateLeftCmd : public ICommand
{
    public:
        void Execute(GameEngine& gameEngine) override;
};

class RotateRightCmd : public ICommand
{
    public:
        void Execute(GameEngine& gameEngine) override;
};

class HardDropCmd : public ICommand
{
    public:
        void Execute(GameEngine& gameEngine) override;
};

class HoldCmd : public ICommand
{
    public:
        void Execute(GameEngine& gameEngine) override;
};

class PauseCmd : public ICommand
{
    public:
        void Execute(GameEngine& gameEngine) override;
};

class ResumeCmd : public ICommand
{
    public:
        void Execute(GameEngine& gameEngine) override;
};

class SaveGameCmd : public ICommand
{
    public:
        void Execute(GameEngine& gameEngine) override;
};

class LoadGameCmd : public ICommand
{
    public:
        void Execute(GameEngine& gameEngine) override;
};

class GoToMenuCmd : public ICommand
{
    public:
        void Execute(GameEngine& gameEngine) override;
};

class StartGameCmd : public ICommand
{
    public:
        void Execute(GameEngine& gameEngine) override;
};