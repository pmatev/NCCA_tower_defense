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


    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);


    // set size of initial window

    m_width = 600;
    m_height = 600;

    //initialize openGl Window

    m_window = SDL_SetVideoMode(m_width, m_height, 16, SDL_OPENGL | SDL_RESIZABLE);


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
        //event handling by SDL

        while (SDL_PollEvent(&m_event))
        {
            switch(m_event.type)
            {
            case SDL_QUIT : quit = true; break;
            case SDL_MOUSEMOTION : mouseMotionEvent(m_event.motion); break;
            case SDL_MOUSEBUTTONDOWN : mouseButtonDownEvent(m_event.button); break;
            case SDL_MOUSEBUTTONUP : mouseButtonUpEvent(m_event.button); break;
            case SDL_VIDEORESIZE :windowResizeEvent(m_event.resize, renderer);break;
            case SDL_KEYUP : keyEvent(m_event.key); break;

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

        SDL_GL_SwapBuffers();

//        game->drawSelection();

        //m_UI->draw();
    }
}


//-------------------------------------------------------------------//

void Window::keyEvent(const SDL_KeyboardEvent &_event)
{
    Game *game = Game::instance();

    if(_event.keysym.sym == SDLK_r)
    {
       game->reset();
    }
}

//-------------------------------------------------------------------//

void Window::windowResizeEvent(const SDL_ResizeEvent &_event, Renderer *_renderer)
{
    m_width = _event.w;
    m_height = _event.h;

    SDL_SetVideoMode(m_width, m_height, 16, SDL_OPENGL | SDL_RESIZABLE);
    _renderer->resize(m_width, m_height);

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
void Window::mouseMotionEvent(const SDL_MouseMotionEvent &_event)
{
    m_mouseX = _event.x;
    m_mouseY = _event.y;

    Renderer *render = Renderer::instance();
    Camera *cam = render->getCam();

    m_motionEvent = _event;

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


    m_UI->mouseMoveEvent();

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


    unsigned int id = getIDFromGameSelection();

    if(_event.button == SDL_BUTTON_LEFT)
    {
          m_UI->mouseLeftUpTowerCreate(id);
    }




//    Game *game = Game::instance();
//    game->reset();

    /* -------- End Testing Code -------------*/

}




//-------------------------------------------------------------------//

//void Window::mouseWheelEvent(const SDL_MouseWheelEvent &_event)
//{
//  //Q unused to remove warnings, will be replaced if used

//  Q_UNUSED(_event)
//}


unsigned int Window::colourToID(ngl::Vec3 _c)
{
  unsigned int i;
  i =   (_c.m_x*(256*256)) + (_c.m_y*256) + _c.m_z;
  return i;
}



//-------------------------------------------------------------------//
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


//-------------------------------------------------------------------//

unsigned int Window::getIDFromGameSelection()
{
  Game *game = Game::instance();
  Renderer *r = Renderer::instance();
  game->drawSelection();
  unsigned int id;
  ngl::Vec3 pixel;

//checks which event it is in order to give the correct selection

  switch(m_event.type)
  {
  case SDL_MOUSEMOTION : pixel = r->readColourSelection(
                         m_motionEvent.x, m_motionEvent.y);
                         id = colourToID(pixel); break;

  case SDL_MOUSEBUTTONUP : pixel = r->readColourSelection(
                  m_clickEvent.x, m_clickEvent.y);
                  id = colourToID(pixel); break;
  }

  return id;
}
