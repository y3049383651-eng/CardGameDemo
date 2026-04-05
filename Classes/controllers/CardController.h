#pragma once

#include <functional>
#include <unordered_map>
#include "cocos2d.h"

struct CardModel;
class CardView;
class GameView;

class CardController
{
public:
    void init(GameView* view);
    void reset();

    CardView* createCard(const CardModel& cardModel, const std::function<void(int)>& onCardClicked);
    void replaceTopCard(int face, int suit, const cocos2d::Vec2& position);

    CardView* getCardView(int cardId) const;
    void moveCardTo(int cardId, const cocos2d::Vec2& targetPosition, float duration, const std::function<void()>& onFinished);
    void restoreCard(int cardId, const cocos2d::Vec2& originalPosition, float duration, const std::function<void()>& onFinished);
    void setCardVisible(int cardId, bool isVisible);

private:
    void bindCardCallback(int cardId);

    GameView* _view = nullptr;
    CardView* _topCard = nullptr;
    std::unordered_map<int, CardView*> _cardViews;
    std::unordered_map<int, std::function<void(int)>> _clickCallbacks;
};
