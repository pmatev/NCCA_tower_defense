#include "node.h"

//-------------------------------------------------------------------//

Node::Node(const ngl::Vec3 &_pos):
  m_pos(_pos),
  m_isOccupied(false)
{
  //variables initialised before constructor body called
}

//-------------------------------------------------------------------//

Node::Node(float _posX, float _posY, float _posZ):
  m_pos(_posX,_posY,_posZ),
  m_isOccupied(false)
{
  //variables initialised before constructor body called
}

//-------------------------------------------------------------------//

Node::~Node()
{
  //currently using default deconstructor
}

//-------------------------------------------------------------------//
