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
    #src/wall.cpp \
    src/databasegrid.cpp \
    src/concrete/bullet.cpp \
    src/concrete/base.cpp \
    src/concrete/testenemy.cpp \
    src/concrete/testturret.cpp \
    src/text.cpp \
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
    src/pointlight.cpp \
    src/mesh.cpp \
    src/concrete/grenade.cpp \
    src/concrete/missilesilo.cpp \
    src/fsm/states/missilesilostate.cpp \
    src/uLayout/uwindow.cpp \
    src/costbutton.cpp




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
    include/uielement.h \
    include/ui.h \
    include/projectile.h \
    include/projectilemanager.h \
    #include/wall.h \
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
    include/pointlight.h \
    include/mesh.h \
    include/concrete/grenade.h \
    include/concrete/missilesilo.h \
    include/fsm/states/missilesilostate.h \
    include/uLayout/uwindow.h \
    include/fwd/uwindow.h \
    include/costbutton.h \
    include/fwd/uielement.h




QMAKE_CXXFLAGS+=$$system(/opt/local/bin/sdl-config  --cflags)

message(output from sdl-config --cflags added to CXXFLAGS= $$QMAKE_CXXFLAGS)

LIBS+=$$system(/opt/local/bin/sdl-config --libs) -lSDL_ttf
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
    \
    shaders/UI.vs \
    shaders/UI.fs \
    shaders/Texture.vs \
    shaders/Texture.fs \
    shaders/Texture3D.vs \
    shaders/Texture3D.fs \
    shaders/Constant.vs \
    shaders/Constant.fs \
    shaders/Phong.vs \
    shaders/Phong.fs \
    \
    textures/grid.png \
    textures/default_texture.jpg \
    textures/HealthBar.png \
    textures/HealthBar_flat.png \
    textures/noMoney.png \
    textures/playButtonNo.png \
    textures/missileButtonNo.png \
    textures/missileButton.png \
    textures/wallButtonNoMoney.png \
    textures/upgrade2GrenadeImage.png \
    textures/upgrade2BulletImage.png \
    textures/startMenuButton_700x150.png \
    textures/settingsMenuButton.png \
    textures/settingsButton.png \
    textures/restartMenuButton.png \
    textures/quitGameMenuButton.png \
    textures/machineGunNoMoney.png \
    textures/machineGun.png \
    textures/backToStartMenuButton.png \
    textures/upgradeButtonNoMoney.png \
    textures/createBackground.png \
    textures/sellGrenadeImage.png \
    textures/sellBulletImage.png \
    textures/closeMenuButton.png \
    textures/startMenuButton_700x150Hover.png \
    textures/settingsMenuButtonHover.png \
    textures/restartMenuButtonHover.png \
    textures/quitGameMenuButtonHover.png \
    textures/closeMenuButtonHover.png \
    textures/backToStartMenuButtonHover.png \
    textures/wallButtonCreation.png \
    textures/machineGunCreation.png \
    textures/grenadeButtonCreation.png \
    textures/settingsButtonHover.png \
    textures/closeMenuButton.png \
    textures/bg_tile.png \
    \
    fonts/Abyssinica_SIL.ttf \
    fonts/Roboto-Regular.ttf \
    \
    models/turret.obj \
    models/turret_base.obj \
    model/turret_cannon.obj \
    models/enemy.obj \
    models/hexagon.obj \
    models/wall.obj \
    textures/wallButtonPressed.png \
    textures/wallButtonHover.png \
    textures/wallButtonCreate.png \
    textures/wallButton.png \
    textures/upgradeButtonPressed.png \
    textures/upgradeButtonHover.png \
    textures/upgradeButton.png \
    textures/towerPanel.png \
    textures/startScreen.png \
    textures/startGamePressed.png \
    textures/startGameHover.png \
    textures/startGame.png \
    textures/settingsPressed.png \
    textures/settingsHover.png \
    textures/settingsButtonPressed.png \
    textures/settingsBackground.png \
    textures/settings.png \
    textures/sellButtonPressed.png \
    textures/sellButtonHover.png \
    textures/sellButton.png \
    textures/restartPressed.png \
    textures/restartHover.png \
    textures/restart.png \
    textures/quitPressed.png \
    textures/quitHover.png \
    textures/quit.png \
    textures/playButtonPressed.png \
    textures/playButtonHover.png \
    textures/playButton.png \
    textures/pauseButtonPressed.png \
    textures/pauseButtonHover.png \
    textures/pauseButton.png \
    textures/grenadeButtonPressed.png \
    textures/grenadeButtonNoMoney.png \
    textures/grenadeButtonHover.png \
    textures/grenadeButtonCreate.png \
    textures/grenadeButton.png \
    textures/gameOverScreen.png \
    textures/closeButton.png \
    textures/bulletButtonPressed.png \
    textures/bulletButtonNoMoney.png \
    textures/bulletButtonHover.png \
    textures/bulletButtonCreate.png \
    textures/bulletButton.png \
    textures/backToStartPressed.png \
    textures/backToStartHover.png \
    textures/backToStart.png \
    textures/backToGamePressed.png \
    textures/backToGameHover.png \
    textures/backToGame.png \
    textures/arrowUpButtonPressed.png \
    textures/arrowUpButton.png \
    textures/arrowDownButtonPressed.png \
    textures/arrowDownButton.png \
    textures/bg_tile.png \
