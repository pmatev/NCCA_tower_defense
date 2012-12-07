#include "include/window.h"
#include "game.h"
#include <string>
#include <iostream>
#include "renderer.h"
#include "ngl/NGLInit.h"
#include "uiSelection.h"

Window* Window::s_instance = 0;

//-------------------------------------------------------------------//
Window::Window():
  m_currentID(0)
{


}
//-------------------------------------------------------------------//
Window::~Window()
{
    ngl::NGLInit *Init = ngl::NGLInit::instance();
    SDL_Quit();
    Init->NGLQuit();
}
//-------------------------------------------------------------------//

Window* Window::instance()
{
    if(s_instance == 0)
    {
        s_instance = new Window();
    }
    return s_instance;
}

void Window::destroy()
{
    if (s_instance)
    {

        delete s_instance;
    }
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
    m_width = 600;
    m_height = 600;


    // now create our window
    m_window=SDL_CreateWindow("Tower Defence",
                                        SDL_WINDOWPOS_CENTERED,
                                        SDL_WINDOWPOS_CENTERED,
                                        m_width,
                                        m_height,
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


    ngl::NGLInit *Init = ngl::NGLInit::instance();

    Init->initGlew();
    #ifdef WIN32
      glewInit(); // need a local glew init as well as lib one for windows
    #endif

    // Init factory
    EntityFactory::initialiseFactory();

    Game *game = Game::instance(); //initialize the game on creation
    game->init();

    Renderer *render = Renderer::instance();
    render->init();


    m_UI = UISelectionPtr(new UISelection());

    m_UI->createTestMenu();





}


//-------------------------------------------------------------------//
void Window::loop()
{
    SDL_Event event;

    Game *game = Game::instance();
    Renderer *renderer = Renderer::instance();

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
            case SDL_MOUSEMOTION : mouseMotionEvent(event.motion); break;
            case SDL_MOUSEBUTTONDOWN : mouseButtonDownEvent(event.button); break;
            case SDL_MOUSEBUTTONUP : mouseButtonUpEvent(event.button); break;
            case SDL_MOUSEWHEEL : mouseWheelEvent(event.wheel); break;
            //case SDL_KEYDOWN:if(event.key.keysym.sym == SDLK_s)glPolygonMode(GL_FRONT_AND_BACK,GL_LINE); break;
            case SDL_WINDOWEVENT :
              int w,h;
              // get the new window size
              SDL_GetWindowSize(m_window,&w,&h);
              renderer->resize(w, h);
            break;

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
        m_UI->draw();


        SDL_GL_SwapWindow(m_window);

    }
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

//-------------------------------------------------------------------//
void Window::mouseMotionEvent(const SDL_MouseMotionEvent &_event)
{
    m_mouseX = _event.x;
    m_mouseY = _event.y;

    Renderer *render = Renderer::instance();
    Camera *cam = render->getCam();

    // Left Mouse Tumble
    if(m_rotate)
    {
      cam->tumble(m_oldMouseX, m_oldMouseY, m_mouseX, m_mouseY);
    }

    // Middle Mouse Track
    else if(m_track)
    {
        cam->track(m_oldMouseX, m_oldMouseY, m_mouseX, m_mouseY);
    }

    // Right Mouse Dolly
    else if(m_dolly)
    {
        cam->dolly(m_oldMouseX, m_mouseX);
    }

    m_oldMouseX = m_mouseX;
    m_oldMouseY = m_mouseY;

}
//-------------------------------------------------------------------//
void Window::mouseButtonDownEvent(const SDL_MouseButtonEvent &_event)
{
    m_oldMouseX = _event.x;
    m_oldMouseY = _event.y;

    if(_event.button == SDL_BUTTON_LEFT)
    {
        m_rotate =true;
    }

    else if(_event.button == SDL_BUTTON_MIDDLE)
    {
        m_track = true;
    }

    else if(_event.button == SDL_BUTTON_RIGHT)
    {
        m_dolly=true;
    }



}
//-------------------------------------------------------------------//
void Window::mouseButtonUpEvent(const SDL_MouseButtonEvent &_event)
{
    m_rotate=false;
    m_track = false;
    m_dolly=false;
    m_oldMouseX = m_mouseX;
    m_oldMouseY = m_mouseY;

    /* -------- Testing Code -------------*/
    m_clickEvent = _event;

    Renderer *r = Renderer::instance();
    r->prepareDrawSelection();


    m_UI->drawSelection();

    ngl::Vec3 pixel = r->readColourSelection(_event.x, _event.y);
    unsigned int id = colourToID(pixel);

    m_UI->mouseLeftUpTowerCreate(id);

    /* -------- End Testing Code -------------*/

}

//-------------------------------------------------------------------//
void Window::mouseWheelEvent(const SDL_MouseWheelEvent &_event)
{

}

unsigned int Window::colourToID(ngl::Vec3 _c)
{
  unsigned int i;
  i =   (_c.m_x*(256*256)) + (_c.m_y*256) + _c.m_z;
  return i;
}

ngl::Vec3 Window::IDToColour(unsigned int _id)
{
  ngl::Vec3 c;
  c.m_x = std::floor(_id/(256*256));
  c.m_y = std::floor(_id/256);
  c.m_z = _id%256;

  //std::cout<<c<<std::endl;
  return c;
}

//-------------------------------------------------------------------//

unsigned int Window::getID()
{
  m_currentID++;

  return m_currentID;
}

unsigned int Window::getIDFromGameSelection()
{
  Game *game = Game::instance();
  Renderer *r = Renderer::instance();
  game->drawSelection();

  ngl::Vec3 pixel = r->readColourSelection(m_clickEvent.x, m_clickEvent.y);
  unsigned int id = colourToID(pixel);

  return id;
}
