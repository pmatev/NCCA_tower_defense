#include "entity.h"

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
        Database::EntityRecord(
          m_ID,
          m_generalType,
          m_pos.m_x,
          m_pos.m_y,
          m_pos.m_z
          )
        );
}

//-------------------------------------------------------------------//

void Entity::updateLocalEntities()
{
  //get a pointer to the database instance

  Database * db = Database::instance();

  //get a pointer to the list of possible local entities and store it
  //it in the m_localEntities variable. This will be further reduced
  //when checked against the exact viewing area

  m_localEntities = db->getLocalEntities(
        m_wsViewBBox.m_minX,
        m_wsViewBBox.m_minY,
        m_wsViewBBox.m_maxX,
        m_wsViewBBox.m_maxY
        );
}

//-------------------------------------------------------------------//

void Entity::clearLocalEntities()
{
  //break the link between the pointer and the list, reduces the
  //reference count to 0 and deletes the object

  m_localEntities.reset();
}

//-------------------------------------------------------------------//
