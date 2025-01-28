#ifndef SQUARE_H
#define SQUARE_H

#include <QPoint>

#include "shape.h"

class Square : public Shape {
public:
    Square(const QPoint& topLeft, int side);
    void draw(QPainter& painter) const override;
    void save(std::ostream& output) const override;
    static Shape* loadFromStream(std::istream &input);
    bool isClicked(int x, int y) const override;
    void move(int dx, int dy);
    Shape* clone() const override;

    
private:
    QPoint topLeft; // wspolrzedne lewego gornego roga kwadratu
    int side; // długość boku kwadratu
};

#endif // SQUARE_H