#include "nodemanager.h"
#include "database.h"
#include "game.h"
#include <boost/foreach.hpp>

//-------------------------------------------------------------------//

float NodeManager::s_hexFactor = 0.866025404;

//-------------------------------------------------------------------//
NodeManager::NodeManager(
    int _gridWidth,
    int _gridHeight,
    float _hexagonSize,
    ngl::Vec3 _origin,
    int _dbGridSizeX,
    int _dbGridSizeZ
    ) :
  m_hexagonSize(_hexagonSize),
  m_gridWidth(_gridWidth),
  m_gridHeight(_gridHeight),
  m_origin(_origin),
  m_centerSqrDist((_hexagonSize * _hexagonSize * 2.999824)) // (sqrt(2/3)/4)
{  
  // Initialise Database
  //first calculate the maximum x and z values

  float maxX = _origin.m_x
      + (_gridWidth-1)
      *(_hexagonSize * 0.75)
      +(_hexagonSize);
  float maxZ = _origin.m_z
      +(_hexagonSize*s_hexFactor)/2
      +(_hexagonSize*s_hexFactor)
      *(_gridHeight-1);

  // then calculate the minimum x and z values

  float minX = _origin.m_x - (_hexagonSize/2);
  float minZ = _origin.m_z - ((_hexagonSize*s_hexFactor/2));

  //finally initialise the database

  Database::init(_dbGridSizeX,_dbGridSizeZ, maxX,maxZ,minX,minZ);

  // create all the necessary nodes
  for(int j = 0; j < _gridHeight; j++)
  {
    for(int i = 0; i < _gridWidth; i++)
    {
      m_nodes.push_back(
            Node::create(
              ngl::Vec3(i * _hexagonSize * 0.75, 0,
                        j * (_hexagonSize * s_hexFactor) + (_hexagonSize * s_hexFactor)/2 * ((i%2 != 0))
                        ) + m_origin,
              m_hexagonSize
              )
            );
    }
  }

  //loop through again and set neighbours
  for(int j = 0; j < _gridHeight; j++)
  {
    for(int i = 0; i < _gridWidth; i++)
    {
      Node::NodeWListPtr neighbours(new Node::NodeWList());

      int x = 0;
      int y = 0;

      //Left
      if(i == 0)
      {
        //Top left
        if(j == 0)
        {
          x = i + 1;
          y = j;
          neighbours->push_back(NodeWPtr(m_nodes[(_gridWidth*y) + x]));

          x = i;
          y = j + 1;
          neighbours->push_back(NodeWPtr(m_nodes[(_gridWidth*y) + x]));
        }

        //Mid left
        else if(j < _gridHeight-1)
        {
          x = i;
          y = j - 1;
          neighbours->push_back(NodeWPtr(m_nodes[(_gridWidth*y) + x]));

          x = i + 1;
          y = j - 1;
          neighbours->push_back(NodeWPtr(m_nodes[(_gridWidth*y) + x]));

          x = i + 1;
          y = j;
          neighbours->push_back(NodeWPtr(m_nodes[(_gridWidth*y) + x]));

          x = i;
          y = j + 1;
          neighbours->push_back(NodeWPtr(m_nodes[(_gridWidth*y) + x]));
        }

        //Bottom left
        else
        {
          x = i;
          y = j - 1;
          neighbours->push_back(NodeWPtr(m_nodes[(_gridWidth*y) + x]));

          x = i + 1;
          y = j - 1;
          neighbours->push_back(NodeWPtr(m_nodes[(_gridWidth*y) + x]));

          x = i + 1;
          y = j;
          neighbours->push_back(NodeWPtr(m_nodes[(_gridWidth*y) + x]));
        }
      }

      //Right
      else if(i == _gridWidth-1)
      {
        //Top right
        if(j == 0)
        {
          //Upper top right
          if(i%2 == 0)
          {
            x = i - 1;
            y = j;
            neighbours->push_back(NodeWPtr(m_nodes[(_gridWidth*y) + x]));

            x = i;
            y = j + 1;
            neighbours->push_back(NodeWPtr(m_nodes[(_gridWidth*y) + x]));
          }

          //Lower top right
          if(i%2 != 0)
          {
            x = i - 1;
            y = j;
            neighbours->push_back(NodeWPtr(m_nodes[(_gridWidth*y) + x]));

            x = i - 1;
            y = j + 1;
            neighbours->push_back(NodeWPtr(m_nodes[(_gridWidth*y) + x]));

            x = i;
            y = j + 1;
            neighbours->push_back(NodeWPtr(m_nodes[(_gridWidth*y) + x]));
          }
        }

        //Mid right
        else if(j < _gridHeight-1)
        {
          x = i;
          y = j - 1;
          neighbours->push_back(NodeWPtr(m_nodes[(_gridWidth*y) + x]));

          x = i - 1;
          y = j;
          neighbours->push_back(NodeWPtr(m_nodes[(_gridWidth*y) + x]));

          x = i - 1;
          y = j + 1;
          neighbours->push_back(NodeWPtr(m_nodes[(_gridWidth*y) + x]));

          x = i;
          y = j + 1;
          neighbours->push_back(NodeWPtr(m_nodes[(_gridWidth*y) + x]));
        }

        //Bottom right
        else
        {
          //Bottom right upper
          if(i%2 == 0)
          {
            x = i - 1;
            y = j;
            neighbours->push_back(NodeWPtr(m_nodes[(_gridWidth*y) + x]));

            x = i - 1;
            y = j - 1;
            neighbours->push_back(NodeWPtr(m_nodes[(_gridWidth*y) + x]));

            x = i;
            y = j - 1;
            neighbours->push_back(NodeWPtr(m_nodes[(_gridWidth*y) + x]));
          }
          //Bottom right lower
          else
          {
            x = i;
            y = j - 1;
            neighbours->push_back(NodeWPtr(m_nodes[(_gridWidth*y) + x]));

            x = i - 1;
            y = j;
            neighbours->push_back(NodeWPtr(m_nodes[(_gridWidth*y) + x]));
          }
        }
      }

      //Top
      else if(j == 0)
      {
        //Lower top
        if(i%2 != 0)
        {
          x = i - 1;
          y = j;
          neighbours->push_back(NodeWPtr(m_nodes[(_gridWidth*y) + x]));

          x = i - 1;
          y = j + 1;
          neighbours->push_back(NodeWPtr(m_nodes[(_gridWidth*y) + x]));

          x = i;
          y = j + 1;
          neighbours->push_back(NodeWPtr(m_nodes[(_gridWidth*y) + x]));

          x = i + 1;
          y = j + 1;
          neighbours->push_back(NodeWPtr(m_nodes[(_gridWidth*y) + x]));

          x = i + 1;
          y = j;
          neighbours->push_back(NodeWPtr(m_nodes[(_gridWidth*y) + x]));
        }

        //Upper top
        else
        {
          x = i - 1;
          y = j;
          neighbours->push_back(NodeWPtr(m_nodes[(_gridWidth*y) + x]));

          x = i;
          y = j + 1;
          neighbours->push_back(NodeWPtr(m_nodes[(_gridWidth*y) + x]));

          x = i + 1;
          y = j;
          neighbours->push_back(NodeWPtr(m_nodes[(_gridWidth*y) + x]));
        }
      }

      //Bottom
      else if(j == _gridHeight-1)
      {
        //Lower bottom
        if(i%2 != 0)
        {
          x = i - 1;
          y = j;
          neighbours->push_back(NodeWPtr(m_nodes[(_gridWidth*y) + x]));

          x = i;
          y = j - 1;
          neighbours->push_back(NodeWPtr(m_nodes[(_gridWidth*y) + x]));

          x = i + 1;
          y = j;
          neighbours->push_back(NodeWPtr(m_nodes[(_gridWidth*y) + x]));
        }

        //Upper bottom
        else
        {
          x = i - 1;
          y = j;
          neighbours->push_back(NodeWPtr(m_nodes[(_gridWidth*y) + x]));

          x = i - 1;
          y = j - 1;
          neighbours->push_back(NodeWPtr(m_nodes[(_gridWidth*y) + x]));

          x = i;
          y = j - 1;
          neighbours->push_back(NodeWPtr(m_nodes[(_gridWidth*y) + x]));

          x = i + 1;
          y = j - 1;
          neighbours->push_back(NodeWPtr(m_nodes[(_gridWidth*y) + x]));

          x = i + 1;
          y = j;
          neighbours->push_back(NodeWPtr(m_nodes[(_gridWidth*y) + x]));
        }
      }

      //enclosed
      else
      {
        //enclosed odd
        if(i%2 != 0)
        {
          x = i - 1;
          y = j;
          neighbours->push_back(NodeWPtr(m_nodes[(_gridWidth*y) + x]));

          x = i;
          y = j - 1;
          neighbours->push_back(NodeWPtr(m_nodes[(_gridWidth*y) + x]));

          x = i + 1;
          y = j;
          neighbours->push_back(NodeWPtr(m_nodes[(_gridWidth*y) + x]));

          x = i + 1;
          y = j + 1;
          neighbours->push_back(NodeWPtr(m_nodes[(_gridWidth*y) + x]));

          x = i;
          y = j + 1;
          neighbours->push_back(NodeWPtr(m_nodes[(_gridWidth*y) + x]));

          x = i - 1;
          y = j + 1;
          neighbours->push_back(NodeWPtr(m_nodes[(_gridWidth*y) + x]));
        }

        //enclosed even
        else
        {
          x = i - 1;
          y = j - 1;
          neighbours->push_back(NodeWPtr(m_nodes[(_gridWidth*y) + x]));

          x = i;
          y = j - 1;
          neighbours->push_back(NodeWPtr(m_nodes[(_gridWidth*y) + x]));

          x = i + 1;
          y = j - 1;
          neighbours->push_back(NodeWPtr(m_nodes[(_gridWidth*y) + x]));

          x = i + 1;
          y = j;
          neighbours->push_back(NodeWPtr(m_nodes[(_gridWidth*y) + x]));

          x = i;
          y = j + 1;
          neighbours->push_back(NodeWPtr(m_nodes[(_gridWidth*y) + x]));

          x = i - 1;
          y = j;
          neighbours->push_back(NodeWPtr(m_nodes[(_gridWidth*y) + x]));
        }
      }
      m_nodes[(j*_gridWidth) + i]->setChildList(neighbours);
    }
  }
  createPathNodes();
}

