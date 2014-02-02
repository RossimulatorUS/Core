#-------------------------------------------------
#
# Project created by QtCreator 2014-02-01T18:33:55
#
#-------------------------------------------------

QMAKE_CXXFLAGS += -std=c++0x

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Core
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    noeud.cpp \
    route.cpp \
    intersection.cpp \
    puit.cpp \
    source.cpp

HEADERS  += mainwindow.h \
    noeud.h \
    route.h \
    intersection.h \
    puit.h \
    source.h

FORMS    += mainwindow.ui
