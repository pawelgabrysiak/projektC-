cmake_minimum_required(VERSION 3.16)
project(MyQtApp)

set(CMAKE_CXX_STANDARD 17)

# Ustawienie ścieżki do Qt
set(CMAKE_PREFIX_PATH "C:/Qt/6.8.0/mingw_64/lib/cmake")

# Automatyczne uruchamianie MOC dla plików z Q_OBJECT
set(CMAKE_AUTOMOC ON)

# Znajdowanie pakietu Qt
find_package(Qt6 REQUIRED COMPONENTS Widgets)

# Dodawanie plików źródłowych
add_executable(MyQtApp main.cpp paintwidget.cpp line.cpp circle.cpp square.cpp shape.cpp)

# Dodawanie ścieżek do nagłówków
target_include_directories(MyQtApp PRIVATE ${CMAKE_SOURCE_DIR})

# Łączenie bibliotek Qt z projektem
target_link_libraries(MyQtApp Qt6::Widgets)
