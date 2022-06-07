#include "Bullet.h"
/**
* \file Bullet.h
* Plik z definicją klasy Pocisku.
*/

Bullet::Bullet(Vector2 initialPosition, Texture2D texture) {
    this->position = initialPosition;
    this->texture = texture;
}

/*!
* Sprawdza czy obiekt znajduje sie poza obszarem ekranu.
*
* \return Zwraca wartość logiczną: true jeśli obiekt poza ekranem, false gdy obiekt nie przekroczył krawędzi ekranu.
*/
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
    DrawTextureEx(this->texture,
                  (Vector2) {this->position.x - ((float)this->texture.width * this->scale / 2), this->position.y - ((float) this->texture.height * this->scale / 2)},
                  0,
                  this->scale,
                  RAYWHITE);
}


/*!
*
* \see moveUp()
*/
void Bullet::update() {
    this->moveUp();
}

/*!
* Odczytuje pozycje pocisku na ekranie.
*
* \return Zwraca obiekt typu Vector2.
*/
Vector2 Bullet::getPosition() {
    return this->position;
}

/*!
* Odczytuje rozmiar pocisku.
*
* \return Zwraca obiekt typu Vector2.
*/
Vector2 Bullet::getSize() const {
    return (Vector2) {(float) this->texture.width, (float) this->texture.height};
}