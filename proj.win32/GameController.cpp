#include "controllers/GameController.h"
#include <memory>
#include "configs/LevelConfig.h"
#include "configs/loaders/LevelConfigLoader.h"
#include "models/GameModel.h"
#include "services/GameModelFromLevelGenerator.h"
#include "services/MatchService.h"
#include "views/GameView.h"

namespace
{
    const float kCardMoveDuration = 0.3f;
    const float kTopCardY = 200.0f;
    const float kTopCardXMargin = 200.0f;
}

void GameController::init(GameView* view)
{
    _view = view;
    _cardController.init(view);
}

bool GameController::startGame(const std::string& levelConfigPath)
{
    if (!_view)
        return false;

    LevelConfig levelConfig;
    if (!LevelConfigLoader::loadFromFile(levelConfigPath, &levelConfig))
    {
        _view->setStatusText("Failed to load level config");
        return false;
    }

    _model = std::make_unique<GameModel>();
    GameModelFromLevelGenerator::populateGameModel(levelConfig, _model.get());

    _undoManager.clear();
    _cardController.init(_view);
    createCardViews();
    refreshTopCard();
    _view->setStatusText("Level loaded from config");
    return true;
}

void GameController::onPlayfieldCardClicked(int cardId)
{
    handleCardSelection(cardId, false);
}

void GameController::onStackCardClicked(int cardId)
{
    handleCardSelection(cardId, true);
}

void GameController::undo()
{
    if (_isAnimating || !_model || !_undoManager.canUndo())
        return;

    const UndoRecord record = _undoManager.popUndo();
    CardModel* cardModel = _model->findCardById(record.cardId);
    if (!cardModel)
        return;

    _isAnimating = true;
    _model->setTopCard(record.previousTopFace, record.previousTopSuit);
    _model->setCardRemoved(record.cardId, false);
    refreshTopCard();

    _cardController.setCardVisible(record.cardId, true);
    _cardController.restoreCard(record.cardId, record.originalPosition, kCardMoveDuration, [this]() {
        _isAnimating = false;
        if (_view)
            _view->setStatusText("Undo complete");
        });
}

void GameController::createCardViews()
{
    if (!_model)
        return;

    for (const CardModel& card : _model->getPlayfieldCards())
    {
        _cardController.createCard(card, [this](int cardId) {
            onPlayfieldCardClicked(cardId);
            });
    }

    for (const CardModel& card : _model->getStackCards())
    {
        if (card.id == -1)
            continue;

        _cardController.createCard(card, [this](int cardId) {
            onStackCardClicked(cardId);
            });
    }
}

void GameController::handleCardSelection(int cardId, bool isStackCard)
{
    if (_isAnimating || !_model)
        return;

    CardModel* cardModel = _model->findCardById(cardId);
    if (!cardModel || cardModel->isRemoved)
        return;

    if (!isStackCard && !MatchService::canMatch(cardModel->face, _model->getTopCardFace()))
    {
        if (_view)
            _view->setStatusText("Playfield card must be +/-1 from top card");
        return;
    }

    UndoRecord record;
    record.cardId = cardId;
    record.sourceArea = cardModel->area;
    record.originalPosition = cocos2d::Vec2(cardModel->x, cardModel->y);
    record.previousTopFace = _model->getTopCardFace();
    record.previousTopSuit = _model->getTopCardSuit();
    _undoManager.record(record);

    _isAnimating = true;
    _cardController.moveCardTo(cardId, getTopCardPosition(), kCardMoveDuration, [this, cardId, isStackCard]() {
        finishCardMove(cardId, isStackCard);
        });
}

void GameController::finishCardMove(int cardId, bool isStackCard)
{
    if (!_model)
        return;

    CardModel* cardModel = _model->findCardById(cardId);
    if (!cardModel)
        return;

    _model->setTopCard(cardModel->face, cardModel->suit);
    _model->setCardRemoved(cardId, true);
    refreshTopCard();
    _cardController.setCardVisible(cardId, false);
    _isAnimating = false;

    if (_view)
    {
        _view->setStatusText(isStackCard ? "Stack card replaced the top card" : "Playfield card matched and replaced the top card");
    }
}

void GameController::refreshTopCard()
{
    if (!_model)
        return;

    _cardController.replaceTopCard(_model->getTopCardFace(), _model->getTopCardSuit(), getTopCardPosition());
}

cocos2d::Vec2 GameController::getTopCardPosition() const
{
    cocos2d::Size visibleSize = cocos2d::Director::getInstance()->getVisibleSize();
    return cocos2d::Vec2(visibleSize.width - kTopCardXMargin, kTopCardY);
}
