#############################################################################
# Makefile for building: towerDefence
# Generated by qmake (2.01a) (Qt 4.8.1) on: Mon Mar 25 15:12:19 2013
# Project:  towerDefence.pro
# Template: app
# Command: /opt/QtSDK/Desktop/Qt/4.8.1/gcc/bin/qmake -spec /opt/QtSDK/Desktop/Qt/4.8.1/gcc/mkspecs/linux-g++ CONFIG+=debug CONFIG+=declarative_debug -o Makefile towerDefence.pro
#############################################################################

####### Compiler, tools and options

CC            = gcc
CXX           = g++
DEFINES       = -DNGL_DEBUG -DLINUX -DQT_XML_LIB -DQT_OPENGL_LIB -DQT_GUI_LIB -DQT_CORE_LIB -DQT_SHARED
CFLAGS        = -pipe -g -Wall -W -D_REENTRANT $(DEFINES)
CXXFLAGS      = -pipe -I/home/i7939074/SDL1//include/SDL -D_GNU_SOURCE=1 -D_REENTRANT -fopenmp -lgomp -g -Wall -W -D_REENTRANT $(DEFINES)
INCPATH       = -I/opt/QtSDK/Desktop/Qt/4.8.1/gcc/mkspecs/linux-g++ -I. -I/opt/QtSDK/Desktop/Qt/4.8.1/gcc/include/QtCore -I/opt/QtSDK/Desktop/Qt/4.8.1/gcc/include/QtGui -I/opt/QtSDK/Desktop/Qt/4.8.1/gcc/include/QtOpenGL -I/opt/QtSDK/Desktop/Qt/4.8.1/gcc/include/QtXml -I/opt/QtSDK/Desktop/Qt/4.8.1/gcc/include -Iinclude -I../NGL/include -I/usr/X11R6/include -Imoc
LINK          = g++
LFLAGS        = -Wl,-rpath,/opt/QtSDK/Desktop/Qt/4.8.1/gcc/lib
LIBS          = $(SUBLIBS)  -L/opt/QtSDK/Desktop/Qt/4.8.1/gcc/lib -L/usr/X11R6/lib -L/home/i7939074/SDL1//lib -Wl,-rpath,/home/i7939074/SDL1//lib -lSDL -lSDL_ttf -L/usr/local/lib -L/$(HOME)/NGL/lib -lNGL -lGLEW -fopenmp -lgomp -lQtXml -L/opt/QtSDK/Desktop/Qt/4.8.1/gcc/lib -lQtOpenGL -L/usr/X11R6/lib64 -lQtGui -lQtCore -lGL -lpthread 
AR            = ar cqs
RANLIB        = 
QMAKE         = /opt/QtSDK/Desktop/Qt/4.8.1/gcc/bin/qmake
TAR           = tar -cf
COMPRESS      = gzip -9f
COPY          = cp -f
SED           = sed
COPY_FILE     = $(COPY)
COPY_DIR      = $(COPY) -r
STRIP         = strip
INSTALL_FILE  = install -m 644 -p
INSTALL_DIR   = $(COPY_DIR)
INSTALL_PROGRAM = install -m 755 -p
DEL_FILE      = rm -f
SYMLINK       = ln -f -s
DEL_DIR       = rmdir
MOVE          = mv -f
CHK_DIR_EXISTS= test -d
MKDIR         = mkdir -p

####### Output directory

OBJECTS_DIR   = obj/

####### Files

SOURCES       = src/main.cpp \
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
		src/wall.cpp \
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
OBJECTS       = obj/main.o \
		obj/renderer.o \
		obj/entity.o \
		obj/staticentity.o \
		obj/node.o \
		obj/dynamicentity.o \
		obj/turret.o \
		obj/wave.o \
		obj/wavemanager.o \
		obj/entityfactory.o \
		obj/database.o \
		obj/uielement.o \
		obj/game.o \
		obj/camera.o \
		obj/window.o \
		obj/environment.o \
		obj/nodemanager.o \
		obj/uibutton.o \
		obj/ui.o \
		obj/enemy.o \
		obj/projectile.o \
		obj/projectilemanager.o \
		obj/wall.o \
		obj/databasegrid.o \
		obj/bullet.o \
		obj/base.o \
		obj/testenemy.o \
		obj/testturret.o \
		obj/text.o \
		obj/statemachine.o \
		obj/enemystates.o \
		obj/steeringbehaviours.o \
		obj/player.o \
		obj/column.o \
		obj/table.o \
		obj/turretstates.o \
		obj/projectilestates.o \
		obj/texturelib.o \
		obj/texture.o \
		obj/billboard.o \
		obj/invisiblewall.o \
		obj/standardwall.o \
		obj/explosion.o \
		obj/meshlib.o \
		obj/pointlight.o \
		obj/mesh.o \
		obj/grenade.o \
		obj/missilesilo.o \
		obj/missilesilostate.o \
		obj/uwindow.o \
		obj/costbutton.o
