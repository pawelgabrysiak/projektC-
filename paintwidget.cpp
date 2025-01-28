#include "paintwidget.h"
#include "line.h" 
#include "circle.h"
#include "square.h" 
#include <memory>
#include <fstream> // do obslugi plikow
#include <sstream> 
#include <QMessageBox> // do komunikacji z uzytkownikiem
#include <QColorDialog>



PaintWidget::PaintWidget(QWidget *parent) : QWidget(parent) {}

void PaintWidget::setDrawMode(DrawMode mode) {
    if (drawMode != mode) {
        drawMode = mode; // Przypisanie nowego trybu rysowania

         // Resetowanie stanu zaznaczenia i rysowania
        selectedShape = nullptr;
        isDragging = false;
        
        // Resetowanie stanów trybu rysowania
        
        if (drawMode == Line) {
            lastLineStart = QPoint(); // Resetuj punkt początkowy linii
        } else if (drawMode == Circle) {
            drawingCircle = false; // Resetuj flagę rysowania koła
            currentRadius = 0;
        } else if (drawMode == Square) {
            drawingSquare = false; // Resetuj flagę rysowania kwadratu
        }
    }
}


void PaintWidget::clear() {
    QMessageBox::StandardButton reply;
    reply = QMessageBox::question(this, "Potwierdzenie", "Czy aby na pewno chcesz usunąć wszystko?", QMessageBox::Yes | QMessageBox::No);
    if (reply == QMessageBox::Yes) {
        shapes.clear();
        update();       
    } 
}

void PaintWidget::mousePressEvent(QMouseEvent *event) {
    QPoint mousePos = event->pos(); // zmienna przechowujaca polozenie myszki
    if (drawMode == Line) {
        if (lastLineStart.isNull()) {
            // zapisanie wspolrzednych klikniecia jesli linia jest pusta
            lastLineStart = mousePos;
        } else {
            auto line = std::make_unique<::Line>(lastLineStart, mousePos); // tworzenie nowego obiektu Line
            line->setEdgeColor(currentEdgeColor);
            shapes.push_back(std::move(line)); // dodanie obiektu do listy
            lastLineStart = QPoint(); // resetowanie punktu poczatkowego linii
        }
    } else if (drawMode == Circle) {
        circleCenter = mousePos;  // ustawia punkt srodka kola
        currentRadius = 0; 
        drawingCircle = true;
    } else if (drawMode == Square) {
        squareStart = mousePos;  // ustawia punkt startowy kwadratu
        squareSide = 0; 
        drawingSquare = true; 
    } else if (drawMode == Select) {
        selectedShape = nullptr; // resetowanie zaznaczenia
        for (auto& shape : shapes) { // przechodzimy przez wszystkie kształty
            if (shape->isClicked(mousePos.x(), mousePos.y())) { // sprawdzamy czy kształt jest kliknięty
                selectedShape = shape.get(); // pobieramy wskaznik na kształt
                isDragging = true; 
                lastMousePos = mousePos;
                break;
            }
        }
    } else if (drawMode == Clone) {
        // Tryb klonowania
        for (auto& shape : shapes) {
            if (shape->isClicked(mousePos.x(), mousePos.y())) {
                selectedShape = shape.get(); // pobranie klikniętego kształtu
                if (selectedShape) {
                    Shape* clonedShape = selectedShape->clone(); // klonowanie kształtu
                    shapes.push_back(std::unique_ptr<Shape>(clonedShape)); // dodanie klona
                }
                break; 
            }
        }
    } else if (drawMode == Delete) {
        auto it = std::find_if(shapes.begin(), shapes.end(), // find_if przeszukuje wektor shapes i zwraca iterator na pierwszy element, ktory spełnia warunek
                           [&mousePos](const std::unique_ptr<Shape>& shape) { // referencja do wskaznika
                               return shape->isClicked(mousePos.x(), mousePos.y()); // sprawdzanie czy kształt jest kliknięty
                           }); 
        if (it != shapes.end()) { // sprawdzanie czy element został znaleziony
            shapes.erase(it); // usuwa element z kontenera na ktory wskazuje iterator it
        } 
    }
    update();
}

void PaintWidget::mouseMoveEvent(QMouseEvent *event) {
    QPoint mousePos = event->pos();
     if (drawMode == Circle && drawingCircle) {
        // oblicza odleglosc od biezacej pozycji myszki do punktu srodka kola
        currentRadius = static_cast<int>(std::hypot(mousePos.x() - circleCenter.x(), 
        mousePos.y() - circleCenter.y()));
        
        update();
        
    } else if (drawMode == Square && drawingSquare) {
         int dx = mousePos.x() - squareStart.x(); // obliczamy roznice biezacej pozycji myszy a punktu startowego
        int dy = mousePos.y() - squareStart.y(); 
        squareSide = std::max(std::abs(dx), std::abs(dy)); // pobieramy wartosci bezwzgledne roznic, i uzywamy max do upewnienia ze boki sa sobie rowne
        update();
    } else if (isDragging && selectedShape) {
        int dx = mousePos.x() - lastMousePos.x();
        int dy = mousePos.y() - lastMousePos.y();
        selectedShape->move(dx, dy); 
        lastMousePos = mousePos; 
        update();
    }
}

