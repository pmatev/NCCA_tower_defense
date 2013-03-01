#ifndef ENTITY_FWD_H
#define ENTITY_FWD_H

#include <ngl/Vec3.h>
#include "smartpointers.h"

DECLARESMART(Entity)

//-------------------------------------------------------------------//
/// @enum an enumeration of the general types that the entity can be
//-------------------------------------------------------------------//

enum GeneralType
{
  ENEMY,
  PROJECTILE,
  TURRET,
  WALL,
  BASE,
  NODE
};

//-------------------------------------------------------------------//
/// @struct a struct to store damage info
//-------------------------------------------------------------------//

struct Damage
{
  //-------------------------------------------------------------------//
  /// @brief the id of the entity that has been hit
  //-------------------------------------------------------------------//

  unsigned int m_id;

  //-------------------------------------------------------------------//
  /// @brief the damage to deal to the object that has been hit
  //-------------------------------------------------------------------//

  float m_damage;

  //-------------------------------------------------------------------//
  /// @brief constructor
  //-------------------------------------------------------------------//

  Damage(int _id, float _damage) :
    m_id(_id),
    m_damage(_damage)
  {}
};

//-------------------------------------------------------------------//
/// @brief a struct to store impulses that should be applied to enemies
//-------------------------------------------------------------------//

struct Impulse
{
  //-------------------------------------------------------------------//
/// @brief  the id of the entity that it should act on
  //-------------------------------------------------------------------//

  unsigned int m_id;

  //-------------------------------------------------------------------//
  /// @brief the impulse vector
  //-------------------------------------------------------------------//

  ngl::Vec3 m_vec;

  //-------------------------------------------------------------------//
  /// @brief ctor
  //-------------------------------------------------------------------//

  Impulse(unsigned int _id, const ngl::Vec3 &_vec):
    m_id(_id),
    m_vec(_vec)
  {;}

};

#endif // ENTITY_FWD_H
