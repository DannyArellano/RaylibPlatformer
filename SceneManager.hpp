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
    LOSING,
    EMPTY,
    LEVEL2
};

class SceneManager {
public:
    SceneManager();
    void Update();
    void Draw();
    ~SceneManager();
    void ChangeScene(Scene newScene);

private:
    SceneManager(const SceneManager&) = delete; // Delete copy constructor
    SceneManager& operator=(const SceneManager&) = delete; // Delete copy assignment operator

    Scene currentScene;
    Player* player;
    Tilemap* tilemap;
    Enemy* enemy;
    LevelChanger* levelChanger;
    Camera2D camera;
    Texture2D background;
    Texture2D backgroundMain;
    Texture2D backgroundVictory;
    Texture2D backgroundLosing;
    
    void UpdateMainMenu();
    void DrawMainMenu();
    void UpdateGame();
    void DrawGame();
    void UpdateVictory();
    void DrawVictory();
    void UpdateLosing();
    void DrawLosing();
    bool IsButtonClicked(Rectangle button);
    void Cleanup();
    void UpdateEmpty();
    void DrawEmpty();
    void UpdateLevel2();
    void DrawLevel2();
    void CheckDotEnemyCollisions();
    bool CheckCollision(Dot* dot, Enemy* enemy);
    std::vector<Dot*> dots;
    std::vector<Enemy*> enemies;
    
};

#endif // SCENEMANAGER_HPP