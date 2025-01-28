#include <QApplication> // biblioteka, ktora odpowiada za zarzadzanie aplikacja Qt
#include "paintwidget.h"
#include <QWidget>
#include <QPushButton>
#include <QVBoxLayout>
#include <QFileDialog>


int main(int argc, char *argv[]) { // funkcja przyjmuje liczbe argumentow przekazywanych do programu oraz tablice argumentow 
    QApplication app(argc, argv); // tworzenie obiektu, ktory odpowiada za obsluge petli zdarzen
    
    QWidget mainWindow; // tworzenie głównego okna w aplikacji
    mainWindow.setWindowTitle("Paint Qt App"); 
    mainWindow.resize(600, 600); // przeskalowanie okna na  szer - 600 pikseli, wys - 600 pikseli

    PaintWidget *paintWidget = new PaintWidget(&mainWindow);  // tworzenie obiektu klasy PaintWidget czyli widzetu do rysowania

    
    // tworzenie przyciskow do zmiany trybu rysowania
    QPushButton *lineButton = new QPushButton("Draw Line", &mainWindow); //&mainWindow dla autmatycznej zarzadzanej pamieci
    QPushButton *circleButton = new QPushButton("Draw Circle", &mainWindow);
    QPushButton *squareButton = new QPushButton("Draw Square", &mainWindow);
    QPushButton *clearButton = new QPushButton("Clear", &mainWindow);
    QPushButton *saveButton = new QPushButton("Save", &mainWindow);
    QPushButton *loadButton = new QPushButton("Load", &mainWindow);
    QPushButton *saveAsButton = new QPushButton("Save as", &mainWindow);
    QPushButton *loadAsButton = new QPushButton("Load as", &mainWindow);
    QPushButton *selectButton = new QPushButton("Select", &mainWindow);
    QPushButton *cloneButton = new QPushButton("Clone", &mainWindow);
    QPushButton *deleteButton = new QPushButton("Delete", &mainWindow);
    QPushButton *undoButton = new QPushButton("Undo", &mainWindow);
    QPushButton *edgeColorButton = new QPushButton("Edge color", &mainWindow);
    QPushButton *fillColorButton = new QPushButton("Fill color", &mainWindow);
    QPushButton *backGroundButton = new QPushButton("Background color", &mainWindow);
    QPushButton *changeColorButton = new QPushButton("Change color of shape", &mainWindow);



    // Łączenie sygnałów przycisków z metodą ustawiającą tryb rysowania

    QObject::connect(lineButton, &QPushButton::clicked, [paintWidget]() {
        paintWidget->setDrawMode(PaintWidget::Line);

    });

    QObject::connect(circleButton, &QPushButton::clicked, [paintWidget]() {
        paintWidget->setDrawMode(PaintWidget::Circle);

    });

    QObject::connect(squareButton, &QPushButton::clicked, [paintWidget]() {
        paintWidget->setDrawMode(PaintWidget::Square);

    });

    QObject::connect(clearButton, &QPushButton::clicked, [paintWidget]() {
        paintWidget->clear(); //wywolanie metody clear aby wyczyscic ekran

    });

    QObject::connect(saveButton, &QPushButton::clicked, [paintWidget]() {
        paintWidget->saveShapes("shapes.txt"); 

    });

    QObject::connect(loadButton, &QPushButton::clicked, [paintWidget]() {
        paintWidget->loadShapes("shapes.txt"); 

    });

    QObject::connect(saveAsButton, &QPushButton::clicked, [paintWidget]() {
        QString fileName = QFileDialog::getSaveFileName(nullptr, "Zapisz jako", "", "Plik tekstowy (*.txt)");
        if (!fileName.isEmpty()){
            if (!fileName.endsWith(".txt")){
                fileName += ".txt";
            }
            paintWidget->saveShapes(fileName.toStdString());
        }
    });

    QObject::connect(loadAsButton, &QPushButton::clicked, [paintWidget]() {
        QString fileName = QFileDialog::getOpenFileName(nullptr, "Wczytaj jako", "", "Plik tekstowy (*.txt)");
        if (!fileName.isEmpty()){
            paintWidget->loadShapes(fileName.toStdString());
        }
    });

    QObject::connect(selectButton, &QPushButton::clicked, [paintWidget]() {
        paintWidget->setDrawMode(PaintWidget::Select); 

    });

    QObject::connect(cloneButton, &QPushButton::clicked, [paintWidget]() {
        paintWidget->setDrawMode(PaintWidget::Clone); 

    });

    QObject::connect(deleteButton, &QPushButton::clicked, [paintWidget]() {
        paintWidget->setDrawMode(PaintWidget::Delete); 

    });

    QObject::connect(edgeColorButton, &QPushButton::clicked, [paintWidget]() {
    paintWidget->selectEdgeColor();
    });

    QObject::connect(fillColorButton, &QPushButton::clicked, [paintWidget]() {
    paintWidget->selectFillColor();
    });

    QObject::connect(undoButton, &QPushButton::clicked, [paintWidget]() {
    paintWidget->undoLastShape();
    });

    QObject::connect(backGroundButton, &QPushButton::clicked, [paintWidget]() {
    paintWidget->newBackGroundColor();
    });

    QObject::connect(changeColorButton, &QPushButton::clicked, [paintWidget]() {
    paintWidget->changeSelectedShapeColor();
    });



    // uklad poziomy dla przycisków
    QHBoxLayout *buttonLayout = new QHBoxLayout;
    buttonLayout->addWidget(lineButton);
    buttonLayout->addWidget(circleButton);
    buttonLayout->addWidget(squareButton);
    buttonLayout->addWidget(clearButton);
    buttonLayout->addWidget(saveButton);
    buttonLayout->addWidget(loadButton);
    buttonLayout->addWidget(saveAsButton);
    buttonLayout->addWidget(loadAsButton);
    buttonLayout->addWidget(selectButton);
    buttonLayout->addWidget(cloneButton);
    buttonLayout->addWidget(deleteButton);
    buttonLayout->addWidget(undoButton);
    buttonLayout->addWidget(edgeColorButton);
    buttonLayout->addWidget(fillColorButton);
    buttonLayout->addWidget(backGroundButton);
    buttonLayout->addWidget(changeColorButton);


    // układ pionowy dla przycisków i obszaru rysowania
    QVBoxLayout *mainLayout = new QVBoxLayout;
    mainLayout->addLayout(buttonLayout); // dodanie przycisków
    mainLayout->addWidget(paintWidget);  // dodanie widżetu rysującego

    mainWindow.setLayout(mainLayout);  // ustawienie ukladu layout na oknie aplikacji


    mainWindow.show(); // wyswietlenie okna na ekranie uzytkownika

    return app.exec(); // kluczowy moment, poniewaz app.exec() uruchamia petle zdarzen aplikacji Qt, dzieki temu aplikacja moze reagowac na interakcje uzytkownika, np klikniecie myszka czy zamkniecie okna
}
