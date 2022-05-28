#include "PointsCounter.h"

void PointsCounter::addPoint() {
    this->points++;
}

unsigned long long PointsCounter::getPoints() const {
    return this->points;
}

void PointsCounter::draw() {
    auto result = "Points: " + std::to_string( this->points );
    DrawText(result.c_str(), (int) this->position.x, (int) this->position.y, this->fontSize, this->color);
}

void PointsCounter::clearPoints() {
    this->points = 0;
}
