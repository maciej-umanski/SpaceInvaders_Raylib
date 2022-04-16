#include "Enemy.h"

Enemy::Enemy(Vector2 initialPosition) {
    this->position = initialPosition;
}

void Enemy::draw() {
    DrawRectangleV(this->position, (Vector2) {this->size, this->size}, this->color);
}

Vector2 Enemy::getPosition() {
    return this->position;
}

float Enemy::getSize() const {
    return this->size;
}
