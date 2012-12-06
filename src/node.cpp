#include "fwd/entity.h"
#include "entity.h"
#include "node.h"

//-------------------------------------------------------------------//

Node::Node(const ngl::Vec3 &_pos):
  Entity(_pos, NODE),
  m_isOccupied(false)
{
  //variables initialised before constructor body called
}

//-------------------------------------------------------------------//

Node::~Node()
{
  //currently using default destructor
}

//-------------------------------------------------------------------//

void Node::update()
{

}

//-------------------------------------------------------------------//

void Node::draw()
{

}

//-------------------------------------------------------------------//

void Node::drawSelection()
{

}

//-------------------------------------------------------------------//

void Node::generateMesh()
{

}

//-------------------------------------------------------------------//
