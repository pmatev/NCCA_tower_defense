#ifndef PROJECTILEMANAGER_H
#define PROJECTILEMANAGER_H

#include "smartpointers.h"
#include "projectile.h"

//-------------------------------------------------------------------//
/// @file projectilemanager.h
/// @brief This is a class to store and manage all of the projectiles
/// currently active in the game
/// @author Peter May
/// @version 1
/// @date 6/12/12
/// Revision History :
/// Initial Version 6/12/12
/// @class ProjectileManager
//-------------------------------------------------------------------//

DECLARESMART(ProjectileManager)

class ProjectileManager
{
public://methods
  //-------------------------------------------------------------------//
  /// @brief creator
  //-------------------------------------------------------------------//
  static ProjectileManagerPtr create();

  //-------------------------------------------------------------------//
  /// @brief destructor
  //-------------------------------------------------------------------//

  ~ProjectileManager();

  //-------------------------------------------------------------------//
  /// @brief a method to get the number of projectiles currently active
  //-------------------------------------------------------------------//

  unsigned int getNumProjectiles() const {return m_projectiles.size();}

  //-------------------------------------------------------------------//
  /// @brief a method to do collision detection for each projectile.
  /// @param [out] returns a list of collisions
  //-------------------------------------------------------------------//

  std::list<Collision> checkCollisions();

  //-------------------------------------------------------------------//
  /// @brief a method to call update on each of the projectiles
  /// @param [in] _dt, the timestep
  //-------------------------------------------------------------------//

  void update(const double _dt);

  //-------------------------------------------------------------------//
  /// @brief a method to deal with any projectiles that have hit
  //-------------------------------------------------------------------//

  void checkDeaths();

  //-------------------------------------------------------------------//
  /// @brief a method to add a new projectile to the set
  /// @param[in] _type, type of projectile to create
  /// @param[in] _pos, initital position of enemy
  /// @param [in] _aim the aim vector of the projectile
  //-------------------------------------------------------------------//

  void addProjectile(
        const std::string &_type,
        const ngl::Vec3 &_pos,
        const ngl::Vec3 &_aim
        );

  //-------------------------------------------------------------------//
  /// @brief remove enemy method
  //-------------------------------------------------------------------//

  ProjectileList::iterator removeProjectile (
        ProjectileList::iterator _listIt
        );

  //-------------------------------------------------------------------//
  /// @brief a method to run through the projectiles and publish their
  /// record to the database
  //-------------------------------------------------------------------//

  void publish();

  //-------------------------------------------------------------------//
  /// @brief draws the current game state
  //-------------------------------------------------------------------//

  void draw();

protected: //methods

  //-------------------------------------------------------------------//
  /// @brief constructor, currently using default
  //-------------------------------------------------------------------//

  ProjectileManager();
protected://attributes
  //-------------------------------------------------------------------//
  /// @brief a list of pointers to the projectiles currently active in
  /// game
  //-------------------------------------------------------------------//

  ProjectileList m_projectiles;
};

#endif // PROJECTILEMANAGER_H
