#include "include/base.h"

//-------------------------------------------------------------------//

Base::Base(
    std::vector<NodePtr> &_linkedNodes,
    const ngl::Vec3 &_pos
    ) :
  StaticEntity(_linkedNodes,_pos,BASE)
{
}

//-------------------------------------------------------------------//
