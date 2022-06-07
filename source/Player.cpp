#include "Player.h"
/**
* \file Player.h
* Plik z definicją klasy Player.
*/

Player::Player(vector<Bullet> &bullets, Texture2D playerTexture, Texture2D bulletTexture, Sound laserSound) : bullets(bullets) {
    this->position = (Vector2) {(float) GetScreenWidth() / 2, (float) GetScreenHeight() - this->size - 10.0f};
    this->texture = playerTexture;
    this->bulletTexture = bulletTexture;
    this->laserSound = laserSound;
}
/*!
 *
 * Rysuje teksturę o zadanej rotacji i skali w odpowiednim kolorze w odpowiednim miejscu (określonym przez pozycję) na ekranie.
 */

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

/*!
 * Sprawdza czy Gracz może oddać strzał, jesli tak to tworzy obiekt Pocisku i dodaje go do kolekcji, odtwarza dźwięk wystrzału
 * i ustawia informację, że Gracz nie może strzelać.
 *
 * \see Bullet
 */
void Player::handleShoot() {
    if(this->isAbleToShoot){
        Bullet bullet(this->position, this->bulletTexture);
        this->bullets.push_back(bullet);
        this->isAbleToShoot = false;
        PlaySound(this->laserSound);
    }
}

/*!
 * Sprawdza czy Gracz ma zablokowaną możliwość oddania strzału, wtedy odlicza od zdefiniowanego czasu oczekiwania na
 * oddczanie strzału do 0, a po osiagnięciu 0 przywraca możliwość strzelania i resetuje obecny czas oczekiwania na strzał.
 */
void Player::handleShootAvailability() {
    if (!this->isAbleToShoot) {
        this->currentShootWaitTime -= GetFrameTime();
        if(this->currentShootWaitTime < 0.0f) {
            this->isAbleToShoot = true;
            this->currentShootWaitTime = this->shootWaitTime;
        }
    }
}

/*!
 * Obsługuje poruszanie obiektem Gracza na ekranie w zalezności od użytego klawisza.
 * \see moveRight()
 * \see moveLeft()
 */

void Player::handleMovement() {
    if (IsKeyDown(KEY_RIGHT) && IsKeyDown(KEY_LEFT)) {}
    if (IsKeyDown(KEY_RIGHT)) this->moveRight();
    if (IsKeyDown(KEY_LEFT)) this->moveLeft();
}

/*!
 * Nasłuchuje na użycie klawisza Spacji.
 * \see handleShoot()
 */
void Player::handleActions() {
    if (IsKeyPressed(KEY_SPACE)) this->handleShoot();
}

/*!
 * Nasłuchuje na użycie klawisza Spacji.
 * \see drawPlayer()
 */
void Player::draw() {
    this->drawPlayer();
}

/*!
 * Aktualizuje stan obiektju Gracza, nasłuchuje na zdarzenia.
 * \see handleMovement()
 * \see handleActions()
 * \see handleShootAvailability()
 */

void Player::update() {
    this->handleMovement();
    this->handleActions();
    this->handleShootAvailability();
}

/*!
 * \return Pozycja obiektu Gracza na ekranie, jako obiekt klasy Vector2.
 */

Vector2 Player::getPosition() {
    return this->position;
}

void Player::resetPosition() {
    this->position = (Vector2) {(float) GetScreenWidth() / 2, (float) GetScreenHeight() - this->size - 10.0f};
}

/*!
 * \return Wysokość tekstury Gracza, wartość float.
 */
float Player::getHeight() const {
    return (float) this->texture.height;
}