DIST          = /opt/QtSDK/Desktop/Qt/4.8.1/gcc/mkspecs/common/unix.conf \
		/opt/QtSDK/Desktop/Qt/4.8.1/gcc/mkspecs/common/linux.conf \
		/opt/QtSDK/Desktop/Qt/4.8.1/gcc/mkspecs/common/gcc-base.conf \
		/opt/QtSDK/Desktop/Qt/4.8.1/gcc/mkspecs/common/gcc-base-unix.conf \
		/opt/QtSDK/Desktop/Qt/4.8.1/gcc/mkspecs/common/g++-base.conf \
		/opt/QtSDK/Desktop/Qt/4.8.1/gcc/mkspecs/common/g++-unix.conf \
		/opt/QtSDK/Desktop/Qt/4.8.1/gcc/mkspecs/qconfig.pri \
		/opt/QtSDK/Desktop/Qt/4.8.1/gcc/mkspecs/modules/qt_webkit_version.pri \
		/opt/QtSDK/Desktop/Qt/4.8.1/gcc/mkspecs/features/qt_functions.prf \
		/opt/QtSDK/Desktop/Qt/4.8.1/gcc/mkspecs/features/qt_config.prf \
		/opt/QtSDK/Desktop/Qt/4.8.1/gcc/mkspecs/features/exclusive_builds.prf \
		/opt/QtSDK/Desktop/Qt/4.8.1/gcc/mkspecs/features/default_pre.prf \
		/opt/QtSDK/Desktop/Qt/4.8.1/gcc/mkspecs/features/debug.prf \
		/opt/QtSDK/Desktop/Qt/4.8.1/gcc/mkspecs/features/default_post.prf \
		/opt/QtSDK/Desktop/Qt/4.8.1/gcc/mkspecs/features/declarative_debug.prf \
		/opt/QtSDK/Desktop/Qt/4.8.1/gcc/mkspecs/features/unix/gdb_dwarf_index.prf \
		/opt/QtSDK/Desktop/Qt/4.8.1/gcc/mkspecs/features/warn_on.prf \
		/opt/QtSDK/Desktop/Qt/4.8.1/gcc/mkspecs/features/qt.prf \
		/opt/QtSDK/Desktop/Qt/4.8.1/gcc/mkspecs/features/unix/opengl.prf \
		/opt/QtSDK/Desktop/Qt/4.8.1/gcc/mkspecs/features/unix/thread.prf \
		/opt/QtSDK/Desktop/Qt/4.8.1/gcc/mkspecs/features/moc.prf \
		/opt/QtSDK/Desktop/Qt/4.8.1/gcc/mkspecs/features/resources.prf \
		/opt/QtSDK/Desktop/Qt/4.8.1/gcc/mkspecs/features/uic.prf \
		/opt/QtSDK/Desktop/Qt/4.8.1/gcc/mkspecs/features/yacc.prf \
		/opt/QtSDK/Desktop/Qt/4.8.1/gcc/mkspecs/features/lex.prf \
		/opt/QtSDK/Desktop/Qt/4.8.1/gcc/mkspecs/features/include_source_dir.prf \
		towerDefence.pro
QMAKE_TARGET  = towerDefence
DESTDIR       = 
TARGET        = towerDefence

first: all
####### Implicit rules

.SUFFIXES: .o .c .cpp .cc .cxx .C

.cpp.o:
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o "$@" "$<"

.cc.o:
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o "$@" "$<"

.cxx.o:
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o "$@" "$<"

.C.o:
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o "$@" "$<"

.c.o:
	$(CC) -c $(CFLAGS) $(INCPATH) -o "$@" "$<"

####### Build rules

all: Makefile $(TARGET)

$(TARGET):  $(OBJECTS)  
	$(LINK) $(LFLAGS) -o $(TARGET) $(OBJECTS) $(OBJCOMP) $(LIBS)
	{ test -n "$(DESTDIR)" && DESTDIR="$(DESTDIR)" || DESTDIR=.; } && test $$(gdb --version | sed -e 's,[^0-9]\+\([0-9]\)\.\([0-9]\).*,\1\2,;q') -gt 72 && gdb --nx --batch --quiet -ex 'set confirm off' -ex "save gdb-index $$DESTDIR" -ex quit '$(TARGET)' && test -f $(TARGET).gdb-index && objcopy --add-section '.gdb_index=$(TARGET).gdb-index' --set-section-flags '.gdb_index=readonly' '$(TARGET)' '$(TARGET)' && rm -f $(TARGET).gdb-index || true

