#ifndef GRENADE_H
#define GRENADE_H


//-------------------------------------------------------------------//
/// @file grenade.h
/// @brief CONCRETE TYPE class for grenade. Basically just acts under free-fall
/// motion.
/// @author Peter May, Jared Auty
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
  /// @param[in] _pos initial position
  /// @param[in] _aim initial velocity
  /// @param[in] _id ID of entity
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

  //-------------------------------------------------------------------//
  /// @brief initialise state values
  //-------------------------------------------------------------------//

  void stateInit();

  //-------------------------------------------------------------------//
  /// @brief filter the local enemies
  //-------------------------------------------------------------------//

  void filterViewVolume(EntityRecordWCList &o_localEntities);

  //-------------------------------------------------------------------//
  /// @brief destructor, used for creating explosions
  //-------------------------------------------------------------------//
  ~Grenade();

  //-------------------------------------------------------------------//
  /// @brief set the gravity value. This is always in the y direction
  //-------------------------------------------------------------------//
  inline void setGravity(float _gravity) {m_gravity = _gravity;}

public:
  //-------------------------------------------------------------------//
  /// @brief ctor
  //-------------------------------------------------------------------//
  Grenade(const ngl::Vec3 &_pos, const ngl::Vec3 &_aim, unsigned int _id);

  //-------------------------------------------------------------------//
  /// @brief work out what to do
  //-------------------------------------------------------------------//
  ngl::Vec3 brain();

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
