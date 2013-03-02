#ifndef MISSILE_H
#define MISSILE_H


//-------------------------------------------------------------------//
/// @file missile.h
/// @brief CONCRETE TYPE class for missile
/// @author Peter May
/// @version 1
/// @date 4/12/12
/// Revision History :
/// Initial Version 4/12/12
/// @class Bullet
//-------------------------------------------------------------------//

#include "projectile.h"

DECLARESMART(Missile)

class Missile : public Projectile
{
public:
  //-------------------------------------------------------------------//
  /// @brief creator
  //-------------------------------------------------------------------//
  static EntityPtr create(
        const ngl::Vec3 &_pos,
        const ngl::Vec3 &_aim,
        unsigned int _id
        );

  //-------------------------------------------------------------------//
  /// @brief draw the object
  //-------------------------------------------------------------------//

  void draw();

  void stateInit();

  void filterViewVolume(EntityRecordWCList &o_localEntities);

  ~Missile();

public:
  //-------------------------------------------------------------------//
  /// @brief ctor
  //-------------------------------------------------------------------//
  Missile(const ngl::Vec3 &_pos, const ngl::Vec3 &_aim, unsigned int _id);

  ngl::Vec3 brain();
};

#endif // MISSILE_H
