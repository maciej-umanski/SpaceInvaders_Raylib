#include "raylib-cpp.hpp"
#include "source/Bullet.h"
/**
* \file Bullet.h
* Plik z definicją klasy Bullet.
*/
#include "source/Player.h"
/**
* \file Player.h
* Plik z definicją klasy Player.
*/
#include "source/Enemy.h"
/**
* \file Enemy.h
* Plik z definicją klasy Enemy.
*/
#include "source/Misc.h"
/**
* \file Misc.h
* Plik z definicją klasy Misc.
*/
#include "source/PointsCounter.h"
/**
* \file PointsCounter.h
* Plik z definicją klasy PointsCounter.
*/
#include <cstdio>

/**
* \file main.cpp
*/

/*!
 * \brief Szerokość okna, domyślnie wartość 1280.
 */
const int screenWidth = 1280;
/*!
 * \brief Wysokość okna, domyślnie wartość 720.
 */
const int screenHeight = 720;
/*!
 * \brief Liczba klatek na sekundę, domyślnie wartość 60.
 */
const int frameRate = 60;

/*! Definicja trybów gry.
 *
 */
enum Mode {
    TITLE, /**< Wartość 0 jako tryb startowy. */
        PAUSE, /**< Wartość 1 jako widok zapauzowanej gry. */
        GAME, /**< Wartość 2 jako tryb gry. */
        LOST, /**< Wartość 3 jako tryb przegranej w grze. */
        NEXT_WAVE /**< Wartość 4 jako tryb następnej fali. */
};
/*! Definicja poziomów trudności gry.
 *
 */
enum Difficulty {
    EASY = 0, /**< Wartość 0 jako tryb łatwy. */
        MEDIUM = 5,  /**< Wartość 5 jako tryb średniej trudności. */
        HARD = 10 /**< Wartość 10 jako tryb trudny. */
};
/*!
 *\brief Kolekcja dostępnych prędkości wrogów, typu float.
 */
const float enemiesSpeed[] = {1.5f, 1.4f, 1.3f, 1.2f, 1.1f, 1.0f, 0.9f, 0.8f, 0.7f, 0.6f, 0.5f, 0.4f, 0.2f, 0.1f, 0.05f, 0.01f};
/*!
 * \brief Nazwa pliku do zapisu punktów.
 */
const char *pointsFilePath = "./points.dat";

/*!
 * \brief Obecny tryb gry, zmienna typu Mode.
 * \see Mode
 */
Mode currentMode = TITLE;
/*!
 * \brief Obecny poziom trudności, zmienna typu Difficulty.
 * \see Difficulty
 */
Difficulty currentDifficulty = EASY;
/*!
 * \brief Flaga ustawiana w przypadku opuszczania gry, zmienna typu logicznego, domyślnie wartość false.
 */
bool shouldQuit = false;
/*!
 * \brief Najwyższy zdobyty wynik, typu unsigned long long, domyślnie wartość 0.
 */
unsigned long long bestPoints = 0;

Texture2D titleScreen;
Texture2D pauseScreen;
Texture2D gameScreen;
Texture2D lostScreen;
Texture2D bulletTexture;
Texture2D playerTexture;
Texture2D enemyTexture;
Sound laserSound;
Sound explosionSound;
Music backgroundMusic;

/*!
 * \brief Aktualizowanie stanu gry.
 * \param[in] player gracz, jako obiekt Player
 * \param[in] bullets kolekcja pocisków, jako obiektów Bullet
 * \param[in] enemies kolekcja wrogów, jako obiektów Enemy
 * \param[in] pointsCounter licznik punktów, jako obiekt PointsCounter
 * \see InitializeGame()
 * \see saveBestPoints()
 * \see PointsCounter#setWave()
 * \see Player#update()
 * \see Enemy#update()
 * \see Bullet#update()
 * \see Bullet#isOutOfScreen()
 * \see Misc#AreCollided()
 * \see Bullet#getPosition()
 * \see Bullet#getSize()
 * \see Enemy#getPosition()
 * \see Enemy#getSize()
 * \see Enemy#destroy()
 * \see PointsCounter#addPoint()
 * \see Player#getPosition()
 * \see Player#getHeight()
 * \see PointsCounter#addWave()
 * \see PointsCounter#clearPoints()
 */
void UpdateGame(Player &player, vector<Bullet> &bullets, vector<Enemy> &enemies, PointsCounter &pointsCounter);
/*!
 * \brief Rysowanie gry na ekranie.
 * \param[in] player gracz, jako obiekt Player
 * \param[in] bullets kolekcja pocisków, jako obiektów Bullet
 * \param[in] enemies kolekcja wrogów, jako obiektów Enemy
 * \param[in] pointsCounter licznik punktów, jako obiekt PointsCounter
 * \see Player#draw()
 * \see Enemy#draw()
 * \see Bullet#draw()
 * \see PointsCounter#draw()
 * \see PointsCounter#getPoints()
 */
