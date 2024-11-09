#pragma once
#include "raylib.h"

class LevelChanger {
public:
    Vector2 position;
    float speed;

    LevelChanger(Vector2 pos, float spd);
    void Update();
    void Draw();
    Rectangle GetCollisionRect() const; // Add this method
};

// LevelChanger.cpp
