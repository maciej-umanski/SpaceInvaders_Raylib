#include "Player.h"

Player::Player(vector<Bullet> &bullets) : bullets(bullets) {
    this->speed = 3.0f;
    this->size = 20.0f;
    this->color = RED;
    this->position = (Vector2) {(float) GetScreenWidth() / 2, (float) GetScreenHeight() - this->size - 10.0f};
}

void Player::drawPlayer() { DrawCircleV(this->position, this->size, this->color); }

void Player::moveRight() {
    if (this->position.x + this->speed + this->size > (float) GetScreenWidth()) return;
    this->position.x += this->speed;
}

void Player::moveLeft() {
    if (this->position.x - this->speed - this->size < 0) return;
    this->position.x -= this->speed;
}

void Player::handleShoot() {
    Bullet bullet(this->position);
    this->bullets.push_back(bullet);
}

void Player::handleMovement() {
    if (IsKeyDown(KEY_RIGHT) && IsKeyDown(KEY_LEFT)) {}
    if (IsKeyDown(KEY_RIGHT)) this->moveRight();
    if (IsKeyDown(KEY_LEFT)) this->moveLeft();
}

void Player::handleActions() {
    if (IsKeyDown(KEY_SPACE)) this->handleShoot();
}

void Player::draw() {
    this->drawPlayer();
}

void Player::update() {
    this->handleMovement();
    this->handleActions();
}