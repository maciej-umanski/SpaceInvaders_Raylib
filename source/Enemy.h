#ifndef SPACEINVADERS_ENEMY_H
#define SPACEINVADERS_ENEMY_H

#include "raylib-cpp.hpp"

enum Direction {LEFT = 0, RIGHT = 1};

class Enemy {
private:
    Vector2 position{};
    float size = 20.0f;
    bool isAbleToMove = false;
    float moveWaitTime = 0.5f;
    float currentMoveWaitTime = moveWaitTime;
    Direction direction = LEFT;
    float scale = 0.5f;
    Texture2D texture = LoadTexture("/Volumes/Dane/Studia/Grafika Komputerowa/SpaceInvaders_Raylib/source/assets/enemy.png");

    void updatePosition();
    bool willGoOutOfScreen() const;

public:
    explicit Enemy(Vector2 initialPosition);

    void draw();
    void update();
    Vector2 getPosition();
    Vector2 getSize() const;
};


#endif //SPACEINVADERS_ENEMY_H
