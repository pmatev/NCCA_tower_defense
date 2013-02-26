#ifndef BULLET_H
#define BULLET_H

#include "projectile.h"
#include "smartpointers.h"

//-------------------------------------------------------------------//
/// @file bullet.h
/// @brief CONCRETE TYPE This is a simple example of a projectile class
/// @author Peter May
/// @version 1
/// @date 4/12/12
/// Revision History :
/// Initial Version 4/12/12
/// @class Bullet
//-------------------------------------------------------------------//

DECLARESMART(Bullet)

class Bullet : public Projectile
{
public: //methods

  //-------------------------------------------------------------------//
  /// @brief creator
  /// @param[in] _damage, damage that bullet can do
  /// @param[in] _maxVelocity, maximum velocity an bullet can travel at
  /// @param[in] _pos, initital position of bullet
  /// @param[in] _initialVelocity, the starting velocity of the bullet
  /// @param[in] _aim, the initial direction of travel of the bullet
  //-------------------------------------------------------------------//

  static EntityPtr create(
        const ngl::Vec3 &_pos,
        const ngl::Vec3 &_aim,
        unsigned int _id
        );

  //-------------------------------------------------------------------//
  /// @brief draw the object
  //-------------------------------------------------------------------//

  void draw() ;

//  //-------------------------------------------------------------------//
//  /// @brief draw the object based on id
//  //-------------------------------------------------------------------//

//  void drawSelection() ;

  void init();

  //-------------------------------------------------------------------//
  /// @brief method to generate the mesh of the object
  //-------------------------------------------------------------------//

  void generateMesh();

  void filterViewVolume(EntityRecordList &o_localEntities);

protected: //methods
  //-------------------------------------------------------------------//
  /// @brief creator
  /// @param[in] _damage, damage that bullet can do
  /// @param[in] _maxVelocity, maximum velocity an bullet can travel at
  /// @param[in] _pos, initital position of bullet
  /// @param[in] _initialVelocity, the starting velocity of the bullet
  /// @param[in] _aim, the initial direction of travel of the bullet
  //-------------------------------------------------------------------//

  Bullet(
        const ngl::Vec3 &_pos,
        const ngl::Vec3 &_aim,
        unsigned int _id
        );

  //-------------------------------------------------------------------//
  /// @brief works out which direction the bullet should go in next
  /// @param[out] new vector for bullet to travel in
  //-------------------------------------------------------------------//

  ngl::Vec3 brain();
};

#endif // BULLET_H
