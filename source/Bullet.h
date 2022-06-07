#ifndef SPACEINVADERS_BULLET_H
#define SPACEINVADERS_BULLET_H

#include "raylib-cpp.hpp"
#include <iostream>

using namespace std;

/*!
* \brief Modeluje pojęcie Pocisku.
*
* Klasa modeluje pojęcie Pocisku o danej pozycji, teksturze, prędkości i skali.
*
*/
class Bullet {
private:
    /*!
    * \brief Pozycja obiektu na ekranie.
    * Obiekt klasy Vector przechowujący pozycję obiektu Pocisk na ekranie.
    */
    Vector2 position{};
    /*!
    * \brief Prędkość poruszania się obiektu po ekranie.
    *
    * Zmienna typu float.
    */
    float speed = 5.0f;
    /*!
    * \brief Skala obiektu.
    *
    * Zmienna typu float.
    */
    float scale = 1.0f;
    /*!
    * \brief Tekstura reprezentująca obiekt Pocisku.
    *
    * Obiekt typu Texture2D.
    */
    Texture2D texture{};

    /*!
    * \brief Metoda zmieniająca położenie obiektu na ekranie w osi y.
    *
    */
    void moveUp();
public:
    /*! \brief Konstruktor klasy Pocisk.
     * Inicjalizuje pozycję pocisku na ekranie i ustawia teksturę.
     * \param[in] initialPosition Początkowa pozycja pocisku.
     * \param[in] texture Tekstura.
     * */
    explicit Bullet(Vector2 initialPosition, Texture2D texture);
    /*! \brief Rysuje teksturę na ekranie. */
    void draw();
    /*! \brief Aktualizuje pozycję obiektu na ekranie. */
    void update();

    /*! \brief Sprawdza czy obiekt znajduje się poza obszarem ekranu. */
    bool isOutOfScreen() const;
    /*! \brief Odczytuje pozycję obiektu na ekranie. */
    Vector2 getPosition();
    /*! \brief Pobiera rozmiar tekstury reprezentującej pocisk. */
    Vector2 getSize() const;
};


#endif //SPACEINVADERS_BULLET_H
