/* #include "SceneManager.hpp"

class level1Scene {
public:
    void Init() {
        player = new Player({290, 400}, 5.0f, camera);
        tilemap = new Tilemap("level1.json");
        enemy = new Enemy({1000, 400}, 5.0f);
        Vector2 lastTilePosition = tilemap->GetLastTilePosition();
        Vector2 levelChangerPosition = { lastTilePosition.x - 128, lastTilePosition.y - 128};
        levelChanger = new LevelChanger(levelChangerPosition, 0.0f);
    }

    void Update(Camera2D& camera) {
        // Update game objects
    }

    void Draw(Camera2D& camera) {
        BeginDrawing();
        ClearBackground(RAYWHITE);
        BeginMode2D(camera);
        // Draw game objects
        EndMode2D();
        EndDrawing();
    }

    void Cleanup() {
        delete player;
        delete tilemap;
        delete enemy;
        delete levelChanger;
        player = nullptr;
        tilemap = nullptr;
        enemy = nullptr;
        levelChanger = nullptr;
    }

private:
    Player* player;
    Tilemap* tilemap;
    Enemy* enemy;
    LevelChanger* levelChanger;
}; */