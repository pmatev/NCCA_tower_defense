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

  //-------------------------------------------------------------------//
  /// @brief overload this so we can compute the intial velocity
  //-------------------------------------------------------------------//
  void setVelocity(const ngl::Vec3 _velocity);

  ~Missile();

public:
  //-------------------------------------------------------------------//
  /// @brief ctor
  //-------------------------------------------------------------------//
  Missile(const ngl::Vec3 &_pos, const ngl::Vec3 &_aim, unsigned int _id);

  ngl::Vec3 brain();

protected:
  //-------------------------------------------------------------------//
  /// @brief find the best target, save it in target pos
  //-------------------------------------------------------------------//
  void calculateTarget();

  //-------------------------------------------------------------------//
  /// @brief adjust the aim vector to hit the target
  //-------------------------------------------------------------------//
  void aim();

protected:
  //-------------------------------------------------------------------//
  /// @brief position of the target
  //-------------------------------------------------------------------//
  ngl::Vec3 m_targetPos;


  //-------------------------------------------------------------------//
  /// @brief gravity used in constant accn calculations. This defaults to
  /// -9.81
  //-------------------------------------------------------------------//
  float m_gravity;

  //-------------------------------------------------------------------//
  /// @brief aproximate time between when lanch and collision
  //-------------------------------------------------------------------//
  float m_horizontalSpeed;

};

#endif // MISSILE_H
