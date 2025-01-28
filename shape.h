#ifndef SHAPE_H
#define SHAPE_H
#include <ostream>
#include <QPainter>
#include <istream>
#include <QColor> 


 class Shape {
protected:
    QColor edgeColor = Qt::white; // domyslny kolor krawedzi
    QColor fillColor = Qt::transparent; // domyslny kolor wypelnienia
    
public:
    virtual ~Shape() = default; // wirtualny destruktor
    virtual void draw(QPainter &painter) const = 0; // metoda odpowiadajaca za rysowanie ksztaltu na ekranie
    virtual void save(std::ostream &output) const = 0; // metoda do zapisu na dowolny strumien wejsciowy
    virtual bool isClicked(int x, int y) const = 0; // metoda sprawdzajaca czy kształt jest klikniety w punkcie (x, y)
    virtual void move(int dx, int dy) = 0; // metoda do przesuniecia kształtu o (dx, dy)
    virtual Shape* clone() const = 0; // metoda do klonowania kształtu

    void setEdgeColor(const QColor &color){edgeColor = color;}
    QColor getEdgeColor() const { return edgeColor;}

    void setFillColor(const QColor &color){fillColor = color;}
    QColor getFillColor() const {return fillColor;} 
    

    
   
    // metoda statyczna do dynamicznego wczytywania ksztaltu z dowolnego strumienia wejsciowego
    static Shape* loadFromStream(std::istream &input); 

    };


    
#endif // SHAPE_H

