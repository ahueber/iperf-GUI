#-------------------------------------------------
#
# Project created by QtCreator 2016-11-07T02:42:52
#
#-------------------------------------------------

QT       += core gui
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

Release:DESTDIR = release
Release:OBJECTS_DIR = release/.obj
Release:MOC_DIR = release/.moc
Release:RCC_DIR = release/.rcc
Release:UI_DIR = release/.ui

Debug:DESTDIR = ~/Desktop/
Debug:OBJECTS_DIR = debug/.obj
Debug:MOC_DIR = debug/.moc
Debug:RCC_DIR = debug/.rcc
Debug:UI_DIR = debug/.ui
