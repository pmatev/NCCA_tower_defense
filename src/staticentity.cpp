#include "staticentity.h"
#include "database.h"

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
  //get a pointer to the instance of the database

  Database * db = Database::instance();

  //un-publish the database record from the database

  db->unPublish(m_generalType,m_ID);
}

//-------------------------------------------------------------------//
