#pragma once
#include "raylib.h"

class LevelChanger {
public:
    Vector2 position;
    float speed;

    LevelChanger(Vector2 pos, float spd);
    void Update();
    void Draw();
    Rectangle GetRect() const { return {position.x, position.y, 32, 32}; }
};

// LevelChanger.cpp
