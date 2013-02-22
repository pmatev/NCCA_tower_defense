#include "window.h"

int main(int argc, char *argv[])
{
  //Q unused to remove warnings, will be replaced if used

  Q_UNUSED(argc);
  Q_UNUSED(argv);

  // create and init the OpenGL Window
  Window *w = Window::instance();

  w->init();

  //   start the loop
  w->loop();

  w->destroy();
}
