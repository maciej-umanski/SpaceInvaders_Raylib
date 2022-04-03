#ifndef SPACEINVADERS_BULLET_H
#define SPACEINVADERS_BULLET_H

#include "raylib-cpp.hpp"
#include <iostream>

using namespace std;

class Bullet {
private:

public:
    Vector2 position{};
    explicit Bullet(Vector2 initialPosition);
    void draw();
};


#endif //SPACEINVADERS_BULLET_H
