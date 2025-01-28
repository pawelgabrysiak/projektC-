#include "line.h"
#include <QPainter>

Line :: Line(const QPoint& start, const QPoint& end) : start(start), end(end) {} // konstruktor przyjmuje wartosci obiektu line

void Line :: draw(QPainter& painter) const { // metoda draw rysuje linię
    QPen pen(edgeColor); // zmienna pen przechowuje kolor kreski
    painter.setPen(pen); // ustawienie koloru kreski
    painter.drawLine(start, end);
}

void Line :: save(std::ostream& output) const{ // zapisuje linie do pliku
    output << "Line (" << start.x() << "," << start.y() << "," << end.x() << "," << end.y() << "," << edgeColor.red() << "," << edgeColor.green() << "," << edgeColor.blue() << ")\n";
}



bool Line::isClicked(int x, int y) const {
    const double threshold = 5.0; // margines błędu dla kliknięcia w linię

    double lineLength = std::hypot(end.x() - start.x(), end.y() - start.y());
    
    if (lineLength == 0) {
        return false; // zapobiega dzieleniu przez zero
    }

    // wzór na odległość punktu (x, y) od odcinka (start, end)
    double distance = std::abs((end.y() - start.y()) * x - (end.x() - start.x()) * y +
                               end.x() * start.y() - end.y() * start.x()) / lineLength;

    if (distance > threshold) {
        return false; // Jeśli punkt jest za daleko, to nie jest kliknięty
    }

    // sprawdzenie, czy punkt (x, y) mieści się wewnątrz zakresu odcinka
    bool withinBoundsX = (x >= std::min(start.x(), end.x()) - threshold &&
                          x <= std::max(start.x(), end.x()) + threshold);
    bool withinBoundsY = (y >= std::min(start.y(), end.y()) - threshold &&
                          y <= std::max(start.y(), end.y()) + threshold);

    return withinBoundsX && withinBoundsY;
}


void Line :: move(int dx, int dy)  { // przesuwa linie
    start.setX(start.x() + dx);
    start.setY(start.y() + dy); 
    end.setX(end.x() + dx);
    end.setY(end.y() + dy);
}

Shape* Line :: clone() const{
    Line* clonedLine = new Line(*this);
    const int offset = 15;
    clonedLine->move(offset, offset);
    return clonedLine;
}

Shape* Line :: loadFromStream(std::istream &input){ // wczytuje linie z pliku
    int r, g, b;
    int x1, y1, x2, y2;
    char openParen, comma, closeParen; // zmienne okreslajace otworz nawias, przecinek, zamknij nawias
    input >> openParen >> x1 >> comma >> y1 >> comma >> x2 >> comma >> y2 >> comma >> r >> comma >> g >> comma >> b >> closeParen;
    if (input){
        Line* loadedLine = new Line(QPoint(x1, y1), QPoint(x2, y2));
        loadedLine->edgeColor = QColor(r, g, b);
        return loadedLine;
    } else {
        return nullptr;
    }
}







