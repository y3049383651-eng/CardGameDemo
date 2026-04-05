#include "configs/LevelConfig.h"

const std::vector<LevelCardConfig>& LevelConfig::getPlayfieldCards() const
{
    return _playfieldCards;
}

const std::vector<LevelCardConfig>& LevelConfig::getStackCards() const
{
    return _stackCards;
}

void LevelConfig::setPlayfieldCards(const std::vector<LevelCardConfig>& cards)
{
    _playfieldCards = cards;
}

void LevelConfig::setStackCards(const std::vector<LevelCardConfig>& cards)
{
    _stackCards = cards;
}
