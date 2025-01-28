#include "shape.h"
#include "line.h"
#include "square.h"
#include "circle.h"
#include <QPainter>
#include <sstream>


 Shape* Shape::loadFromStream(std::istream &input){ // zwraca wskaznik na obiekt klasy shape
    std::string line;
    std::getline(input, line); // przechowuje cala linie
    std::istringstream lineStream(line); // strumien do przetwarzania pojedynczej linii

    std::string shapeType; // zmienna przechowujaca typ figury
    lineStream >> shapeType; // wczytanie pierwszego slowa czyli typu figury

    if (shapeType == "Line"){ //wywolanie metod wczytywania dla typow figur
        return Line::loadFromStream(lineStream);
    } else if (shapeType == "Square"){
        return Square::loadFromStream(lineStream);
    } else if (shapeType == "Circle") {
        return Circle::loadFromStream(lineStream);
    } else {
        qWarning("Nieznany typ figury: %s", shapeType.c_str());
        return nullptr;
    }

 } 