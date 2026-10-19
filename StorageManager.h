#pragma once

#include <string>

#include "Data.h"

class StorageManager
{
    public:
        bool Save(Data data, std::string filepath);
        Data Load(std::string filepath);
        bool SaveHighScore(int score);
        int LoadHighScore();
};