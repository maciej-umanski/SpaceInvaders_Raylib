#ifndef SPACEINVADERS_BULLET_H
#define SPACEINVADERS_BULLET_H

#include "raylib-cpp.hpp"
#include <iostream>

using namespace std;

class Bullet {
private:
    Vector2 position{};
    float speed = 5.0f;
    float scale = 1.0f;
    Texture2D texture{};

    void moveUp();
public:
    explicit Bullet(Vector2 initialPosition, Texture2D texture);
    void draw();
    void update();

    bool isOutOfScreen() const;
    Vector2 getPosition();
    Vector2 getSize() const;
};


#endif //SPACEINVADERS_BULLET_H
