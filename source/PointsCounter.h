#ifndef SPACEINVADERS_POINTSCOUNTER_H
#define SPACEINVADERS_POINTSCOUNTER_H

#include <string>
#include <raylib-cpp.hpp>

/*!
* \brief Modeluje pojęcie Licznika Punktów.
*
* Klasa modeluje pojęcie Licznika Punktów o pozycji, kolorze, wielkości czcionki, liczbie punktów i fali.
 *
*
*/
class PointsCounter {
private:
    /*!
* \brief Liczba punktów.
* Wartość typu unsigned long long.
*/
    unsigned long long points = 0;
    /*!
* \brief Numer fali.
* Zmienna typu całkowitoliczbowego.
*/
    int wave;
    /*!
* \brief Rozmiar czcionki, domyślnie 20.
*
*/
    int fontSize = 20;
    /*!
* \brief Kolor czcionki, domyślnie czerwony.
*/
    Color color = RED;
    /*!
* \brief Pozycja obiektu Licznika na ekranie.
* Obiekt klasy Vector2, domyślnie wartości w pozomie 10, w pionie wysokość ekranu - 20.
*/
    Vector2 position = {10, (float)GetScreenHeight() - 20};
public:
    /*! \brief Konstruktor klasy Licznika Punktów.
 *
 * Inicjalizuje obiekt Licznika Punktów podanym numerem fali.
 *
 * \param[in] wave Numer fali.
 * */
    explicit PointsCounter(int wave);
    /*!
* \brief Resetuje liczbę punktów.
*
*/
    void clearPoints();
    /*!
* \brief Zwiększa liczbę punktów .
*
*/
    void addPoint();
    /*!
* \brief Zwiększa falę o 1.
*
*/
    void addWave();
    /*!
* \brief Ustawia numer fali na wartość podaną.
*
*/
    void setWave(int wave);
    /*!
* \brief Odczytuje liczbę punktów.
*
*/
    unsigned long long getPoints() const;
    /*!
* \brief Rysuje obiekt Licznika Punktów na ekranie.
*
*/
    void draw();

};


#endif //SPACEINVADERS_POINTSCOUNTER_H
