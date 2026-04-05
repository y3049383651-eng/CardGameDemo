#pragma once
#include "cocos2d.h"

USING_NS_CC;

class GameView : public Node
{
public:
    CREATE_FUNC(GameView);

    bool init() override;
    void addCard(Node* card);
    void setStatusText(const std::string& text);

private:
    Label* _statusLabel = nullptr;
};
