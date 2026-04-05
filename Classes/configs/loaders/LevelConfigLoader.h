#pragma once

#include <string>

class LevelConfig;

class LevelConfigLoader
{
public:
    static bool loadFromFile(const std::string& filePath, LevelConfig* outConfig);
};
