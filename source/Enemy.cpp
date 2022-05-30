#include "Enemy.h"
#include "Misc.h"
#include "cmath"

Enemy::Enemy(Vector2 initialPosition, Texture2D texture, Sound explosionSound, float moveWaitTime, Direction initialDirection) {
    this->moveWaitTime = moveWaitTime;
    this->currentMoveWaitTime = moveWaitTime;
    this->position = initialPosition;
    this->texture = texture;
    this->distanceToMove = - ((float) texture.width / 2);
    if(initialDirection == RIGHT) {
        this->distanceToMove *= -1;
    }
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
    bool willGoOutOfRight = this->distanceToMove < 0 && this->position.x - (float)this->texture.width / 2 - abs(this->distanceToMove) <= 0;
    bool willGoOutOfLeft = this->distanceToMove > 0 && this->position.x + (float)this->texture.width / 2 + abs(this->distanceToMove) >= (float) GetScreenWidth();
    return willGoOutOfLeft || willGoOutOfRight;
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