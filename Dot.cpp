#include "Dot.hpp"

Dot::Dot() : position({0, 0}), active(false) {}

void Dot::Update(float deltaTime) {
    if (!active) return;
    position.x += direction.x * speed * deltaTime;
    position.y += direction.y * speed * deltaTime;
}

void Dot::Draw() {
    if (!active) return;
    DrawCircleV(position, 5, RED);
}

void Dot::Activate(Vector2 pos) {
    position = pos;
    active = true;
}

void Dot::Deactivate() {
    active = false;
}

bool Dot::IsActive() const {
    return active;
}

void Dot::SetDirection(Vector2 direction) {
    this->direction = direction;
}

void Dot::SetSpeed(float speed) {
    this->speed = speed;
}