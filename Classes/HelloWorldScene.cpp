#include "HelloWorldScene.h"

USING_NS_CC;

Scene* HelloWorld::createScene()
{
    return HelloWorld::create();
}

bool HelloWorld::init()
{
    if (!Scene::init())
        return false;

    auto visibleSize = Director::getInstance()->getVisibleSize();

    _view = GameView::create();
    _controller = new GameController();

    this->addChild(_view);

    _controller->init(_view);
    _controller->startGame("configs/levels/task2_level.json");

    auto undoLabel = Label::createWithSystemFont("Undo", "Arial", 40);
    undoLabel->setColor(Color3B::YELLOW);

    auto undoItem = MenuItemLabel::create(
        undoLabel,
        [this](Ref*) {
            if (_controller)
            {
                _controller->undo();
            }
        }
    );

    undoItem->setPosition(Vec2(
        visibleSize.width - 120,
        visibleSize.height - 80
    ));

    auto menu = Menu::create(undoItem, nullptr);
    menu->setPosition(Vec2::ZERO);

    this->addChild(menu, 999);

    return true;
}
