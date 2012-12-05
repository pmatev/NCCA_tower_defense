#include "entity.h"
#include "database.h"
#include "boost/lexical_cast.hpp"
#include "game.h"

//-------------------------------------------------------------------//

Entity::Entity(const ngl::Vec3 &_pos, GeneralType _type) :
  m_pos(_pos),
  m_health(100.0),
  m_wsViewBBox(0,0,0,0,0,0),
  m_lsMeshBBox(0,0,0,0,0,0),
  m_generalType(_type)
{
  // Initialise id and register with game
  Game* game = Game::instance();
  // register instance with Game
  m_ID = game->registerID(EntityPtr(this));
  m_IDStr = boost::lexical_cast<std::string>(m_ID);

  m_transformStack = ngl::TransformStack();
}

//-------------------------------------------------------------------//

Entity::~Entity()
{
  //currently using default

}

//-------------------------------------------------------------------//

void Entity::publish()
{
  //grabs a pointer to the database

  Database * db = Database::instance();

  //add the record

  db->addRecord(
        EntityRecord(
          m_ID,
          m_generalType,
          m_pos.m_x,
          m_pos.m_y,
          m_pos.m_z
          )
        );
}

//-------------------------------------------------------------------//

entityRecordListPtr Entity::updateLocalEntities(
    std::list<GeneralType> &_typeList
    )
{
  //get a pointer to the database instance

  Database * db = Database::instance();

  //get a pointer to the list of possible local entities

  entityRecordListPtr result = db->getLocalEntities(
        m_wsViewBBox.m_minX,
        m_wsViewBBox.m_minY,
        m_wsViewBBox.m_maxX,
        m_wsViewBBox.m_maxY,
        _typeList
        );

  //and return it

  return result;
}

//-------------------------------------------------------------------//

void Entity::clearLocalEntities()
{
  //break the link between the pointer and the list, reduces the
  //reference count to 0 and deletes the object

  m_localEntities.reset();
}

//-------------------------------------------------------------------//


