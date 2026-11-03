#include "GameEngine.h"

void GameEngine::FillQueue()
{
    while (_nextQueue.size() < 3)
    {
        std::vector<Tetromino> bag = {
        Tetromino(TetrominoType::I, "Cyan", Position(-1, -1)),
        Tetromino(TetrominoType::L, "Orange", Position(-1, -1)),
        Tetromino(TetrominoType::J, "Blue", Position(-1, -1)),
        Tetromino(TetrominoType::S, "Green", Position(-1, -1)),
        Tetromino(TetrominoType::Z, "Red", Position(-1, -1)),
        Tetromino(TetrominoType::O, "Yellow", Position(-1, -1)),
        Tetromino(TetrominoType::T, "Purple", Position(-1, -1))
        };

        std::shuffle(bag.begin(), bag.end(), _rng);

        for (const Tetromino& piece : bag)
        {
            _nextQueue.push(piece);
        }
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
        _lockDelay = 0.0f;
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
        _lockDelay = 0.0f;
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
        _lockDelay = 0.0f;
        return true;
    }

    return false;
}

void GameEngine::HardDrop()
{
    if (_activePiece.GetType() == TetrominoType::None)
    {
        return;
    }

    while (IsValidMove(_activePiece, Position(_activePiece.GetPosition().GetX(), _activePiece.GetPosition().GetY() + 1)))
    {
        _activePiece.Move(_activePiece.GetPosition().GetX(), _activePiece.GetPosition().GetY() + 1);
    }

    if (_activePiece.GetIsBomb())
    {
        _board.TriggerBomb(_activePiece);
    }
    else
    {
        _board.PlacePiece(_activePiece);
    }

    std::vector<int> fullRows = _board.CheckFullRows();

    if (!fullRows.empty())
    {
        for (int i = 0; i < fullRows.size(); i++)
        {
            _board.ClearRow(fullRows[i]);
        }
    }

    _currScore += VICTORY_POINTS * fullRows.size();
    _linesCleared += fullRows.size();

    if (_currScore > _highScore)
    {
        _highScore = _currScore;
        _storage.SaveHighScore(_highScore);
    }

    SpawnPiece();
}

void GameEngine::HoldPiece()
{
    if (!_canHold || _activePiece.GetType() == TetrominoType::None)
    {
        return;
    }

    Tetromino temp = Tetromino(_activePiece.GetType(), _activePiece.GetColor(), Position(-1, -1), _activePiece.GetIsBomb());

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

    _lockDelay = 0.0f;
    _dropTimer = 0.0f;

    _state = GameState::Playing;

    SpawnPiece();

    return true;
}

bool GameEngine::IsValidMove(Tetromino piece, Position newPosition)
{
    const int* shape = piece.GetShape();
    const int* grid = _board.GetGrid();
    
    int x = newPosition.GetX();
    int y = newPosition.GetY();

    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            if (shape[i * 4 + j] == 1)
            {
                int boardX = x + j;
                int boardY = y + i;

                if (boardX< 0 || boardY < 0 || 
                    boardX >= _board.GetWidth() || boardY >= _board.GetHeight())
                {
                    return false;
                }

                if (grid[boardY * 10 + boardX] == 1)
                {
                    return false;
                }
            }
        }
    }

    return true;
}

void GameEngine::Update(float time)
{
    if (_state != GameState::Playing)
    {
        return;
    }

    _dropTimer += time;

    if (IsValidMove(_activePiece, Position(_activePiece.GetPosition().GetX(), _activePiece.GetPosition().GetY() + 1)))
    {
        if (_dropTimer >= 0.5f)
        {
            _activePiece.Move(_activePiece.GetPosition().GetX(), _activePiece.GetPosition().GetY() + 1);
            _dropTimer = 0.0f;
        }

        _lockDelay = 0.0f;
    }
    else
    {
        _lockDelay += time;

        if (_lockDelay >= 0.5f)
        {
            if (_activePiece.GetIsBomb())
            {
                _board.TriggerBomb(_activePiece);
            }
            else
            {
                _board.PlacePiece(_activePiece);
            }

            _lockDelay = 0.0f;

            std::vector<int> fullRows = _board.CheckFullRows();

            if (!fullRows.empty())
            {
                for (int i = 0; i < fullRows.size(); i++)
                {
                    _board.ClearRow(fullRows[i]);
                }       
            }

            _currScore += VICTORY_POINTS * fullRows.size();
            _linesCleared += fullRows.size();

            if (_currScore > _highScore)
            {
                _highScore = _currScore;
                _storage.SaveHighScore(_highScore);
            }

            SpawnPiece();
        }
    }
}

void GameEngine::PauseGame()
{
    if (_state == GameState::Playing)
    {
        _state = GameState::Paused;
    }
}

void GameEngine::ResumeGame()
{
    if (_state == GameState::Paused)
    {
        _state = GameState::Playing;
    }
}

void GameEngine::GoToMenu()
{
    _state = GameState::Menu;
}

bool GameEngine::SaveGame()
{
    if (_state != GameState::Playing && _state != GameState::Paused)
    {
        return false;
    }
    const int* board = _board.GetGrid();

    Data toSave = Data(reinterpret_cast<const int(*)[10]>(board), 
                        _currScore,
                        _linesCleared,
                        _activePiece.GetType(),
                        _heldPiece.GetType());
                    
    if (!_storage.Save(toSave, "tetris_game.txt"))
    {
        return false;
    }

    return true;
}

bool GameEngine::LoadGame()
{
    Data loaded = _storage.Load("tetris_game.txt");

    TetrominoType active = loaded.GetActivePiece();
    
    if (active == TetrominoType::None)
    {
        return false;
    }

    _board.SetGrid(loaded.GetBoardState());
    _currScore = loaded.GetScore();
    _linesCleared = loaded.GetLinesCleared();

    _nextQueue = std::queue<Tetromino>();
    FillQueue();

    TetrominoType held = loaded.GetHeldPiece();

    if (held != TetrominoType::None)
    {
        _heldPiece = Tetromino(held, "", Position(-1, -1), false);
    }
    else
    {
        _heldPiece = Tetromino(TetrominoType::None, "", Position(-1, -1), false);
    }

    _activePiece = Tetromino(active, "", Position(-1, -1), false);

    int spawnX = (_board.GetWidth() / 2) - 2;
    _activePiece.Move(spawnX, 0);

    _canHold = true;

    _lockDelay = 0.0f;
    _dropTimer = 0.0f;

    if (!IsValidMove(_activePiece, _activePiece.GetPosition()))
    {
        _state = GameState::GameOver;
    }
    else
    {
        _state = GameState::Paused;
    }

    return true;
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

GameState GameEngine::GetState()
{
    return _state;
}