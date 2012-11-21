#-------------------------------------------------
#
# Project created by QtCreator 2012-11-21T15:04:39
#
#-------------------------------------------------

QT       += core

QT       -= gui

TARGET = towerDefence
CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app

OBJECTS_DIR=./obj
SOURCES += src/main.cpp \
    src/entity.cpp
INCLUDEPATH +=./include
HEADERS += \
    include/entity.h
