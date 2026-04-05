#pragma once

enum class CardAreaType
{
    Playfield,
    Stack
};

struct CardModel
{
    int id = -1;
    int face = 0;
    int suit = 0;
    float x = 0.0f;
    float y = 0.0f;
    CardAreaType area = CardAreaType::Playfield;
    bool isRemoved = false;
};
