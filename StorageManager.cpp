#include <string>
#include <fstream>

#include "StorageManager.h"
#include "TetrominoType.h"

bool StorageManager::Save(Data data, std::string filepath)
{
    std::ofstream file(filepath);

    if (!file.is_open())
    {
        return false;
    }

    const int* board = data.GetBoardState();

    for (int i = 0; i < 20; i++)
    {
        for (int j = 0; j < 10; j++)
        {
            file << board[i * 10 + j] << " ";
        }

        file << "\n";
    }

    file << data.GetScore() << "\n" <<
            data.GetLinesCleared() << "\n" <<
            static_cast<int>(data.GetActivePiece()) << "\n" <<
            static_cast<int>(data.GetHeldPiece()) << "\n";

    file.close();

    return true;
}

Data StorageManager::Load(std::string filepath)
{
    std::ifstream file(filepath);

    if (!file.is_open())
    {
        int emptyBoard[20][10] = { {0} };
        return Data(emptyBoard, 0, 0, TetrominoType::None, TetrominoType::None);
    }

    int score = 0;
    int linesCleared = 0;
    int activePiece = 0;
    int heldPiece = 0;

    int board[20][10] = { {0} };

    for (int i = 0; i < 20; i++)
    {
        for (int j = 0; j < 10; j++)
        {
            file >> board[i][j];
        }
    }

    file >> score >> linesCleared >> activePiece >> heldPiece;

    TetrominoType activePieceType = static_cast<TetrominoType>(activePiece);
    TetrominoType heldPieceType = static_cast<TetrominoType>(heldPiece);

    file.close();

    return Data(board, score, linesCleared, activePieceType, heldPieceType);
}

bool StorageManager::SaveHighScore(int score)
{
    std::ofstream file("highscore.txt");

    if (!file.is_open())
    {
        return false;
    }

    file << score;

    file.close();

    return true;
}

int StorageManager::LoadHighScore()
{
    std::ifstream file("highscore.txt");

    if (!file.is_open())
    {
        return 0;
    }

    int score = 0;
    file >> score;

    file.close();

    return score;
}