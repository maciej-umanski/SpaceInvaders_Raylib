#include "raylib-cpp.hpp"
#include "source/Bullet.h"
#include "source/Player.h"
#include "source/Enemy.h"
#include "source/Misc.h"

const int screenWidth = 800;
const int screenHeight = 450;
const int frameRate = 60;

void UpdateGame(Player &player, vector<Bullet> &bullets, vector<Enemy> &enemies);
void DrawGame(Player &player, vector<Bullet> &bullets, vector<Enemy> &enemies);

int main() {

    raylib::Window window(screenWidth, screenHeight, "SpaceInvaders");
    SetTargetFPS(frameRate);

    vector<Bullet> bullets;
    Player player(bullets);
    vector<Enemy> enemies;

    for(int i = 0; i < 10; i++) {
        Enemy enemy((Vector2) {((float) GetScreenWidth() - (float) (i * 100) - 50), (float) GetScreenHeight() / 4});
        enemies.push_back(enemy);
    }

    while (!window.ShouldClose()) {
        UpdateGame(player, bullets, enemies);
        DrawGame(player, bullets, enemies);
    }

    return 0;
}

void UpdateGame(Player &player, vector<Bullet> &bullets, vector<Enemy> &enemies) {
    player.update();

    for(int i = 0; i < bullets.size(); i++) {
        bullets[i].update();
        if(bullets[i].isOutOfScreen()) {
            bullets.erase(bullets.begin() + i);
            i--;
        }

        for(int j = 0; j < enemies.size(); j++) {
            if(Misc::AreCollided(bullets[i].getPosition(), bullets[i].getSize(), enemies[j].getPosition(), enemies[j].getSize())){
                bullets.erase(bullets.begin() + i);
                i--;
                enemies.erase(enemies.begin() + j);
                j--;
            }
        }
    }

}

void DrawGame(Player &player, vector<Bullet> &bullets, vector<Enemy> &enemies) {
    BeginDrawing();

    ClearBackground(RAYWHITE);
    player.draw();
    for(auto &bullet : bullets) bullet.draw();
    for(auto &enemy : enemies) enemy.draw();

    EndDrawing();
}