Makefile: towerDefence.pro  /opt/QtSDK/Desktop/Qt/4.8.1/gcc/mkspecs/linux-g++/qmake.conf /opt/QtSDK/Desktop/Qt/4.8.1/gcc/mkspecs/common/unix.conf \
		/opt/QtSDK/Desktop/Qt/4.8.1/gcc/mkspecs/common/linux.conf \
		/opt/QtSDK/Desktop/Qt/4.8.1/gcc/mkspecs/common/gcc-base.conf \
		/opt/QtSDK/Desktop/Qt/4.8.1/gcc/mkspecs/common/gcc-base-unix.conf \
		/opt/QtSDK/Desktop/Qt/4.8.1/gcc/mkspecs/common/g++-base.conf \
		/opt/QtSDK/Desktop/Qt/4.8.1/gcc/mkspecs/common/g++-unix.conf \
		/opt/QtSDK/Desktop/Qt/4.8.1/gcc/mkspecs/qconfig.pri \
		/opt/QtSDK/Desktop/Qt/4.8.1/gcc/mkspecs/modules/qt_webkit_version.pri \
		/opt/QtSDK/Desktop/Qt/4.8.1/gcc/mkspecs/features/qt_functions.prf \
		/opt/QtSDK/Desktop/Qt/4.8.1/gcc/mkspecs/features/qt_config.prf \
		/opt/QtSDK/Desktop/Qt/4.8.1/gcc/mkspecs/features/exclusive_builds.prf \
		/opt/QtSDK/Desktop/Qt/4.8.1/gcc/mkspecs/features/default_pre.prf \
		/opt/QtSDK/Desktop/Qt/4.8.1/gcc/mkspecs/features/debug.prf \
		/opt/QtSDK/Desktop/Qt/4.8.1/gcc/mkspecs/features/default_post.prf \
		/opt/QtSDK/Desktop/Qt/4.8.1/gcc/mkspecs/features/declarative_debug.prf \
		/opt/QtSDK/Desktop/Qt/4.8.1/gcc/mkspecs/features/unix/gdb_dwarf_index.prf \
		/opt/QtSDK/Desktop/Qt/4.8.1/gcc/mkspecs/features/warn_on.prf \
		/opt/QtSDK/Desktop/Qt/4.8.1/gcc/mkspecs/features/qt.prf \
		/opt/QtSDK/Desktop/Qt/4.8.1/gcc/mkspecs/features/unix/opengl.prf \
		/opt/QtSDK/Desktop/Qt/4.8.1/gcc/mkspecs/features/unix/thread.prf \
		/opt/QtSDK/Desktop/Qt/4.8.1/gcc/mkspecs/features/moc.prf \
		/opt/QtSDK/Desktop/Qt/4.8.1/gcc/mkspecs/features/resources.prf \
		/opt/QtSDK/Desktop/Qt/4.8.1/gcc/mkspecs/features/uic.prf \
		/opt/QtSDK/Desktop/Qt/4.8.1/gcc/mkspecs/features/yacc.prf \
		/opt/QtSDK/Desktop/Qt/4.8.1/gcc/mkspecs/features/lex.prf \
		/opt/QtSDK/Desktop/Qt/4.8.1/gcc/mkspecs/features/include_source_dir.prf \
		/opt/QtSDK/Desktop/Qt/4.8.1/gcc/lib/libQtXml.prl \
		/opt/QtSDK/Desktop/Qt/4.8.1/gcc/lib/libQtCore.prl \
		/opt/QtSDK/Desktop/Qt/4.8.1/gcc/lib/libQtOpenGL.prl \
		/opt/QtSDK/Desktop/Qt/4.8.1/gcc/lib/libQtGui.prl
	$(QMAKE) -spec /opt/QtSDK/Desktop/Qt/4.8.1/gcc/mkspecs/linux-g++ CONFIG+=debug CONFIG+=declarative_debug -o Makefile towerDefence.pro
/opt/QtSDK/Desktop/Qt/4.8.1/gcc/mkspecs/common/unix.conf:
/opt/QtSDK/Desktop/Qt/4.8.1/gcc/mkspecs/common/linux.conf:
/opt/QtSDK/Desktop/Qt/4.8.1/gcc/mkspecs/common/gcc-base.conf:
/opt/QtSDK/Desktop/Qt/4.8.1/gcc/mkspecs/common/gcc-base-unix.conf:
/opt/QtSDK/Desktop/Qt/4.8.1/gcc/mkspecs/common/g++-base.conf:
/opt/QtSDK/Desktop/Qt/4.8.1/gcc/mkspecs/common/g++-unix.conf:
/opt/QtSDK/Desktop/Qt/4.8.1/gcc/mkspecs/qconfig.pri:
/opt/QtSDK/Desktop/Qt/4.8.1/gcc/mkspecs/modules/qt_webkit_version.pri:
/opt/QtSDK/Desktop/Qt/4.8.1/gcc/mkspecs/features/qt_functions.prf:
/opt/QtSDK/Desktop/Qt/4.8.1/gcc/mkspecs/features/qt_config.prf:
/opt/QtSDK/Desktop/Qt/4.8.1/gcc/mkspecs/features/exclusive_builds.prf:
/opt/QtSDK/Desktop/Qt/4.8.1/gcc/mkspecs/features/default_pre.prf:
/opt/QtSDK/Desktop/Qt/4.8.1/gcc/mkspecs/features/debug.prf:
/opt/QtSDK/Desktop/Qt/4.8.1/gcc/mkspecs/features/default_post.prf:
/opt/QtSDK/Desktop/Qt/4.8.1/gcc/mkspecs/features/declarative_debug.prf:
/opt/QtSDK/Desktop/Qt/4.8.1/gcc/mkspecs/features/unix/gdb_dwarf_index.prf:
/opt/QtSDK/Desktop/Qt/4.8.1/gcc/mkspecs/features/warn_on.prf:
/opt/QtSDK/Desktop/Qt/4.8.1/gcc/mkspecs/features/qt.prf:
/opt/QtSDK/Desktop/Qt/4.8.1/gcc/mkspecs/features/unix/opengl.prf:
/opt/QtSDK/Desktop/Qt/4.8.1/gcc/mkspecs/features/unix/thread.prf:
/opt/QtSDK/Desktop/Qt/4.8.1/gcc/mkspecs/features/moc.prf:
/opt/QtSDK/Desktop/Qt/4.8.1/gcc/mkspecs/features/resources.prf:
/opt/QtSDK/Desktop/Qt/4.8.1/gcc/mkspecs/features/uic.prf:
/opt/QtSDK/Desktop/Qt/4.8.1/gcc/mkspecs/features/yacc.prf:
/opt/QtSDK/Desktop/Qt/4.8.1/gcc/mkspecs/features/lex.prf:
/opt/QtSDK/Desktop/Qt/4.8.1/gcc/mkspecs/features/include_source_dir.prf:
/opt/QtSDK/Desktop/Qt/4.8.1/gcc/lib/libQtXml.prl:
/opt/QtSDK/Desktop/Qt/4.8.1/gcc/lib/libQtCore.prl:
/opt/QtSDK/Desktop/Qt/4.8.1/gcc/lib/libQtOpenGL.prl:
/opt/QtSDK/Desktop/Qt/4.8.1/gcc/lib/libQtGui.prl:
qmake:  FORCE
	@$(QMAKE) -spec /opt/QtSDK/Desktop/Qt/4.8.1/gcc/mkspecs/linux-g++ CONFIG+=debug CONFIG+=declarative_debug -o Makefile towerDefence.pro

