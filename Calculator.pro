#-------------------------------------------------
#
# Project created by QtCreator 2017-02-19T21:53:25
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Calculator
TEMPLATE = app


SOURCES += main.cpp\
        widget.cpp \
    mainwindow.cpp
#    advancedlineedit.cpp

HEADERS  += widget.h \
    mainwindow.h
#    advancedlineedit.h

FORMS    += widget.ui \
    mainwindow.ui
