/* #include "SceneManager.hpp"

class MainMenuScene {
public:
    void Update(Camera2D& camera) {
        if (IsKeyPressed(KEY_ENTER)) {
            SceneManager::GetInstance().ChangeScene(Scene::GAME);
        }
        if (IsKeyPressed(KEY_ESCAPE)) {
            CloseWindow();
        }
        Vector2 mousePoint = GetMousePosition();
        Rectangle button1 = { 300, 400, 200, 50 };
        Rectangle button2 = { 300, 500, 200, 50 };

        if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
            if (CheckCollisionPointRec(mousePoint, button1)) {
                SceneManager::GetInstance().ChangeScene(Scene::GAME);
            }
            if (CheckCollisionPointRec(mousePoint, button2)) {
                SceneManager::GetInstance().ChangeScene(Scene::EMPTY);
            }
        }
    }

    void Draw(Camera2D& camera) {
        Rectangle button1 = { 300, 400, 200, 50 };
        Rectangle button2 = { 300, 500, 200, 50 };

        BeginDrawing();
        ClearBackground(GRAY);
        DrawText("Main Menu", 350, 200, 40, WHITE);
        DrawText("Press ENTER to Play", 300, 300, 20, WHITE);
        DrawText("Press ESC to Exit", 300, 350, 20, WHITE);
        DrawRectangleRec(button1, WHITE);
        DrawRectangleRec(button2, WHITE);
        DrawText("Play", 370, 420, 20, BLACK);
        DrawText("Exit", 370, 520, 20, BLACK);
        EndDrawing();
    }
}; */