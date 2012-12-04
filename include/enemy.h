#ifndef ENEMY_H
#define ENEMY_H

#include "smartpointers.h"
#include "dynamicentity.h"

//-------------------------------------------------------------------//
/// @file enemy.h
/// @brief This is an intermediate class that individual enemies
/// inherit from which sets the m_general type of the entity
/// @author Peter May
/// @version 1
/// @date 4/12/12
/// Revision History :
/// Initial Version 4/12/12
/// @class Enemy
//-------------------------------------------------------------------//

DECLARESMART(Enemy)

class Enemy : public DynamicEntity
{
public:
  //-------------------------------------------------------------------//
  /// @brief a parameterised constructor
  /// @param [in] _damage, a float to initialise the damage value
  /// @param [in] __maxVelocity, a float value describing the maximum
  /// velocity of the dynamic entity
  /// @param [in] _pos, a vector containing the initial position in 3D
  /// space of the entity, passed to the entity constructor
  /// @param[in] _initialVelocity, the starting velocity of the enemy
  //-------------------------------------------------------------------//

  Enemy(
        float _damage,
        float _maxVelocity,
        const ngl::Vec3 &_pos,
        float _initialVelocity,
        const ngl::Vec3 &_aim
        );
};

#endif // ENEMY_H
