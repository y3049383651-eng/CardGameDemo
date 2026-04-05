#pragma once

#include <vector>
#include "cocos2d.h"

struct LevelCardConfig
{
    int face = 0;
    int suit = 0;
    cocos2d::Vec2 position = cocos2d::Vec2::ZERO;
};

class LevelConfig
{
public:
    const std::vector<LevelCardConfig>& getPlayfieldCards() const;
    const std::vector<LevelCardConfig>& getStackCards() const;

    void setPlayfieldCards(const std::vector<LevelCardConfig>& cards);
    void setStackCards(const std::vector<LevelCardConfig>& cards);

private:
    std::vector<LevelCardConfig> _playfieldCards;
    std::vector<LevelCardConfig> _stackCards;
};