void DrawGame(Player &player, vector<Bullet> &bullets, vector<Enemy> &enemies, PointsCounter &pointsCounter);

/*!
 * \brief Inicjowanie gry.
 * \param[in] player gracz, jako obiekt Player
 * \param[in] bullets kolekcja pocisków, jako obiektów Bullet
 * \param[in] enemies kolekcja wrogów, jako obiektów Enemy
 * \param[in] pointsCounter licznik punktów, jako obiekt PointsCounter
 * \see Player#resetPosition()
 */
void InitializeGame(Player &player, vector<Bullet> &bullets, vector<Enemy> &enemies, PointsCounter &pointsCounter);
/*!
 * \brief Zapisywanie najlepszego wyniku.
 * \param[in] pointsCounter licznik punktów, jako obiekt PointsCounter
 * \see PointsCounter#getPoints()
 */
void saveBestPoints(PointsCounter &pointsCounter);
/*!
 * \brief Ładowanie zasobow do gry.
 */
void loadAssets();

int main() {
    SetRandomSeed(time(nullptr));
    raylib::Window window(screenWidth, screenHeight, "SpaceInvaders");
    InitAudioDevice();
    SetTargetFPS(frameRate);
    loadAssets();

    vector<Bullet> bullets;
    Player player(bullets, playerTexture, bulletTexture, laserSound);
    vector<Enemy> enemies;
    PointsCounter pointsCounter(currentDifficulty);

    if(FileExists(pointsFilePath)) {
        bestPoints = stoi(LoadFileText(pointsFilePath));
    }

    while (!shouldQuit) {
        UpdateGame(player, bullets, enemies, pointsCounter);
        DrawGame(player, bullets, enemies, pointsCounter);
    }

    return 0;
}

void UpdateGame(Player &player, vector<Bullet> &bullets, vector<Enemy> &enemies, PointsCounter &pointsCounter) {
    UpdateMusicStream(backgroundMusic);

    switch (currentMode) {

        case TITLE: {
            if (IsKeyPressed(KEY_ESCAPE)) shouldQuit = true;
            if (IsKeyPressed(KEY_SPACE)) {
                pointsCounter.setWave(currentDifficulty);
                pointsCounter.clearPoints();
                InitializeGame(player, bullets, enemies, pointsCounter);
                currentMode = GAME;
            }
            if (IsKeyPressed(KEY_ENTER)) {
                if (currentDifficulty == EASY) currentDifficulty = MEDIUM;
                else if (currentDifficulty == MEDIUM) currentDifficulty = HARD;
                else if (currentDifficulty == HARD) currentDifficulty = EASY;
            }
            break;
        }
        case PAUSE: {
            if (IsKeyPressed(KEY_SPACE)) currentMode = GAME;
            if (IsKeyPressed(KEY_ESCAPE)) {
                saveBestPoints(pointsCounter);
                currentMode = TITLE;
            }
            break;
        }
        case GAME: {
            if (IsKeyPressed(KEY_ESCAPE)) currentMode = PAUSE;
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
                        enemies[j].destroy();
                        enemies.erase(enemies.begin() + j);
                        j--;
                        pointsCounter.addPoint();
                    }
                }
            }
            for (auto &enemy: enemies) {
                if (enemy.getPosition().y >= player.getPosition().y - player.getHeight() / 2) {
                    currentMode = LOST;
                }
            }
            if(enemies.empty()) currentMode = NEXT_WAVE;
            break;
        }
        case NEXT_WAVE : {
            if (IsKeyPressed(KEY_SPACE)) {
                pointsCounter.addWave();
                InitializeGame(player, bullets, enemies, pointsCounter);
                currentMode = GAME;
            }
            break;
        }
        case LOST: {
            if (IsKeyPressed(KEY_ESCAPE)){
                saveBestPoints(pointsCounter);
                currentMode = TITLE;
            }
            if (IsKeyPressed(KEY_SPACE)) {
                pointsCounter.clearPoints();
                InitializeGame(player, bullets, enemies, pointsCounter);
                currentMode = GAME;
            }
            break;
        }
    }
}

