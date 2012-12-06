#include "turret.h"

//-------------------------------------------------------------------//

Turret::Turret(
    const ngl::Vec3 &_aim,
    NodePtr _linkedNode,
    unsigned int _id
    ):
  StaticEntity(_linkedNode,TURRET,_id),
  m_fov(360),
  m_viewDistance(20),
  m_maxRotationSpeed(20),
  m_aim(_aim)
{
  //variables initialised before constructor body called
}


//-------------------------------------------------------------------//

Turret::~Turret()
{
  //currently using default destructor
}

//-------------------------------------------------------------------//
