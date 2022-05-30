#include "Player.h"

Player::Player(vector<Bullet> &bullets, Texture2D playerTexture, Texture2D bulletTexture) : bullets(bullets) {
    this->position = (Vector2) {(float) GetScreenWidth() / 2, (float) GetScreenHeight() - this->size - 10.0f};
    this->texture = playerTexture;
    this->bulletTexture = bulletTexture;
}

void Player::drawPlayer() {
    DrawTextureEx(this->texture,
                  (Vector2) {this->position.x - ((float)this->texture.width * this->scale / 2), this->position.y - ((float) this->texture.height * this->scale / 2) - 5},
                  0,
                  this->scale,
                  WHITE);
}

void Player::moveRight() {
    if (this->position.x + this->speed + this->size > (float) GetScreenWidth()) return;
    this->position.x += this->speed;
}

void Player::moveLeft() {
    if (this->position.x - this->speed - this->size < 0) return;
    this->position.x -= this->speed;
}

void Player::handleShoot() {
    if(this->isAbleToShoot){
        Bullet bullet(this->position, this->bulletTexture);
        this->bullets.push_back(bullet);
        this->isAbleToShoot = false;
    }
}

void Player::handleShootAvailability() {
    if (!this->isAbleToShoot) {
        this->currentShootWaitTime -= GetFrameTime();
        if(this->currentShootWaitTime < 0.0f) {
            this->isAbleToShoot = true;
            this->currentShootWaitTime = this->shootWaitTime;
        }
    }
}

void Player::handleMovement() {
    if (IsKeyDown(KEY_RIGHT) && IsKeyDown(KEY_LEFT)) {}
    if (IsKeyDown(KEY_RIGHT)) this->moveRight();
    if (IsKeyDown(KEY_LEFT)) this->moveLeft();
}

void Player::handleActions() {
    if (IsKeyPressed(KEY_SPACE)) this->handleShoot();
}

void Player::draw() {
    this->drawPlayer();
}

void Player::update() {
    this->handleMovement();
    this->handleActions();
    this->handleShootAvailability();
}

Vector2 Player::getPosition() {
    return this->position;
}

void Player::resetPosition() {
    this->position = (Vector2) {(float) GetScreenWidth() / 2, (float) GetScreenHeight() - this->size - 10.0f};
}
