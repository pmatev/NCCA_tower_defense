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
  //currently using default deconstructor
}

//-------------------------------------------------------------------//

void Entity::publish()
{
  //yet to be implemented
  std::cout<<"publishing "<<m_pos.m_x<<m_pos.m_y<<m_pos.m_z;
}

//-------------------------------------------------------------------//
