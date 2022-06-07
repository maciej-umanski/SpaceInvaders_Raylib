#ifndef SPACEINVADERS_PLAYER_H
#define SPACEINVADERS_PLAYER_H

#include "raylib-cpp.hpp"
#include "Bullet.h"
/**
* \file Bullet.h
* Plik z definicją klasy Bullet.
*/

#include <iostream>

using namespace std;

/*!
* \brief Modeluje pojęcie Gracza.
*
* Klasa modeluje pojęcie Gracza o danej pozycji, teksturze, skali, rozmiarze, prędkości, dźwięku wystrzału i parametrach strzelania.
 *
*
*/
class Player {
private:
    /*!
    * \brief Pozycja obiektu na ekranie.
    * Obiekt klasy Vector przechowujący pozycję obiektu Gracz na ekranie.
    */
    Vector2 position{};
    /*!
    * \brief Prędkość poruszania się Gracza.
    * Zmienna typu float, domyślnie ustawiona na wartość 3.
    */
    float speed = 3.0f;
    /*!
* \brief Rozmiar tekstury reprezentującej obiekt Gracza.
* Zmienna typu float, domyślnie ustawiona na wartość 20.
*/
    float size = 20.0f;
    /*!
* \brief Skala obiektu Gracza.
* Zmienna typu float, domyślnie ustawiona na wartość 0.5.
*/
    float scale = 0.5f;
    /*!
* \brief Informacja czy Gracz może strzelać.
* Zmienna typu logicznego, domyślnie wartość true.
*/
    bool isAbleToShoot = true;
    /*!
* \brief Czas opóźnienia wystrzału.
* Zmienna typu float, domyślnie wartość 0.2.
*/
    float shootWaitTime = 0.2f;
    /*!
* \brief Obecny czas oczekiwania na wystrzał.
* Zmienna typu float.
*/
    float currentShootWaitTime = shootWaitTime;
    /*!
* \brief Tekstura reprezentująca obiekt Gracza.
* Obiekt klasy Texture2D.
*/
    Texture2D texture{};
    /*!
* \brief Tekstura reprezentująca obiekt pocisku.
* Obiekt klasy Texture2D.
*/
    Texture2D bulletTexture{};
    /*!
* \brief Dźwięk wystarzału pocisku.
* Obiekt klasy Sound.
*/
    Sound laserSound;

    /*!
* \brief Kolekcja pocisków Bullet należących do Gracza.
* Kolekcja vector obiektów typu Bullet.
*/
    vector<Bullet> &bullets;

    /*!
* \brief Rysuje teksturę reprezentującą obiekt Gracza.
*
*/
    void drawPlayer();
    /*!
* \brief Zmienia pozycję Gracza w osi x w prawym kierunku aż do napotkania prawej krawędzi ekranu.
*
*/
    void moveRight();
    /*!
* \brief Zmienia pozycję Gracza w osi x w lewym kierunku aż do napotkania prawej krawędzi ekranu.
*
*/
    void moveLeft();
    /*!
* \brief Obsługuje wystrzał pocisku przez Gracza.
*
*/
    void handleShoot();
    /*!
* \brief Obsługuje ruch obiektem Gracza.
*
*/
    void handleMovement();
    /*!
* \brief Obsługuje akcje strzelania przez Gracza.
*
*/
    void handleActions();
    /*!
* \brief Obsługuje możliwość strzelania przez Gracza.
*
*/
    void handleShootAvailability();

public:
    /*! \brief Konstruktor klasy Gracza.
 *
 * Inicjalizuje obiekt Gracza początkowymi wartościami. Ustawia pozycję początkową Gracza, teksturę obiektu reprezentującego
     * Gracza, teksturę reprezentującą obiekty Pocisków Gracza i dźwiek wystrzału.
 *
 * \param[in] bullets Kolekcja pociskow Gracza.
 * \param[in] playerTexture Tekstura obiektu Gracza.
 * \param[in] bulletTexture Tekstura obiektu Bullet.
 * \param[in] laserSound Dźwięk wystrzału pocisku przez Gracza.
 * */
    explicit Player(vector<Bullet> &bullets, Texture2D playerTexture, Texture2D bulletTexture, Sound laserSound);
    /*!
* \brief Rysuje teksturę reprezentującą obiekt Gracza na ekranie.
*
*/
    void draw();
    /*!
* \brief Aktualizuję obiekt Gracza.
*
*/
    void update();
    /*!
* \brief Odczytuje pozycję obiektu Gracza na ekranie.
*
*/
    Vector2 getPosition();
    /*!
* \brief Resetuje pozycję obiektu Gracza na ekranie do wartości początkowych.
*
*/
    void resetPosition();
    /*!
* \brief Odczytuje wysokość tekstury reprezentującej obiekt Gracza.
*
*/
    float getHeight() const;
};


#endif //SPACEINVADERS_PLAYER_H
