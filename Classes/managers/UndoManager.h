#pragma once

#include <stack>
#include "cocos2d.h"
#include "models/CardModel.h"

struct UndoRecord
{
    int cardId = -1;
    CardAreaType sourceArea = CardAreaType::Playfield;
    cocos2d::Vec2 originalPosition = cocos2d::Vec2::ZERO;
    int previousTopFace = 0;
    int previousTopSuit = 0;
};

class UndoManager
{
public:
    void clear();
    void record(const UndoRecord& record);
    bool canUndo() const;
    UndoRecord popUndo();

private:
    std::stack<UndoRecord> _records;
};
