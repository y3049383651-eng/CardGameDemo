#include "views/GameView.h"

bool GameView::init()
{
    if (!Node::init())
        return false;

    auto visibleSize = Director::getInstance()->getVisibleSize();

    // Background fills the whole screen
    auto background = LayerColor::create(Color4B(20, 90, 60, 255), visibleSize.width, visibleSize.height);
    background->setIgnoreAnchorPointForPosition(false);
    background->setAnchorPoint(Vec2::ZERO);
    background->setPosition(Vec2::ZERO);
    addChild(background, -10);

    // Define playfield and stack sizes (requested)
    const float kPlayfieldWidth = 1080.0f;
    const float kPlayfieldHeight = 1500.0f;
    const float kStackWidth = 1080.0f;
    const float kStackHeight = 580.0f;

    // Center areas horizontally
    float playfieldX = (visibleSize.width - kPlayfieldWidth) / 2.0f;
    float playfieldTopY = visibleSize.height - 80.0f; // leave some top margin

    auto playfieldLayer = LayerColor::create(Color4B(50, 140, 100, 200), kPlayfieldWidth, kPlayfieldHeight);
    playfieldLayer->setIgnoreAnchorPointForPosition(false);
    playfieldLayer->setAnchorPoint(Vec2(0.0f, 1.0f)); // position by top-left
    playfieldLayer->setPosition(Vec2(playfieldX, playfieldTopY));
    addChild(playfieldLayer, -5);

    // Place stack area below playfield with small gap
    float stackX = (visibleSize.width - kStackWidth) / 2.0f;
    float stackTopY = playfieldTopY - kPlayfieldHeight - 20.0f;
    auto stackLayer = LayerColor::create(Color4B(80, 180, 140, 200), kStackWidth, kStackHeight);
    stackLayer->setIgnoreAnchorPointForPosition(false);
    stackLayer->setAnchorPoint(Vec2(0.0f, 1.0f));
    stackLayer->setPosition(Vec2(stackX, stackTopY));
    addChild(stackLayer, -5);

    auto playfieldLabel = Label::createWithSystemFont("", "Arial", 36);
    playfieldLabel->setPosition(Vec2(playfieldX + 30.0f, playfieldTopY - 40.0f));
    addChild(playfieldLabel);

    auto stackLabel = Label::createWithSystemFont("", "Arial", 36);
    stackLabel->setPosition(Vec2(stackX + 30.0f, stackTopY - 40.0f));
    addChild(stackLabel);

    auto topLabel = Label::createWithSystemFont("", "Arial", 36);
    topLabel->setPosition(Vec2(visibleSize.width - 170, 310));
    addChild(topLabel);

    _statusLabel = Label::createWithSystemFont("", "Arial", 34);
    _statusLabel->setAnchorPoint(Vec2(0.5f, 1.0f));
    _statusLabel->setPosition(Vec2(visibleSize.width / 2, visibleSize.height - 30));
    addChild(_statusLabel, 20);

    return true;
}

void GameView::addCard(Node* card)
{
    this->addChild(card);
}

void GameView::setStatusText(const std::string& text)
{
    if (_statusLabel)
        _statusLabel->setString(text);
}