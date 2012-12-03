#ifndef GAME_H
#define GAME_H

#include "fwd/game.h"
#include "fwd/window.h"


//-------------------------------------------------------------------//
/// @file game.h
/// @brief a class to manage the game state and delegate key/mouse events
/// to other managers
/// @author Peter Matev
/// @version 1
/// @date 29/11/12
/// Revision History :
/// Initial Version 29/11/12
/// @class Game
//-------------------------------------------------------------------//

class Game
{
public:
    //-------------------------------------------------------------------//
    /// @brief the destructor
    //-------------------------------------------------------------------//
    ~Game();
    //-------------------------------------------------------------------//
    /// @brief constructs the object and returns smart pointer
    //-------------------------------------------------------------------//
    static GamePtr create(WindowPtr _parent);
    //-------------------------------------------------------------------//
    /// @brief initiates the game. Calls update() and draw().
    //-------------------------------------------------------------------//
    void run();
    //-------------------------------------------------------------------//
    /// @brief updates the game state
    //-------------------------------------------------------------------//
    void update(const double _t);
    //-------------------------------------------------------------------//
    /// @brief draws the current game state
    //-------------------------------------------------------------------//
    void draw();

protected:
    //-------------------------------------------------------------------//
    /// @brief hidden ctor
    //-------------------------------------------------------------------//
    Game(WindowPtr _m_parent);

    //-------------------------------------------------------------------//
    /// @brief Smart pointer to parent window
    //-------------------------------------------------------------------//
    WindowPtr m_parent;



};

#endif // GAME_H
