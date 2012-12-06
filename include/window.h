#ifndef WINDOW_H
#define WINDOW_H

#include "smartpointers.h"
#include <SDL.h>
#include "fwd/game.h"
#include "fwd/window.h"
#include <string>
#include <ngl/Vec3.h>
#include "uiSelection.h"
//-------------------------------------------------------------------//
/// @file window.h
/// @brief manages the OS window and OpenGL context. Manages the Game Loop and Rendering Loop
/// also distributes key events
/// @author Peter Matev (based on Jon Macey's SDLNGL demo)
/// @version 1.1
/// @date 04/12/12
/// Revision History :
/// Initial Version 29/11/12
/// @class Window
//-------------------------------------------------------------------//

class Window
{
public:


    //-------------------------------------------------------------------//
    /// @brief constructs the object and returns smart pointer
    //-------------------------------------------------------------------//
    static Window* instance();


    //-------------------------------------------------------------------//
    /// @brief initialize the window and display it on screen
    //-------------------------------------------------------------------//
    void init();

    //-------------------------------------------------------------------//
    /// @brief the game loop
    //-------------------------------------------------------------------//
    void loop();

    //-------------------------------------------------------------------//
    /// @brief close the window gracefully and delete the singleton
    //-------------------------------------------------------------------//
    void destroy();




    //-------------------------------------------------------------------//
    /// @brief getter for time.
    //-------------------------------------------------------------------//
    inline double get_time() const {return m_time;}

    inline double getScreenWidth() const {return m_width;}

    inline double getScreenHeight() const {return m_height;}

    //-------------------------------------------------------------------//
    /// @brief function triggered on mouse move.
    //-------------------------------------------------------------------//
    void mouseMotionEvent(const SDL_MouseMotionEvent &_event);
    //-------------------------------------------------------------------//
    /// @brief function triggered on mouse button down
    //-------------------------------------------------------------------//
    void mouseButtonDownEvent(const SDL_MouseButtonEvent &_event);
    //-------------------------------------------------------------------//
    /// @brief function triggered on mouse button up
    //-------------------------------------------------------------------//
    void mouseButtonUpEvent(const SDL_MouseButtonEvent &_event);
    //-------------------------------------------------------------------//
    /// @brief function triggered on mouse wheel event
    //-------------------------------------------------------------------//
    void mouseWheelEvent(const SDL_MouseWheelEvent &_event);


    unsigned int colourToID(ngl::Vec3 _c);
    ngl::Vec3 IDToColour(unsigned int _id);

    //-------------------------------------------------------------------//
    /// @brief a method to get a unique id
    //-------------------------------------------------------------------//

    unsigned int getID();

protected:
    //-------------------------------------------------------------------//
    /// @brief hidden ctor
    //-------------------------------------------------------------------//
    Window();

    //-------------------------------------------------------------------//
    /// @brief the destructor
    //-------------------------------------------------------------------//
    ~Window();

    //-------------------------------------------------------------------//
    /// @brief singleton pointer
    //-------------------------------------------------------------------//
    static Window* s_instance;

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


    UISelectionPtr m_UI;


    void doSelection();


    //-------------------------------------------------------------------//
    /// @brief game time counter.
    //-------------------------------------------------------------------//
    double m_time;

    //-------------------------------------------------------------------//
    /// @brief width of window
    //-------------------------------------------------------------------//
    double m_width;
    //-------------------------------------------------------------------//
    /// @brief height of window
    //-------------------------------------------------------------------//
    double m_height;
    //-------------------------------------------------------------------//
    /// @brief current mouse X coord
    //-------------------------------------------------------------------//
    double m_mouseX;
    //-------------------------------------------------------------------//
    /// @brief current mouse Y coord
    //-------------------------------------------------------------------//
    double m_mouseY;
    //-------------------------------------------------------------------//
    /// @brief previous mouse X coord
    //-------------------------------------------------------------------//
    double m_oldMouseX;
    //-------------------------------------------------------------------//
    /// @brief previous mouse Y coord
    //-------------------------------------------------------------------//
    double m_oldMouseY;
    //-------------------------------------------------------------------//
    /// @brief flag for camera tumble
    //-------------------------------------------------------------------//
    bool m_rotate;
    //-------------------------------------------------------------------//
    /// @brief flag for camera track
    //-------------------------------------------------------------------//
    bool m_track;
    //-------------------------------------------------------------------//
    /// @brief flag for camera dolly
    //-------------------------------------------------------------------//
    bool m_dolly;
    //-------------------------------------------------------------------//
    /// @brief ID Counter for distributing unique IDs to entities.
    //-------------------------------------------------------------------//
    unsigned int m_currentID;

};

#endif // WINDOW_H
