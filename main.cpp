#include "raylib-cpp.hpp"

int screenWidth = 800;
int screenHeight = 450;

void UpdateGame();     // Update and Draw one frame
void DrawGame();

int main() {

    raylib::Window window(screenWidth, screenHeight, "raylib-cpp [core] example - basic window");
    SetTargetFPS(60);   // Set our game to run at 60 frames-per-second

    while (!window.ShouldClose()) {    // Detect window close button or ESC key, mainloop
        UpdateGame();
        DrawGame();
    }

    return 0;
}

void UpdateGame() {
    BeginDrawing();

    ClearBackground(RAYWHITE);
    DrawText("Congrats! You created your first raylib-cpp window!", 190, 200, 20, LIGHTGRAY);

    EndDrawing();
}

void DrawGame() {
    // Update
    //----------------------------------------------------------------------------------
    // TODO: Update your variables here
    //----------------------------------------------------------------------------------
}