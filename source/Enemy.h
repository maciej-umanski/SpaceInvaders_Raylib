#ifndef SPACEINVADERS_ENEMY_H
#define SPACEINVADERS_ENEMY_H

#include "raylib-cpp.hpp"


class Enemy {
private:
    Vector2 position{};
    float size;

public:
    explicit Enemy(Vector2 initialPosition);

    void draw();
};


#endif //SPACEINVADERS_ENEMY_H