dist: 
	@$(CHK_DIR_EXISTS) obj/towerDefence1.0.0 || $(MKDIR) obj/towerDefence1.0.0 
	$(COPY_FILE) --parents $(SOURCES) $(DIST) obj/towerDefence1.0.0/ && $(COPY_FILE) --parents include/window.h include/renderer.h include/smartpointers.h include/game.h include/entity.h include/node.h include/turret.h include/staticentity.h include/dynamicentity.h include/database.h include/wave.h include/wavemanager.h include/entityfactory.h include/enemy.h include/camera.h include/environment.h include/nodemanager.h include/uibutton.h include/uielement.h include/ui.h include/projectile.h include/projectilemanager.h include/wall.h include/databasegrid.h include/concrete/bullet.h include/concrete/base.h include/concrete/testenemy.h include/concrete/testturret.h include/fwd/database.h include/fwd/entity.h include/fwd/game.h include/fwd/uibutton.h include/fwd/ui.h include/text.h include/fwd/camera.h include/fsm/statemachine.h include/fsm/state.h include/fsm/states/enemystates.h include/ai/steeringbehaviours.h include/player.h include/uLayout/column.h include/uLayout/row.h include/uLayout/table.h include/fwd/table.h include/fwd/row.h include/fwd/column.h include/fsm/states/turretstates.h include/fsm/states/projectilestates.h include/texturelib.h include/texture.h include/billboard.h include/concrete/invisiblewall.h include/concrete/standardwall.h include/explosion.h include/fwd/projectileManager.h include/meshlib.h include/pointlight.h include/mesh.h include/concrete/grenade.h include/concrete/missilesilo.h include/fsm/states/missilesilostate.h include/uLayout/uwindow.h include/fwd/uwindow.h include/costbutton.h include/fwd/uielement.h obj/towerDefence1.0.0/ && $(COPY_FILE) --parents src/main.cpp src/renderer.cpp src/entity.cpp src/staticentity.cpp src/node.cpp src/dynamicentity.cpp src/turret.cpp src/wave.cpp src/wavemanager.cpp src/entityfactory.cpp src/database.cpp src/uielement.cpp src/game.cpp src/camera.cpp src/window.cpp src/environment.cpp src/nodemanager.cpp src/uibutton.cpp src/ui.cpp src/enemy.cpp src/projectile.cpp src/projectilemanager.cpp src/wall.cpp src/databasegrid.cpp src/concrete/bullet.cpp src/concrete/base.cpp src/concrete/testenemy.cpp src/concrete/testturret.cpp src/text.cpp src/fsm/statemachine.cpp src/fsm/states/enemystates.cpp src/ai/steeringbehaviours.cpp src/player.cpp src/uLayout/column.cpp src/uLayout/table.cpp src/fsm/states/turretstates.cpp src/fsm/states/projectilestates.cpp src/texturelib.cpp src/texture.cpp src/billboard.cpp src/concrete/invisiblewall.cpp src/concrete/standardwall.cpp src/explosion.cpp src/meshlib.cpp src/pointlight.cpp src/mesh.cpp src/concrete/grenade.cpp src/concrete/missilesilo.cpp src/fsm/states/missilesilostate.cpp src/uLayout/uwindow.cpp src/costbutton.cpp obj/towerDefence1.0.0/ && (cd `dirname obj/towerDefence1.0.0` && $(TAR) towerDefence1.0.0.tar towerDefence1.0.0 && $(COMPRESS) towerDefence1.0.0.tar) && $(MOVE) `dirname obj/towerDefence1.0.0`/towerDefence1.0.0.tar.gz . && $(DEL_FILE) -r obj/towerDefence1.0.0


clean:compiler_clean 
	-$(DEL_FILE) $(OBJECTS)
	-$(DEL_FILE) *~ core *.core


####### Sub-libraries

distclean: clean
	-$(DEL_FILE) $(TARGET) 
	-$(DEL_FILE) Makefile


check: first

mocclean: compiler_moc_header_clean compiler_moc_source_clean

mocables: compiler_moc_header_make_all compiler_moc_source_make_all

compiler_moc_header_make_all:
compiler_moc_header_clean:
compiler_rcc_make_all:
compiler_rcc_clean:
compiler_image_collection_make_all: qmake_image_collection.cpp
compiler_image_collection_clean:
	-$(DEL_FILE) qmake_image_collection.cpp
compiler_moc_source_make_all:
compiler_moc_source_clean:
compiler_uic_make_all:
compiler_uic_clean:
compiler_yacc_decl_make_all:
compiler_yacc_decl_clean:
compiler_yacc_impl_make_all:
compiler_yacc_impl_clean:
compiler_lex_make_all:
compiler_lex_clean:
compiler_clean: 

####### Compile

obj/main.o: src/main.cpp 
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o obj/main.o src/main.cpp

obj/renderer.o: src/renderer.cpp ../NGL/include/ngl/ShaderLib.h \
		../NGL/include/ngl/Types.h \
		../NGL/include/ngl/Singleton.h \
		../NGL/include/ngl/Colour.h \
		../NGL/include/ngl/Mat4.h \
		../NGL/include/ngl/Mat3.h \
		../NGL/include/ngl/Vec4.h \
		../NGL/include/ngl/Vec2.h \
		../NGL/include/ngl/Vec3.h \
		../NGL/include/ngl/Shader.h \
		../NGL/include/ngl/ShaderProgram.h \
		../NGL/include/ngl/Util.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o obj/renderer.o src/renderer.cpp

