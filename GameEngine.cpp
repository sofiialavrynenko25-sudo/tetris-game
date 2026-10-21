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

    _canHold = true;
}

bool GameEngine::MovePiece(int newX, int newY)
{
    if (_activePiece.GetType() == TetrominoType::None)
    {
        return false;
    }

    Position target = Position(newX, newY);

    if (IsValidMove(_activePiece, target))
    {
        _activePiece.Move(newX, newY);
        return true;
    }

    return false;
}

bool GameEngine::RotatePieceLeft()
{
    if (_activePiece.GetType() == TetrominoType::None)
    {
        return false;
    }

    Tetromino testPiece = _activePiece;
    testPiece.RotateLeft();

    if (IsValidMove(testPiece, testPiece.GetPosition()))
    {
        _activePiece.RotateLeft();
        return true;
    }

    return false;
}

bool GameEngine::RotatePieceRight()
{
    if (_activePiece.GetType() == TetrominoType::None)
    {
        return false;
    }

    Tetromino testPiece = _activePiece;
    testPiece.RotateRight();

    if (IsValidMove(testPiece, testPiece.GetPosition()))
    {
        _activePiece.RotateRight();
        return true;
    }

    return false;
}

void GameEngine::HardDrop()
{

}

void GameEngine::HoldPiece()
{
    if (!_canHold || _activePiece.GetType() == TetrominoType::None)
    {
        return;
    }

    Tetromino temp = Tetromino(_activePiece.GetType(), _activePiece.GetColor(), Position(-1, -1));

    if (_heldPiece.GetType() == TetrominoType::None)
    {
        _heldPiece = temp;
        SpawnPiece();
    }
    else
    {
        Tetromino tempCurr = _heldPiece;
        _heldPiece = temp;

        _activePiece = tempCurr;

        int spawnX = (_board.GetWidth() / 2) - 2;
        int spawnY = 0;
        _activePiece.Move(spawnX, spawnY);

        if (!IsValidMove(_activePiece, Position(spawnX, spawnY)))
        {
            _state = GameState::GameOver;
        }
    }

    _canHold = false;
}

bool GameEngine::CheckGameOver()
{
    return _state == GameState::GameOver;
}

bool GameEngine::ResetGame()
{
    _board.ClearAll();

    _activePiece = Tetromino(TetrominoType::None, "", Position(-1, -1));
    _heldPiece = Tetromino(TetrominoType::None, "", Position(-1, -1));
    _canHold = true;

    std::queue<Tetromino> emptyQueue = {};
    _nextQueue = emptyQueue;

    _currScore = 0;
    _linesCleared = 0;

    _state = GameState::Playing;

    SpawnPiece();

    return true;
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