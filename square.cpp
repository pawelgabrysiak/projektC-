#include "square.h"
#include <QPainter>

Square::Square(const QPoint& topLeft, int side) : topLeft(topLeft), side(side) {}
void Square::draw(QPainter& painter) const {
    QPen pen(edgeColor);         // kolor krawędzi
    painter.setPen(pen);

    QBrush brush(fillColor);     // kolor wypełnienia
    painter.setBrush(brush);

    painter.drawRect(topLeft.x(), topLeft.y(), side, side); // rysuj kwadrat
}

void Square :: save(std::ostream& output) const{
    output << "Square (" << topLeft.x() << "," << topLeft.y() << "," << side << "," << edgeColor.red() << "," << edgeColor.green() << "," << edgeColor.blue() << "," << fillColor.red() << "," << fillColor.green() << "," << fillColor.blue() << ")\n";
}



bool Square::isClicked(int x, int y) const {
    return (x >= topLeft.x() && x <= topLeft.x() + side &&
            y >= topLeft.y() && y <= topLeft.y() + side); // sprawdzanie czy punkt znajduje sie w srodku kwadratu
}

void Square::move(int dx, int dy) { // przesuniecie kwadratu o dx, dy
    topLeft.setX(topLeft.x() + dx);
    topLeft.setY(topLeft.y() + dy);
}

Shape* Square::clone() const {
    Square* clonedSquare = new Square(*this);
    const int offset = 15;
    clonedSquare->move(offset, offset);
    return clonedSquare;
}

Shape* Square::loadFromStream(std::istream &input){
    int r, g, b;
    int r1, g2, b3;
    int x, y, side;
    char openParen, comma, closeParen;

    input >> openParen >> x >> comma >> y >> comma >> side >> comma >> r >> comma >> g >> comma >> b >> comma >> r1 >> comma >> g2 >> comma >> b3 >> closeParen;

    if (input){
        Square* loadedSquare = new Square(QPoint(x, y), side);
        loadedSquare->edgeColor = QColor(r, g, b);
        loadedSquare->fillColor = QColor(r1, g2, b3);
        return loadedSquare;
    } else {
        return nullptr;
    }
}