//-------------------------------------------------------------------//

void NodeManager::createPathNodes()
{
  BOOST_FOREACH(NodePtr node, m_nodes)
  {
    PathNodePtr pathNode = PathNode::create(
          NodeWPtr(node),
          0,
          0
          );
    m_pathNodeMap[node] = pathNode;
    m_pathNodes.push_back(pathNode);
  }
}

//-------------------------------------------------------------------//

NodeManagerPtr NodeManager::create(
    int _gridWidth,
    int _gridHeight,
    float _hexagonSize,
    ngl::Vec3 _origin,
    int _dbGridSizeX,
    int _dbGridSizeZ
    )
{
  NodeManagerPtr a(new NodeManager(_gridWidth,
                                   _gridHeight,
                                   _hexagonSize,
                                   _origin,
                                   _dbGridSizeX,
                                   _dbGridSizeZ));
  return a;
}

//-------------------------------------------------------------------//

NodeManager::~NodeManager()
{
  // default dtor
}

//-------------------------------------------------------------------//

void NodeManager::update(const double _dt)
{
  for(unsigned long int i = 0; i < m_nodes.size(); i++)
  {
    m_nodes[i]->update(_dt);
  }
}

//-------------------------------------------------------------------//

void NodeManager::draw()
{
  for(unsigned long int i = 0; i < m_nodes.size(); i++)
  {
    m_nodes[i]->draw();
  }
}

