#include "Enemy.h"
/**
* \file Enemy.h
* Plik z definicją klasy Wroga.
*/
#include "Misc.h"
/**
* \file Misc.h
* Plik z definicją klasy Misc.
*/
#include "cmath"


Enemy::Enemy(Vector2 initialPosition, Texture2D texture, Sound explosionSound, float moveWaitTime, Direction initialDirection) {
    this->wiggleDuration = 0.2f;
    this->currentWiggleDuration = this->wiggleDuration;
    this->wiggleSleep = moveWaitTime - (moveWaitTime / 3);
    this->currentWiggleSleep = wiggleSleep;
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
/*!
 *
 * Rysuje teksturę o zadanej rotacji i skali w odpowiednim kolorze w odpowiednim miejscu (określonym przez pozycję) na ekranie.
 */

void Enemy::draw() {
    DrawTextureEx(this->texture,
                  (Vector2) {this->position.x - ((float)this->texture.width * this->scale / 2), this->position.y - ((float) this->texture.height * this->scale / 2)},
                  this->currentRotation,
                  this->scale,
                  this->color);
}

/*!
* Odczytuje pozycje wroga na ekranie.
*
* \return Zwraca obiekt typu Vector2.
*/

Vector2 Enemy::getPosition() {
    return this->position;
}

/*!
* Odczytuje rozmiar tekstury reprezentującej wroga.
*
* \return Zwraca obiekt typu Vector2.
*/

Vector2 Enemy::getSize() const {
    return (Vector2) {(float) this->texture.width, (float) this->texture.height};
}

/*!
* Sprawdza czy jeśli obiekt zmieni swoją pozycję o wartość określoną poprzez distanceToMove w osi x to czy przekroczy lewą lub prawą krawędź ekranu.
 * \return Wartość logiczna informująca czy obiekt wyjdzie poza ekran.
*/
bool Enemy::willGoOutOfScreen() const {
    bool willGoOutOfRight = this->distanceToMove < 0 && this->position.x - (float)this->texture.width / 2 - abs(this->distanceToMove) <= 0;
    bool willGoOutOfLeft = this->distanceToMove > 0 && this->position.x + (float)this->texture.width / 2 + abs(this->distanceToMove) >= (float) GetScreenWidth();
    return willGoOutOfLeft || willGoOutOfRight;
}

/*!
* Ustawia nowa pozycję obiektu na ekranie. Sprawdz czy obiekt może się poruszać, jeśli tak to zmienia jego pozycję
 * w poziomie o wartość zdefiniowana przez distanceToMove. W przypadku gdy obiekt ma przekroczyć krawędź ekranu, zmieniany
 * jest kierunek poruszania się obiektu i jego pozycja w osi y. Jeśli obiekt nie może sie poruszać to pozostaje w bezruchu
 * przez określony czas, a następnie przez drga (zrealizowani z wykorzystaniem rotacji).
 *
 * \see willGoOutOfScreen()
 * \see getSize()
*/
void Enemy::updatePosition() {
    if(this->isAbleToMove){
        if(this->willGoOutOfScreen()) {
            this->position.y += this->getSize().y;
            this->distanceToMove *= -1;
        }
        this->position.x += this->distanceToMove;
        this->isAbleToMove = false;
        this->currentWiggleDuration = this->wiggleDuration;
        this->currentWiggleSleep = this->wiggleSleep;
    } else {
        this->currentMoveWaitTime -= GetFrameTime();
        this->currentWiggleDuration -= GetFrameTime();
        this->currentWiggleSleep -= GetFrameTime();
        if(this->currentMoveWaitTime < 0.0f) {
            this->isAbleToMove = true;
            this->currentMoveWaitTime = this->moveWaitTime;
        }
        if(this->currentWiggleDuration < 0.0f && this->currentWiggleSleep < 0.0f) {
            this->currentRotation *= -1;
            this->currentWiggleDuration = this->wiggleDuration;
        } else {
            this->currentRotation = -3;
        }
    }
}

/*!
 * \see updatePosition()
 */

void Enemy::update() {
    this->updatePosition();
}

/*!
* Niszczy obiekt wroga i odtwarza dźwięk eksplozji.
*
*/
void Enemy::destroy() {
    PlaySound(this->explosionSound);
}