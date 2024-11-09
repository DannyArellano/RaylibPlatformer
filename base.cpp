#include "raylib.h"
#include "SceneManager.hpp"

int main() {
    const int screenWidth = 800;
    const int screenHeight = 600;

    InitWindow(screenWidth, screenHeight, "Scene Manager Example");

    SceneManager sceneManager;

    SetTargetFPS(60);

    while (!WindowShouldClose()) {
        sceneManager.Update();
        sceneManager.Draw();
    }

    CloseWindow();

    return 0;
}