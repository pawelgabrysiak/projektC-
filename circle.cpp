#include "circle.h"
#include <QPainter>

Circle::Circle(const QPoint& center, int radius) : center(center), radius(radius) {}

void Circle::draw(QPainter& painter) const {
    QPen pen(edgeColor);         
    painter.setPen(pen);

    QBrush brush(fillColor);     
    painter.setBrush(brush);

    painter.drawEllipse(center, radius, radius); 
}

void Circle :: save(std::ostream& output) const{
    output << "Circle (" << center.x() << "," << center.y() << "," << radius << "," << edgeColor.red() << "," << edgeColor.green() << "," << edgeColor.blue() << "," << fillColor.red() << "," << fillColor.green() << "," << fillColor.blue() << ")\n";
}


bool Circle::isClicked(int x, int y) const { 
    int dx = x - center.x();
    int dy = y - center.y();
    return (dx * dx + dy * dy) <= (radius * radius); // punkt wewnątrz koła
}

void Circle::move(int dx, int dy) { // przesuwanie środka kola o dx i dy
    center.setX(center.x() + dx);
    center.setY(center.y() + dy);
}

Shape* Circle::clone() const {
    Circle* clonedCircle = new Circle(*this);
    const int offset = 15;
    clonedCircle->move(offset, offset);
    return clonedCircle;
}


Shape* Circle :: loadFromStream(std::istream &input){
    int r, g, b;
    int r1, g2, b3;
    int x, y, radius;
    char openParen, comma, closeParen;
    input >> openParen >> x >> comma >> y >> comma >> radius >> comma >> r >> comma >> g >> comma >> b >> comma >> r1 >> comma >> g2 >> comma >> b3 >> closeParen;

    if (input){
        Circle* loadedCircle = new Circle(QPoint(x, y), radius);
        loadedCircle->edgeColor = QColor(r, g, b);
        loadedCircle->fillColor = QColor(r1, g2, b3);
        return loadedCircle;
    } else {
        return nullptr;
    }
}

