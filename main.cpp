#include "raylib-cpp.hpp"
#include "source/Bullet.h"
#include "source/Player.h"
#include "source/Enemy.h"
#include "source/Misc.h"
#include "source/PointsCounter.h"

const int screenWidth = 800;
const int screenHeight = 450;
const int frameRate = 60;

bool isLost = false;
bool isPaused = true;

void UpdateGame(Player &player, vector<Bullet> &bullets, vector<Enemy> &enemies, PointsCounter &pointsCounter);
void DrawGame(Player &player, vector<Bullet> &bullets, vector<Enemy> &enemies, PointsCounter &pointsCounter);
void InitializeNewGame(Player &player, vector<Bullet> &bullets, vector<Enemy> &enemies, PointsCounter &pointsCounter);

int main() {

    raylib::Window window(screenWidth, screenHeight, "SpaceInvaders");
    SetTargetFPS(frameRate);

    vector<Bullet> bullets;
    Player player(bullets);
    vector<Enemy> enemies;
    PointsCounter pointsCounter;

    InitializeNewGame(player, bullets, enemies, pointsCounter);

    while (!window.ShouldClose()) {
        UpdateGame(player, bullets, enemies, pointsCounter);
        DrawGame(player, bullets, enemies, pointsCounter);
    }

    return 0;
}

void UpdateGame(Player &player, vector<Bullet> &bullets, vector<Enemy> &enemies, PointsCounter &pointsCounter) {
    if(!isPaused){
        if (IsKeyPressed(KEY_T)) isPaused = true;
    }
    if(!isPaused){
        if (!isLost) {
            player.update();
            for (auto &enemy: enemies) enemy.update();

            for (int i = 0; i < bullets.size(); i++) {
                bullets[i].update();
                if (bullets[i].isOutOfScreen()) {
                    bullets.erase(bullets.begin() + i);
                    i--;
                }

                for (int j = 0; j < enemies.size(); j++) {
                    if (Misc::AreCollided(bullets[i].getPosition(), bullets[i].getSize(), enemies[j].getPosition(),
                                          enemies[j].getSize())) {
                        bullets.erase(bullets.begin() + i);
                        i--;
                        enemies.erase(enemies.begin() + j);
                        j--;
                        pointsCounter.addPoint();
                    }
                }
            }

            for (auto enemy: enemies) {
                if (CheckCollisionPointLine(
                        enemy.getPosition(), (Vector2) {0, player.getPosition().y},
                        (Vector2) {(float) GetScreenWidth(), player.getPosition().y},
                        10)) {
                    isLost = true;
                }
            }
        } else {
            if (IsKeyPressed(KEY_R)) InitializeNewGame(player, bullets, enemies, pointsCounter);
        }
    } else {
        if (IsKeyPressed(KEY_SPACE)) isPaused = false;
    }
}

void DrawGame(Player &player, vector<Bullet> &bullets, vector<Enemy> &enemies, PointsCounter &pointsCounter) {
    BeginDrawing();

    if(isPaused) {
        ClearBackground(RAYWHITE);
        DrawText("Press \"SPACE\" to start the game.", GetScreenWidth() / 4, GetScreenHeight() / 3, 20, BLACK);
    } else {
        if(!isLost){
            ClearBackground(RAYWHITE);
            player.draw();
            for (auto &bullet: bullets) bullet.draw();
            for (auto &enemy: enemies) enemy.draw();
            pointsCounter.draw();
        } else {
            ClearBackground(RED);
            auto result = "You have lost! Gained: " + std::to_string( pointsCounter.getPoints() ) + " Points!";
            DrawText(result.c_str(), GetScreenWidth() / 4, GetScreenHeight() / 2, 30, BLACK);
            DrawText("Press \"R\" to restart the game.", GetScreenWidth() / 4, GetScreenHeight() / 3, 20, BLACK);
        }
    }

    EndDrawing();
}

void InitializeNewGame(Player &player, vector<Bullet> &bullets, vector<Enemy> &enemies, PointsCounter &pointsCounter) {

    enemies.clear();
    bullets.clear();
    player.resetPosition();
    pointsCounter.clearPoints();
    isLost = false;

    for(int i = 0; i < 10; i++) {
        Enemy enemy((Vector2) {((float) GetScreenWidth() - (float) (i * 100) - 50), (float) GetScreenHeight() / 2});
        enemies.push_back(enemy);
    }
}