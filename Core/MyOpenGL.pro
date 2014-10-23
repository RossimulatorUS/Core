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

INCLUDEPATH += C:\Users\dinf0014_admin\Documents\Rossimulatorus\curl-7.38.0\include
LIBS += -LC:\Users\dinf0014_admin\Documents\Rossimulatorus\curl-7.38.0-rtmp-ssh2-ssl-sspi-zlib-idn-static-bin-w32 -lcurl

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
    road.cpp \
    signaler.cpp \
    vehicle.cpp \
    vehiclethread.cpp \
    lane.cpp \
    map_fetcher.cpp \
    lib/pugixml/pugixml.cpp

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
    signaler.h \
    vehicle.h \
    vehiclethread.h \
    lane.h \
    map_fetcher.h \
    utils.h \
    map_node.h \
    map_way.h \
    lib/pugixml/pugiconfig.hpp \
    lib/pugixml/pugixml.hpp

FORMS    += window.ui
