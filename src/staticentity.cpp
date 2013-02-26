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
  m_linkedNode(NodeWPtr(_linkedNode))
{
  // tag node as occupied
  _linkedNode->setOccupied(true);
  //publish to the Database
  //publish();
}

//-------------------------------------------------------------------//

StaticEntity::~StaticEntity()
{
  //get a pointer to the instance of the database

  Database * db = Database::instance();

  //un-publish the database record from the database

  db->unPublish(getGeneralType(),m_ID);
  // release node occupation
  NodePtr linkedNode = m_linkedNode.lock();
  if(linkedNode)
  {
    linkedNode->setOccupied(false);
  }
}

//-------------------------------------------------------------------//


void StaticEntity::prepareForUpdate()
{
  // Get the local entities
  std::list<GeneralType> types;
  types.push_back(ENEMY);
  m_localEntities = EntityRecordListPtr(new EntityRecordList());
  calculateLocalEntities(*m_localEntities, types);
  // Filter the entities
  filterViewVolume(*m_localEntities);
}

//-------------------------------------------------------------------//
