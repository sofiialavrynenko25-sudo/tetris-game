#include "Commands.h"

void MoveLeftCmd::Execute(GameEngine& gameEngine)
{
    Position position = gameEngine.GetActivePiece().GetPosition();

    int x = position.GetX();
    int y = position.GetY();

    gameEngine.MovePiece(x - 1, y);
}

void MoveRightCmd::Execute(GameEngine& gameEngine)
{
    Position position = gameEngine.GetActivePiece().GetPosition();

    int x = position.GetX();
    int y = position.GetY();

    gameEngine.MovePiece(x + 1, y);
}

void RotateLeftCmd::Execute(GameEngine& gameEngine)
{
    gameEngine.RotatePieceLeft();
}

void RotateRightCmd::Execute(GameEngine& gameEngine)
{
    gameEngine.RotatePieceRight();
}

void HardDropCmd::Execute(GameEngine& gameEngine)
{
    gameEngine.HardDrop();
}

void HoldCmd::Execute(GameEngine& gameEngine)
{
    gameEngine.HoldPiece();
}

void PauseCmd::Execute(GameEngine& gameEngine)
{
    gameEngine.PauseGame();
}

void ResumeCmd::Execute(GameEngine& gameEngine)
{
    gameEngine.ResumeGame();
}

void SaveGameCmd::Execute(GameEngine& gameEngine)
{
    gameEngine.SaveGame();
}

void LoadGameCmd::Execute(GameEngine& gameEngine)
{
    gameEngine.LoadGame();
}

void GoToMenuCmd::Execute(GameEngine& gameEngine)
{
    gameEngine.GoToMenu();
}

void StartGameCmd::Execute(GameEngine& gameEngine)
{
    gameEngine.ResetGame();
}