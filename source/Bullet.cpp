#include "Bullet.h"

Bullet::Bullet(Vector2 initialPosition) {
    this->position = initialPosition;
}

bool Bullet::isOutOfScreen() const {
    return this->position.y < 0
            || this->position.y > (float) GetScreenHeight()
            || this->position.x < 0
            || this->position.x > (float) GetScreenWidth();
}

void Bullet::moveUp() {
    this->position.y -= this->speed;
}

void Bullet::draw() {
    DrawCircleV(this->position, 10, BLACK);
}

void Bullet::update() {
    this->moveUp();
}