void NodeManager::resetPathNodes()
{
  BOOST_FOREACH(PathNodeMap::value_type pathNode, m_pathNodeMap)
  {
    pathNode.second->m_hasSuccessfulPath = false;
  }
}

//-------------------------------------------------------------------//

void NodeManager::recalculateSearchTree(NodeWPtr _goal)
{
  // Go through each node and it's children in a depth first search to
  // storing the depth values as it goes

  // reset nodes
  BOOST_FOREACH(NodePtr node, m_nodes)
  {
    node->resetSearchInfo();
  }
  // start at the goal and spread out
  // do the first iteration seperate from recalculateChildren since otherwise
  // it will stop immediately because the first node is occupied by the base
  NodePtr goal = _goal.lock();
  if(goal)
  {
    int depth = 0;
    Node::NodeWListPtr currentList(new Node::NodeWList);
    Node::NodeWListPtr nextList(new Node::NodeWList);
    currentList->push_back(_goal);
    while(currentList->size() != 0)
    {
      // Go through currentList setting each nodes depth to depth
      BOOST_FOREACH(NodeWPtr nodeWeak, *currentList)
      {
        NodePtr node = nodeWeak.lock();
        if(node)
        {
          if(node->isFound())
          {
            continue;
          }
          else
          {
            node->setFound(true);
          }
          node->setSearchDepth(depth);
          // Put each nodes valid children into the nextList
          BOOST_FOREACH(NodeWPtr childWeak, *node->getChildList())
          {
            NodePtr child = childWeak.lock();
            if(child && !child->isFound() && !child->isOccupied())
            {
              nextList->push_back(child);
            }
          }
        }
      }
      // set currentList to be nextList
      currentList = nextList;
      nextList = Node::NodeWListPtr(new Node::NodeWList);
      ++depth;
    }
  }
}

