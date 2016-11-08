#-------------------------------------------------
#
# Project created by QtCreator 2016-11-07T02:42:52
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = iperf
TEMPLATE = app


SOURCES += main.cpp \
    welcomescreen.cpp \
    client.cpp \
    server.cpp

HEADERS  += \
    welcomescreen.h \
    client.h \
    server.h
