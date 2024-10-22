#include "Player.hpp"
#include "Tilemap.hpp"
#include <iostream> // For debug prints

Player::Player(Vector2 pos, float alt, Color col)
    : position(pos), altura(alt), color(col), isJumping(false), currentFrame(0), frameTime(0.1f), currentFrameTime(0.0f) {
    velocity = {0, 0};

    // Load the sprite sheet
    spriteSheet = LoadTexture("assets/spritesheet_player.png");
    frameWidth = spriteSheet.width / 7; // Assuming 7 frames per row
    frameHeight = spriteSheet.height / 8; // Assuming 8 rows (idle, walking, etc.)

    // Check for division by zero
    if (frameWidth == 0 || frameHeight == 0) {
        std::cerr << "Error: Frame width or height is zero. Check the sprite sheet dimensions." << std::endl;
        frameWidth = 1; // Set a default value to avoid division by zero
        frameHeight = 1; // Set a default value to avoid division by zero
    }

    maxFrames = 4; // Number of frames per animation
}

void Player::Update(float gravity, float dt, const Tilemap& tilemap) {
    // Apply gravity
    velocity.y += gravity * dt;

    // Update position
    position.x += velocity.x * dt;
    position.y += velocity.y * dt;

    // Check for collisions
   /*  if (CheckCollisionWithTilemap(tilemap)) {
        // Handle collision
        velocity.y = 0;
        isJumping = false;
    } */

    // Update animation
    UpdateAnimation(dt);
}

void Player::UpdateAnimation(float dt) {
    currentFrameTime += dt;
    if (currentFrameTime >= frameTime) {
        currentFrameTime = 0.0f;
        currentFrame++;
        if (currentFrame >= maxFrames) {
            currentFrame = 0;
        }
    }
}

void Player::Draw() const {
    // Define the vertical offset (e.g., 10 pixels of empty space between rows)
    int verticalOffset = 10;

    // Determine the source rectangle based on the current frame
    int row = (velocity.x != 0) ? 1 : 0; // Row 0 for idle, 1 for walking
    Rectangle sourceRect = { 
        static_cast<float>(currentFrame * frameWidth), 
        static_cast<float>(row * (frameHeight + verticalOffset)), // Add vertical offset
        static_cast<float>(frameWidth), 
        static_cast<float>(frameHeight) 
    };
    Rectangle destRect = { position.x, position.y, static_cast<float>(frameWidth), static_cast<float>(frameHeight) };

    // Draw the current frame
    DrawTexturePro(spriteSheet, sourceRect, destRect, {0, 0}, 0.0f, WHITE);
}

/* bool Player::CheckCollisionWithTilemap(const Tilemap& tilemap) const {
    // Implement collision detection with the tilemap
    // Return true if collision detected, otherwise false
    // Placeholder implementation
} */