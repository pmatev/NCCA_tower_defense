#include "dynamicentity.h"

//-------------------------------------------------------------------//

DynamicEntity::DynamicEntity(
    float _damage,
    const ngl::vec3 &_aimVector,
    float _maxVelocity,
    const ngl::Vec3 &_pos,
    float _health
    ):
  m_damage(_damage),
  m_aimVector(_aimVector),
  m_maxVelocity(_maxVelocity),
  Entity(_pos,_health)
{
  //variables initialised before the constructor body
}

//-------------------------------------------------------------------//

DynamicEntity::~DynamicEntity()
{
  //currently using default deconstructor
}

//-------------------------------------------------------------------//
