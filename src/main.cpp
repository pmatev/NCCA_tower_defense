#include <iostream>
#include <SDL.h>

#include "window.h"
#include "nodemanager.h"


int main(int argc, char *argv[])
{
  NodeManagerPtr nm_test(NodeManager::create(6, 6, 2));
  // create and init the OpenGL Window
  Window *w = Window::instance();
  w->init();





  // start the loop
  w->loop();


  //exit and close
  w->destroy();
}


