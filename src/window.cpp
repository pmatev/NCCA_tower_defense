#include "renderer.h"
#include "window.h"
#include "ngl/NGLInit.h"
#include <QtGui>
#include "ngl/Text.h"
#include "ui.h"
#include <iostream>
#include <string>
#include "game.h"
#include "boost/lexical_cast.hpp"
#include <SDL_ttf.h>
#include "text.h"
#include "texturelib.h"




Window* Window::s_instance = 0;

//-------------------------------------------------------------------//
Window::Window():
  m_currentID(0)
{


}

//-------------------------------------------------------------------//
Window::~Window()
{
//    ngl::NGLInit *Init = ngl::NGLInit::instance();
    SDL_Quit();
//    Init->NGLQuit();
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




    //initialize openGl Window

    m_window = SDL_SetVideoMode(0,0, 16, SDL_OPENGL | SDL_RESIZABLE| SDL_FULLSCREEN);

    const SDL_VideoInfo* videoSize = SDL_GetVideoInfo();

    m_width = videoSize->current_w;
    m_height = videoSize->current_h;

    ngl::NGLInit *Init = ngl::NGLInit::instance();

    Init->initGlew();
     #ifdef WIN32
      glewInit(); // need a local glew init as well as lib one for windows
    #endif


    if (TTF_Init() == -1)
    {
      printf("Unable to initialize SDL_ttf: %s \n", TTF_GetError());
    }

    // Init factory
    EntityFactory::initialiseFactory();

    Game *game = Game::instance(); //initialize the game on creation
    game->init();

    Renderer *render = Renderer::instance();
    render->init();

    TextureLib *tex = TextureLib::instance();
    tex->init();

    m_UI = UIPtr(new UI());


    m_UI->setupUI();


    m_screenBillboard = Billboard::create(Billboard::b2D, ngl::Vec4(-1,-1,0,1),2,2);

    m_viewmode=0;
    m_clickedID = 0;

}


