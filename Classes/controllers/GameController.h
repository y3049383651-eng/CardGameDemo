#pragma once

#include <memory>
#include <string>
#include "cocos2d.h"
#include "controllers/CardController.h"
#include "managers/UndoManager.h"
#include "models/GameModel.h"

class GameView;

class GameController
{
public:
    void init(GameView* view);
    bool startGame(const std::string& levelConfigPath);

    void onPlayfieldCardClicked(int cardId);
    void onStackCardClicked(int cardId);
    void undo();

private:
    void createCardViews();
    void handleCardSelection(int cardId, bool isStackCard);
    void finishCardMove(int cardId, bool isStackCard);
    void refreshTopCard();
    cocos2d::Vec2 getTopCardPosition() const;

    GameView* _view = nullptr;
    std::unique_ptr<GameModel> _model;
    CardController _cardController;
    UndoManager _undoManager;
    bool _isAnimating = false;
};
