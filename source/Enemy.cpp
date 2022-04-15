#include "Enemy.h"

Enemy::Enemy(Vector2 initialPosition) {
    this->position = initialPosition;
}

void Enemy::draw() {
    DrawCircleV(this->position, 10, BLUE);
}
