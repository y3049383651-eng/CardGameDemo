#pragma once

#include "cocos2d.h"
#include "controllers/GameController.h"
#include "views/GameView.h"

class HelloWorld : public cocos2d::Scene
{
public:
    static cocos2d::Scene* createScene();
    virtual bool init();

    CREATE_FUNC(HelloWorld);

private:
    GameController* _controller;
    GameView* _view;
};
