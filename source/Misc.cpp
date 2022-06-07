#include "Misc.h"
/**
* \file Misc.h
* Plik z definicją klasy Misc.
*/

/*!
* Metoda wykrywa sytuację w której dwa obiekty kolidują ze sobą.
 * \param[in] position1 Pozycja pierwszego obiektu, obiekt klasy Vector2
 * \param[in] width1 Szerokość pierwszego obiektu, wartość float
 * \param[in] height1 Wyokość pierwszego obiektu, wartość float
 * \param[in] position2 Pozycja drugiego obiektu, obiekt klasy Vector2
 * \param[in] width2 Szerokość drugiego obiektu, wartość float
 * \param[in] height2 Wysokość drugiego obiektu, wartość
 * \return Wartość logiczna, informująca o kolizji obiektów
*
*/
bool Misc::AreCollided(Vector2 position1, float width1, float height1, Vector2 position2, float width2, float height2) {

    Rectangle rectangle1 = (Rectangle) {position2.x - width2 / 4, position2.y - height2 / 4, width2 / 2, height2 / 2};
    Rectangle rectangle2 = (Rectangle) {position1.x - width1 / 4, position1.y - height1 / 4, width1 / 2, height1 / 2};

    return CheckCollisionRecs(rectangle1,rectangle2);
}

/*!
* Generuje losowo kolor z puli: {ORANGE, RED, GOLD, LIME, BLUE, VIOLET, BROWN, LIGHTGRAY, PINK,
                        YELLOW, GREEN, SKYBLUE, PURPLE, BEIGE }
 * \return Wylosowany kolor, obiekt typu Color
*
*/
Color Misc::getRandomColor() {
    Color colors[14] = {ORANGE, RED, GOLD, LIME, BLUE, VIOLET, BROWN, LIGHTGRAY, PINK,
                        YELLOW, GREEN, SKYBLUE, PURPLE, BEIGE };
    return colors[GetRandomValue(0, 13)];
}
