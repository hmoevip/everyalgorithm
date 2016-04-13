QT += core
QT -= gui

TARGET = GaleShapley
CONFIG += console
CONFIG -= app_bundle

TEMPLATE = app

SOURCES += main.cpp \
    mygs1.cpp \
    hungarymatch.cpp \
    kuhnmunkres.cpp

HEADERS += \
    mygs1.h \
    hungarymatch.h \
    kuhnmunkres.h

QMAKE_CXXFLAGS += -std=c++11
