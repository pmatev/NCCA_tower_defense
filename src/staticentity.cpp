#include "staticentity.h"

//-------------------------------------------------------------------//

StaticEntity::StaticEntity(
    std::vector<NodePtr> &_linkedNodes,
    const ngl::Vec3 &_pos,
    float _health
    ):
  Entity(_pos,_health),
  m_level(0),
  m_linkedNodes(_linkedNodes)
{
  //variables initialised before constructor body called
}

//-------------------------------------------------------------------//

StaticEntity::~StaticEntity()
{
  //currently using default destructor
}

//-------------------------------------------------------------------//
