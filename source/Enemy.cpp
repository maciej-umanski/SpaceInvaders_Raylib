#include "Enemy.h"

Enemy::Enemy(Vector2 initialPosition) {
    this->position = initialPosition;
}

void Enemy::draw() {
    DrawTextureEx(this->texture,
                  (Vector2) {this->position.x - ((float)this->texture.width * this->scale / 2), this->position.y - ((float) this->texture.height * this->scale / 2)},
                  0,
                  this->scale,
                  RAYWHITE);
}

Vector2 Enemy::getPosition() {
    return this->position;
}

Vector2 Enemy::getSize() const {
    return (Vector2) {(float) this->texture.width, (float) this->texture.height};
}

bool Enemy::willGoOutOfScreen() const {
    return this->position.y - 2 * this->size < 0
        || this->position.y + 2 * this->size > (float) GetScreenHeight()
        || this->position.x - 2 * this->size< 0
        || this->position.x + 2 * this->size > (float) GetScreenWidth();
}

void Enemy::updatePosition() {
    if(this->isAbleToMove){
        if(this->willGoOutOfScreen()) {
            this->position.y += 2 * this->size;
            if(this->direction == LEFT)
                this->direction = RIGHT;
            else
                this->direction = LEFT;
        }
        if(direction == LEFT) {
            this->position.x += this->size;
        } else {
            this->position.x -= this->size;
        }
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