//-------------------------------------------------------------------//
void Window::loop()
{
    Game *game = Game::instance();

    // ------- GAME LOOP ------- //

    // Based on:   http://gafferongames.com/game-physics/fix-your-timestep/


    m_time = 0.0;
//    const double dt = 10; // update interval

    double currentTime = SDL_GetTicks();
//    double accumulator = 0.0;



    // flag to indicate if we need to exit

    m_quit=false;

    int frameCount = 0;
    float avgFPS = 0;

    while(!m_quit)
    {
        //event handling by SDL

        while (SDL_PollEvent(&m_event))
        {
            switch(m_event.type)
            {
            case SDL_QUIT : m_quit = true; break;
            case SDL_MOUSEMOTION : mouseMotionEvent(m_event.motion); break;
            case SDL_MOUSEBUTTONDOWN : mouseButtonDownEvent(m_event.button); break;
            case SDL_MOUSEBUTTONUP : mouseButtonUpEvent(m_event.button); break;
            case SDL_VIDEORESIZE :windowResizeEvent(m_event.resize);break;
            case SDL_KEYUP : keyEvent(m_event.key); break;
            case SDL_KEYDOWN:
            {
              switch(m_event.key.keysym.sym )
              {
                // if it's the escape key quit
                case SDLK_ESCAPE : m_quit = true; break;
                default : break;
              } // end of key process
            }
            }
        }

        double newTime = SDL_GetTicks();
        double frameTime = newTime - currentTime;
        currentTime = newTime;

//        if(frameTime>1000/15.0)frameTime=1000/15.0; // cap simulation if frame is taking too long

        if(frameCount % 20 == 0)
        {
          std::string fpsStr = boost::lexical_cast<std::string>(int(avgFPS/20));
          SDL_WM_SetCaption(&fpsStr[0],fpsStr.c_str());
          avgFPS = 0;
        }
        float fps = 1000.0/frameTime;
        avgFPS += fps;

        float maxDt = 70;

        if(game->getPaused() == 0)
        {
            if(frameTime > maxDt)
            {
                game->update(maxDt / 1000.0);
            }
            else
            {
                game->update(frameTime / 1000.0);
            }     
        }

        if(game->getBaseHealth() <=0)
        {
            if(!game->getLost())
            {
                m_UI->gameLost();
                game->setLost(true);
            }
        }

        Renderer *r = Renderer::instance();

        r->loadLightsToShader("Phong");

    // render to texture
        r->bindFrameBuffer("Texture");
        GLenum buffers[] = { GL_COLOR_ATTACHMENT0, GL_COLOR_ATTACHMENT1 };
        glDrawBuffers(2, buffers);
        glViewport(0,0,r->getResolutionX(),r->getResolutionY());
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        game->draw();
        r->visualiseLights();
        m_UI->update(frameTime);

        m_UI->draw();
        ngl::Vec4 pixel = r->readPixels(m_mouseX, m_mouseY);
        m_idUnderMouse = colourToID(pixel.toVec3());

        r->bindFrameBuffer(0);

        glViewport(0,0,m_width, m_height);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glBindTexture(GL_TEXTURE_2D, r->getTexture(m_viewmode));
        glGenerateMipmap(GL_TEXTURE_2D);

        m_screenBillboard->draw("Texture");


        SDL_GL_SwapBuffers();
        frameCount++;
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

    if(_event.keysym.sym == SDLK_f)
    {
        Renderer *renderer = Renderer::instance();

        Uint16 flags = SDL_OPENGL | SDL_RESIZABLE;

        flags = m_window->flags; /* Save the current flags in case toggling fails */

        if(m_fullscreen == false)
        {
            m_window = SDL_SetVideoMode(0, 0, 0, m_window->flags ^ SDL_FULLSCREEN); /*Toggles FullScreen Mode */
            if(m_window == NULL) m_window = SDL_SetVideoMode(0, 0, 0, flags); /* If toggle FullScreen failed, then switch back */
            if(m_window == NULL) exit(1); /* If you can't switch back for some reason, then epic fail */
            renderer->resize();
        }
        else
        {
            m_window = SDL_SetVideoMode(m_width, m_height,0, flags);
            renderer->resize();
        }

    }

    if(_event.keysym.sym == SDLK_1)
    {
        m_viewmode = 0;
    }
    if(_event.keysym.sym == SDLK_2)
    {
        m_viewmode = 1;
    }
    if(_event.keysym.sym == SDLK_3)
    {
        m_viewmode = 2;
    }
    if(_event.keysym.sym == SDLK_g)
    {
      game->startWaves();
    }

}

//-------------------------------------------------------------------//

void Window::windowResizeEvent(const SDL_ResizeEvent &_event)
{
    m_width = _event.w;
    m_height = _event.h;

    SDL_SetVideoMode(m_width, m_height, 16, SDL_OPENGL | SDL_RESIZABLE);

    Renderer *r = Renderer::instance();
    r->resize();


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
    CameraPtr cam = render->getCam().lock();

//    render->bindFrameBuffer("Texture");

//    ngl::Vec4 pixel = render->readPixels(_event.x, _event.y);
//    int id = colourToID(pixel.toVec3());
    //std::cout<<pixel<<std::endl;

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

    m_UI->mouseMoveEvent(m_idUnderMouse);

}
//-------------------------------------------------------------------//
void Window::mouseButtonDownEvent(const SDL_MouseButtonEvent &_event)
{
    Renderer *render = Renderer::instance();
    m_oldMouseX = _event.x;
    m_oldMouseY = _event.y;

    m_clickedID = m_idUnderMouse;
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
    m_UI->mouseLeftDown(m_idUnderMouse);
}



//-------------------------------------------------------------------//

void Window::mouseButtonUpEvent(const SDL_MouseButtonEvent &_event)
{

    if(_event.button == SDL_BUTTON_LEFT && m_idUnderMouse == m_clickedID)
    {
        m_UI->mouseDisablePressedState();
        m_UI->mouseLeftUp(m_idUnderMouse);
    }




    m_rotate=false;
    m_track = false;
    m_dolly=false;
    m_oldMouseX = m_mouseX;
    m_oldMouseY = m_mouseY;

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



