#-------------------------------------------------
#
# Project created by QtCreator 2014-12-06T17:27:18
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = graphics_test
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    painter.cpp \
    animate.cpp

HEADERS  += mainwindow.h \
    painter.h \
    animate.h

FORMS    += mainwindow.ui
