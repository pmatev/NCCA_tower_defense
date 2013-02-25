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
    int _hexagonSize,
    ngl::Vec3 _origin,
    int _dbGridSizeX,
    int _dbGridSizeZ
    ) :
  m_centerSqrDist((_hexagonSize * _hexagonSize * 2.999824)), // (sqrt(2/3)/4)
  m_gridWidth(_gridWidth),
  m_gridHeight(_gridHeight),
  m_hexagonSize(_hexagonSize),
  m_origin(_origin)
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

//  //get a pointer to the game
//  Game* game = Game::instance();

  // create all the necessary node
  for(int j = 0; j < _gridHeight; j++)
  {
    for(int i = 0; i < _gridWidth; i++)
    {
//      unsigned int ID = game->getID();
//      NodePtr node(
//            new Node(
//              ngl::Vec3(i * _hexagonSize * 0.75, 0,
//                        j * (_hexagonSize * s_hexFactor) + (_hexagonSize * s_hexFactor)/2 * ((i%2 != 0))
//                        ) + m_origin,
//              m_hexagonSize,
//              ID
      //              )
      //            );
//      game->registerID(node,ID);
      m_nodes.push_back(
            Node::create(
              ngl::Vec3(i * _hexagonSize * 0.75, 0,
                        j * (_hexagonSize * s_hexFactor) + (_hexagonSize * s_hexFactor)/2 * ((i%2 != 0))
                        ) + m_origin,
              m_hexagonSize
              )
            );
      //std::cout<<"#"<<(_gridWidth*j) + i<<": Node "<<"("<<i<<","<<j<<")" << " has coords: ["<<node->getPos().m_x<<","<<node->getPos().m_z<<std::endl;
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
    int _hexagonSize,
    ngl::Vec3 _origin,
    int _dbGridSizeX,
    int _dbGridSizeZ)
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
  for(int i = 0; i < m_nodes.size(); i++)
  {
    m_nodes[i]->update(_dt);
  }
}

//-------------------------------------------------------------------//

void NodeManager::draw()
{
  for(int i = 0; i < m_nodes.size(); i++)
  {
    m_nodes[i]->draw();
  }
}

//-------------------------------------------------------------------//

void NodeManager::drawSelection()
{
  for(int i = 0; i < m_nodes.size(); i++)
  {
    m_nodes[i]->drawSelection();
  }
}

void NodeManager::resetPathNodes()
{
  BOOST_FOREACH(PathNodeMap::value_type pathNode, m_pathNodeMap)
  {
#pragma omp critical
    pathNode.second->m_hasSuccessfulPath = false;

  }
}

//-------------------------------------------------------------------//

bool NodeManager::getAStar(Node::NodeWList &o_newPath, NodeWPtr _start, NodeWPtr _goal)
{
  // From http://en.wikipedia.org/wiki/A*_search_algorithm
  // THIS FUNCTION COULD PROBABLY BE SIMPLIFIED

  // this keeps track of which nodes relate to which paths, this way we can
  // access PathNode data via the Node. This is useful as children are stored
  // as Nodes rather than path nodes
  //std::map<NodeWPtr, PathNodePtr> m_pathNodeMap;

//  PathNodePtr start = PathNode::create(
//                      _start,
//                      0,
//                      heuristicPath(_start, _goal)
//                      );
  //m_pathNodeMap[_start] = start;
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
        #pragma omp critical
        {
          reconstructPath(o_newPath, current, _start);
        }
        std::cout<<"Completed path in "<<numSteps<<" steps"<<std::endl;
        return true;
      }

//      // If there's a successful path from the current point use the rest of it
//      // and return
//      if(current->m_hasSuccessfulPath)
//      {
//        // clear open set and continue, this should shortcut to the end
//        openSet.clear();
//        PathNodePtr child = current->m_child.lock();

//        if(child)
//        {
//          child->m_parent = PathNodePtr(current);
//          openSet.push_back(child);
//        }
//        continue;
//      }

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

  return getAStar(o_newPath, start, goal);
}

NodeWPtr NodeManager::getNodeFromPos(ngl::Vec3 _pos) const
{
  float x = _pos.m_x - m_origin.m_x;
  float y = _pos.m_z - m_origin.m_z;

  //transform into coordinate space
  x /= m_hexagonSize*0.75;
  y /= (m_hexagonSize*(s_hexFactor));

  //round to nearest int
  x = floor(x + 0.5);
  y = floor(y + 0.5);

  //clamp between values within the grid
  x = x < 0 ? 0 : x > m_gridWidth - 1 ? m_gridWidth - 1 : x;
  y = y < 0 ? 0 : y > m_gridHeight-1 ? m_gridHeight-1 : y;

  //calculate the index of the nearest based on x and y
  int index = (y * m_gridWidth) + x;

  return m_nodes[index];
}

NodeWPtr NodeManager::getNodeFromCoords(int _x, int _y) const
{
  return m_nodes[(_y*m_gridWidth) + _x];
}
