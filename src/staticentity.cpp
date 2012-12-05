#include "staticentity.h"

//-------------------------------------------------------------------//

StaticEntity::StaticEntity(
    NodePtr _linkedNode,
    GeneralType _type
    ):
  Entity(_linkedNode->getPos(),_type),
  m_level(0),
  m_linkedNode(_linkedNode)
{
  //variables initialised before constructor body called
}

//-------------------------------------------------------------------//

StaticEntity::~StaticEntity()
{
  //currently using default destructor
}

//-------------------------------------------------------------------//