//-------------------------------------------------------------------//

bool NodeManager::getSearchTreePath(
    Node::NodeWList &o_newPath,
    NodeWPtr _start,
    NodeWPtr _goal
    )
{
  // Start at start and go through node tree always picking the node with lowest
  // search depth

  // check that it's possible from this point
  NodePtr start = _start.lock();
  if(start)
  {
    // Make sure all nodes are marked as not found
    BOOST_FOREACH(NodePtr node, m_nodes)
    {
      node->setFound(false);
    }
    return traverseChildren(o_newPath, _goal, _start);
  }
  return true;
}

bool NodeManager::traverseChildren(
    Node::NodeWList &o_newPath,
    NodeWPtr _goal,
    NodeWPtr _current,
    bool _isStart
    )
{
  NodePtr current = _current.lock();
  NodePtr goal = _goal.lock();
  if(current && goal)
  {
      if(current->isFound())
      {
        return true;
      }
      else
      {
        current->setFound(true);
      }
      //bool startIsBlocked = false;
      if(_isStart && current->getSearchDepth() == -1)
      {
       // startIsBlocked = true;
      }
      else
      {
        o_newPath.push_back(_current);
      }
      // go through children
      // 1. find child with lowest search depth
      // 2. add child to o_newPath
      // 3. continue searching
      Node::NodeWListPtr children = current->getChildList();
      int lowestDepth = current->getSearchDepth();
      if(lowestDepth == -1)
      {
        lowestDepth = 10000;
      }
      bool foundSomething = false;
      NodePtr bestChild;
      BOOST_FOREACH(NodeWPtr childWeak, *children)
      {
        NodePtr child = childWeak.lock();
        if(child)
        {
          if(child == goal)
          {
            o_newPath.push_back(child);
            return true;
          }
          if(!child->isOccupied())
          {
            if(child->getSearchDepth() <= lowestDepth)
            {
              lowestDepth = child->getSearchDepth();
              bestChild = child;
              foundSomething = true;
            }
          }
        }
      }
      if(lowestDepth == -1)
      {
        return false;
      }
      if (foundSomething)
      {
        return traverseChildren(o_newPath, _goal,bestChild, false);
      }
  }
  return true;
}

//-------------------------------------------------------------------//

bool NodeManager::getAStar(Node::NodeWList &o_newPath, NodeWPtr _start, NodeWPtr _goal)
{
  // From http://en.wikipedia.org/wiki/A*_search_algorithm
  PathNodePtr start = m_pathNodeMap[_start];
  PathNodePtr goal = m_pathNodeMap[_goal];
  if(start && goal)
  {
    PathNodeList closedSet;
    PathNodeList openSet;
    int numSteps = 0;

    openSet.push_back(start);
    while(openSet.size() > 0)
    {
      // Current node to work on. This should be the node with the lowest fScore
      // in the openSet
      PathNodePtr current = *openSet.begin();

      // If we've found the goal
      if(*current == _goal)
      {
        reconstructPath(o_newPath, current, _start);
        return true;
      }

      // Take current from openSet and move it into closedSet
      openSet.remove(current);
      closedSet.push_back(current);
      NodePtr currentNode = current->m_node.lock();
      if(currentNode)
      {
        if(currentNode->isOccupied() && !(*current == _start))
        {
          continue;
        }

        // Go through children of current
        Node::NodeWListPtr children = currentNode->getChildList();
        for(
            Node::NodeWList::iterator it = children->begin();
            it != children->end();
            ++it)
        {
          PathNodePtr child;
          child = m_pathNodeMap[*it];
          if(checkListForNode(child, closedSet))
          {
            continue;
          }
          float tentativeGScore = current->m_gScore + m_centerSqrDist;
          bool inOpenSet = checkListForNode(child, openSet);
          if(!inOpenSet || tentativeGScore <= child->m_gScore)
          {
            child->m_parent = current;
            child->m_gScore = tentativeGScore;
            child->m_fScore = tentativeGScore + heuristicPath(m_pathNodeMap[child->m_node], goal);
            if(!inOpenSet)
            {
              //Add to openSet
              openSet.push_back(child);
            }
            //sort the set so that the top one will be chosen
            openSet.sort(PathNode::compare);
          }
        }
      }
      ++numSteps;
    }
  }
  // Failed to find a valid path
  return false;
}

//-------------------------------------------------------------------//

