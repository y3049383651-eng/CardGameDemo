#include "models/GameModel.h"

const std::vector<CardModel>& GameModel::getPlayfieldCards() const
{
    return _playfieldCards;
}

const std::vector<CardModel>& GameModel::getStackCards() const
{
    return _stackCards;
}

void GameModel::setPlayfieldCards(const std::vector<CardModel>& cards)
{
    _playfieldCards = cards;
}

void GameModel::setStackCards(const std::vector<CardModel>& cards)
{
    _stackCards = cards;
}

CardModel* GameModel::findCardById(int cardId)
{
    for (auto& card : _playfieldCards)
    {
        if (card.id == cardId)
            return &card;
    }

    for (auto& card : _stackCards)
    {
        if (card.id == cardId)
            return &card;
    }

    return nullptr;
}

const CardModel* GameModel::findCardById(int cardId) const
{
    for (const auto& card : _playfieldCards)
    {
        if (card.id == cardId)
            return &card;
    }

    for (const auto& card : _stackCards)
    {
        if (card.id == cardId)
            return &card;
    }

    return nullptr;
}

int GameModel::getTopCardFace() const
{
    return _topCardFace;
}

int GameModel::getTopCardSuit() const
{
    return _topCardSuit;
}

void GameModel::setTopCard(int face, int suit)
{
    _topCardFace = face;
    _topCardSuit = suit;
}

void GameModel::setCardRemoved(int cardId, bool isRemoved)
{
    CardModel* card = findCardById(cardId);
    if (!card)
        return;

    card->isRemoved = isRemoved;
}
