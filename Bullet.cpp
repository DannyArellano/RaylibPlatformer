#include "Bullet.hpp"
#include "raylib.h"
#include "raymath.h"

Bullet::Bullet() : position({0, 0}), velocity({0, 0}), active(false), lifetime(0) {}

void Bullet::Update(float deltaTime) {
    if (!active) return;

    position.x += velocity.x * deltaTime;
    position.y += velocity.y * deltaTime;
    lifetime -= deltaTime;

    if (lifetime <= 0) {
        Reset();
    }
}

void Bullet::Draw() {
    if (!active) return;

    DrawCircleV(position, 1, RED);

    // Debug text
    DrawText("Drawing bullet", position.x, position.y - 20, 10, WHITE);
}

bool Bullet::IsActive() {
    if (active) {
        return true;
        DrawText("Bullet is active", position.x, position.y - 20, 10, WHITE);
    } else {
        return false;
        DrawText("Bullet is not active", position.x, position.y - 20, 10, WHITE);
    }
}

void Bullet::Fire(Vector2 startPos, Vector2 targetPos, float speed) {
    this->startPos = startPos; // Store the starting position
    position = startPos;
    Vector2 direction = Vector2Subtract(targetPos, startPos);
    float length = Vector2Length(direction);
    velocity = Vector2Scale(direction, speed / length);
    active = true; 
    lifetime = 5.0f; // Bullet lifetime in seconds

    // Debug text
    DrawText("Firing bullet", position.x, position.y - 20, 10, WHITE);
    DrawText(TextFormat("Start Pos: (%.2f, %.2f)", startPos.x, startPos.y), 10, 50, 20, WHITE);
}

void Bullet::Reset() {
    active = false;
    lifetime = 0;
}
