#include "LevelChanger.hpp"

LevelChanger::LevelChanger(Vector2 pos, float spd) : position(pos), speed(spd) {}

void LevelChanger::Update() {
    // Update logic for LevelChanger if needed
}

void LevelChanger::Draw() {
    DrawRectangleV(position, {32, 32}, GREEN); // Assuming each tile is 32x32
}

Rectangle LevelChanger::GetCollisionRect() const {
    return { position.x, position.y, 32, 32 }; // Assuming each tile is 32x32
}