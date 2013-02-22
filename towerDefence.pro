#-------------------------------------------------
#
# Project created by QtCreator 2012-11-21T15:04:39
#
#-------------------------------------------------

QT       += core \
            opengl


TARGET = towerDefence
CONFIG   += console
CONFIG   -= app_bundle
#QMAKE_CXX=clang++  -fdiagnostics-fixit-info
TEMPLATE = app

#setting up project directories

OBJECTS_DIR=./obj
INCLUDEPATH +=./include
MOC_DIR=./moc/
#project files

SOURCES += src/main.cpp \
    src/renderer.cpp \
    src/entity.cpp \
    src/staticentity.cpp \
    src/node.cpp \
    src/dynamicentity.cpp \
    src/turret.cpp \
    src/wave.cpp \
    src/wavemanager.cpp \
    src/entityfactory.cpp \
    src/database.cpp \
    src/uiwindow.cpp \
    src/uielement.cpp \
    src/uimenu.cpp \
    src/game.cpp \
    src/camera.cpp \
    src/window.cpp \
    src/concrete/bullet.cpp \
    src/environment.cpp \
    src/nodemanager.cpp \
    src/uiSelection.cpp \
    src/uibutton.cpp \ 
    src/enemy.cpp \
    src/projectile.cpp \
    src/wall.cpp \
    src/concrete/base.cpp \
    src/databasegrid.cpp \
    src/concrete/testenemy.cpp \
    src/concrete/testturret.cpp \
    src/projectilemanager.cpp


HEADERS += \
    include/window.h \
    include/renderer.h \
    include/smartpointers.h \
    include/game.h \
    include/entity.h \
    include/node.h \
    include/turret.h \
    include/staticentity.h \
    include/dynamicentity.h \
    include/database.h \
    include/wave.h \
    include/wavemanager.h \
    include/entityfactory.h \
    include/enemy.h \
    include/camera.h \
    include/environment.h \
    include/nodemanager.h \
    include/uiSelection.h \
    include/uibutton.h \  
    include/uiwindow.h \
    include/uielement.h \
    include/uimenu.h \
    include/projectile.h \
    include/projectilemanager.h \
    include/wall.h \
    include/databasegrid.h \
    include/concrete/bullet.h \
    include/concrete/base.h \
    include/concrete/testenemy.h \
    include/concrete/testturret.h \
    include/fwd/database.h \
    include/fwd/entity.h \
    include/fwd/game.h \
    include/fwd/uimenu.h \
    include/fwd/uibutton.h \
    include/fwd/uiselection.h \
    include/fwd/window.h


#including the NGL library

QMAKE_CXXFLAGS+=$$system($$(HOME)/SDL1/bin/sdl-config  --cflags)
message(output from sdl-config --cflags added to CXXFLAGS= $$QMAKE_CXXFLAGS)

LIBS+=$$system($$(HOME)/SDL1/bin/sdl-config  --libs)
message(output from sdl-config --libs added to LIB=$$LIBS)

#include for threading
QMAKE_CXXFLAGS += -fopenmp
QMAKE_CXXFLAGS += -lgomp


#including the NGL library
INCLUDEPATH += $$(HOME)/NGL/include/
DEPENDPATH += $$(HOME)/NGL/include/

DEFINES +=NGL_DEBUG

LIBS += -L/usr/local/lib
LIBS +=  -L/$(HOME)/NGL/lib -lNGL

linux-g++* {
    DEFINES += LINUX
    LIBS+= -lGLEW
}
linux-clang* {
    DEFINES += LINUX
    LIBS+= -lGLEW
}


#include for threading
LIBS += -fopenmp
LIBS += -lgomp


OTHER_FILES += \
    shaders/Phong.vs \
    shaders/Phong.fs \
    shaders/Colour.vs \
    shaders/Colour.fs \
    shaders/UI.vs \
    shaders/UI.fs \
    textures/grid.png \
    textures/default_texture.jpg
