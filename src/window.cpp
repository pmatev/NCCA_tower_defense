#include "include/window.h"
#include "game.h"
#include <string>
#include <iostream>

//-------------------------------------------------------------------//
Window::Window()
{
    Game *game = Game::instance(); //initialize the game on creation
}
//-------------------------------------------------------------------//
Window::~Window()
{
    //delete m_window;
}
//-------------------------------------------------------------------//
WindowPtr Window::create()
{
    WindowPtr a(new Window());
    return a;
}
//-------------------------------------------------------------------//
void Window::init()
{
    //***** Based on Jon Macey's SDLNGL demo ******//

    // Initialize SDL's Video subsystem
    if (SDL_Init(SDL_INIT_VIDEO) < 0 )
    {
      // Or die on error
      SDLErrorExit("Unable to initialize SDL");
    }

    // now get the size of the display and create a window we need to init the video
    SDL_Rect rect;
    SDL_GetDisplayBounds(0,&rect);
    // now create our window
    m_window=SDL_CreateWindow("Tower Defence",
                                        SDL_WINDOWPOS_CENTERED,
                                        SDL_WINDOWPOS_CENTERED,
                                        rect.w,
                                        rect.h,
                                        SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE
                                       );
    // check to see if that worked or exit
    if (!m_window)
    {
      SDLErrorExit("Unable to create window");
    }

    SDL_GLContext glContext=createOpenGLContext(m_window);
    if(!glContext)
    {
      SDLErrorExit("Problem creating OpenGL context");
    }

    // make this our current GL context (we can have more than one window but in this case not)
    SDL_GL_MakeCurrent(m_window, glContext);

    /* This makes our buffer swap syncronized with the monitor's vertical refresh */
    SDL_GL_SetSwapInterval(1);



}
//-------------------------------------------------------------------//
void Window::loop()
{
    SDL_Event event;

    Game *game = Game::instance();


    // ------- GAME LOOP ------- //

    // Based on:   http://gafferongames.com/game-physics/fix-your-timestep/


    m_time = 0.0;
    const double dt = 1; // update interval

    double currentTime = SDL_GetTicks();
    double accumulator = 0.0;

    // flag to indicate if we need to exit
    bool quit=false;

    while(!quit)
    {
        while (SDL_PollEvent(&event))
        {
            switch(event.type)
            {
            case SDL_QUIT : quit = true; break;
            }
        }

        double newTime = SDL_GetTicks();
        double frameTime = newTime - currentTime;
        currentTime = newTime;

        if(frameTime>80)frameTime=80; // cap simulation if frame is taking too long

        accumulator += frameTime;

        while (accumulator >= dt)
        {
            game->update(dt);

            accumulator -= dt;
            m_time += dt;
        }

        game->draw();

        SDL_GL_SwapWindow(m_window);
        std::cout<<"swapped"<<std::endl;
    }
}

//-------------------------------------------------------------------//
void Window::quit()
{
    SDL_Quit();
}
//-------------------------------------------------------------------//

SDL_GLContext Window::createOpenGLContext(SDL_Window *_window)
{
    //***** Based on Jon Macey's SDLNGL demo ******//

  // Request an opengl 3.2 context first we setup our attributes, if you need any
  // more just add them here before the call to create the context
  // SDL doesn't have the ability to choose which profile at this time of writing,
  // but it should default to the core profile
  // for some reason we need this for mac but linux crashes on the latest nvidia drivers
  // under centos
  #ifdef DARWIN
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 2);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
    SDL_GL_SetAttribute(SDL_GL_ACCELERATED_VISUAL, 1);
  #endif
  // set multi sampling else we get really bad graphics that aliasr
  SDL_GL_SetAttribute(SDL_GL_MULTISAMPLEBUFFERS, 1);
  SDL_GL_SetAttribute(SDL_GL_MULTISAMPLESAMPLES,4);
  // Turn on double buffering with a 24bit Z buffer.
  // You may need to change this to 16 or 32 for your system
  // on mac up to 32 will work but under linux centos build only 16
  SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 16);
  // enable double buffering (should be on by default)
  SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
  //
  return SDL_GL_CreateContext(_window);

}
//-------------------------------------------------------------------//
void Window::SDLErrorExit(const std::string &_msg)
{
    //***** Based on Jon Macey's SDLNGL demo ******//

  std::cerr<<_msg<<"\n";
  std::cerr<<SDL_GetError()<<"\n";
  SDL_Quit();
  exit(EXIT_FAILURE);
}
//-------------------------------------------------------------------//
