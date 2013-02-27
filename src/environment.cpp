#include <boost/foreach.hpp>
#include "environment.h"
#include "entityfactory.h"
#include "database.h"
#include "game.h"

//-------------------------------------------------------------------//

Environment::Environment(
    int _gridWidth,
    int _gridHeight,
    int _hexagonSize,
    ngl::Vec3 _origin,
    int _baseX,
    int _baseY,
    int _dbGridSizeX,
    int _dbGridSizeZ,
    const std::vector<ngl::Vec2> &_spawnCoords
    ):
  m_nodeMap(NodeManager::create(
              _gridWidth,
              _gridHeight,
              _hexagonSize,
              _origin,
              _dbGridSizeX,
              _dbGridSizeZ))
{
  // base needs to be initialised here as it fails when putting it in the
  // inititalisation list
  //get an instance of the game

  Game* game = Game::instance();

  //create the base

  unsigned int ID = game->getID();
  NodePtr linkedNode = m_nodeMap->getNodeFromCoords(_baseX, _baseY).lock();
  if(linkedNode)
  {
    m_base = Base::create(
          linkedNode,
          ID
          );

    game->registerID(m_base,ID);
  }
  // Do first pass at scene graph, this is so objects can find initial paths when
  // they are constructed.
  m_nodeMap->recalculateSearchTree(NodeWPtr(linkedNode));

  // Create spawn points from coordinates.
  m_spawnNodes = Node::NodeWVecPtr(new Node::NodeWVec(_spawnCoords.size()));
  for(unsigned int i = 0; i < _spawnCoords.size(); ++i)
  {
    (*m_spawnNodes)[i] = m_nodeMap->getNodeFromCoords(
          _spawnCoords[i][0],
          _spawnCoords[i][1]
          );
  }
  resetSpawnPathHighlighting();
}

//-------------------------------------------------------------------//

EnvironmentPtr Environment::create(
    int _gridWidth,
    int _gridHeight,
    int _hexagonSize,
    ngl::Vec3 _origin,
    int _baseX,
    int _baseY,
    int _dbGridSizeX,
    int _dbGridSizeZ,
    const std::vector<ngl::Vec2> &_spawnCoords
    )
{
  EnvironmentPtr a(
        new Environment(
          _gridWidth,
          _gridHeight,
          _hexagonSize,
          _origin,
          _baseX,
          _baseY,
          _dbGridSizeX,
          _dbGridSizeZ,
          _spawnCoords
          )
        );
  return a;
}

//-------------------------------------------------------------------//

Environment::~Environment()
{
  //default dtor
}

//-------------------------------------------------------------------//

void Environment::update(const double _dt)
{
  // Go through all the towers and draw
  for(
      StaticEntityList::iterator it = m_towers.begin();
      it != m_towers.end();
      ++it
      )
  {
    (*it)->prepareForUpdate();
    (*it)->update(_dt);
  }
  // update base
  m_base->update(_dt);
  m_nodeMap->update(_dt);
}

//-------------------------------------------------------------------//

void Environment::draw() const
{
  // Go through all the towers and draw
  for(
      StaticEntityList::const_iterator it = m_towers.begin();
      it != m_towers.end();
      ++it
      )
  {
      (*it)->draw();
  }
  // draw base
  m_base->draw();
  m_nodeMap->draw();
}

//-------------------------------------------------------------------//

//void Environment::drawSelection() const
//{
//  // Go through all the towers and draw
//  for(
//      StaticEntityList::const_iterator it = m_towers.begin();
//      it != m_towers.end();
//      ++it
//      )
//  {
//    (*it)->drawSelection();
//  }
//  // draw base
//  m_base->drawSelection();
//  m_nodeMap->drawSelection();
//}

//-------------------------------------------------------------------//

void Environment::createTower(
    const std::string &_type,
    NodePtr _centerNode
    )
{
  // Create the new tower
  StaticEntityPtr newTower = EntityFactory::createStaticEntity(
        _type,
        _centerNode
        );
  // make sure it created a tower properly
  if(newTower)
  {
    m_towers.push_back(newTower);
  }
  recalculateSearchTree();
  // Highlight paths between spawn nodes and base
  resetSpawnPathHighlighting();
}

//-------------------------------------------------------------------//

void Environment::removeTower(StaticEntityList::iterator _tower)
{
  // unregister
  Game::instance()->unregisterID((*_tower)->getID());
  // remove
  if(m_towers.size() != 0)
  {
    m_towers.erase(_tower);
  }
}

//-------------------------------------------------------------------//

ngl::Vec3 Environment::getBasePos()
{
  return m_base->getPos();
}

//-------------------------------------------------------------------//

NodeManagerWPtr Environment::getNodeManagerWeakPtr()
{
  NodeManagerWPtr a(m_nodeMap);
  return a;
}

//-------------------------------------------------------------------//

void Environment::recalculateSearchTree()
{
  m_nodeMap->recalculateSearchTree(m_base->getLinkedNode());
}

//-------------------------------------------------------------------//

Node::NodeWVecWPtr Environment::getSpawnNodes() const
{
  return Node::NodeWVecWPtr(m_spawnNodes);
}

//-------------------------------------------------------------------//

bool Environment::checkSpawnNodePaths() const
{
  BOOST_FOREACH(NodeWPtr nodeWeak, *m_spawnNodes)
  {
    NodePtr node = nodeWeak.lock();
    if(node)
    {
      if(node->getSearchDepth() == -1)
      {
        return false;
      }
    }
  }
  return true;
}

//-------------------------------------------------------------------//

void Environment::resetSpawnPathHighlighting()
{
  // Clear all booleans
  m_nodeMap->clearSpawnPathHighlighting();

  // Find the path for each spawn node and flag all the nodes with isInSpawnPath
  BOOST_FOREACH(NodeWPtr spawnWeak, *m_spawnNodes)
  {
    NodePtr spawnNode = spawnWeak.lock();
    if(spawnNode)
    {
      // get path
      Node::NodeWList path;
      m_nodeMap->getSearchTreePath(path, spawnWeak, m_base->getLinkedNode());
      BOOST_FOREACH(NodeWPtr nodeWeak, path)
      {
        NodePtr node = nodeWeak.lock();
        if(node)
        {
          node->setInSpawnPath(true);
        }
      }
    }
  }
}
