#ifndef LINE_H
#define LINE_H

#include <QPoint>

#include "shape.h"

class Line : public Shape {
public:
    Line(const QPoint& start, const QPoint& end); // Konstruktor przyjmuje dwa argumenty QPoint, ktore reprezentuja wspolrzedne punktu startowego i koncowego linii.
    void draw(QPainter& painter) const override; // rysuje linie za pomoca Qpainter
    void save(std::ostream& output) const override; // zapisuje wspolrzedne x,y punktu startowego i koncowego linii do pliku.
    bool isClicked(int x, int y) const override; // sprawdza czy linia jest kliknieta w punkcie
    void move(int dx, int dy); // przesuwa linie o dx, dy
    static Shape* loadFromStream(std::istream &input);
    Shape* clone() const override;
    
    
    QPoint getEnd() const { return end; } // Zwraca punkt końcowy linii

private:
    QPoint start, end;
};

#endif // LINE_H