#include <iostream>
#include "Enemy.h"
#include "Misc.h"

Enemy::Enemy(Vector2 initialPosition, Texture2D texture, Sound explosionSound) {
    this->position = initialPosition;
    this->texture = texture;
    this->distanceToMove = (float) texture.width / 2;
    this->explosionSound = explosionSound;
}

void Enemy::draw() {
    DrawTextureEx(this->texture,
                  (Vector2) {this->position.x - ((float)this->texture.width * this->scale / 2), this->position.y - ((float) this->texture.height * this->scale / 2)},
                  0,
                  this->scale,
                  this->color);
}

Vector2 Enemy::getPosition() {
    return this->position;
}

Vector2 Enemy::getSize() const {
    return (Vector2) {(float) this->texture.width, (float) this->texture.height};
}

bool Enemy::willGoOutOfScreen() const {
    return this->position.x - abs(this->distanceToMove) <= 0
        || this->position.x + abs(this->distanceToMove) >= (float) GetScreenWidth();
}

void Enemy::updatePosition() {
    if(this->isAbleToMove){
        if(this->willGoOutOfScreen()) {
            this->position.y += this->getSize().y;
            this->distanceToMove *= -1;
        }
        this->position.x += this->distanceToMove;
        this->isAbleToMove = false;
    } else {
        this->currentMoveWaitTime -= GetFrameTime();
        if(this->currentMoveWaitTime < 0.0f) {
            this->isAbleToMove = true;
            this->currentMoveWaitTime = this->moveWaitTime;
        }
    }
}

void Enemy::update() {
    this->updatePosition();
}

void Enemy::destroy() {
    PlaySound(this->explosionSound);
}