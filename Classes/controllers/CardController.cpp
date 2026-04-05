#include "controllers/CardController.h"

#include "models/CardModel.h"
#include "views/CardView.h"
#include "views/GameView.h"

namespace
{
const float kCardScale = 1.4f;
}

void CardController::init(GameView* view)
{
    _view = view;
    reset();
}

void CardController::reset()
{
    _cardViews.clear();
    _clickCallbacks.clear();
    _topCard = nullptr;
}

CardView* CardController::createCard(const CardModel& cardModel, const std::function<void(int)>& onCardClicked)
{
    if (!_view)
        return nullptr;

    CardView* cardView = CardView::create(cardModel.face, cardModel.suit);
    if (!cardView)
        return nullptr;

    cardView->setScale(kCardScale);
    cardView->setPosition(cardModel.x, cardModel.y);
    cardView->setVisible(!cardModel.isRemoved);
    _clickCallbacks[cardModel.id] = onCardClicked;
    _view->addCard(cardView);
    _cardViews[cardModel.id] = cardView;
    bindCardCallback(cardModel.id);
    return cardView;
}

void CardController::replaceTopCard(int face, int suit, const cocos2d::Vec2& position)
{
    if (!_view)
        return;

    if (_topCard)
    {
        _topCard->removeFromParent();
        _topCard = nullptr;
    }

    _topCard = CardView::create(face, suit);
    if (!_topCard)
        return;

    _topCard->setScale(kCardScale);
    _topCard->setPosition(position);
    _view->addCard(_topCard);
}

CardView* CardController::getCardView(int cardId) const
{
    auto iter = _cardViews.find(cardId);
    if (iter == _cardViews.end())
        return nullptr;

    return iter->second;
}

void CardController::moveCardTo(int cardId, const cocos2d::Vec2& targetPosition, float duration, const std::function<void()>& onFinished)
{
    CardView* cardView = getCardView(cardId);
    if (!cardView)
        return;

    cardView->stopAllActions();
    cardView->setClickCallback(nullptr);

    auto move = cocos2d::MoveTo::create(duration, targetPosition);
    auto finish = cocos2d::CallFunc::create([onFinished]() {
        if (onFinished)
            onFinished();
    });

    cardView->runAction(cocos2d::Sequence::create(move, finish, nullptr));
}

void CardController::restoreCard(int cardId, const cocos2d::Vec2& originalPosition, float duration, const std::function<void()>& onFinished)
{
    CardView* cardView = getCardView(cardId);
    if (!cardView)
        return;

    cardView->stopAllActions();
    cardView->setClickCallback(nullptr);

    auto move = cocos2d::MoveTo::create(duration, originalPosition);
    auto finish = cocos2d::CallFunc::create([this, cardId, onFinished]() {
        bindCardCallback(cardId);
        if (onFinished)
            onFinished();
    });

    cardView->runAction(cocos2d::Sequence::create(move, finish, nullptr));
}

void CardController::setCardVisible(int cardId, bool isVisible)
{
    CardView* cardView = getCardView(cardId);
    if (!cardView)
        return;

    cardView->setVisible(isVisible);
}

void CardController::bindCardCallback(int cardId)
{
    CardView* cardView = getCardView(cardId);
    auto callbackIter = _clickCallbacks.find(cardId);
    if (!cardView || callbackIter == _clickCallbacks.end())
        return;

    const std::function<void(int)>& callback = callbackIter->second;
    cardView->setClickCallback([cardId, callback](CardView*) {
        if (callback)
            callback(cardId);
    });
}
