#pragma once

#include "cocos2d.h"
#include <functional>

USING_NS_CC;

class CardView : public Node
{
public:
    static CardView* create(int face, int suit);
    bool init(int face, int suit);

    void setClickCallback(std::function<void(CardView*)> cb);

    int getCardId() const { return _cardId; }
    int getSuit() const { return _suit; }

private:
    int _cardId;
    int _suit;

    std::function<void(CardView*)> _clickCallback;
};