#ifndef SPACEINVADERS_ENEMY_H
#define SPACEINVADERS_ENEMY_H

#include "raylib-cpp.hpp"

class Enemy {
private:
    Vector2 position{};
    bool isAbleToMove = false;
    float moveWaitTime = 0.5f;
    float currentMoveWaitTime = moveWaitTime;
    float scale = 0.5f;
    Texture2D texture{};
    float distanceToMove;

    void updatePosition();
    bool willGoOutOfScreen() const;

public:
    explicit Enemy(Vector2 initialPosition, Texture2D texture);

    void draw();
    void update();
    Vector2 getPosition();
    Vector2 getSize() const;
};


#endif //SPACEINVADERS_ENEMY_H
