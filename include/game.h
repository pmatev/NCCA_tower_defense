#ifndef GAME_H
#define GAME_H

#include "fwd/game.h"
#include "fwd/window.h"
#include <map>
#include "entity.h"


//-------------------------------------------------------------------//
/// @file game.h
/// @brief a class to manage the game state and delegate key/mouse events
/// to other managers
/// @author Peter Matev
/// @version 1.1
/// @date 3/12/12
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
    /// @brief returns instance of singleton
    //-------------------------------------------------------------------//
    static Game* instance();
    //-------------------------------------------------------------------//
    /// @brief returns instance of singleton
    //-------------------------------------------------------------------//
    void destroy();
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

    unsigned int getNewID();

    void registerID(EntityPtr _e);

    void unregisterID(EntityPtr _e);

    void unregisterID(const unsigned int _i);

protected:
    //-------------------------------------------------------------------//
    /// @brief hidden ctor for singleton
    //-------------------------------------------------------------------//
    Game();

    unsigned int m_currentID;


    std::map<unsigned int, EntityPtr> m_IDMap;


private:

    static Game* s_instance;

};

#endif // GAME_H
