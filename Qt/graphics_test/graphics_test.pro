#-------------------------------------------------
#
# Project created by QtCreator 2014-12-06T17:27:18
#
#-------------------------------------------------

QT       += core gui
QT       += xml

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = graphics_test
TEMPLATE = app


SOURCES +=  main.cpp                                \
            mainwindow.cpp                          \
            painter.cpp                             \
            animate.cpp                             \
            ../../src/algorithms/find_path.cpp      \
            ../../src/map/Map.cpp                   \
            ../../src/test/add_functions.cpp        \
            ../../src/dyn_obj/TMainDynObject.cpp    \

HEADERS  += mainwindow.h                            \
            painter.h                               \
            animate.h                               \
            ../../src/algorithms/find_path.h        \
            ../../src/map/Map.h                     \
            ../../src/test/add_functions.h          \
            ../../src/dyn_obj/TMainDynObject.h      \
            ../../src/saves/saves.h

FORMS    += mainwindow.ui
