#ifndef PAINTWIDGET_H
#define PAINTWIDGET_H

#include <QWidget>
#include <QMouseEvent>
#include <QPainter>
#include <QPoint>
#include <vector>
#include <memory>
#include "shape.h"
#include "line.h"
#include "circle.h"
#include "square.h"
#include <QPushButton>


class PaintWidget : public QWidget {
    Q_OBJECT

public:
    enum DrawMode {Line, Circle, Square, Select, Clone, Delete, Undo}; // definicja trybow rysowania, pozwala na okreslenie danego rysowania
    explicit PaintWidget(QWidget *parent = nullptr);
    void setDrawMode(DrawMode mode); // zmienia tryb rysowania
    void clear(); //  metoda do czyszczenia pola rysowania
    void saveShapes(const std::string &fileName); // metoda do zapisu kształtów
    void loadShapes(const std::string &fileName); // metoda do wczytania kształtów
    void selectEdgeColor();
    void selectFillColor(); 
    void undoLastShape();
    void newBackGroundColor();
    void changeSelectedShapeColor();
    
    
    


    




protected:
    void paintEvent(QPaintEvent *event) override;
    void mousePressEvent(QMouseEvent *event) override; // zdarzenie wywolywane gdy uzutkownik nacisnie mysz
    void mouseMoveEvent(QMouseEvent *event) override; // zdarzenie wywolywane gdy uzytkownik przemiesci mysz
    void mouseReleaseEvent(QMouseEvent *event) override; // zdarzenie wywolywane gdy uzytkownik zwolni mysz
    
    

private:
    std::vector<std::unique_ptr<Shape>> shapes; // wektor przechowujacy wskazniki do obiektow Shape
    DrawMode drawMode =  Select; //  domyślny tryb rysowania
    QPoint lastLineStart; // punkt startowy linii
    QPoint circleCenter; // Punkt środkowy koła
    int currentRadius = 0; // Obecny promień koła
    bool drawingCircle = false; // Flaga wskazująca, czy aktualnie rysujemy koło
    QPoint squareStart; // Punkt startowy kwadratu
    int squareSide = 0; // Długość boku kwadratu
    bool drawingSquare = false; // Flaga wskazująca, czy aktualnie rysujemy kwadrat
    
    Shape* selectedShape = nullptr; // wskaznik do obiektu Shape, ktory jest aktualnie wybrany
    bool isDragging = false; // Flaga wskazująca, czy aktualnie przeciągamy kształt;
    QPoint lastMousePos; // Punkt, w którym znajdowała się ostatnio mysz

    QColor currentEdgeColor = Qt::white;        // Aktualny kolor krawędzi
    QColor currentFillColor = Qt::transparent; // Aktualny kolor wypełnienia
    QColor currentBackgroundColor = Qt::transparent; // Aktualny kolor tła
    


    
};

#endif // PAINTWIDGET_H