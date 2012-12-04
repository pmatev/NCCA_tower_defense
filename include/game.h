#ifndef GAME_H
#define GAME_H

#include "fwd/game.h"
#include "fwd/window.h"
#include <map>
#include "entity.h"
#include <SDL.h>


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
    /// @brief updates the game state
    //-------------------------------------------------------------------//
    void update(const double _t);

    //-------------------------------------------------------------------//
    /// @brief draws the current game state
    //-------------------------------------------------------------------//
    void draw();

    //-------------------------------------------------------------------//
    /// @brief register the id of given Entity and return its ID
    //-------------------------------------------------------------------//
    unsigned int registerID(EntityPtr _e);

    //-------------------------------------------------------------------//
    /// @brief unregister Entity via ID
    //-------------------------------------------------------------------//
    void unregisterID(const unsigned int _i);

    //-------------------------------------------------------------------//
    /// @brief return Smart Pointer to Entity via ID.
    //-------------------------------------------------------------------//
    EntityPtr getEntityByID(const unsigned int _i);

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



protected:
    //-------------------------------------------------------------------//
    /// @brief hidden ctor for singleton
    //-------------------------------------------------------------------//
    Game();

    //-------------------------------------------------------------------//
    /// @brief ID Counter for distributing unique IDs to entities.
    //-------------------------------------------------------------------//
    unsigned int m_currentID;

    //-------------------------------------------------------------------//
    /// @brief A map of IDs to Entity Pointers for game object management.
    //-------------------------------------------------------------------//
    std::map<unsigned int, EntityPtr> m_IDMap;




private:
    //-------------------------------------------------------------------//
    /// @brief instance pointer for singleton
    //-------------------------------------------------------------------//
    static Game* s_instance;

};

#endif // GAME_H
