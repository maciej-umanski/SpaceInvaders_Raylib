#ifndef SPACEINVADERS_PLAYER_H
#define SPACEINVADERS_PLAYER_H

#include "raylib-cpp.hpp"
#include "Bullet.h"
#include <iostream>

using namespace std;

class Player {
private:
    Vector2 position{};
    float speed = 3.0f;
    float size = 20.0f;
    Color color = RED;
    bool isAbleToShoot = true;
    float shootWaitTime = 0.2f;
    float currentShootWaitTime = shootWaitTime;

    vector<Bullet> &bullets;

    void drawPlayer();
    void moveRight();
    void moveLeft();
    void handleShoot();
    void handleMovement();
    void handleActions();
    void handleShootAvailability();

public:
    explicit Player(vector<Bullet> &bullets);
    void draw();
    void update();
    Vector2 getPosition();
    float getSize() const;
};


#endif //SPACEINVADERS_PLAYER_H
