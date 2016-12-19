#-------------------------------------------------
#
# Project created by QtCreator 2016-11-07T02:42:52
#
#-------------------------------------------------

QT       += core gui network
CONFIG   += c++11

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = iperf
TEMPLATE = app


SOURCES += main.cpp \
    welcomescreen.cpp \
    client.cpp \
    server.cpp \
    trafficlight.cpp \
    numpad.cpp \
    iperfinterface.cpp

HEADERS  += \
    welcomescreen.h \
    client.h \
    server.h \
    trafficlight.h \
    numpad.h \
    iperfinterface.h

RESOURCES += \
    ../images.qrc
