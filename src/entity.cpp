#include "entity.h"
#include "database.h"
#include "boost/lexical_cast.hpp"
#include "game.h"
#include "renderer.h"
#include "window.h"
#include "ngl/Vec3.h"
#include "ngl/TransformStack.h"
#include "ngl/ShaderLib.h"
#include "texturelib.h"

//-------------------------------------------------------------------//

Entity::Entity(const ngl::Vec3 &_pos, GeneralType _type, unsigned int _id) :
  m_ID(_id),
  m_pos(_pos),
  m_health(100.0),
  m_shieldPercentage(1.0),
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

void Entity::stateInit()
{

}

//-------------------------------------------------------------------//

void Entity::publish()
{
  //grabs a pointer to the database

  Database * db = Database::instance();

  //add the record

  EntityRecordPtr r = EntityRecord::create(
        m_ID,
        m_generalType,
        m_pos.m_x,
        m_pos.m_y,
        m_pos.m_z,
        m_velocity.m_x,
        m_velocity.m_y,
        m_velocity.m_z,
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

void Entity::initialiseMesh(std::string _name)
{
  MeshLibWPtr w_mesh_lib = MeshLib::instance();
  MeshLibPtr mesh_lib = w_mesh_lib.lock();
  if(mesh_lib)
  {
    generateLsBBox(mesh_lib->getVertDataFromMesh(_name));
    //publish();
  }
  else
  {
    std::cout << "Meshlib failed to load." << std::endl;
  }
}

//-------------------------------------------------------------------//

void Entity::calculateLocalEntities(
    EntityRecordWCList &o_newList,
    std::list<GeneralType> &_typeList
    )
{
  //get a pointer to the database instance

  Database * db = Database::instance();

  //get a pointer to the list of possible local entities

  db->getLocalEntities(
        o_newList,
        m_wsViewBBox.m_minX,
        m_wsViewBBox.m_minZ,
        m_wsViewBBox.m_maxX,
        m_wsViewBBox.m_maxZ,
        _typeList
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

void Entity::generateLsBBox(const std::vector <Renderer::vertData> & _meshData)
{
  //set an iterator for the list of vertData objects

  std::vector<Renderer::vertData>::const_iterator vertIt = _meshData.begin();

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

void Entity::draw()
{
  drawWithColour(ngl::Vec3(1, 0, 0));
}

void Entity::drawWithColour(const ngl::Vec3 &_colour)
{
  Renderer *r = Renderer::instance();
  TextureLib *tex = TextureLib::instance();
  ngl::ShaderLib *shader = ngl::ShaderLib::instance();
  Q_UNUSED(_colour);
  Q_UNUSED(tex);

  r->loadMatrixToShader(m_transformStack.getCurrentTransform().getMatrix(), "Constant");
  (*shader)["Constant"]->use();
  ngl::Vec3 c = Window::instance()->IDToColour(m_ID);
  c = c/255.0f;

  shader->setShaderParam4f("colour", 1,1,1,1);

  if(m_generalType != ENEMY)
  {
      shader->setShaderParam4f("colourSelect", c[0], c[1], c[2], 1);
  } else{
      shader->setShaderParam4f("colourSelect",0,0,0,0);
  }


  r->draw(m_IDStr, "Constant");
}
