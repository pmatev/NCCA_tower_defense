#include "wall.h"

//-------------------------------------------------------------------//

Wall::Wall(
    std::vector<NodePtr> &_linkedNodes,
    const ngl::Vec3 &_pos
    ) :
  StaticEntity(_linkedNodes,_pos,WALL)
{
}

//-------------------------------------------------------------------//
