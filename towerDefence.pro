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
    src/entity.cpp \
    src/staticentity.cpp \
    src/node.cpp \
    src/dynamicentity.cpp \
    src/turret.cpp \
    src/wave.cpp \
    src/wavemanager.cpp \
    src/entityfactory.cpp \
    src/enemy.cpp

HEADERS += \
    include/entity.h \
    include/staticentity.h \
    include/node.h \
    include/dynamicentity.h \
    include/turret.h \
    include/wave.h \
    include/wavemanager.h \
    include/entityfactory.h \
    include/enemy.h

#including the Imath Library

#LIBS += -L/usr/lib64 -lImath
#INCLUDEPATH += /usr/local/include/OpenEXR
#DEPENDPATH += /usr/lib64

#including the NGL library

LIBS +=  -L/$(HOME)/NGL/lib -l NGL
INCLUDEPATH += $$(HOME)/NGL/include/
DEPENDPATH += $$(HOME)/NGL/include/
