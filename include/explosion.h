#ifndef EXPLOSION_H
#define EXPLOSION_H


//-------------------------------------------------------------------//
/// @file explosion.h
/// @brief This class manages the creation of explosions. Explosions can
/// be created by projectiles to deal damage and apply impulses to a group
/// of Enemies.
/// @author Jared Auty
/// @version 1
/// @date 1/3/13
/// Revision History :
/// Initial Version 1/3/13
/// @class Explosion
//-------------------------------------------------------------------//

#include <ngl/Vec3.h>
#include "smartpointers.h"
#include "fwd/entity.h"

DECLARESMARTLIST(Explosion)

class Explosion
{
public:
  //-------------------------------------------------------------------//
  /// @brief creator
  //-------------------------------------------------------------------//
  static ExplosionPtr create(
        float _power,
        float _damage,
        float _radius,
        const ngl::Vec3 &_pos,
        float _lifetime = 0
        );

  //-------------------------------------------------------------------//
  /// @brief update the explosion. This could be used for explosion animations
  /// @param[in] _dt time difference
  /// @param[out] o_damages list of damage values for enemies
  /// @param[out] o_impulses list the impulses that should be applied to enemies
  /// @return whether the explosion should be removed or not
  //-------------------------------------------------------------------//
  bool execute(
        float _dt,
        std::list<Damage> &o_damages,
        std::list<Impulse> &o_impulses
        );

protected:
  //-------------------------------------------------------------------//
  /// @brief how powerful the explosion is
  //-------------------------------------------------------------------//

  float m_power;

  //-------------------------------------------------------------------//
  /// @brief maxium damage to deal. This will then be spread out to the edges of
  /// the radius
  //-------------------------------------------------------------------//

  float m_damage;

  //-------------------------------------------------------------------//
  /// @brief radius of effect, sqr radius is used in most calculations but
  /// keep this so if we need it we don't have to sqrt it.
  //-------------------------------------------------------------------//

  float m_radius;

  //-------------------------------------------------------------------//
  /// @brief square of the radius of effect, pre-squared for efficiency
  //-------------------------------------------------------------------//

  float m_sqrRadius;

  //-------------------------------------------------------------------//
  /// @brief center of explosion
  //-------------------------------------------------------------------//

  ngl::Vec3 m_pos;

  //-------------------------------------------------------------------//
  /// @brief how long the explosion has been active. This should be updated
  /// in update
  //-------------------------------------------------------------------//

  float m_currentAge;

  //-------------------------------------------------------------------//
  /// @brief how long the explosion should be active. If this is set to 0
  /// it should survive for one update.
  //-------------------------------------------------------------------//

  float m_lifetime;

protected:
  //-------------------------------------------------------------------//
  /// @brief ctor
  //-------------------------------------------------------------------//
  Explosion(
        float _power,
        float _damage,
        float _radius,
        const ngl::Vec3 &_pos,
        float _lifetime
      );
};

#endif // EXPLOSION_H
