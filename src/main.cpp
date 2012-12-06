#include <iostream>
#include <SDL.h>

#include "window.h"


int main(int argc, char *argv[])
{
  // create and init the OpenGL Window
  Window *w = Window::instance();

  w->init();


  // start the loop
  w->loop();

  //exit and close
  w->destroy();
}


