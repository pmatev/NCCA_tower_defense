#include "include/concrete/testturret.h"

//-------------------------------------------------------------------//
TestTurret::TestTurret(
    NodePtr _linkedNode,
    unsigned int &_id
    ):
  Turret(
    _linkedNode,
    _id
    )
{
  m_fov = 90;
  m_viewDistance = 10;
  m_maxRotationSpeed = 3;
  // pass everything into the turret
}

//-------------------------------------------------------------------//

EntityPtr TestTurret::create(
    NodePtr _linkedNode,
    unsigned int _id
    )
{
  // pass everything to the ctor
  EntityPtr a(new TestTurret(
                    _linkedNode,
                    _id
                    )
                  );
  return a;
}
//-------------------------------------------------------------------//

void TestTurret::generateMesh()
{

}

//-------------------------------------------------------------------//

void TestTurret::draw()
{

}

//-------------------------------------------------------------------//

void TestTurret::drawSelection()
{

}

//-------------------------------------------------------------------//

ngl::Vec3 TestTurret::brain()
{
  // do something
  // return test aim
  return ngl::Vec3(0, 1, 0);
}

//-------------------------------------------------------------------//

