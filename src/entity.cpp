#include "entity.h"

//-------------------------------------------------------------------//

Entity::Entity(const ngl::Vec3 & _pos, float _health):
  m_pos(_pos),
  m_health(_health)
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
