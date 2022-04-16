#ifndef SPACEINVADERS_BULLET_H
#define SPACEINVADERS_BULLET_H

#include "raylib-cpp.hpp"
#include <iostream>

using namespace std;

class Bullet {
private:
    Vector2 position{};
    float speed = 5.0f;
    float size = 10.0f;
    Color color = BLACK;

    void moveUp();
public:
    explicit Bullet(Vector2 initialPosition);
    void draw();
    void update();

    bool isOutOfScreen() const;
    Vector2 getPosition();
    float getSize() const;
};


#endif //SPACEINVADERS_BULLET_H
