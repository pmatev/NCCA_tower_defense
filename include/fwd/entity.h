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

#endif // ENTITY_FWD_H
