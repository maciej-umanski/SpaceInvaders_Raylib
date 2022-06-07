#ifndef SPACEINVADERS_ENEMY_H
#define SPACEINVADERS_ENEMY_H

#include "raylib-cpp.hpp"
#include "Misc.h"
/**
* \file Misc.h
* Plik z definicją klasy Misc.
*/

/*! Definicja typów kierunków ruchu.
*
*/
enum Direction {
    LEFT = 0, /**< Wartość 0 reprezentująca kierunek w lewo. */
    RIGHT /**< Wartość 1 reprezentująca kierunek w prawo. */
};

/*!
* \brief Modeluje pojęcie Wroga.
*
* Klasa modeluje pojęcie Wroga o danej pozycji, teksturze, skali, dźwięku ekspplozji i parametrach poruszania się i transformacji.
 *
 * \see Misc#getRandomColor()
*
*/
class Enemy {
private:
    /*!
    * \brief Pozycja obiektu na ekranie.
    * Obiekt klasy Vector przechowujący pozycję obiektu Pocisk na ekranie.
    */
    Vector2 position{};
    /*!
    * \brief Informacja czy obiekt jest w stanie się poruszać
    * Zmienna typu logicznego, domyślna wartość to false.
    */
    bool isAbleToMove = false;
    /*!
    * \brief Czas przez który obiekt będzie czekał na mozliwość poruszania się.
     * Zmienna typu float.
    */
    float moveWaitTime;
    /*!
    * \brief Obecny czas, który został obiektowi do momentu poruszania się.
     * Zmienna typu float.
    */
    float currentMoveWaitTime;
    /*!
    * \brief Czas trwania drgania obiektu.
    * Zmienna typu float.
    */
    float wiggleDuration;
    /*!
    * \brief Czas w którym obiekt pozostaje w bezruchu.
    * Zmienna typu float.
    */
    float wiggleSleep;
    /*!
    * \brief Obecny czas który pozostał obiektowi do rozpoczęcia drgania.
    * Zmienna typu float.
    */
    float currentWiggleSleep;
    /*!
    * \brief Obecny czas który pozostał obiektowi w trybie drgania.
    * Zmienna typu float.
    */
    float currentWiggleDuration;
    /*!
    * \brief Skala obiektu.
    * Zmienna typu float.
    */
    float scale = 0.5f;
    /*!
    * \brief Tekstura reprezentująca obiekt na ekranie.
    * Obiekt typu Texture2D.
    */
    Texture2D texture{};
    /*!
    * \brief Wartość o jaką obiekt zmienia swoją pozycję w pionie i poziomie.
    * Zmienna typu float.
    */
    float distanceToMove;
    /*!
    * \brief Dźwięk odtwarzany w przypadku zniszczenia obiektu Wroga.
    * Obiekt klasy Sound.
    */
    Sound explosionSound{};
    /*!
    * \brief Kolor tekstury reprezentującego obiekt Wroga.
    * Obiekt klasy Color, generowany losowo.
    */
    Color color = Misc::getRandomColor();
    /*!
    * \brief Wartość o jaką obiekt będzie rotowany w trybie drgania.
    * Zmienna typu float, domyślnie ustawiona na -0.3.
    */
    float wiggleRotation = -3.0f;
    /*!
    * \brief Wartość o jaką rotowany jest obiekt.
    * Zmienna typu float, domyślnie ustawiona na wartość 0.
    */
    float currentRotation = 0;

    /*!
    * \brief Aktualizuje pozycję obiektu na ekranie.
    */
    void updatePosition();
    /*!
    * \brief Sprawdza czy obiekt zmieniając pozycję przekroczy krawędzi ekranu.
    * \return Zwraca wartość logiczną: true jeśli przekroczy, false jeśli nie przekroczy.
    */
    bool willGoOutOfScreen() const;

public:
    /*! \brief Konstruktor klasy Wroga.
     *
     * Inicjalizuje obiekt początkowymi wartościami. Ustawia czas trwania drgania obiektu na 0.2, czas w którym obiekt pozostaje
     * w bezruchu na 2/3 czasu poruszania się obiektu, ustawia pozycję początkową obiektu, teksturę, dźwięk wybuchu, początkowy kierunek
     * ruchu obiektu w osi x.
     *
     * \param[in] initialPosition Pozycja początkowa wroga.
     * \param[in] texture Tekstura.
     * \param[in] explosionSound Dźwięk eksplozji.
     * \param[in] moveWaitTime Czas oczekiwania na możliwość poruszania się obiektu.
     * \param[in] initialDirection Początkowy kierunek poruszania się wroga.
     * */
    explicit Enemy(Vector2 initialPosition, Texture2D texture, Sound explosionSound, float moveWaitTime, Direction initialDirection);

    /*! \brief Rysuje teksturę na ekranie. */
    void draw();
    /*! \brief Aktualizuje pozycje obiektu na ekranie. */
    void update();
    /*! \brief Niszczy obiekt po trafieniu. */
    void destroy();
    /*! \brief Pobiera pozycję obiektu na ekranie. */
    Vector2 getPosition();
    /*! \brief Pobiera rozmiar tekstury obiektu. */
    Vector2 getSize() const;
};


#endif //SPACEINVADERS_ENEMY_H
