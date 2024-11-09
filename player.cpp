#include "Player.hpp"
#include <string> // For std::to_string
#include "raylib.h"
#include "raymath.h"
#include <algorithm>

Player::Player(Vector2 position, float speed, Camera2D& camera)
    : dotPool(10), position(position), speed(speed), gravity(0.5f), isJumping(false), currentFrame(0), frameTime(0.1f), frameCounter(0.0f), camera(camera) { // Initialize bullet pool with 10 bullets
    velocity = {0, 0};
    spritesheet = LoadTexture("assets/spritesheet_players.png");

    if (spritesheet.id == 0) {
        DrawText("Failed to load spritesheet!", 10, 10, 20, RED);
    }

    // Define frame dimensions
    const int frameWidth = 130;
    const int frameHeight = 160;
    spriteFlip = false;

    // Define idle frames
    idleFrames = {
        {0, 1898, frameWidth, frameHeight}
    };

    // Define run frames
    runFrames = {
        {0, 100, frameWidth, frameHeight},
        {0, 361, frameWidth, frameHeight},
    };

    // Define jump frames
    jumpFrames = {
        {0, 611, frameWidth, frameHeight},
        {0, 869, frameWidth, frameHeight},
    };
}

void Player::Update(const Tilemap& tilemap) {
    Vector2 oldPosition = position;

    // Horizontal movement
    if (IsKeyDown(KEY_D)) {
        velocity.x = speed;
        spriteFlip = false; // Not flipped
    } else if (IsKeyDown(KEY_A)) {
        velocity.x = -speed;
        spriteFlip = true; // Flipped
    } else {
        velocity.x = 0;
    }

    // Apply gravity
    velocity.y += gravity;

    // Update horizontal position
    position.x += velocity.x;

    // Check for horizontal collisions
    if (tilemap.IsColliding(GetCollisionRect())) {
        position.x = oldPosition.x; // Revert to old horizontal position if colliding
    }

    // Update vertical position
    position.y += velocity.y;

    // Check for vertical collisions
    if (tilemap.IsColliding(GetCollisionRect())) {
        position.y = oldPosition.y; // Revert to old vertical position if colliding
        velocity.y = 0; // Stop vertical movement
        isJumping = false; // Reset jumping flag
    }

    // Jumping
    if (IsKeyPressed(KEY_SPACE) && !isJumping) {
        velocity.y = -11.0f; // Jump strength
        isJumping = true;
    }
    if (colorTimer > 0.0f) {
        colorTimer -= GetFrameTime();
        if (colorTimer <= 0.0f) {
            color = WHITE; // Reset color to white
        }
    }
    HandleInput();
    UpdateAnimation();
    UpdateDots();
}

void Player::UpdateAnimation() {
    frameCounter += GetFrameTime();
    if (frameCounter >= frameTime) {
        frameCounter = 0.0f;
        currentFrame++;
        if (isJumping) {
            if (currentFrame >= (int)jumpFrames.size()) currentFrame = 0;
        } else if (velocity.x != 0) {
            if (currentFrame >= (int)runFrames.size()) currentFrame = 0;
        } else {
            if (currentFrame >= (int)idleFrames.size()) currentFrame = 0;
        }
    }
}

void Player::Draw() {
    if (isJumping) {
        sourceRect = jumpFrames[currentFrame];
    } else if (velocity.x != 0) {
        sourceRect = runFrames[currentFrame];
    } else {
        sourceRect = idleFrames[currentFrame];
    }

    // Flip the source rectangle width if spriteFlip is true
    if (spriteFlip) {
        sourceRect.width = -abs(sourceRect.width);
    } else {
        sourceRect.width = abs(sourceRect.width);
    }
    // Define the destination rectangle with scaling
    float scale = 0.5f; // Scale down to 50%
    Rectangle destRect = {position.x, position.y, abs(sourceRect.width) * scale, sourceRect.height * scale};

    // Adjust the destination rectangle position if the sprite is flipped
    if (spriteFlip) {
        destRect.x -= destRect.width;
    }
    // Draw the player using the spritesheet with scaling
    DrawTexturePro(spritesheet, sourceRect, destRect, {sourceRect.width * scale / 2, sourceRect.height * scale}, 0.0f, WHITE);
    for (Dot* dot : activeDots) {
        dot->Draw();
    }
}

void Player::HandleInput() {
    // Existing input handling code...

    if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
        Vector2 mousePosition = GetMousePosition();
        Vector2 worldMousePosition = GetScreenToWorld2D(mousePosition, camera);
        Vector2 direction = { worldMousePosition.x - position.x, worldMousePosition.y - position.y };

        // Normalize the direction vector
        float length = sqrt(direction.x * direction.x + direction.y * direction.y);
        if (length != 0) {
            direction.x /= length;
            direction.y /= length;
        }

        Vector2 playerPosition = { position.x, position.y - sourceRect.height / 4 };
        Dot* dot = dotPool.Get();
        if (dot) {
            dot->Activate(playerPosition);
            dot->SetDirection(direction);
            dot->SetSpeed(600.0f);
            activeDots.push_back(dot);
        } else {
            // No available dots, remove the oldest dot from activeDots and return it to the dotPool
            if (!activeDots.empty()) {
                Dot* oldestDot = activeDots.front();
                activeDots.erase(activeDots.begin());
                dotPool.Return(oldestDot);
            }
            // Try to get a new dot again after removing the oldest dot
            dot = dotPool.Get();
            if (dot) {
                dot->Activate(playerPosition); // Offset the new dot
                dot->SetDirection(direction);
                dot->SetSpeed(600.0f);
                activeDots.push_back(dot);
            }
        }
    }
    float deltaTime = GetFrameTime();
    for (Dot* dot : activeDots) {
        dot->Update(deltaTime);
    }
}

void Player::UpdateDots() {
    for (auto it = activeDots.begin(); it != activeDots.end(); ) {
        Dot* dot = *it;
        if (!dot->IsActive()) {
            dotPool.Return(dot);
            it = activeDots.erase(it);
        } else {
            ++it;
        }
    }
}

Rectangle Player::GetCollisionRect() const {
    float scale = 0.5f; // Scale down to 50%
    float width = (130 * scale) / 2; // Halve the width
    float height = 160 * scale;
    return {position.x - width / 2, position.y - height, width, height}; // Adjusted to match the sprite size
}

Vector2 Player::GetPosition() const {
    return position;
}

void Player::SetColor(Color newColor) {
    color = newColor;
}

void Player::SetColorTimer(float time) {
    colorTimer = time;
}