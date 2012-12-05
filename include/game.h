#ifndef GAME_H
#define GAME_H

#include "fwd/game.h"
#include "fwd/window.h"
#include <map>
#include "entity.h"
#include <SDL.h>
#include <ngl/Light.h>
#include "node.h"
#include "wavemanager.h"
#include "environment.h"

//-------------------------------------------------------------------//
/// @file game.h
/// @brief a class to manage the game state and other game managers
/// to other managers
/// @author Peter Matev
/// @version 1.2
/// @date 04/12/12
/// Revision History :
/// Initial Version 29/11/12
/// @class Game
//-------------------------------------------------------------------//

class Game
{
public:


    //-------------------------------------------------------------------//
    /// @brief returns instance of singleton
    //-------------------------------------------------------------------//
    static Game* instance();


    void init();

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
    /// @brief try to create a tower on the specified node with the specified
    /// type.
    /// @param[in] _type, the type of tower to create
    /// @param[in] _node, which node to create the tower on
    /// @param[out] whether the creation was successful or not
    //-------------------------------------------------------------------//
    bool tryToCreateTower(const std::string &_type, NodePtr _node);





protected:
    //-------------------------------------------------------------------//
    /// @brief hidden ctor for singleton
    //-------------------------------------------------------------------//
    Game();

    //-------------------------------------------------------------------//
    /// @brief hidden destructor
    //-------------------------------------------------------------------//
    ~Game();

protected:

    //-------------------------------------------------------------------//
    /// @brief ID Counter for distributing unique IDs to entities.
    //-------------------------------------------------------------------//
    unsigned int m_currentID;

    //-------------------------------------------------------------------//
    /// @brief A map of IDs to Entity Pointers for game object management.
    //-------------------------------------------------------------------//
    std::map<unsigned int, EntityPtr> m_IDMap;

    //-------------------------------------------------------------------//
    /// @brief pointer to the wavemanager
    //-------------------------------------------------------------------//

    WaveManagerPtr m_waveManager;

    //-------------------------------------------------------------------//
    /// @brief pointer to the environment
    //-------------------------------------------------------------------//

    EnvironmentPtr m_environment;

private:
    //-------------------------------------------------------------------//
    /// @brief instance pointer for singleton
    //-------------------------------------------------------------------//
    static Game* s_instance;

    ngl::Light *m_light;

};

#endif // GAME_H
