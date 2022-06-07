#ifndef SPACEINVADERS_MISC_H
#define SPACEINVADERS_MISC_H

#include "raylib-cpp.hpp"

/*!
* \brief Klasa pomocnicza.
*
* Klasa posiadająca metody pomocnicze dla obiektów innych klas.
 *
*
*/
class Misc {

public:
    /*!
* \brief Sprawdza czy pozycje obiektów ze sobą kolidują.
*/
    static bool AreCollided(Vector2 position1, float width1, float height1, Vector2 position2, float width2, float height2);
    /*!
* \brief generuje losowy kolor.
*/
    static Color getRandomColor();

};


#endif //SPACEINVADERS_MISC_H
