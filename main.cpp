#include "raylib-cpp.hpp"
#include "source/Bullet.h"
#include "source/Player.h"
#include "source/Enemy.h"
#include "source/Misc.h"
#include "source/PointsCounter.h"

const int screenWidth = 1280;
const int screenHeight = 720;
const int frameRate = 60;

bool isLost = false;
bool isPaused = true;

void UpdateGame(Player &player, vector<Bullet> &bullets, vector<Enemy> &enemies, PointsCounter &pointsCounter, Texture2D enemyTexture, Sound explosionSound, Music backgroundMusic);
void DrawGame(Player &player, vector<Bullet> &bullets, vector<Enemy> &enemies, PointsCounter &pointsCounter, Texture2D background);
void InitializeNewGame(Player &player, vector<Bullet> &bullets, vector<Enemy> &enemies, PointsCounter &pointsCounter, Texture2D enemyTexture, Sound explosionSound);

int main() {
    raylib::Window window(screenWidth, screenHeight, "SpaceInvaders");
    InitAudioDevice();
    SetTargetFPS(frameRate);

    Texture2D backgroundTexture = LoadTexture("../source/assets/background.png");
    Texture2D bulletTexture = LoadTexture("../source/assets/bullet.png");
    Texture2D playerTexture = LoadTexture("../source/assets/ship.png");
    Texture2D enemyTexture = LoadTexture("../source/assets/enemy.png");

    Sound laserSound = LoadSound("../source/assets/laser.wav");
    Sound explosionSound = LoadSound("../source/assets/explosion.wav");
    Music backgroundMusic = LoadMusicStream("../source/assets/music.mp3");
    backgroundMusic.looping = true;

    SetSoundVolume(explosionSound, 0.2f);
    SetSoundVolume(laserSound, 0.3f);
    SetMusicVolume(backgroundMusic, 0.3f);

    PlayMusicStream(backgroundMusic);

    vector<Bullet> bullets;
    Player player(bullets, playerTexture, bulletTexture, laserSound);
    vector<Enemy> enemies;
    PointsCounter pointsCounter;

    InitializeNewGame(player, bullets, enemies, pointsCounter, enemyTexture, explosionSound);

    while (!window.ShouldClose()) {
        UpdateGame(player, bullets, enemies, pointsCounter, enemyTexture, explosionSound, backgroundMusic);
        DrawGame(player, bullets, enemies, pointsCounter, backgroundTexture);
    }

    return 0;
}

void UpdateGame(Player &player, vector<Bullet> &bullets, vector<Enemy> &enemies, PointsCounter &pointsCounter, Texture2D enemyTexture, Sound explosionSound, Music backgroundMusic) {
    UpdateMusicStream(backgroundMusic);
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
                    if (Misc::AreCollided(bullets[i].getPosition(), bullets[i].getSize().x, bullets[i].getSize().y,
                                          enemies[j].getPosition(), enemies[j].getSize().x, enemies[j].getSize().y)) {
                        bullets.erase(bullets.begin() + i);
                        i--;
                        enemies[j].playDestroyedSound();
                        enemies.erase(enemies.begin() + j);
                        j--;
                        pointsCounter.addPoint();
                    }
                }
            }

            for (auto &enemy: enemies) {
                if (enemy.getPosition().y >= player.getPosition().y - player.getHeight() / 2) {
                    isLost = true;
                }
            }
        } else {
            if (IsKeyPressed(KEY_R)) InitializeNewGame(player, bullets, enemies, pointsCounter, enemyTexture, explosionSound);
        }
    } else {
        if (IsKeyPressed(KEY_SPACE)) isPaused = false;
    }
}

void DrawGame(Player &player, vector<Bullet> &bullets, vector<Enemy> &enemies, PointsCounter &pointsCounter, Texture2D background) {
    BeginDrawing();

    if(isPaused) {
        ClearBackground(RAYWHITE);
        DrawText("Press \"SPACE\" to start the game.", GetScreenWidth() / 4, GetScreenHeight() / 3, 20, BLACK);
    } else {
        if(!isLost){
            ClearBackground(RAYWHITE);
            DrawTexture(background, 0, 0, WHITE);
            for (auto &bullet: bullets) bullet.draw();
            player.draw();
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

void InitializeNewGame(Player &player, vector<Bullet> &bullets, vector<Enemy> &enemies, PointsCounter &pointsCounter, Texture2D enemyTexture, Sound explosionSound) {

    enemies.clear();
    bullets.clear();
    player.resetPosition();
    pointsCounter.clearPoints();
    isLost = false;

    for(int i = 1; i < 5; i++) {
        enemies.emplace_back((Vector2) {((float) GetScreenWidth() - (float) (i * 150)), (float) GetScreenHeight() / 2}, enemyTexture, explosionSound);
    }
}