#include "PointsCounter.h"

PointsCounter::PointsCounter(int wave) {
    this->wave = wave;
}

void PointsCounter::addPoint() {
    this->wave == 0 ? this->points+=1 : this->points+=this->wave;
}

unsigned long long PointsCounter::getPoints() const {
    return this->points;
}

void PointsCounter::draw() {
    auto result = "Wave: " + std::to_string( this->wave + 1 ) + " | Points: " + std::to_string( this->points );
    DrawText(result.c_str(), (int) this->position.x, (int) this->position.y, this->fontSize, this->color);
}

void PointsCounter::clearPoints() {
    this->points = 0;
}

void PointsCounter::addWave() {
    this->wave++;
}

void PointsCounter::setWave(int newWave) {
    this->wave = newWave;
}
