#ifndef ENTITY_FWD_H
#define ENTITY_FWD_H

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
/// @struct a struct to store collision info
//-------------------------------------------------------------------//

struct Collision
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

  Collision(int _id, float _damage) :
    m_id(_id),
    m_damage(_damage)
  {}
};

#endif // ENTITY_FWD_H
