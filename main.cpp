#include "raylib.h"
#include "Player.hpp"
#include "Tilemap.hpp"
#include <vector>
#include <cstdio> // Add this for printf

int main() {
    const int screenWidth = 800;
    const int screenHeight = 600;
    InitWindow(screenWidth, screenHeight, "Sistema mamalón de gravedad");

    // Gravedad definida
    const float gravity = 980.0f;

    // Inicializar jugador
    Player player({400, 300}, 20, RED);

    // Inicializar tilemap
    Tilemap tilemap("assets/tilemap.json", "assets/spritesheet_ground.png", 128, 128);

    SetTargetFPS(60);

    while (!WindowShouldClose()) {
        float dt = GetFrameTime();

        // Actualizar jugador
        player.Update(gravity, dt, tilemap);

        BeginDrawing();
        ClearBackground(RAYWHITE);

        // Dibujar tilemap
        tilemap.Draw();
        printf("Drawing tilemap\n"); // Debug print

        // Dibujar jugador
        player.Draw();
        printf("Drawing player\n"); // Debug print

        EndDrawing();
    }

    CloseWindow();
    return 0;
}