QT += core
QT -= gui

TARGET = waterbucket
CONFIG += console
CONFIG -= app_bundle

TEMPLATE = app

SOURCES += main.cpp \
    bucket_state.cpp

HEADERS += \
    bucket_state.h

