#ifndef CIRCLE_H
#define CIRCLE_H

#include <QPoint>

#include "shape.h"

class Circle : public Shape {
public:
    Circle(const QPoint& center, int radius);
    void draw(QPainter& painter) const override;
    void save(std::ostream& output) const override;
    static Shape* loadFromStream(std::istream &input);
     bool isClicked(int x, int y) const override;
     void move(int dx, int dy);
     Shape* clone() const override;
     
    
private:
    QPoint center;
    int radius;
};

#endif // CIRCLE_H

