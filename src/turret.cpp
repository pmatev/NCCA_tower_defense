#include "turret.h"

//-------------------------------------------------------------------//

Turret::Turret(
    float _fov,
    float _viewDistance,
    float _maxRotationSpeed,
    const ngl::Vec3 &_aim,
    NodePtr _linkedNode
    ):
  StaticEntity(_linkedNode,TURRET),
  m_fov(_fov),
  m_viewDistance(_viewDistance),
  m_maxRotationSpeed(_maxRotationSpeed),
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
