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

#setting up project directories

OBJECTS_DIR=./obj
INCLUDEPATH +=./include

#project files

SOURCES += src/main.cpp \
    src/entity.cpp
HEADERS += \
    include/entity.h

#including the Imath Library

LIBS += -L/usr/lib64 -lImath
INCLUDEPATH += /usr/local/include/OpenEXR
DEPENDPATH += /usr/lib64
