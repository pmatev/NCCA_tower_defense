#include "base.h"

//-------------------------------------------------------------------//

Base::Base(
    NodePtr _linkedNode
    ) :
  StaticEntity(_linkedNode,BASE)
{

}

//-------------------------------------------------------------------//

BasePtr Base::create(NodePtr _linkedNode)
{
  BasePtr a = BasePtr(new Base(_linkedNode));
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
