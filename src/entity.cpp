#include "entity.h"
#include "database.h"
#include "boost/lexical_cast.hpp"
#include "game.h"
#include "renderer.h"
#include "ngl/Vec3.h"
#include "ngl/TransformStack.h"

//-------------------------------------------------------------------//

Entity::Entity(const ngl::Vec3 &_pos, GeneralType _type, unsigned int _id) :
  m_ID(_id),
  m_pos(_pos),
  m_health(100.0),
  m_wsViewBBox(0,0,0,0,0,0),
  m_lsMeshBBox(0,0,0,0,0,0),
  m_generalType(_type)
{
  // THIS IS BUGGY AND CREATES PROBLEMS WHEN TRYING TO FREE MEMORY
  // SPECIFICALLY EntityPtr(this)
  // IMPLEMENTING REGISTERING IN ENTITY FACTORY

//  // Initialise id and register with game
//  Game* game = Game::instance();
//  // register instance with Game
//  m_ID = game->registerID(EntityPtr(this));
//  m_IDStr = boost::lexical_cast<std::string>(m_ID);

  m_IDStr = boost::lexical_cast<std::string>(m_ID);

  m_transformStack = ngl::TransformStack();
  m_transformStack.setPosition(m_pos);
}

//-------------------------------------------------------------------//

Entity::~Entity()
{
  Renderer *r = Renderer::instance();
  r->deleteVAO(m_IDStr);
}

//-------------------------------------------------------------------//

void Entity::init()
{

}

//-------------------------------------------------------------------//

void Entity::publish()
{
  //grabs a pointer to the database

  Database * db = Database::instance();

  //add the record

  EntityRecord r(m_ID,
                 m_generalType,
                 m_pos.m_x,
                 m_pos.m_y,
                 m_pos.m_z,
                 m_lsMeshBBox.m_minX + m_pos.m_x,
                 m_lsMeshBBox.m_maxX + m_pos.m_x,
                 m_lsMeshBBox.m_minY + m_pos.m_y,
                 m_lsMeshBBox.m_maxY + m_pos.m_y,
                 m_lsMeshBBox.m_minZ + m_pos.m_z,
                 m_lsMeshBBox.m_maxZ + m_pos.m_z
                 );

  db->addRecord(r);
}

//-------------------------------------------------------------------//

EntityRecordListPtr Entity::updateLocalEntities(
    std::list<GeneralType> &_typeList
    )
{
  //get a pointer to the database instance

  Database * db = Database::instance();

  //get a pointer to the list of possible local entities

  EntityRecordListPtr result = db->getLocalEntities(
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

void Entity::generateLsBBox(const std::vector <vertData> & _meshData)
{
  //set an iterator for the list of vertData objects

  std::vector<vertData>::const_iterator vertIt = _meshData.begin();

  //set the bounding box to initially start as the same as the first vert

  m_lsMeshBBox.m_maxX = vertIt->x;
  m_lsMeshBBox.m_minX = vertIt->x;
  m_lsMeshBBox.m_maxY = vertIt->y;
  m_lsMeshBBox.m_minY = vertIt->y;
  m_lsMeshBBox.m_maxZ = vertIt->z;
  m_lsMeshBBox.m_minZ = vertIt->z;

  //then increment the iterator

  vertIt++;

  //then cycle through the rest of the vert points

  while (vertIt != _meshData.end())
  {
    //check if the x value is less than the minimum x value

    if ((*vertIt).x < m_lsMeshBBox.m_minX)
    {
      //set the new min value

      m_lsMeshBBox.m_minX = (*vertIt).x;
    }

    //if not check if it's greater than the max x value

    else if ((*vertIt).x > m_lsMeshBBox.m_maxX)
    {
      //set the new max value

      m_lsMeshBBox.m_maxX = (*vertIt).x;
    }

    //repeat for y

    if ((*vertIt).y < m_lsMeshBBox.m_minY)
    {
      m_lsMeshBBox.m_minY = (*vertIt).y;
    }

    else if ((*vertIt).y > m_lsMeshBBox.m_maxY)
    {
      m_lsMeshBBox.m_maxY = (*vertIt).y;
    }

    //and z

    if ((*vertIt).z < m_lsMeshBBox.m_minZ)
    {
      m_lsMeshBBox.m_minZ = (*vertIt).z;
    }

    else if ((*vertIt).z > m_lsMeshBBox.m_maxZ)
    {
      m_lsMeshBBox.m_maxZ = (*vertIt).z;
    }

    //finally increment the counter

    vertIt++;
  }
}

//-------------------------------------------------------------------//


