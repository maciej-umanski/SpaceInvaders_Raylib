#include "raylib-cpp.hpp"
#include "source/Player.h"

const int screenWidth = 800;
const int screenHeight = 450;
const int frameRate = 60;

void UpdateGame(Player &player, vector<Bullet> &bullets);
void DrawGame(Player &player, vector<Bullet> &bullets);

int main() {

    raylib::Window window(screenWidth, screenHeight, "SpaceInvaders");
    SetTargetFPS(frameRate);

    vector<Bullet> bullets;
    Player player(bullets);

    while (!window.ShouldClose()) {
        UpdateGame(player, bullets);
        DrawGame(player, bullets);
    }

    return 0;
}

void UpdateGame(Player &player, vector<Bullet> &bullets) {
    player.update();

    for(int i = 0; i < bullets.size(); i++) {
        bullets[i].update();
        if(bullets[i].isOutOfScreen()) {
            bullets.erase(bullets.begin() + i);
            i--;
        }
    }

}

void DrawGame(Player &player, vector<Bullet> &bullets) {
    BeginDrawing();

    ClearBackground(RAYWHITE);
    player.draw();
    for(auto &bullet : bullets) bullet.draw();

    EndDrawing();
}