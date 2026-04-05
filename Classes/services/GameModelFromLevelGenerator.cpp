#include "services/GameModelFromLevelGenerator.h"

#include <vector>
#include "configs/LevelConfig.h"
#include "models/GameModel.h"

namespace
{
const float kStackCardStartX = 200.0f;
const float kStackCardY = 200.0f;
const float kStackCardSpacing = 120.0f;
}

void GameModelFromLevelGenerator::populateGameModel(const LevelConfig& levelConfig, GameModel* gameModel)
{
    if (!gameModel)
        return;

    std::vector<CardModel> playfieldCards;
    std::vector<CardModel> stackCards;
    int nextCardId = 1;

    const std::vector<LevelCardConfig>& playfieldConfigs = levelConfig.getPlayfieldCards();
    playfieldCards.reserve(playfieldConfigs.size());
    for (const LevelCardConfig& config : playfieldConfigs)
    {
        CardModel card;
        card.id = nextCardId++;
        card.face = config.face;
        card.suit = config.suit;
        card.x = config.position.x;
        card.y = config.position.y;
        card.area = CardAreaType::Playfield;
        playfieldCards.push_back(card);
    }

    const std::vector<LevelCardConfig>& stackConfigs = levelConfig.getStackCards();
    stackCards.reserve(stackConfigs.size());
    for (size_t i = 0; i < stackConfigs.size(); ++i)
    {
        const LevelCardConfig& config = stackConfigs[i];

        CardModel card;
        card.id = nextCardId++;
        card.face = config.face;
        card.suit = config.suit;
        card.x = config.position.x;
        card.y = config.position.y;
        card.area = CardAreaType::Stack;

        if (card.x == 0.0f && card.y == 0.0f)
        {
            if (i == 0)
            {
                card.x = 0.0f;
                card.y = 0.0f;
            }
            else
            {
                card.x = kStackCardStartX + static_cast<float>(i - 1) * kStackCardSpacing;
                card.y = kStackCardY;
            }
        }

        stackCards.push_back(card);
    }

    gameModel->setPlayfieldCards(playfieldCards);
    gameModel->setStackCards(stackCards);

    if (!stackCards.empty())
    {
        gameModel->setTopCard(stackCards.front().face, stackCards.front().suit);
        gameModel->setCardRemoved(stackCards.front().id, true);
    }
}