obj/entity.o: src/entity.cpp ../NGL/include/ngl/Vec3.h \
		../NGL/include/ngl/Types.h \
		../NGL/include/ngl/TransformStack.h \
		../NGL/include/ngl/Transformation.h \
		../NGL/include/ngl/Vec4.h \
		../NGL/include/ngl/Vec2.h \
		../NGL/include/ngl/Mat4.h \
		../NGL/include/ngl/NGLassert.h \
		../NGL/include/ngl/ShaderLib.h \
		../NGL/include/ngl/Singleton.h \
		../NGL/include/ngl/Colour.h \
		../NGL/include/ngl/Mat3.h \
		../NGL/include/ngl/Shader.h \
		../NGL/include/ngl/ShaderProgram.h \
		../NGL/include/ngl/Util.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o obj/entity.o src/entity.cpp

obj/staticentity.o: src/staticentity.cpp 
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o obj/staticentity.o src/staticentity.cpp

obj/node.o: src/node.cpp ../NGL/include/ngl/ShaderLib.h \
		../NGL/include/ngl/Types.h \
		../NGL/include/ngl/Singleton.h \
		../NGL/include/ngl/Colour.h \
		../NGL/include/ngl/Mat4.h \
		../NGL/include/ngl/Mat3.h \
		../NGL/include/ngl/Vec4.h \
		../NGL/include/ngl/Vec2.h \
		../NGL/include/ngl/Vec3.h \
		../NGL/include/ngl/Shader.h \
		../NGL/include/ngl/ShaderProgram.h \
		../NGL/include/ngl/Util.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o obj/node.o src/node.cpp

obj/dynamicentity.o: src/dynamicentity.cpp 
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o obj/dynamicentity.o src/dynamicentity.cpp

obj/turret.o: src/turret.cpp ../NGL/include/ngl/Quaternion.h \
		../NGL/include/ngl/Types.h \
		../NGL/include/ngl/Vec4.h \
		../NGL/include/ngl/Vec2.h \
		../NGL/include/ngl/Vec3.h \
		../NGL/include/ngl/Mat4.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o obj/turret.o src/turret.cpp

obj/wave.o: src/wave.cpp 
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o obj/wave.o src/wave.cpp

obj/wavemanager.o: src/wavemanager.cpp 
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o obj/wavemanager.o src/wavemanager.cpp

obj/entityfactory.o: src/entityfactory.cpp 
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o obj/entityfactory.o src/entityfactory.cpp

obj/database.o: src/database.cpp 
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o obj/database.o src/database.cpp

obj/uielement.o: src/uielement.cpp ../NGL/include/ngl/ShaderLib.h \
		../NGL/include/ngl/Types.h \
		../NGL/include/ngl/Singleton.h \
		../NGL/include/ngl/Colour.h \
		../NGL/include/ngl/Mat4.h \
		../NGL/include/ngl/Mat3.h \
		../NGL/include/ngl/Vec4.h \
		../NGL/include/ngl/Vec2.h \
		../NGL/include/ngl/Vec3.h \
		../NGL/include/ngl/Shader.h \
		../NGL/include/ngl/ShaderProgram.h \
		../NGL/include/ngl/Util.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o obj/uielement.o src/uielement.cpp

obj/game.o: src/game.cpp ../NGL/include/ngl/NGLInit.h \
		../NGL/include/ngl/Types.h \
		../NGL/include/ngl/Singleton.h \
		../NGL/include/ngl/VAOPrimitives.h \
		../NGL/include/ngl/VertexArrayObject.h \
		../NGL/include/ngl/Vec3.h \
		../NGL/include/ngl/Camera.h \
		../NGL/include/ngl/Vec4.h \
		../NGL/include/ngl/Vec2.h \
		../NGL/include/ngl/Mat4.h \
		../NGL/include/ngl/RibExport.h \
		../NGL/include/ngl/Plane.h \
		../NGL/include/ngl/ShaderLib.h \
		../NGL/include/ngl/Colour.h \
		../NGL/include/ngl/Mat3.h \
		../NGL/include/ngl/Shader.h \
		../NGL/include/ngl/ShaderProgram.h \
		../NGL/include/ngl/Util.h \
		include/game.h \
		include/fwd/game.h \
		include/fwd/window.h \
		include/entity.h \
		include/smartpointers.h \
		include/fwd/database.h \
		include/fwd/entity.h \
		include/renderer.h \
		../NGL/include/ngl/Light.h \
		../NGL/include/ngl/TransformStack.h \
		../NGL/include/ngl/Transformation.h \
		../NGL/include/ngl/NGLassert.h \
		include/camera.h \
		include/fwd/camera.h \
		../NGL/include/ngl/Obj.h \
		../NGL/include/ngl/Texture.h \
		../NGL/include/ngl/AbstractMesh.h \
		../NGL/include/ngl/BBox.h \
		include/pointlight.h \
		include/fsm/statemachine.h \
		include/fsm/state.h \
		include/uielement.h \
		include/texture.h \
		include/billboard.h \
		include/fwd/uielement.h \
		include/node.h \
		include/meshlib.h \
		include/mesh.h \
		include/wavemanager.h \
		include/wave.h \
		include/enemy.h \
		include/dynamicentity.h \
		include/ai/steeringbehaviours.h \
		include/entityfactory.h \
		include/staticentity.h \
		include/environment.h \
		include/nodemanager.h \
		include/concrete/base.h \
		include/projectilemanager.h \
		include/fwd/projectileManager.h \
		include/projectile.h \
		include/explosion.h \
		include/player.h \
		include/turret.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o obj/game.o src/game.cpp

