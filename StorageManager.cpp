#include <string>

#include "StorageManager.h"
#include "TetrominoType.h"

bool StorageManager::Save(Data data, std::string filepath)
{
    return false;
}

Data StorageManager::Load(std::string filepath)
{
    int emptyBoard[20][10] = { {0} };
    return Data(emptyBoard, 0, 0, TetrominoType::None, TetrominoType::None);
}

bool StorageManager::SaveHighScore(int score)
{
    return false;
}

int StorageManager::LoadHighScore()
{
    return 0;
}