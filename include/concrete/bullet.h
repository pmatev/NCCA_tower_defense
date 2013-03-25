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
  /// @param [in] _pos initital position of bullet
  /// @param [in] _aim the initial direction of travel of the bullet
  /// @param [in] _id the unique identifier for the bullet
  //-------------------------------------------------------------------//

  static EntityPtr create(
        const ngl::Vec3 &_pos,
        const ngl::Vec3 &_aim,
        unsigned int _id
        );

  //-------------------------------------------------------------------//
  /// @brief dtor
  //-------------------------------------------------------------------//

  ~Bullet();

  //-------------------------------------------------------------------//
  /// @brief draw the object
  //-------------------------------------------------------------------//

  void draw() ;

  //-------------------------------------------------------------------//
  /// @brief the method to initialiser the state machine for the bullet
  //-------------------------------------------------------------------//

  void stateInit();

  //-------------------------------------------------------------------//
  /// @brief empty method, implemented to satisfy pure virtual
  /// @param [in][out] o_localEntities, unused
  //-------------------------------------------------------------------//

  void filterViewVolume(EntityRecordWCList &o_localEntities);

protected: //methods
  //-------------------------------------------------------------------//
  /// @brief constructor
  /// @param [in] _pos initital position of bullet
  /// @param [in] _aim the initial direction of travel of the bullet
  /// @param [in] _id the unique identifier for the bullet
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