void PaintWidget::paintEvent(QPaintEvent *event) {
    QPainter painter(this);

    painter.fillRect(rect(), currentBackgroundColor);

    // petla pozwala na rysowanie razem figur na ekranie
    for (const auto& shape : shapes) { // przechodzimy przez ksztalty w shapes
        shape->draw(painter); // wywolujemy metode draw na kazdym kształcie
    }

    if (drawMode == Circle && drawingCircle) {
        painter.drawEllipse(circleCenter, currentRadius, currentRadius);
    } else if (drawMode == Square && drawingSquare) {
        painter.drawRect(squareStart.x(), squareStart.y(), squareSide, squareSide);
    }
    
}

void PaintWidget::mouseReleaseEvent(QMouseEvent *event) {
    if (drawMode == Circle && drawingCircle) {
        // zapisanie kola w wektorze shapes
        auto circle = std::make_unique<::Circle>(circleCenter,currentRadius); // tworzenie nowego kola
        circle->setEdgeColor(currentEdgeColor);
        circle->setFillColor(currentFillColor);
        shapes.push_back(std::move(circle)); // dodanie kola do wektora shapes
        drawingCircle = false;
        currentRadius = 0;
        update();
    } else if (drawMode == Square && drawingSquare) {
        auto square = std::make_unique<::Square>(squareStart, squareSide); // tworzenie nowego kwadratu
        square->setEdgeColor(currentEdgeColor);
        square->setFillColor(currentFillColor);
        shapes.push_back(std::move(square)); // zapisanie kwadratu w wektorze shapes
        drawingSquare = false;
        squareSide = 0;
        update();
    }
}


void PaintWidget::saveShapes(const std::string &filename) { // tworzenie strumienia do pliku
    std::ofstream file(filename); // konstruktor przyjmuje nazwe pliku i otwiera go w trybie zapisu
    
    if (!file.is_open()){
        qWarning("Nie udało się otworzyć pliku");
        return;
    }
    
    for (const auto &shape : shapes) { // przechodzimy po wszystkich elementach w wektorze shapes
        shape->save(file); // wywolujemy metode save ktora zapisuje specyficzne dane dla danej figury
    }

    file.close (); 
}

void PaintWidget::loadShapes(const std::string &filename) {

    std::ifstream file(filename); // otwieranie pliku w trybie odczytu

    if (!file.is_open()){
        qWarning("Nie udało się otworzyć pliku");
        return;
    }

    std::string line; // zmienna do przechowywania linii

    while (std::getline(file, line)){
        std::istringstream stream(line); // strumien do przetwarzania pojedynczej linii

        Shape* shape = Shape::loadFromStream(stream); // wywolanie metody loadFromStream ktora zwraca wskaznik na obiekt klasy Shape

        if (shape){
            // po powrocie z Shape::loadFromStream utworzony obiekt jest dodawany do wektora shapes
            shapes.push_back(std::unique_ptr<Shape>(shape)); 
        } else {
            qWarning("Nie udalo sie zaladowac figury");
        }
    }

    file.close();
    update();
}

void PaintWidget::selectEdgeColor() {
    QColor color = QColorDialog::getColor(currentEdgeColor, this, "Wybierz kolor krawędzi");
    if (color.isValid()) { // sprawdzanie, czy użytkownik wybrał kolor
        currentEdgeColor = color;
    }
}

void PaintWidget::selectFillColor() {
    QColor color = QColorDialog::getColor(currentFillColor, this, "Wybierz kolor wypełnienia");
    if (color.isValid()) { // sprawdzanie, czy użytkownik wybrał kolor
        currentFillColor = color;
    }
}

void PaintWidget::undoLastShape() {
    if (!shapes.empty()){
        shapes.pop_back(); // usuwa ostatni element wektora shapes
        update();
    }

}

void PaintWidget::newBackGroundColor(){
    QColor color = QColorDialog::getColor(currentBackgroundColor, this, "Wybierz kolor tŁa");
    if (color.isValid()) {
        currentBackgroundColor = color;
        update();
    }
}

void PaintWidget::changeSelectedShapeColor(){
    if (selectedShape != nullptr) {
        selectedShape->setEdgeColor(currentEdgeColor);
        selectedShape->setFillColor(currentFillColor);
        update();
    } else {
        QMessageBox::information(this, "Błąd", "Nie wybrano żadnej figury");
    }

}



