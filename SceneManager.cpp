#include "SceneManager.hpp"

// Initialize the static instance variable

SceneManager::SceneManager() {
    background = LoadTexture("assets/MainScreen.png");
    backgroundMain = LoadTexture("assets/MainScreen.png");
    backgroundVictory = LoadTexture("assets/WinScreen.png");
    backgroundLosing = LoadTexture("assets/LoseScreen.png");
    currentScene = Scene::MAIN_MENU;
    player = nullptr;
    tilemap = nullptr;
    enemy = nullptr;
    levelChanger = nullptr;
    // Initialize the camera
    camera = { 0 };
    camera.target = { 0.0f, 0.0f };
    camera.offset = { 400.0f, 300.0f }; // Assuming screen width and height are 800x600
    camera.rotation = 0.0f;
    camera.zoom = 1.0f;
}

SceneManager::~SceneManager() {
    UnloadTexture(background);
    UnloadTexture(backgroundMain);
    UnloadTexture(backgroundVictory); 
    UnloadTexture(backgroundLosing);
}


void SceneManager::Update() {
    switch (currentScene) {
        case Scene::MAIN_MENU:
            UpdateMainMenu();
            break;
        case Scene::GAME:
            UpdateGame();
            break;
        case Scene::VICTORY:
            UpdateVictory();
            break;
        case Scene::LOSING:
            UpdateLosing();
            break;
        case Scene::EMPTY:
            UpdateEmpty();
            break;
    }
}

void SceneManager::Draw() {
    switch (currentScene) {
        case Scene::MAIN_MENU:
            DrawMainMenu();
            break;
        case Scene::GAME:
            DrawGame();
            break;
        case Scene::VICTORY:
            DrawVictory();
            break;
        case Scene::LOSING:
            DrawLosing();
            break;
        case Scene::EMPTY:
            DrawEmpty();
            break;
    }
}

void SceneManager::ChangeScene(Scene newScene) {
    currentScene = newScene;

    if (newScene == Scene::GAME) {
        // Initialize game objects
        player = new Player({64, 668}, 5.0f, camera);
        tilemap = new Tilemap("level1.json");
        enemy = new Enemy({600, 668}, 5.0f);
        Vector2 lastTilePosition = tilemap->GetLastTilePosition();
        Vector2 levelChangerPosition = { lastTilePosition.x - 32, lastTilePosition.y - 32};
        levelChanger = new LevelChanger(levelChangerPosition, 0.0f);
    } else {
        // Clean up game objects
        delete player;
        delete tilemap;
        delete enemy;
        player = nullptr;
        tilemap = nullptr;
        enemy = nullptr;
        levelChanger = nullptr;

    }
}

void SceneManager::UpdateMainMenu() {
    if (IsKeyPressed(KEY_ENTER)) {
        ChangeScene(Scene::GAME);
    }
    if (IsKeyPressed(KEY_ESCAPE)) {
        CloseWindow();
    }
    Vector2 mousePoint = GetMousePosition();
    Rectangle button1 = { 300, 400, 200, 50 };
    Rectangle button2 = { 300, 500, 200, 50 };

    if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
        if (CheckCollisionPointRec(mousePoint, button1)) {
            // Handle the first button click
            ChangeScene(Scene::GAME);
        }
        if (CheckCollisionPointRec(mousePoint, button2)) {
            // Handle the second button click
            Cleanup();
            ChangeScene(Scene::EMPTY);
        }
    }
}

void SceneManager::DrawMainMenu() {
    Rectangle button1 = { 300, 400, 200, 50 };
    Rectangle button2 = { 300, 500, 200, 50 };

    BeginDrawing();
    ClearBackground(BLACK);
    DrawRectangleRec(button1, WHITE);
    DrawRectangleRec(button2, WHITE);
    DrawText("Play", 370, 420, 20, BLACK); // Text for the first button
    DrawText("Exit", 370, 520, 20, BLACK); // Text for the second button
    EndDrawing();
}

void SceneManager::UpdateGame() {
    player->Update(*tilemap);
    enemy->Update(*tilemap, *player);

    // Update camera target to follow the player
    camera.target = player->GetPosition();

    // Check for victory or losing conditions
    if (CheckCollisionRecs(enemy->GetCollisionRect(), player->GetCollisionRect())) {
        ChangeScene(Scene::LOSING);
    }
    else if (CheckCollisionRecs(levelChanger->GetCollisionRect(), player->GetCollisionRect())) {
        ChangeScene(Scene::VICTORY);
    }
    // Add your victory condition here
}

void SceneManager::DrawGame() {
    BeginDrawing();
    ClearBackground(BLACK);
    BeginMode2D(camera);
    tilemap->Draw();
    player->Draw();
    enemy->Draw();
    levelChanger->Draw();
    EndMode2D();
    EndDrawing();
}

void SceneManager::UpdateVictory() {
    if (IsKeyPressed(KEY_ENTER)) {
        ChangeScene(Scene::MAIN_MENU);
    }
}

void SceneManager::DrawVictory() {
    BeginDrawing();
    ClearBackground(GRAY);
    DrawText("Press ENTER to Return to Main Menu", 250, 300, 20, WHITE);
    EndDrawing();
}

void SceneManager::UpdateLosing() {
    if (IsKeyPressed(KEY_ENTER)) {
        ChangeScene(Scene::MAIN_MENU);
    }
}

void SceneManager::DrawLosing() {
    BeginDrawing();
    ClearBackground(GRAY);
    DrawText("Press ENTER to Return to Main Menu", 250, 300, 20, WHITE);
    EndDrawing();
}

void SceneManager::Cleanup() {
    // Add cleanup code here
    if (player) {
        delete player;
        player = nullptr;
    }
    if (tilemap) {
        delete tilemap;
        tilemap = nullptr;
    }
    if (enemy) {
        delete enemy;
        enemy = nullptr;
    }
    if (levelChanger) {
        delete levelChanger;
        levelChanger = nullptr;
    }
    // Add any other necessary cleanup
}

void SceneManager::UpdateEmpty() {
    CloseWindow();
}

void SceneManager::DrawEmpty() {
    // Nothing to draw for the empty scene
}