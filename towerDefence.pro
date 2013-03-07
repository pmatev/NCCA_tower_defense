#-------------------------------------------------
#
# Project created by QtCreator 2012-11-21T15:04:39
#
#-------------------------------------------------

QT       += core \
            opengl \
            gui \
            opengl \
            xml



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
    src/game.cpp \
    src/camera.cpp \
    src/window.cpp \
    src/environment.cpp \
    src/nodemanager.cpp \
    src/uibutton.cpp \ 
    src/ui.cpp \
    src/enemy.cpp \
    src/projectile.cpp \
    src/projectilemanager.cpp \
    src/wall.cpp \
    src/databasegrid.cpp \
    src/concrete/bullet.cpp \
    src/concrete/base.cpp \
    src/concrete/testenemy.cpp \
    src/concrete/testturret.cpp \
    src/text.cpp \
    src/createtowerbutton.cpp \
    src/fsm/statemachine.cpp \
    src/fsm/states/enemystates.cpp \
    src/ai/steeringbehaviours.cpp \
    src/player.cpp \
    src/uLayout/column.cpp \
    src/uLayout/row.cpp \
    src/uLayout/table.cpp \
    src/fsm/states/turretstates.cpp \
    src/fsm/states/projectilestates.cpp \
    src/texturelib.cpp \
    src/texture.cpp \
    src/billboard.cpp \
    src/concrete/invisiblewall.cpp \
    src/concrete/standardwall.cpp \
    src/explosion.cpp \
    src/meshlib.cpp \
    src/mesh.cpp \
    src/concrete/grenade.cpp \
    src/concrete/missilesilo.cpp \
    src/fsm/states/missilesilostate.cpp




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
    include/uibutton.h \  
    include/uiwindow.h \
    include/uielement.h \
    include/ui.h \
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
    include/fwd/uibutton.h \
    include/fwd/ui.h \
    include/text.h \
    include/createtowerbutton.h \
    include/fwd/camera.h \
    include/fsm/statemachine.h \
    include/fsm/state.h \
    include/fsm/states/enemystates.h \
    include/ai/steeringbehaviours.h \
    include/player.h \
    include/uLayout/column.h \
    include/uLayout/row.h \
    include/uLayout/table.h \
    include/fwd/table.h \
    include/fwd/row.h \
    include/fwd/column.h \
    include/fsm/states/turretstates.h \
    include/fsm/states/projectilestates.h \
    include/texturelib.h \
    include/texture.h \
    include/billboard.h \
    include/concrete/invisiblewall.h \
    include/concrete/standardwall.h \
    include/explosion.h \
    include/fwd/projectileManager.h \
    include/meshlib.h \
    include/mesh.h \
    include/concrete/grenade.h \
    include/concrete/missilesilo.h \
    include/fsm/states/missilesilostate.h





QMAKE_CXXFLAGS+=$$system($$(HOME)/SDL1/bin/sdl-config  --cflags)

message(output from sdl-config --cflags added to CXXFLAGS= $$QMAKE_CXXFLAGS)

LIBS+=$$system($$(HOME)/SDL1/bin/sdl-config --libs) -lSDL_ttf
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
    config/config.xml \
    shaders/UI.vs \
    shaders/UI.fs \
    shaders/Texture.vs \
    shaders/Texture.fs \
    shaders/Constant.vs \
    shaders/Constant.fs \
    shaders/TexturedConst.vs \
    shaders/TexturedConst.fs \
    textures/grid.png \
    textures/default_texture.jpg \
    fonts/Abyssinica_SIL.ttf \
    fonts/Roboto-Regular.ttf \
    config/config.xml \
    models/turret.obj \
    shaders/Texture.vs \
    shaders/Texture.fs \
    textures/HealthBar.png \
    textures/default_texture.png \
    textures/HealthBar_flat.png \
    models/turret_base.obj \
    model/turret_cannon.obj \
    models/enemy.obj \
    models/hexagon.obj \
    models/wall.obj \

