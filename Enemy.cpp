#include "Enemy.hpp"
#include "Player.hpp"

Enemy::Enemy(Vector2 position, float speed)
    : position(position), speed(speed), gravity(0.5f), velocity({0, 0}), direction(1), frameWidth(130), frameHeight(90) {
    // Load enemy texture or spritesheet
    spritesheet = LoadTexture("assets/spritesheet_enemies.png");

    if (spritesheet.id == 0) {
        DrawText("Failed to load enemy spritesheet!", 10, 10, 20, RED);
    }
}

void Enemy::Update(const Tilemap& tilemap, Player& player) {
    Vector2 oldPosition = position;

    // Apply gravity
    velocity.y += gravity;

    // Update horizontal position
    position.x += speed * direction;

    // Check for horizontal collisions (walls)
    if (tilemap.IsColliding(GetCollisionRect())) {
        position.x = oldPosition.x; // Revert to old horizontal position if colliding
        direction = -direction; // Change direction
    }

    // Update vertical position
    position.y += velocity.y;

    // Check for vertical collisions (ground)
    if (tilemap.IsColliding(GetCollisionRect())) {
        position.y = oldPosition.y; // Revert to old vertical position if colliding
        velocity.y = 0; // Stop vertical movement
    }

    // Check for collision with player
    if (CheckCollisionRecs(GetCollisionRect(), player.GetCollisionRect())) {
        player.SetColor(RED);
        player.SetColorTimer(1.0f); // Set the timer to 1 second
    }

    // Additional enemy logic (e.g., animations)
    // ...
}

Rectangle Enemy::GetCollisionRect() const {
    float scale = 0.5f; // Scale down to 50%
    return {position.x - (frameWidth * scale) / 2, position.y - (frameHeight * scale), frameWidth * scale, frameHeight * scale}; // Adjusted to match the sprite size
}

void Enemy::Draw() const {
    // Draw the enemy using the spritesheet with scaling
    float scale = 0.5f; // Scale down to 50%
    Rectangle sourceRect = {0, 196, (float)frameWidth, (float)frameHeight};
    Rectangle destRect = {position.x, position.y, sourceRect.width * scale, sourceRect.height * scale};

    DrawTexturePro(spritesheet, sourceRect, destRect, {sourceRect.width * scale / 2, sourceRect.height * scale}, 0.0f, WHITE);
}

Vector2 Enemy::GetPosition() const {
    return position;
}