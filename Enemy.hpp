#ifndef ENEMY_HPP
#define ENEMY_HPP

#include "raylib.h"
#include "Tilemap.hpp"
#include "raymath.h"
#include "Player.hpp" // Include the Player header

class Enemy {
public:
    Enemy(Vector2 position, float speed);
    void Update(const Tilemap& tilemap, Player& player); // Update method now takes a Player reference
    void Draw() const;
    Vector2 GetPosition() const;
    Rectangle GetCollisionRect() const;
    Vector2 GetSize() const { return { (float)frameWidth, (float)frameHeight }; }

private:
    Vector2 position;
    float speed;
    float gravity;
    Vector2 velocity;
    int direction; // 1 for right, -1 for left
    Texture2D spritesheet;
    int frameWidth;
    int frameHeight;
};

#endif // ENEMY_HPP