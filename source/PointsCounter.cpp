#include "PointsCounter.h"
/**
* \file PointsCounter.h
* Plik z definicją klasy PointsCounter.
*/

PointsCounter::PointsCounter(int wave) {
    this->wave = wave;
}

/*!
* Jeśli fala ustawiona na 0, to zwiększa liczbę punktów o 1, w przeciwnym wypadku zwiększa liczbę punktów o numer fali.
*
*/
void PointsCounter::addPoint() {
    this->wave == 0 ? this->points+=1 : this->points+=this->wave;
}

/*!
* \return Liczba punktów, wartość typu unsigned long long.
*
*/
unsigned long long PointsCounter::getPoints() const {
    return this->points;
}

/*!
* Wyświetla liczbę punktów jako napis o podanej wielkości czcionki, kolorze i pozycji na ekranie.
*
*/

void PointsCounter::draw() {
    auto result = "Wave: " + std::to_string( this->wave + 1 ) + " | Points: " + std::to_string( this->points );
    DrawText(result.c_str(), (int) this->position.x, (int) this->position.y, this->fontSize, this->color);
}

/*!
* Ustawia liczbę punktów na 0.
*
*/

void PointsCounter::clearPoints() {
    this->points = 0;
}

void PointsCounter::addWave() {
    this->wave++;
}

/*!
* \param[in] newWave Nowy numer fali, wartość typu int.
*
*/

void PointsCounter::setWave(int newWave) {
    this->wave = newWave;
}
