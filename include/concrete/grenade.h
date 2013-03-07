#ifndef GRENADE_H
#define GRENADE_H


//-------------------------------------------------------------------//
/// @file grenade.h
/// @brief CONCRETE TYPE class for grenade
/// @author Peter May
/// @version 1
/// @date 4/12/12
/// Revision History :
/// Initial Version 4/12/12
/// @class Grenade
//-------------------------------------------------------------------//

#include "projectile.h"

DECLARESMART(Grenade)

class Grenade : public Projectile
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

//  //-------------------------------------------------------------------//
//  /// @brief overload this so we can compute the intial velocity
//  //-------------------------------------------------------------------//
//  void setVelocity(const ngl::Vec3 _velocity);

  ~Grenade();

  inline void setGravity(float _gravity) {m_gravity = _gravity;}

public:
  //-------------------------------------------------------------------//
  /// @brief ctor
  //-------------------------------------------------------------------//
  Grenade(const ngl::Vec3 &_pos, const ngl::Vec3 &_aim, unsigned int _id);

  ngl::Vec3 brain();

protected:

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

#endif // GRENADE_H
