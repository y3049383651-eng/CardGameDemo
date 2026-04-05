#pragma once

class GameModel;
class LevelConfig;

class GameModelFromLevelGenerator
{
public:
    static void populateGameModel(const LevelConfig& levelConfig, GameModel* gameModel);
};
