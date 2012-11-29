#include <iostream>
#include <SDL.h>

#include "window.h"


#include "entityfactory.h"
#include "enemy.h"

int main(int argc, char *argv[])
{
    // create and init the OpenGL Window
    WindowPtr w = Window::create();
    w->init();

    // start the loop
    w->loop();

    //exit and close
    w->quit();
}


