#include "views/CardView.h"

USING_NS_CC;

CardView* CardView::create(int face, int suit)
{
    auto ret = new CardView();
    if (ret && ret->init(face, suit))
    {
        ret->autorelease();
        return ret;
    }
    delete ret;
    return nullptr;
}

bool CardView::init(int face, int suit)
{
    if (!Node::init())
        return false;

    _cardId = face;
    _suit = suit;

    auto bg = Sprite::create("res/card_general.png");
    if (!bg)
        return false;

    this->addChild(bg);

    Size size = bg->getContentSize();
    this->setContentSize(size);

    bool isRed = (suit == 1 || suit == 2);
    std::string color = isRed ? "red" : "black";

    std::string faceStr;
    switch (face)
    {
    case 0: faceStr = "A"; break;
    case 10: faceStr = "J"; break;
    case 11: faceStr = "Q"; break;
    case 12: faceStr = "K"; break;
    default:
        faceStr = StringUtils::format("%d", face + 1);
        break;
    }

    std::string smallPath = StringUtils::format("res/number/small_%s_%s.png", color.c_str(), faceStr.c_str());
    std::string bigPath = StringUtils::format("res/number/big_%s_%s.png", color.c_str(), faceStr.c_str());

    std::string suitPath;
    switch (suit)
    {
    case 0: suitPath = "res/suits/club.png"; break;
    case 1: suitPath = "res/suits/diamond.png"; break;
    case 2: suitPath = "res/suits/heart.png"; break;
    case 3: suitPath = "res/suits/spade.png"; break;
    }

    auto smallsp = Sprite::create(smallPath);
    if (smallsp)
    {
        smallsp->setAnchorPoint(Vec2(0, 1));
        smallsp->setPosition(Vec2(10, size.height - 10));
        smallsp->setScale(0.8f);
        bg->addChild(smallsp);
    }

    auto suitsp = Sprite::create(suitPath);
    if (suitsp)
    {
        suitsp->setAnchorPoint(Vec2(1, 1));
        suitsp->setPosition(Vec2(size.width - 10, size.height - 10));
        suitsp->setScale(0.8f);
        bg->addChild(suitsp);
    }

    auto bigsp = Sprite::create(bigPath);
    if (bigsp)
    {
        bigsp->setPosition(Vec2(size.width / 2, size.height / 2));
        bigsp->setScale(1.2f);
        bg->addChild(bigsp);
    }

    auto listener = EventListenerTouchOneByOne::create();

    listener->onTouchBegan = [this](Touch* touch, Event* event) {

        Vec2 local = this->convertToNodeSpace(touch->getLocation());
        Rect rect(0, 0, this->getContentSize().width, this->getContentSize().height);

        if (rect.containsPoint(local))
        {
            if (_clickCallback)
                _clickCallback(this);

            return true;
        }
        return false;
        };

    _eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);

    return true;
}

void CardView::setClickCallback(std::function<void(CardView*)> cb)
{
    _clickCallback = cb;
}
