#-------------------------------------------------
#
# Project created by QtCreator 2012-11-21T15:04:39
#
#-------------------------------------------------

QT       += core \
            gui  \
            opengl


TARGET = towerDefence
CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app

#setting up project directories

OBJECTS_DIR=./obj
INCLUDEPATH +=./include
MOC_DIR=./moc/
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
    src/enemy.cpp \
    src/database.cpp \
    src/uiwindow.cpp \
    src/uielement.cpp \
    src/uimenu.cpp \
    src/game.cpp \
    src/window.cpp \
    src/environment.cpp \
    src/nodemanager.cpp \
    src/uiSelection.cpp \
    src/uibutton.cpp


HEADERS += \
    include/entity.h \
    include/staticentity.h \
    include/node.h \
    include/dynamicentity.h \
    include/turret.h \
    include/database.h \
    include/wave.h \
    include/wavemanager.h \
    include/entityfactory.h \
    include/enemy.h \
    include/uiwindow.h \
    include/uielement.h \
    include/uimenu.h \
    include/smartpointers.h \
    include/game.h \
    include/fwd/game.h \
    include/smartpointers.h \
    include/window.h \
    include/fwd/window.h \
    include/environment.h \
    include/nodemanager.h \
    include/uiSelection.h \
    include/uibutton.h


#including the Imath Library

#LIBS += -L/usr/lib64 -lImath
#INCLUDEPATH += /usr/local/include/OpenEXR
#DEPENDPATH += /usr/lib64

#including the NGL library

QMAKE_CXXFLAGS+=$$system($$(HOME)/SDL2.0/bin/sdl2-config  --cflags)
message(output from sdl2-config --cflags added to CXXFLAGS= $$QMAKE_CXXFLAGS)

LIBS+=$$system($$(HOME)/SDL2.0/bin/sdl2-config  --libs)
message(output from sdl2-config --libs added to LIB=$$LIBS)


INCLUDEPATH += $$(HOME)/NGL/include/
DEPENDPATH += $$(HOME)/NGL/include/

DEFINES +=NGL_DEBUG

LIBS += -L/usr/local/lib
LIBS +=  -L/$(HOME)/NGL/lib -l NGL
