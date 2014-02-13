#-------------------------------------------------
#
# Project created by QtCreator 2014-01-30T09:41:25
#
#-------------------------------------------------

QMAKE_CXXFLAGS += -std=c++0x

QT       += core gui opengl

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = MyOpenGL
TEMPLATE = app


SOURCES += main.cpp\
        window.cpp \
    myglwidget.cpp \
    voie.cpp \
    formule.cpp \
    vehicule.cpp \
    vehiculethread.cpp \
    glutility.cpp \
    noeud.cpp \
    route.cpp

HEADERS  += window.h \
    myglwidget.h \
    voie.h \
    formule.h \
    vehicule.h \
    vehiculethread.h \
    glutility.h \
    noeud.h \
    route.h

FORMS    += window.ui