obj/camera.o: src/camera.cpp ../NGL/include/ngl/Camera.h \
		../NGL/include/ngl/Types.h \
		../NGL/include/ngl/Vec4.h \
		../NGL/include/ngl/Vec2.h \
		../NGL/include/ngl/Vec3.h \
		../NGL/include/ngl/Mat4.h \
		../NGL/include/ngl/RibExport.h \
		../NGL/include/ngl/Plane.h \
		../NGL/include/ngl/Quaternion.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o obj/camera.o src/camera.cpp

obj/window.o: src/window.cpp ../NGL/include/ngl/NGLInit.h \
		../NGL/include/ngl/Types.h \
		../NGL/include/ngl/Singleton.h \
		../NGL/include/ngl/VAOPrimitives.h \
		../NGL/include/ngl/VertexArrayObject.h \
		../NGL/include/ngl/Vec3.h \
		../NGL/include/ngl/Text.h \
		../NGL/include/ngl/Colour.h \
		../NGL/include/ngl/Vec2.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o obj/window.o src/window.cpp

obj/environment.o: src/environment.cpp 
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o obj/environment.o src/environment.cpp

obj/nodemanager.o: src/nodemanager.cpp 
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o obj/nodemanager.o src/nodemanager.cpp

obj/uibutton.o: src/uibutton.cpp ../NGL/include/ngl/ShaderLib.h \
		../NGL/include/ngl/Types.h \
		../NGL/include/ngl/Singleton.h \
		../NGL/include/ngl/Colour.h \
		../NGL/include/ngl/Mat4.h \
		../NGL/include/ngl/Mat3.h \
		../NGL/include/ngl/Vec4.h \
		../NGL/include/ngl/Vec2.h \
		../NGL/include/ngl/Vec3.h \
		../NGL/include/ngl/Shader.h \
		../NGL/include/ngl/ShaderProgram.h \
		../NGL/include/ngl/Util.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o obj/uibutton.o src/uibutton.cpp

obj/ui.o: src/ui.cpp 
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o obj/ui.o src/ui.cpp

obj/enemy.o: src/enemy.cpp ../NGL/include/ngl/ShaderLib.h \
		../NGL/include/ngl/Types.h \
		../NGL/include/ngl/Singleton.h \
		../NGL/include/ngl/Colour.h \
		../NGL/include/ngl/Mat4.h \
		../NGL/include/ngl/Mat3.h \
		../NGL/include/ngl/Vec4.h \
		../NGL/include/ngl/Vec2.h \
		../NGL/include/ngl/Vec3.h \
		../NGL/include/ngl/Shader.h \
		../NGL/include/ngl/ShaderProgram.h \
		../NGL/include/ngl/Util.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o obj/enemy.o src/enemy.cpp

obj/projectile.o: src/projectile.cpp 
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o obj/projectile.o src/projectile.cpp

obj/projectilemanager.o: src/projectilemanager.cpp 
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o obj/projectilemanager.o src/projectilemanager.cpp

obj/wall.o: src/wall.cpp 
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o obj/wall.o src/wall.cpp

obj/databasegrid.o: src/databasegrid.cpp 
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o obj/databasegrid.o src/databasegrid.cpp

obj/bullet.o: src/concrete/bullet.cpp include/fsm/states/projectilestates.h \
		../NGL/include/ngl/ShaderLib.h \
		../NGL/include/ngl/Types.h \
		../NGL/include/ngl/Singleton.h \
		../NGL/include/ngl/Colour.h \
		../NGL/include/ngl/Mat4.h \
		../NGL/include/ngl/Mat3.h \
		../NGL/include/ngl/Vec4.h \
		../NGL/include/ngl/Vec2.h \
		../NGL/include/ngl/Vec3.h \
		../NGL/include/ngl/Shader.h \
		../NGL/include/ngl/ShaderProgram.h \
		../NGL/include/ngl/Util.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o obj/bullet.o src/concrete/bullet.cpp

obj/base.o: src/concrete/base.cpp ../NGL/include/ngl/ShaderLib.h \
		../NGL/include/ngl/Types.h \
		../NGL/include/ngl/Singleton.h \
		../NGL/include/ngl/Colour.h \
		../NGL/include/ngl/Mat4.h \
		../NGL/include/ngl/Mat3.h \
		../NGL/include/ngl/Vec4.h \
		../NGL/include/ngl/Vec2.h \
		../NGL/include/ngl/Vec3.h \
		../NGL/include/ngl/Shader.h \
		../NGL/include/ngl/ShaderProgram.h \
		../NGL/include/ngl/Util.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o obj/base.o src/concrete/base.cpp

obj/testenemy.o: src/concrete/testenemy.cpp ../NGL/include/ngl/ShaderLib.h \
		../NGL/include/ngl/Types.h \
		../NGL/include/ngl/Singleton.h \
		../NGL/include/ngl/Colour.h \
		../NGL/include/ngl/Mat4.h \
		../NGL/include/ngl/Mat3.h \
		../NGL/include/ngl/Vec4.h \
		../NGL/include/ngl/Vec2.h \
		../NGL/include/ngl/Vec3.h \
		../NGL/include/ngl/Shader.h \
		../NGL/include/ngl/ShaderProgram.h \
		../NGL/include/ngl/Util.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o obj/testenemy.o src/concrete/testenemy.cpp

