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

INCLUDEPATH += $$_PRO_FILE_PWD_/lib/curl-7.38.0/curl-7.38.0/include
LIBS += -L$$_PRO_FILE_PWD_\lib\curl-7.38.0-ssl-sspi-zlib-static-bin-w32\curl-7.38.0-ssl-sspi-zlib-static-bin-w32 -lcurl

SOURCES += main.cpp \
        window.cpp \
    myglwidget.cpp \
    glutility.cpp \
    cortex.cpp \
    module.cpp \
    dvutility.cpp \
    simulationdata.cpp \
    analyser.cpp \
    distributor.cpp \
    formula.cpp \
    node.cpp \
    signaler.cpp \
    vehicle.cpp \
    vehiclethread.cpp \
    lane.cpp \
    map_fetcher.cpp \
    lib/pugixml/pugixml.cpp \
    TLight.cpp \
    road_segment.cpp \
    road.cpp \
    utils.cpp \
    StopSign.cpp

HEADERS  += window.h \
    myglwidget.h \
    glutility.h \
    cortex.h \
    module.h \
    dvutility.h \
    simulationdata.h \
    simulationtraits.h \
    analyser.h \
    distributor.h \
    autolock.h \
    node.h \
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
    lib/pugixml/pugixml.hpp \
    road_segment.h \
    TLight.h \
    road.h \
    StopSign.h

FORMS    += window.ui
