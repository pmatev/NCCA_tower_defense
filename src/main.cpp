#include <iostream>
#include <SDL.h>


#include "database.h"

#include "window.h"
#include "uiSelection.h"


int main(int argc, char *argv[])
{
  // create and init the OpenGL Window
  Window *w = Window::instance();

  w->init();




  UISelection* test = UISelection::instance();

  test->createTestMenu();


  // start the loop
  w->loop();

  //exit and close
  w->destroy();
}


