#include "Bullet.h"

Bullet::Bullet(Vector2 initialPosition) {
    this->position = {initialPosition.x, initialPosition.y};
}

void Bullet::draw() {
    DrawCircleV(this->position, 10, BLACK);
}
