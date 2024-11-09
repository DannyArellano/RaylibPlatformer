#ifndef BULLET_HPP
#define BULLET_HPP

#include "raylib.h"
#include "raymath.h"

class Bullet {
public:
    Vector2 position;
    Vector2 velocity;
    bool active;
    float lifetime;

    Bullet();
    void Update(float deltaTime);
    void Draw();
    void Fire(Vector2 startPos, Vector2 targetPos, float speed);
    bool IsActive(); // Add this method to activate the bullet
    void Reset(); // Add this method to reset the bullet

    Vector2 startPos; // Add this line to store the starting position
};

#endif // BULLET_HPP