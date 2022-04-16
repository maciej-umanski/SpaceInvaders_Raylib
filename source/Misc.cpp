#include "Misc.h"

bool Misc::AreCollided(Vector2 position1, float size1, Vector2 position2, float size2) {
    return CheckCollisionRecs(
            (Rectangle) {position1.x - size1 / 2, position1.y - size1 / 2, size1, size1},
            (Rectangle) {position2.x - size2 / 2, position2.y - size2 / 2, size2, size2}
            );
}