obj/testturret.o: src/concrete/testturret.cpp include/concrete/testturret.h \
		include/fsm/states/turretstates.h \
		include/concrete/grenade.h \
		../NGL/include/ngl/ShaderLib.h \
		../NGL/include/ngl/Types.h \
		../NGL/include/ngl/Singleton.h \
		../NGL/include/ngl/Colour.h \
		../NGL/include/ngl/Mat4.h \
		../NGL/include/ngl/Mat3.h \
		../NGL/include/ngl/Vec4.h \
		../NGL/include/ngl/Vec2.h \
		../NGL/include/ngl/Vec3.h \
		../NGL/include/ngl/Shader.h \
		../NGL/include/ngl/ShaderProgram.h \
		../NGL/include/ngl/Util.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o obj/testturret.o src/concrete/testturret.cpp

obj/text.o: src/text.cpp ../NGL/include/ngl/Types.h \
		../NGL/include/ngl/ShaderLib.h \
		../NGL/include/ngl/Singleton.h \
		../NGL/include/ngl/Colour.h \
		../NGL/include/ngl/Mat4.h \
		../NGL/include/ngl/Mat3.h \
		../NGL/include/ngl/Vec4.h \
		../NGL/include/ngl/Vec2.h \
		../NGL/include/ngl/Vec3.h \
		../NGL/include/ngl/Shader.h \
		../NGL/include/ngl/ShaderProgram.h \
		../NGL/include/ngl/Util.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o obj/text.o src/text.cpp

obj/statemachine.o: src/fsm/statemachine.cpp 
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o obj/statemachine.o src/fsm/statemachine.cpp

obj/enemystates.o: src/fsm/states/enemystates.cpp 
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o obj/enemystates.o src/fsm/states/enemystates.cpp

obj/steeringbehaviours.o: src/ai/steeringbehaviours.cpp include/ai/steeringbehaviours.h \
		../NGL/include/ngl/Vec3.h \
		../NGL/include/ngl/Types.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o obj/steeringbehaviours.o src/ai/steeringbehaviours.cpp

obj/player.o: src/player.cpp 
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o obj/player.o src/player.cpp

obj/column.o: src/uLayout/column.cpp 
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o obj/column.o src/uLayout/column.cpp

obj/table.o: src/uLayout/table.cpp src/uLayout/row.cpp
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o obj/table.o src/uLayout/table.cpp

obj/turretstates.o: src/fsm/states/turretstates.cpp include/fsm/states/turretstates.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o obj/turretstates.o src/fsm/states/turretstates.cpp

obj/projectilestates.o: src/fsm/states/projectilestates.cpp include/fsm/states/projectilestates.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o obj/projectilestates.o src/fsm/states/projectilestates.cpp

obj/texturelib.o: src/texturelib.cpp include/texturelib.h \
		include/texture.h \
		../NGL/include/ngl/Types.h \
		include/smartpointers.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o obj/texturelib.o src/texturelib.cpp

obj/texture.o: src/texture.cpp include/texture.h \
		../NGL/include/ngl/Types.h \
		include/smartpointers.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o obj/texture.o src/texture.cpp

obj/billboard.o: src/billboard.cpp include/billboard.h \
		../NGL/include/ngl/Vec4.h \
		../NGL/include/ngl/Types.h \
		../NGL/include/ngl/Vec2.h \
		../NGL/include/ngl/Vec3.h \
		../NGL/include/ngl/Mat4.h \
		include/smartpointers.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o obj/billboard.o src/billboard.cpp

obj/invisiblewall.o: src/concrete/invisiblewall.cpp include/concrete/invisiblewall.h \
		../NGL/include/ngl/ShaderLib.h \
		../NGL/include/ngl/Types.h \
		../NGL/include/ngl/Singleton.h \
		../NGL/include/ngl/Colour.h \
		../NGL/include/ngl/Mat4.h \
		../NGL/include/ngl/Mat3.h \
		../NGL/include/ngl/Vec4.h \
		../NGL/include/ngl/Vec2.h \
		../NGL/include/ngl/Vec3.h \
		../NGL/include/ngl/Shader.h \
		../NGL/include/ngl/ShaderProgram.h \
		../NGL/include/ngl/Util.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o obj/invisiblewall.o src/concrete/invisiblewall.cpp

obj/standardwall.o: src/concrete/standardwall.cpp ../NGL/include/ngl/ShaderLib.h \
		../NGL/include/ngl/Types.h \
		../NGL/include/ngl/Singleton.h \
		../NGL/include/ngl/Colour.h \
		../NGL/include/ngl/Mat4.h \
		../NGL/include/ngl/Mat3.h \
		../NGL/include/ngl/Vec4.h \
		../NGL/include/ngl/Vec2.h \
		../NGL/include/ngl/Vec3.h \
		../NGL/include/ngl/Shader.h \
		../NGL/include/ngl/ShaderProgram.h \
		../NGL/include/ngl/Util.h \
		include/concrete/standardwall.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o obj/standardwall.o src/concrete/standardwall.cpp

obj/explosion.o: src/explosion.cpp include/explosion.h \
		../NGL/include/ngl/Vec3.h \
		../NGL/include/ngl/Types.h \
		include/smartpointers.h \
		include/fwd/entity.h \
		../NGL/include/ngl/ShaderLib.h \
		../NGL/include/ngl/Singleton.h \
		../NGL/include/ngl/Colour.h \
		../NGL/include/ngl/Mat4.h \
		../NGL/include/ngl/Mat3.h \
		../NGL/include/ngl/Vec4.h \
		../NGL/include/ngl/Vec2.h \
		../NGL/include/ngl/Shader.h \
		../NGL/include/ngl/ShaderProgram.h \
		../NGL/include/ngl/Util.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o obj/explosion.o src/explosion.cpp

