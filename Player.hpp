#ifndef PLAYER_HPP
#define PLAYER_HPP

#include "raylib.h"
#include "tilemap.hpp"

class Player {
public:
    Player(Vector2 pos, float alt, Color col);
    void Update(float gravity, float dt, const Tilemap& tilemap);
    void Draw() const;

private:
    Vector2 position;
    Vector2 velocity;
    float altura;
    Color color;
    bool isJumping;

    // Animation members
    Texture2D spriteSheet;
    int frameWidth;
    int frameHeight;
    int currentFrame;
    int maxFrames;
    float frameTime;
    float currentFrameTime;

    void UpdateAnimation(float dt);
    bool CheckCollisionWithTilemap(const Tilemap& tilemap) const;
};

#endif // PLAYER_HPP