#ifndef PROJECTILE_H
#define PROJECTILE_H


#include "smartpointers.h"
#include "dynamicentity.h"
#include "fwd/projectileManager.h"

//-------------------------------------------------------------------//
/// @file projectile.h
/// @brief This is an intermediate class that individual projectiles
/// inherit from which sets the m_general type of the entity
/// @author Peter May
/// @version 1
/// @date 4/12/12
/// Revision History :
/// Initial Version 4/12/12
/// @class Projectile
//-------------------------------------------------------------------//

DECLARESMARTLIST(Projectile)

class Projectile : public DynamicEntity
{
public://methods
  //-------------------------------------------------------------------//
  /// @brief a parameterised constructor
  /// @param [in] _damage, a float to initialise the damage value
  /// @param [in] _maxVelocity, a float value describing the maximum
  /// velocity of the dynamic entity
  /// @param [in] _pos, a vector containing the initial position in 3D
  /// space of the entity, passed to the entity constructor
  /// @param[in] _initialVelocity, the starting velocity of the enemy
  //-------------------------------------------------------------------//

  Projectile(
        const ngl::Vec3 &_pos,
        const ngl::Vec3 &_aim,
        unsigned int _id
        );

  //-------------------------------------------------------------------//
  /// @brief a method to enforce the grid boundaries
  //-------------------------------------------------------------------//

//  void enforceGridBoundaries();

  //-------------------------------------------------------------------//
  /// @brief a method to get the emmiter Id
  //-------------------------------------------------------------------//

  inline int getEmitterID() const {return m_emitterID;}

  //-------------------------------------------------------------------//
  /// @brief a method to set the emitter id
  //-------------------------------------------------------------------//

  inline void setEmitterID(int _ID) {m_emitterID = _ID;}

  //-------------------------------------------------------------------//
  /// @brief a method to set the velocity of the projectile, virtual
  /// so that concrete types can over-ride it with other specific behaviour
  //-------------------------------------------------------------------//

  virtual void setVelocity(const ngl::Vec3 _velocity){m_velocity = _velocity;}

  //-------------------------------------------------------------------//
  /// @brief set the projectiles parent. This should be called in the
  /// addProjectile method in ProjectileManager.
  //-------------------------------------------------------------------//

  inline void setParent(ProjectileManager *_parent) {m_parent = _parent;}

protected:

    //-------------------------------------------------------------------//
    /// @brief a variable to store the emitter turret
    //-------------------------------------------------------------------//

    int m_emitterID;

    //-------------------------------------------------------------------//
    /// @brief pointer to parent. This is mainly used for creating
    /// explosions
    //-------------------------------------------------------------------//

    ProjectileManager *m_parent;


};

#endif // PROJECTILE_H
