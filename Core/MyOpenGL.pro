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

INCLUDEPATH += "C:\Program Files\boost\boost_1_55_0"

SOURCES += main.cpp\
        window.cpp \
    myglwidget.cpp \
    voie.cpp \
    formule.cpp \
    vehicule.cpp \
    vehiculethread.cpp \
    glutility.cpp \
    noeud.cpp \
    route.cpp \
    cortex.cpp \
    poissoneur.cpp \
    distributeur.cpp \
    signaleur.cpp \
    module.cpp \
    analyseur.cpp \
    dvutility.cpp \
    historique_dexecution.cpp \
    simulationdata.cpp

HEADERS  += window.h \
    myglwidget.h \
    voie.h \
    formule.h \
    vehicule.h \
    vehiculethread.h \
    glutility.h \
    noeud.h \
    route.h \
    cortex.h \
    distributeur.h \
    poissoneur.h \
    signaleur.h \
    module.h \
    analyseur.h \
    dvutility.h \
    historique_dexecution.h \
    simulationdata.h \
    simulationtraits.h \
    autoverrou.h

FORMS    += window.ui
