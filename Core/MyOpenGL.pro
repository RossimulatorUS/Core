#-------------------------------------------------
#
# Project created by QtCreator 2014-01-30T09:41:25
#
#-------------------------------------------------

QMAKE_CXXFLAGS += -std=c++0x -gdwarf-3

QT       += core gui opengl

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = MyOpenGL
TEMPLATE = app

INCLUDEPATH += "C:\Program Files\boost\boost_1_55_0\boost_1_55_0"

SOURCES += main.cpp\
        window.cpp \
    myglwidget.cpp \
    glutility.cpp \
    cortex.cpp \
    module.cpp \
    dvutility.cpp \
    simulationdata.cpp \
    analyser.cpp \
    distributor.cpp \
    StopSign.cpp \
    formula.cpp \
    execution_history.cpp \
    node.cpp \
    poissoner.cpp \
    road.cpp \
    signaler.cpp \
    vehicle.cpp \
    vehiclethread.cpp \
    lane.cpp

HEADERS  += window.h \
    myglwidget.h \
    glutility.h \
    cortex.h \
    module.h \
    dvutility.h \
    simulationdata.h \
    simulationtraits.h \
    intersection.h \
    StopSign.h \
    analyser.h \
    distributor.h \
    autolock.h \
    node.h \
    road.h \
    execution_history.h \
    formula.h \
    poissoner.h \
    signaler.h \
    vehicle.h \
    vehiclethread.h \
    lane.h

FORMS    += window.ui
