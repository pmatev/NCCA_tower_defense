#ifndef ENEMY_H
#define ENEMY_H

#include "dynamicentity.h"
#include "smartpointers.h"

//-------------------------------------------------------------------//
/// @file Enemy.h
/// @brief CONCRETE TYPE This is a simple example of an enemy class
/// @author Jared Auty
/// @version 1
/// @date 22/11/12
/// Revision History :
/// Initial Version 22/11/12
/// @class Enemy
//-------------------------------------------------------------------//

DECLARESMART(Enemy)

class Enemy : public DynamicEntity
{
public:

  //-------------------------------------------------------------------//
  /// @brief creator
  /// @param[in] _damage, damage that enemy can do
  /// @param[in] _maxVelocity, maximum velocity an enemy can travel at
  /// @param[in] _pos, initital position of enemy
  //-------------------------------------------------------------------//
  static EntityPtr create(
      float _damage,
      float _maxVelocity,
      const ngl::Vec3 & _pos
      );

protected:
  //-------------------------------------------------------------------//
  /// @brief ctor
  /// @param[in] _damage, damage that enemy can do
  /// @param[in] _maxVelocity, maximum velocity an enemy can travel at
  /// @param[in] _pos, initital position of enemy
  //-------------------------------------------------------------------//
  Enemy(
      float _damage,
      float _maxVelocity,
      const ngl::Vec3 &_pos
      );

  //-------------------------------------------------------------------//
  /// @brief works out which direction the enemy should go in next
  /// @param[out] new vector for enemy to travel in
  //-------------------------------------------------------------------//

  ngl::Vec3 brain();

  //-------------------------------------------------------------------//
  /// @brief draw the object
  //-------------------------------------------------------------------//

  void draw() const;
};

#endif // ENEMY_H
