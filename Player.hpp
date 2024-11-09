#ifndef PLAYER_HPP
#define PLAYER_HPP

#include "raylib.h"
#include "Tilemap.hpp"
#include "ObjPool.hpp"
#include "Dot.hpp"
#include <vector>

class Player {
public:
    Player(Vector2 position, float speed, Camera2D& camera);
    void Update(const Tilemap& tilemap);
    void Draw();
    Vector2 GetPosition() const;
    void SetColor(Color color);
    void SetColorTimer(float time);
    Rectangle GetCollisionRect() const;

private:
    Vector2 position;
    Vector2 velocity;
    float speed;
    float gravity;
    bool isJumping;
    bool spriteFlip;
    Rectangle sourceRect;

    Texture2D spritesheet;
    std::vector<Rectangle> idleFrames;
    std::vector<Rectangle> runFrames;
    std::vector<Rectangle> jumpFrames;
    int currentFrame;
    float frameTime;
    float frameCounter;
    Color color;
    float colorTimer;

    ObjectPool<Dot> dotPool;
    std::vector<Dot*> activeDots;

    Camera2D& camera;

    void UpdateAnimation();
    void HandleInput();
    void UpdateDots();
};

#endif // PLAYER_HPP