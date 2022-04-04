#ifndef SPACEINVADERS_BULLET_H
#define SPACEINVADERS_BULLET_H

#include "raylib-cpp.hpp"
#include <iostream>

using namespace std;

class Bullet {
private:
    Vector2 position{};
    float speed;

    void moveUp();
public:
    explicit Bullet(Vector2 initialPosition);
    void draw();
    void update();

    bool isOutOfScreen() const;
};


#endif //SPACEINVADERS_BULLET_H
