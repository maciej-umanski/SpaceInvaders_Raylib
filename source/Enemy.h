#ifndef SPACEINVADERS_ENEMY_H
#define SPACEINVADERS_ENEMY_H

#include "raylib-cpp.hpp"


class Enemy {
private:
    Vector2 position{};
    float size = 20.0f;
    Color color = BLUE;

public:
    explicit Enemy(Vector2 initialPosition);

    void draw();
    Vector2 getPosition();
    float getSize() const;
};


#endif //SPACEINVADERS_ENEMY_H
