#pragma once

#include <vector>
#include "models/CardModel.h"

class GameModel
{
public:
    const std::vector<CardModel>& getPlayfieldCards() const;
    const std::vector<CardModel>& getStackCards() const;

    void setPlayfieldCards(const std::vector<CardModel>& cards);
    void setStackCards(const std::vector<CardModel>& cards);

    CardModel* findCardById(int cardId);
    const CardModel* findCardById(int cardId) const;

    int getTopCardFace() const;
    int getTopCardSuit() const;

    void setTopCard(int face, int suit);
    void setCardRemoved(int cardId, bool isRemoved);

private:
    std::vector<CardModel> _playfieldCards;
    std::vector<CardModel> _stackCards;
    int _topCardFace = 0;
    int _topCardSuit = 0;
};
