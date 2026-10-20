#include "GameEngine.h"

void GameEngine::SpawnPiece()
{

}

bool GameEngine::MovePiece(int newX, int newY)
{
    return false;
}

bool GameEngine::RotatePiece()
{
    return false;
}

void GameEngine::HardDrop()
{

}

void GameEngine::HoldPiece()
{

}

bool GameEngine::CheckGameOver()
{
    return false;
}

bool GameEngine::ResetGame()
{
    return false;
}

bool GameEngine::IsValidMove(Tetromino piece, Position newPosition)
{
    return false;
}

void GameEngine::Update(float time)
{

}

void GameEngine::SaveGame()
{

}

void GameEngine::LoadGame()
{

}

Board GameEngine::GetBoard()
{
    return _board;
}

Tetromino GameEngine::GetActivePiece()
{
    return _activePiece;
}

Tetromino GameEngine::GetHeldPiece()
{
    return _heldPiece;
}

std::queue<Tetromino> GameEngine::GetNextQueue()
{
    return _nextQueue;
}

int GameEngine::GetCurrScore()
{
    return _currScore;
}

int GameEngine::GetHighScore()
{
    return _highScore;
}