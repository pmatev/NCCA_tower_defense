#include <boost/foreach.hpp>
#include "environment.h"
#include "entityfactory.h"
#include "database.h"
#include "game.h"

//-------------------------------------------------------------------//

Environment::Environment(
    const EnvironmentInfo &_info
    ):
  m_nodeMap(
    NodeManager::create(
      _info.m_gridWidth,
      _info.m_gridHeight,
      _info.m_hexagonSize,
      ngl::Vec3(0, 0, 0),
      _info.m_dbGridX,
      _info.m_dbGridZ)
    )
{
  // base needs to be initialised here as it fails when putting it in the
  // inititalisation list
  //get an instance of the game

  Game* game = Game::instance();

  //create the base

  unsigned int ID = game->getID();
  NodePtr linkedNode = m_nodeMap->getNodeFromCoords(
        _info.m_baseX,
        _info.m_baseZ
        ).lock();
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
  m_spawnNodes = Node::NodeWVecPtr(new Node::NodeWVec(_info.m_spawnCoords.size()));
  for(unsigned int i = 0; i < _info.m_spawnCoords.size(); ++i)
  {
    (*m_spawnNodes)[i] = m_nodeMap->getNodeFromCoords(
          _info.m_spawnCoords[i][0],
          _info.m_spawnCoords[i][1]
          );
  }

//  // Add invisible nodes around the edge
  std::list<ngl::Vec2> invisibleCoords;
  for(int i = 0; i < _info.m_gridWidth; ++i)
  {
    for(int j = 0; j < _info.m_gridHeight; ++j)
    {
      if(
         i == 0 ||
         i == _info.m_gridWidth -1 ||
         j == 0 ||
         j == _info.m_gridHeight -1
         )
      {
        // Add left and right edges
        invisibleCoords.push_back(ngl::Vec2(i, j));
      }
    }
  }

  invisibleCoords.insert(
        invisibleCoords.end(),
        _info.m_invisibleCoords.begin(),
        _info.m_invisibleCoords.end()
        );

  // Set invisible nodes to be invisible.
  BOOST_FOREACH(ngl::Vec2 visCoord, invisibleCoords)
  {
    NodePtr visNode = m_nodeMap->getNodeFromCoords(
          visCoord[0],
          visCoord[1]
          ).lock();
    if(visNode)
    {
      createTower("InvisibleWall", visNode);
    }
  }

  std::list<ngl::Vec2> wallCoords;
  wallCoords.insert(
        wallCoords.end(),
        _info.m_wallCoords.begin(),
        _info.m_wallCoords.end()
        );

  // Create walls from coordinates.
  BOOST_FOREACH(ngl::Vec2 wallCoord, wallCoords)
  {
    NodePtr wallNode = m_nodeMap->getNodeFromCoords(
          wallCoord[0],
          wallCoord[1]
          ).lock();
    if(wallNode)
    {
      createTower("StandardWall", wallNode);
    }
  }

  m_nodeMap->recalculateSearchTree(NodeWPtr(linkedNode));
  resetSpawnPathHighlighting();

}

//-------------------------------------------------------------------//

void Environment::createHexagonShape(
    int _gridX,
    int _gridZ,
    const ngl::Vec2 &_start,
    int _size,
    std::list<ngl::Vec2> &o_coords
    )
{
  // THIS SECTION DOES NOT WORK YET --------------------------------------------------------
  // finding the start position doesn't work on some odd numbered _size
  int sideLength;
  ngl::Vec2 start;
  if(_size % 2 == 0)
  {
   sideLength = std::ceil((_size - 1.0) / 2.0);
  }
  else
  {
     sideLength = _size / 2.0 + 1;
  }
  start = ngl::Vec2(_start.m_x, _start.m_y + std::ceil((_size - sideLength) / 2));
  if(_size % 2 != 0 && _size % 3 != 0) // every second odd number
  {
    start.m_y +=1;
  }
  // THIS SECTION DOES NOT WORK YET --------------------------------------------------------
  int xSize = (sideLength * 2) - 1;
  int evenOffset;
  if(int(start.m_x) % 2 == 0)
  {
    evenOffset = -1;
  }
  else
  {
    evenOffset = 0;
  }
  for(int i = 0; i < _gridX; ++i)
  {
    int rightStop = _gridZ;
    int leftStop = 0;
    if(i ==  start.m_x || i == start.m_x + xSize  - 1)
    {
      // Top and Bottom edges
      rightStop = start.m_y;
      leftStop = start.m_y + sideLength - 1;
    }
    else
    {
      // Top diagonals
      if(i > start.m_x && i < start.m_x + sideLength)
      {
        if(i % 2 == 0) // even
        {
          rightStop = start.m_y + (start.m_x - i) / 2 + 1 + evenOffset;
          leftStop =  start.m_y + sideLength -(start.m_x - i) / 2 +evenOffset;
        }
        else // odd
        {
          rightStop = start.m_y + (start.m_x - i) / 2;
          leftStop = start.m_y + sideLength -(start.m_x - i) / 2 - 1;
        }
      }
      // Bottom diagonals
      if(i >= start.m_x + sideLength && i < start.m_x + xSize)
      {
        if(i % 2 == 0) // even
        {
          rightStop = start.m_y + (i - start.m_x) / 2  - sideLength + 2+ evenOffset;
          leftStop = start.m_y + sideLength*2 - (i - start.m_x) / 2 -1+ evenOffset;
        }
        else // odd
        {
          rightStop =  start.m_y + (i - start.m_x) / 2  - sideLength + 1;
          leftStop = start.m_y + sideLength*2 - (i - start.m_x) / 2  - 2;
        }
      }
    }

    for(int j = 0; j < _gridZ; ++j)
    {
      if(j > leftStop || j < rightStop)
      {
        o_coords.push_back(ngl::Vec2(i, j));
      }
    }
  }

}

//-------------------------------------------------------------------//

EnvironmentPtr Environment::create(
    const EnvironmentInfo &_info
    )
{
  EnvironmentPtr a(new Environment(_info));
  return a;
}

//-------------------------------------------------------------------//

void Environment::update(const double _dt)
{
  // Go through all the towers and update
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

  if(m_spawnNodes)
  {
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
}

float Environment::getBaseHealth() const
{
    return m_base->getHealth();
}
