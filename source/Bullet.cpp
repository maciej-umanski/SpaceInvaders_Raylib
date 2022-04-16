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
    DrawRectangleV(this->position, (Vector2) {this->size, this->size}, this->color);
}

void Bullet::update() {
    this->moveUp();
}

Vector2 Bullet::getPosition() {
    return this->position;
}

float Bullet::getSize() const {
    return this->size;
}