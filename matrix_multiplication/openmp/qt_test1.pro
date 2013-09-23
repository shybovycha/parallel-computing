#-------------------------------------------------
#
# Project created by QtCreator 2013-09-23T23:45:55
#
#-------------------------------------------------

QT       += core

QT       -= gui

TARGET = qt_test1
CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app

QMAKE_LFLAGS += -fopenmp
QMAKE_CXXFLAGS += -fopenmp

SOURCES += main.cpp
