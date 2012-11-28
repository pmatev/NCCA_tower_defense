#include "entity.h"

//-------------------------------------------------------------------//

Entity::Entity(const ngl::Vec3 & _pos):
  m_pos(_pos),
  m_health(100.0)
{
  //variables initialised before the constructor body
}

//-------------------------------------------------------------------//

Entity::~Entity()
{
  //currently using default destructor
}

//-------------------------------------------------------------------//

void Entity::publish()
{
  //yet to be implemented
}

//-------------------------------------------------------------------//
