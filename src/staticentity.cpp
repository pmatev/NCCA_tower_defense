#include "staticentity.h"
#include "database.h"

//-------------------------------------------------------------------//

StaticEntity::StaticEntity(
    NodePtr _linkedNode,
    GeneralType _type,
    unsigned int _id
    ):
  Entity(_linkedNode->getPos(),_type,_id),
  m_level(0),
  m_linkedNode(_linkedNode)
{
  // tag node as occupied
  m_linkedNode->setOccupied(true);
  //publish to the Database
  publish();
}

//-------------------------------------------------------------------//

StaticEntity::~StaticEntity()
{
  //get a pointer to the instance of the database

  Database * db = Database::instance();

  //un-publish the database record from the database

  db->unPublish(getGeneralType(),m_ID);
  // release node occupation
  m_linkedNode->setOccupied(false);
}

//-------------------------------------------------------------------//