obj/meshlib.o: src/meshlib.cpp include/meshlib.h \
		include/smartpointers.h \
		include/mesh.h \
		../NGL/include/ngl/Vec3.h \
		../NGL/include/ngl/Types.h \
		include/renderer.h \
		../NGL/include/ngl/Light.h \
		../NGL/include/ngl/Colour.h \
		../NGL/include/ngl/Vec4.h \
		../NGL/include/ngl/Vec2.h \
		../NGL/include/ngl/TransformStack.h \
		../NGL/include/ngl/Transformation.h \
		../NGL/include/ngl/Mat4.h \
		../NGL/include/ngl/NGLassert.h \
		include/camera.h \
		../NGL/include/ngl/Camera.h \
		../NGL/include/ngl/RibExport.h \
		../NGL/include/ngl/Plane.h \
		include/fwd/camera.h \
		include/fwd/window.h \
		../NGL/include/ngl/VertexArrayObject.h \
		../NGL/include/ngl/Obj.h \
		../NGL/include/ngl/Texture.h \
		../NGL/include/ngl/AbstractMesh.h \
		../NGL/include/ngl/BBox.h \
		include/pointlight.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o obj/meshlib.o src/meshlib.cpp

obj/pointlight.o: src/pointlight.cpp include/pointlight.h \
		include/smartpointers.h \
		../NGL/include/ngl/Vec4.h \
		../NGL/include/ngl/Types.h \
		../NGL/include/ngl/Vec2.h \
		../NGL/include/ngl/Vec3.h \
		../NGL/include/ngl/ShaderLib.h \
		../NGL/include/ngl/Singleton.h \
		../NGL/include/ngl/Colour.h \
		../NGL/include/ngl/Mat4.h \
		../NGL/include/ngl/Mat3.h \
		../NGL/include/ngl/Shader.h \
		../NGL/include/ngl/ShaderProgram.h \
		../NGL/include/ngl/Util.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o obj/pointlight.o src/pointlight.cpp

obj/mesh.o: src/mesh.cpp include/mesh.h \
		../NGL/include/ngl/Vec3.h \
		../NGL/include/ngl/Types.h \
		include/smartpointers.h \
		include/renderer.h \
		../NGL/include/ngl/Light.h \
		../NGL/include/ngl/Colour.h \
		../NGL/include/ngl/Vec4.h \
		../NGL/include/ngl/Vec2.h \
		../NGL/include/ngl/TransformStack.h \
		../NGL/include/ngl/Transformation.h \
		../NGL/include/ngl/Mat4.h \
		../NGL/include/ngl/NGLassert.h \
		include/camera.h \
		../NGL/include/ngl/Camera.h \
		../NGL/include/ngl/RibExport.h \
		../NGL/include/ngl/Plane.h \
		include/fwd/camera.h \
		include/fwd/window.h \
		../NGL/include/ngl/VertexArrayObject.h \
		../NGL/include/ngl/Obj.h \
		../NGL/include/ngl/Texture.h \
		../NGL/include/ngl/AbstractMesh.h \
		../NGL/include/ngl/BBox.h \
		include/pointlight.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o obj/mesh.o src/mesh.cpp

obj/grenade.o: src/concrete/grenade.cpp include/concrete/grenade.h \
		include/fsm/states/projectilestates.h \
		../NGL/include/ngl/ShaderLib.h \
		../NGL/include/ngl/Types.h \
		../NGL/include/ngl/Singleton.h \
		../NGL/include/ngl/Colour.h \
		../NGL/include/ngl/Mat4.h \
		../NGL/include/ngl/Mat3.h \
		../NGL/include/ngl/Vec4.h \
		../NGL/include/ngl/Vec2.h \
		../NGL/include/ngl/Vec3.h \
		../NGL/include/ngl/Shader.h \
		../NGL/include/ngl/ShaderProgram.h \
		../NGL/include/ngl/Util.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o obj/grenade.o src/concrete/grenade.cpp

obj/missilesilo.o: src/concrete/missilesilo.cpp include/concrete/missilesilo.h \
		../NGL/include/ngl/ShaderLib.h \
		../NGL/include/ngl/Types.h \
		../NGL/include/ngl/Singleton.h \
		../NGL/include/ngl/Colour.h \
		../NGL/include/ngl/Mat4.h \
		../NGL/include/ngl/Mat3.h \
		../NGL/include/ngl/Vec4.h \
		../NGL/include/ngl/Vec2.h \
		../NGL/include/ngl/Vec3.h \
		../NGL/include/ngl/Shader.h \
		../NGL/include/ngl/ShaderProgram.h \
		../NGL/include/ngl/Util.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o obj/missilesilo.o src/concrete/missilesilo.cpp

obj/missilesilostate.o: src/fsm/states/missilesilostate.cpp include/fsm/states/missilesilostate.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o obj/missilesilostate.o src/fsm/states/missilesilostate.cpp

obj/uwindow.o: src/uLayout/uwindow.cpp ../NGL/include/ngl/Vec2.h \
		../NGL/include/ngl/Types.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o obj/uwindow.o src/uLayout/uwindow.cpp

obj/costbutton.o: src/costbutton.cpp 
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o obj/costbutton.o src/costbutton.cpp

####### Install

install:   FORCE

uninstall:   FORCE

FORCE:

