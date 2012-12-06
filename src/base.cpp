#include "base.h"

//-------------------------------------------------------------------//

Base::Base(
    NodePtr _linkedNode,
    unsigned int _id
    ) :
  StaticEntity(_linkedNode,BASE, _id)
{

}

//-------------------------------------------------------------------//

BasePtr Base::create(NodePtr _linkedNode, unsigned int _id)
{
  BasePtr a = BasePtr(new Base(_linkedNode,_id));
  return a;
}

//-------------------------------------------------------------------//

void Base::update()
{
  // do something
}

//-------------------------------------------------------------------//

void Base::draw()
{
  // do something
}

//-------------------------------------------------------------------//

void Base::drawSelection()
{
  // do something
}

//-------------------------------------------------------------------//

void Base::generateMesh()
{
  // do something
}

//-------------------------------------------------------------------//
