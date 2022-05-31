#ifndef SPACEINVADERS_ENEMY_H
#define SPACEINVADERS_ENEMY_H

#include "raylib-cpp.hpp"
#include "Misc.h"

enum Direction {LEFT = 0, RIGHT};

class Enemy {
private:
    Vector2 position{};
    bool isAbleToMove = false;
    float moveWaitTime;
    float currentMoveWaitTime;
    float wiggleWaitTime;
    float wiggleSleep;
    float currentWiggleSleep;
    float currentWiggleWaitTime;
    float scale = 0.5f;
    Texture2D texture{};
    float distanceToMove;
    Sound explosionSound{};
    Color color = Misc::getRandomColor();
    float wiggleRotation = -3.0f;
    float currentRotation = 0;

    void updatePosition();
    bool willGoOutOfScreen() const;

public:
    explicit Enemy(Vector2 initialPosition, Texture2D texture, Sound explosionSound, float moveWaitTime, Direction initialDirection);

    void draw();
    void update();
    void destroy();
    Vector2 getPosition();
    Vector2 getSize() const;
};


#endif //SPACEINVADERS_ENEMY_H
