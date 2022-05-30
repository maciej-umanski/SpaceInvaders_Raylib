#include "Misc.h"

bool Misc::AreCollided(Vector2 position1, float width1, float height1, Vector2 position2, float width2, float height2) {

    Rectangle rectangle1 = (Rectangle) {position2.x - width2 / 4, position2.y - height2 / 4, width2 / 2, height2 / 2};
    Rectangle rectangle2 = (Rectangle) {position1.x - width1 / 4, position1.y - height1 / 4, width1 / 2, height1 / 2};

    return CheckCollisionRecs(rectangle1,rectangle2);
}