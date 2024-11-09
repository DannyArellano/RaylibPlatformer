#include "LevelChanger.hpp"

LevelChanger::LevelChanger(Vector2 pos, float spd) : position(pos), speed(spd) {}

void LevelChanger::Update() {
    // Update logic for LevelChanger if needed
}

void LevelChanger::Draw() {
    DrawRectangleV(position, {32, 32}, GREEN); // Assuming each tile is 32x32
}