void DrawGame(Player &player, vector<Bullet> &bullets, vector<Enemy> &enemies, PointsCounter &pointsCounter) {
    BeginDrawing();
    switch (currentMode) {

        case TITLE: {
            DrawTexture(titleScreen, 0, 0, GRAY);
            DrawText("SPACE_INVADERS", 100, GetScreenHeight() / 5, 50, RED);
            DrawText("Press \"SPACE\" to start the game.\nPress \"ESC\" to exit the game.\nPress \"ENTER\" to change difficulty.", 100, GetScreenHeight() / 3, 40, WHITE);

            string difficulty;
            if(currentDifficulty == EASY) difficulty = "EASY";
            else if(currentDifficulty == MEDIUM) difficulty = "MEDIUM";
            else if(currentDifficulty == HARD) difficulty = "HARD";

            DrawText(("Difficulty: " + difficulty).c_str(), 100, GetScreenHeight() - 100, 40, WHITE);
            DrawText(("Best: " + std::to_string(bestPoints) + " points.").c_str(), 100, GetScreenHeight() - 200, 40, WHITE);

            break;
        }
        case PAUSE: {
            DrawTexture(pauseScreen, 0, 0, GRAY);
            DrawText("PAUSED", 100, GetScreenHeight() / 5, 50, RED);
            DrawText("Press \"SPACE\" to resume the game.\nPress \"ESC\" to exit to title screen.", 100, GetScreenHeight() / 3, 40, WHITE);
            break;
        }
        case GAME: {
            DrawTexture(gameScreen, 0, 0, WHITE);
            for (auto &bullet: bullets) bullet.draw();
            player.draw();
            for (auto &enemy: enemies) enemy.draw();
            pointsCounter.draw();
            DrawText("Press \"ESC\" to pause the game", (int) ((float) GetScreenWidth() / 1.35f) , GetScreenHeight() - 20, 20,RED);
            break;
        }
        case NEXT_WAVE: {
            DrawTexture(lostScreen, 0, 0, GRAY);
            DrawText("CONGRATULATIONS!\nPress \"SPACE\" to continue to the next wave!", 100, GetScreenHeight() / 3, 40, WHITE);
            pointsCounter.draw();
            break;
        }
        case LOST: {
            DrawTexture(lostScreen, 0, 0, GRAY);
            auto result = "LOST! Gained: " + std::to_string( pointsCounter.getPoints() ) + " Points!";
            DrawText(result.c_str(), 100, GetScreenHeight() / 5, 50, RED);
            DrawText("Press \"SPACE\" to restart the game.\nPress \"ESC\" to exit to title screen.", 100, GetScreenHeight() / 3, 40, WHITE);
            break;
        }
    }

    EndDrawing();
}

void InitializeGame(Player &player, vector<Bullet> &bullets, vector<Enemy> &enemies, PointsCounter &pointsCounter) {
    enemies.clear();
    bullets.clear();
    player.resetPosition();
    currentMode = GAME;

    for(int i = 0; i < 4; i++){
        for (int j = 0; j < 7; j++) {
            Direction initialDirection = LEFT;
            if(i % 2 != 0) initialDirection = RIGHT;
            enemies.emplace_back((Vector2) {
                    (float) GetScreenWidth() - ((float) j * (float) enemyTexture.width) - (float) enemyTexture.width / 2 - 40,
                    (float) i * (float) enemyTexture.height + (float)enemyTexture.height / 2 }, enemyTexture, explosionSound, enemiesSpeed[currentDifficulty], initialDirection);
        }
    }
}

void saveBestPoints(PointsCounter &pointsCounter) {
    unsigned long long currentPoints = pointsCounter.getPoints();
    if (currentPoints > bestPoints){
        bestPoints = currentPoints;
        char temp[100];
        sprintf(temp, "%llu", pointsCounter.getPoints());
        SaveFileText(pointsFilePath, temp);
    }
}

void loadAssets() {
    titleScreen = LoadTexture("../source/assets/title.png");
    lostScreen = LoadTexture("../source/assets/lost.png");
    gameScreen = LoadTexture("../source/assets/background.png");
    bulletTexture = LoadTexture("../source/assets/bullet.png");
    playerTexture = LoadTexture("../source/assets/ship.png");
    enemyTexture = LoadTexture("../source/assets/enemy.png");
    pauseScreen = LoadTexture("../source/assets/pause.png");
    laserSound = LoadSound("../source/assets/laser.wav");
    explosionSound = LoadSound("../source/assets/explosion.wav");
    backgroundMusic = LoadMusicStream("../source/assets/music.mp3");
    backgroundMusic.looping = true;
    SetSoundVolume(explosionSound, 0.2f);
    SetSoundVolume(laserSound, 0.3f);
    SetMusicVolume(backgroundMusic, 0.3f);
    PlayMusicStream(backgroundMusic);
}