#include "wall.h"

//-------------------------------------------------------------------//

Wall::Wall(
    NodePtr _linkedNode, unsigned int _id
    ) :
  StaticEntity(_linkedNode,WALL, _id)
{
}

//-------------------------------------------------------------------//
