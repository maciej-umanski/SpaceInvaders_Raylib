#ifndef SPACEINVADERS_ENEMY_H
#define SPACEINVADERS_ENEMY_H

#include "raylib-cpp.hpp"

enum Direction {LEFT = 0, RIGHT = 1};

class Enemy {
private:
    Vector2 position{};
    float size = 20.0f;
    Color color = BLUE;
    bool isAbleToMove = false;
    float moveWaitTime = 0.01f;
    float currentMoveWaitTime= moveWaitTime;
    Direction direction = LEFT;

    void updatePosition();
    bool willGoOutOfScreen() const;

public:
    explicit Enemy(Vector2 initialPosition);

    void draw();
    void update();
    Vector2 getPosition();
    float getSize() const;
};


#endif //SPACEINVADERS_ENEMY_H
