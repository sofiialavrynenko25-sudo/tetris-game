#include "GameEngine.h"

void GameEngine::FillQueue()
{
    while (_nextQueue.size() < 3)
    {
        _nextQueue.push(Tetromino(TetrominoType::I, "Cyan", Position(-1, -1)));
        _nextQueue.push(Tetromino(TetrominoType::L, "Orange", Position(-1, -1)));
        _nextQueue.push(Tetromino(TetrominoType::J, "Blue", Position(-1, -1)));
        _nextQueue.push(Tetromino(TetrominoType::S, "Green", Position(-1, -1)));
        _nextQueue.push(Tetromino(TetrominoType::Z, "Red", Position(-1, -1)));
        _nextQueue.push(Tetromino(TetrominoType::O, "Yellow", Position(-1, -1)));
        _nextQueue.push(Tetromino(TetrominoType::T, "Purple", Position(-1, -1)));
    }
}

void GameEngine::SpawnPiece()
{
    FillQueue();
    
    _activePiece = _nextQueue.front();
    _nextQueue.pop();

    int spawnX = (_board.GetWidth() / 2) - 2;
    int spawnY = 0;

    _activePiece.Move(spawnX, spawnY);

    if (!IsValidMove(_activePiece, Position(spawnX, spawnY)))
    {
        _state = GameState::GameOver;
    }
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