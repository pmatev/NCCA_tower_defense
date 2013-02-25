#ifndef GAME_H
#define GAME_H

#include "fwd/game.h"
#include "fwd/window.h"
#include <map>
#include "entity.h"
#include <SDL.h>
#include <ngl/Light.h>
#include "uielement.h"
#include "node.h"
#include "wavemanager.h"
#include "environment.h"
#include "projectilemanager.h"
#include "player.h"


//-------------------------------------------------------------------//
/// @file game.h
/// @brief a class to manage the game state and other game managers
/// to other managers
/// @author Peter Matev, Jared Auty
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
    /// @brief clear everything and run sceneSetup()
    //-------------------------------------------------------------------//
    void reset();

    //-------------------------------------------------------------------//
    /// @brief returns instance of singleton
    //-------------------------------------------------------------------//
    void destroy();

    //-------------------------------------------------------------------//
    /// @brief updates the game state
    //-------------------------------------------------------------------//
    void update(const double _dt);

    //-------------------------------------------------------------------//
    /// @brief draws the current game state
    //-------------------------------------------------------------------//
    void draw();

    //-------------------------------------------------------------------//
    /// @brief draws the selection buffer for current game state
    //-------------------------------------------------------------------//
    void drawSelection();

    //-------------------------------------------------------------------//
    /// @brief returns an ID for an entity
    //-------------------------------------------------------------------//

    unsigned int getID();

    //-------------------------------------------------------------------//
    /// @brief register the id of given Entity and return its ID
    //-------------------------------------------------------------------//

    void registerID(EntityPtr _e, unsigned int _id);

    //-------------------------------------------------------------------//
    /// @brief unregister Entity via ID
    //-------------------------------------------------------------------//
    void unregisterID(const unsigned int _i);

    //-------------------------------------------------------------------//
    /// @brief return Smart Pointer to Entity via ID.
    //-------------------------------------------------------------------//
    EntityWPtr getEntityByID(const unsigned int _i) const;

    //-------------------------------------------------------------------//
    /// @brief try to create a tower on the specified node with the specified
    /// type.
    /// @param[in] _type, the type of tower to create
    /// @param[in] _node, which node to create the tower on
    /// @param[out] whether the creation was successful or not
    //-------------------------------------------------------------------//
    bool tryToCreateTower(const std::string &_type, NodePtr _node);

    //-------------------------------------------------------------------//
    /// @brief return base position
    /// @param[out] an ngl::Vec3
    //-------------------------------------------------------------------//
    ngl::Vec3 getBasePos() const;

    //-------------------------------------------------------------------//
    /// @brief return weak smart pointer to the environment
    //-------------------------------------------------------------------//
    void setNodehighlighted(int _id, bool _highlighted);


    EnvironmentWPtr getEnvironmentWeakPtr();


    //-------------------------------------------------------------------//
    /// @brief a method to return a smart weak pointer to the projectile
    /// manager
    /// @param [out] pointer to the projectile manager
    //-------------------------------------------------------------------//

    ProjectileManagerWPtr getProjectileManagerWeakPtr();


protected:
    //-------------------------------------------------------------------//
    /// @brief hidden ctor for singleton
    //-------------------------------------------------------------------//
    Game();

    //-------------------------------------------------------------------//
    /// @brief hidden destructor
    //-------------------------------------------------------------------//
    ~Game();

    //-------------------------------------------------------------------//
    /// @brief apply collision damage
    /// @param[in] _collisionList, is of all the entities that have been
    /// collided and the damage to be dealt.
    //-------------------------------------------------------------------//

    void dealDamage(std::list<Collision> _collisionList);

    //-------------------------------------------------------------------//
    /// @brief setup the whole scene. This is where any scene information
    /// should be read from file, interpreted and initialisd.
    //-------------------------------------------------------------------//

    void setupScene();

protected:

    //-------------------------------------------------------------------//
    /// @brief A map of IDs to Entity Pointers for game object management.
    //-------------------------------------------------------------------//
    std::map<unsigned int, EntityWPtr> m_IDMap;

    //-------------------------------------------------------------------//
    /// @brief pointer to the wavemanager
    //-------------------------------------------------------------------//

    WaveManagerPtr m_waveManager;

    //-------------------------------------------------------------------//
    /// @brief pointer to the environment
    //-------------------------------------------------------------------//

    EnvironmentPtr m_environment;

    //-------------------------------------------------------------------//
    /// @brief pointer to the projectile manager
    //-------------------------------------------------------------------//

    ProjectileManagerPtr m_projectileManager;

    //-------------------------------------------------------------------//
    /// @brief pointer to the player object
    //-------------------------------------------------------------------//

    PlayerPtr m_player;
private:
    //-------------------------------------------------------------------//
    /// @brief instance pointer for singleton
    //-------------------------------------------------------------------//

    static Game* s_instance;

    ngl::Light *m_light;

};

#endif // GAME_H
