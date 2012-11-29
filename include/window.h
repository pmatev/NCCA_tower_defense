#ifndef WINDOW_H
#define WINDOW_H

#include "smartpointers.h"
#include <SDL.h>
#include "fwd/game.h"
#include "fwd/window.h"
#include <string>

//-------------------------------------------------------------------//
/// @file window.h
/// @brief manages the OS window and OpenGL context. Also controls the game
/// loop and the Game Class.
/// @author Peter Matev (based on Jon Macey's SDLNGL demo)
/// @version 1
/// @date 29/11/12
/// Revision History :
/// Initial Version 29/11/12
/// @class Window
//-------------------------------------------------------------------//

class Window
{
public:
    //-------------------------------------------------------------------//
    /// @brief the destructor
    //-------------------------------------------------------------------//
    ~Window();
    //-------------------------------------------------------------------//
    /// @brief constructs the object and returns smart pointer
    //-------------------------------------------------------------------//
    static WindowPtr create();
    //-------------------------------------------------------------------//
    /// @brief initialize the window and display it on screen
    //-------------------------------------------------------------------//
    void init();
    //-------------------------------------------------------------------//
    /// @brief the game loop
    //-------------------------------------------------------------------//
    void loop();
    //-------------------------------------------------------------------//
    /// @brief close the window gracefully.
    //-------------------------------------------------------------------//
    void quit();


protected:
    //-------------------------------------------------------------------//
    /// @brief hidden ctor
    //-------------------------------------------------------------------//
    Window();

    //-------------------------------------------------------------------//
    /// @brief Smart Pointer to the Game Object
    //-------------------------------------------------------------------//
    GamePtr m_game;

    //-------------------------------------------------------------------//
    /// @brief Smart Pointer to the internal SDL window
    //-------------------------------------------------------------------//
    SDL_Window *m_window;

    //-------------------------------------------------------------------//
    /// @brief initialize OpenGL Context
    //-------------------------------------------------------------------//
    SDL_GLContext createOpenGLContext( SDL_Window *_window);

    //-------------------------------------------------------------------//
    /// @brief function to quit SDL with error message
    /// @param[in] _msg the error message to send
    //-------------------------------------------------------------------//
    void SDLErrorExit(const std::string &_msg);

};

#endif // WINDOW_H
