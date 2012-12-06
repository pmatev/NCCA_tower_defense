#include "turret.h"

//-------------------------------------------------------------------//

Turret::Turret(
    NodePtr _linkedNode,
    unsigned int _id
    ):
  StaticEntity(_linkedNode,TURRET,_id),
  m_fov(360),
  m_viewDistance(20),
  m_maxRotationSpeed(20),
  m_aim(ngl::Vec3(0, 1, 0))
{
  //variables initialised before constructor body called
}


//-------------------------------------------------------------------//

Turret::~Turret()
{
  //currently using default destructor
}

//-------------------------------------------------------------------//

void Turret::update()
{
  // TEST
  // just do whatever the brain says
  m_aim = brain();
}