float NodeManager::heuristicPath(PathNodeWPtr _start, PathNodeWPtr _goal) const
{
  PathNodePtr start = _start.lock();
  PathNodePtr goal = _goal.lock();
  if(start && goal)
  {
    if(start->m_hasSuccessfulPath)
    {
      return start->m_successfulPathFScore;
    }
    NodePtr startNode = start->m_node.lock();
    NodePtr goalNode = goal->m_node.lock();
    if(startNode && goalNode)
    {
      ngl::Vec3 distVec =  startNode->getPos() - goalNode->getPos();
      float sqrDist =
          (distVec.m_x * distVec.m_x) +
          (distVec.m_y * distVec.m_y) +
          (distVec.m_z * distVec.m_z);
      return sqrDist;
    }
    return 0;
  }
  return 0;
}

//-------------------------------------------------------------------//

void NodeManager::reconstructPath(
    Node::NodeWList &io_newPath,
    PathNodeWPtr _current,
    NodeWPtr _start,
    float _fScore
    ) const
{
  PathNodePtr current = _current.lock();
  if(current)
  {
    current->m_hasSuccessfulPath = true;
    current->m_successfulPathFScore = _fScore;
    _fScore+=m_centerSqrDist;
    // Add the current node to the list
    io_newPath.push_back(current->m_node);
    // if we've got back to the start
    if(*current == _start)
    {
      // Finish
      return;
    }

    // save child for caching
    PathNodePtr parent = current->m_parent.lock();
    if(parent)
    {
      parent->m_child = _current;
    }

    // Keep searching from the parent
    reconstructPath(io_newPath, current->m_parent, _start, _fScore);
  }
  return;

}

//-------------------------------------------------------------------//

void NodeManager::reconstructOptimisedPath(
    Node::NodeWList &io_newPath,
    NodeManager::PathNodeWPtr _current,
    NodeWPtr _goal
    ) const
{
  PathNodePtr current = _current.lock();
  if(current)
  {
    io_newPath.push_back(current->m_node);
    // if we've got to the goal
    if(*current == _goal)
    {
      // Finish
      return;
    }
    // Keep searching from the parent
    reconstructOptimisedPath(io_newPath, current->m_child, _goal);
  }
  return;
}

//-------------------------------------------------------------------//

bool NodeManager::checkListForNode(PathNodePtr _node, PathNodeList _list) const
{
  // If the child is in closed set
  bool o_inList = false;
  for(
      PathNodeList::iterator it = _list.begin();
      it != _list.end();
      ++it
      )
  {
    if(*it == _node)
    {
      o_inList = true;
      break;
    }
  }
  return o_inList;
}

//-------------------------------------------------------------------//

bool NodeManager::findPathFromPos(
    Node::NodeWList &o_newPath,
    ngl::Vec3 _start,
    ngl::Vec3 _goal)
{
  //need to find the start and finish nodes in m_nodes from the vec3s.
  NodeWPtr start = getNodeFromPos(_start);
  NodeWPtr goal = getNodeFromPos(_goal);
  return getSearchTreePath(o_newPath, start, goal);
}

//-------------------------------------------------------------------//

NodeWPtr NodeManager::getNodeFromPos(ngl::Vec3 _pos) const
{
  float x = _pos.m_x - m_origin.m_x;
  float z = _pos.m_z - m_origin.m_z;

  //transform into coordinate space
  x /= m_hexagonSize*0.75;
  z /= (m_hexagonSize*(s_hexFactor));

  //round to nearest int
  x = floor(x + 0.5);
  z = floor(z + 0.5);

  //clamp between values within the grid
  x = x < 0 ? 0 : x > m_gridWidth - 1 ? m_gridWidth - 1 : x;
  z = z < 0 ? 0 : z > m_gridHeight-1 ? m_gridHeight-1 : z;

  //calculate the index of the nearest based on x and y
  int index = (z * m_gridWidth) + x;

  return NodeWPtr(m_nodes[index]);
}

//-------------------------------------------------------------------//
NodeWPtr NodeManager::getNodeFromCoords(int _x, int _z) const
{
  //clamp between values within the grid
  _x = _x < 0 ? 0 : _x > m_gridWidth - 1 ? m_gridWidth - 1 : _x;
  _z = _z < 0 ? 0 : _z > m_gridHeight-1 ? m_gridHeight-1 : _z;
  return NodeWPtr(m_nodes[(_z*m_gridWidth) + _x]);
}

//-------------------------------------------------------------------//

void NodeManager::clearSpawnPathHighlighting()
{
  BOOST_FOREACH(NodePtr node, m_nodes)
  {
    node->setInSpawnPath(false);
  }
}
