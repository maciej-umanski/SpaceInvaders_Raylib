#ifndef SPACEINVADERS_POINTSCOUNTER_H
#define SPACEINVADERS_POINTSCOUNTER_H

#include <string>
#include <raylib-cpp.hpp>

class PointsCounter {
private:
    unsigned long long points = 0;
    int fontSize = 20;
    Color color = RED;
    Vector2 position = {10, 10};
public:
    void addPoint();
    unsigned long long getPoints() const;
    void draw();

};


#endif //SPACEINVADERS_POINTSCOUNTER_H
