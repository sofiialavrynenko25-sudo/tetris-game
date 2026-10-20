#pragma once

#include <string>
#include <queue>

#include "Tetromino.h"
#include "Board.h"
#include "StorageManager.h"
#include "GameState.h"

class GameEngine
{
    private:
        Board _board = Board();
        Tetromino _activePiece = Tetromino(TetrominoType::None, "", Position(-1, -1));
        Tetromino _heldPiece = Tetromino(TetrominoType::None, "", Position(-1, -1));
        std::queue<Tetromino> _nextQueue = {};
        bool _canHold = true;
        int _currScore = 0;
        int _highScore = 0;
        int _linesCleared = 0;
        GameState _state = GameState::Menu;
        float _lockDelay = 0.0f;
        StorageManager _storage = StorageManager();

        void FillQueue();

    public:
        GameEngine()
        {
            _highScore = _storage.LoadHighScore();
        }

        void SpawnPiece();

        bool MovePiece(int newX, int newY);
        bool RotatePieceLeft();
        bool RotatePieceRight();

        void HardDrop();

        void HoldPiece();

        bool CheckGameOver();
        bool ResetGame();

        bool IsValidMove(Tetromino piece, Position newPosition);

        void Update(float time);

        void SaveGame();
        void LoadGame();

        Board GetBoard();
        Tetromino GetActivePiece();
        Tetromino GetHeldPiece();
        std::queue<Tetromino> GetNextQueue();
        int GetCurrScore();
        int GetHighScore();
};