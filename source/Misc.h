#ifndef SPACEINVADERS_MISC_H
#define SPACEINVADERS_MISC_H

#include "raylib-cpp.hpp"


class Misc {

public:
    static bool AreCollided(Vector2 position1, float size1, Vector2 position2, float size2);

};


#endif //SPACEINVADERS_MISC_H
