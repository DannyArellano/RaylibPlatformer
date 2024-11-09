#ifndef SCENEMANAGER_HPP
#define SCENEMANAGER_HPP

#include "raylib.h"
#include "Player.hpp"
#include "Tilemap.hpp"
#include "Enemy.hpp"
#include "LevelChanger.hpp"

enum class Scene {
    MAIN_MENU,
    GAME,
    VICTORY,
    LOSING
};

class SceneManager {
public:
    SceneManager();
    void Update();
    void Draw();
    void ChangeScene(Scene newScene);

private:
    Scene currentScene;
    Player* player;
    Tilemap* tilemap;
    Enemy* enemy;
    LevelChanger* levelChanger;
    Camera2D camera;

    void UpdateMainMenu();
    void DrawMainMenu();
    void UpdateGame();
    void DrawGame();
    void UpdateVictory();
    void DrawVictory();
    void UpdateLosing();
    void DrawLosing();
    bool IsButtonClicked(Rectangle button);
};

#endif // SCENEMANAGER_HPP