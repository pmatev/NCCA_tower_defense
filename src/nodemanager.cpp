#include "nodemanager.h"

//-------------------------------------------------------------------//

NodeManager::NodeManager(int _gridWidth, int _gridHeight, int _hexagonSize, ngl::Vec3 _origin) :
  m_centerDist(_hexagonSize * 1.732),
  m_gridWidth(_gridWidth),
  m_gridHeight(_gridHeight),
  m_hexagonSize(_hexagonSize),
  m_origin(_origin)
{

  // create all the necessary node
  for(int j = 0; j < _gridHeight; j++)
  {
    for(int i = 0; i < _gridWidth; i++)
    {
      NodePtr node(
            new Node(
              ngl::Vec3(i * _hexagonSize * 0.75, 0,
                        j * (_hexagonSize * (sqrt(3)/2)) + (_hexagonSize * (sqrt(3)/2))/2 * ((i%2 != 0))
                        ) + m_origin,
              m_hexagonSize
              )
            );
      m_nodes.push_back(node);
      //std::cout<<"#"<<(_gridWidth*j) + i<<": Node "<<"("<<i<<","<<j<<")" << " has coords: ["<<i * _hexagonSize<<","<<j * (_hexagonSize * (sqrt(3)/2))<<"]"<<std::endl;
    }
  }

  //loop through again and set neighbours
  for(int j = 0; j < _gridHeight; j++)
  {
    for(int i = 0; i < _gridWidth; i++)
    {
      Node::NodeListPtr neighbours(new Node::NodeList());

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
          neighbours->push_back(m_nodes[(_gridWidth*y) + x]);

          x = i;
          y = j + 1;
          neighbours->push_back(m_nodes[(_gridWidth*y) + x]);
        }

        //Mid left
        else if(j < _gridHeight-1)
        {
          x = i;
          y = j - 1;
          neighbours->push_back(m_nodes[(_gridWidth*y) + x]);

          x = i + 1;
          y = j - 1;
          neighbours->push_back(m_nodes[(_gridWidth*y) + x]);

          x = i + 1;
          y = j;
          neighbours->push_back(m_nodes[(_gridWidth*y) + x]);

          x = i;
          y = j + 1;
          neighbours->push_back(m_nodes[(_gridWidth*y) + x]);
        }

        //Bottom left
        else
        {
          x = i;
          y = j - 1;
          neighbours->push_back(m_nodes[(_gridWidth*y) + x]);

          x = i + 1;
          y = j - 1;
          neighbours->push_back(m_nodes[(_gridWidth*y) + x]);

          x = i + 1;
          y = j;
          neighbours->push_back(m_nodes[(_gridWidth*y) + x]);
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
            neighbours->push_back(m_nodes[(_gridWidth*y) + x]);

            x = i;
            y = j + 1;
            neighbours->push_back(m_nodes[(_gridWidth*y) + x]);
          }

          //Lower top right
          if(i%2 != 0)
          {
            x = i - 1;
            y = j;
            neighbours->push_back(m_nodes[(_gridWidth*y) + x]);

            x = i - 1;
            y = j + 1;
            neighbours->push_back(m_nodes[(_gridWidth*y) + x]);

            x = i;
            y = j + 1;
            neighbours->push_back(m_nodes[(_gridWidth*y) + x]);
          }
        }

        //Mid right
        else if(j < _gridHeight-1)
        {
          x = i;
          y = j - 1;
          neighbours->push_back(m_nodes[(_gridWidth*y) + x]);

          x = i - 1;
          y = j;
          neighbours->push_back(m_nodes[(_gridWidth*y) + x]);

          x = i - 1;
          y = j + 1;
          neighbours->push_back(m_nodes[(_gridWidth*y) + x]);

          x = i;
          y = j + 1;
          neighbours->push_back(m_nodes[(_gridWidth*y) + x]);
        }

        //Bottom right
        else
        {
          //Bottom right upper
          if(i%2 == 0)
          {
            x = i - 1;
            y = j;
            neighbours->push_back(m_nodes[(_gridWidth*y) + x]);

            x = i - 1;
            y = j - 1;
            neighbours->push_back(m_nodes[(_gridWidth*y) + x]);

            x = i;
            y = j - 1;
            neighbours->push_back(m_nodes[(_gridWidth*y) + x]);
          }
          //Bottom right lower
          else
          {
            x = i;
            y = j - 1;
            neighbours->push_back(m_nodes[(_gridWidth*y) + x]);

            x = i - 1;
            y = j;
            neighbours->push_back(m_nodes[(_gridWidth*y) + x]);
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
          neighbours->push_back(m_nodes[(_gridWidth*y) + x]);

          x = i - 1;
          y = j + 1;
          neighbours->push_back(m_nodes[(_gridWidth*y) + x]);

          x = i;
          y = j + 1;
          neighbours->push_back(m_nodes[(_gridWidth*y) + x]);

          x = i + 1;
          y = j + 1;
          neighbours->push_back(m_nodes[(_gridWidth*y) + x]);

          x = i + 1;
          y = j;
          neighbours->push_back(m_nodes[(_gridWidth*y) + x]);
        }

        //Upper top
        else
        {
          x = i - 1;
          y = j;
          neighbours->push_back(m_nodes[(_gridWidth*y) + x]);

          x = i;
          y = j + 1;
          neighbours->push_back(m_nodes[(_gridWidth*y) + x]);

          x = i + 1;
          y = j;
          neighbours->push_back(m_nodes[(_gridWidth*y) + x]);
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
          neighbours->push_back(m_nodes[(_gridWidth*y) + x]);

          x = i;
          y = j - 1;
          neighbours->push_back(m_nodes[(_gridWidth*y) + x]);

          x = i + 1;
          y = j;
          neighbours->push_back(m_nodes[(_gridWidth*y) + x]);
        }

        //Upper bottom
        else
        {
          x = i - 1;
          y = j;
          neighbours->push_back(m_nodes[(_gridWidth*y) + x]);

          x = i - 1;
          y = j - 1;
          neighbours->push_back(m_nodes[(_gridWidth*y) + x]);

          x = i;
          y = j - 1;
          neighbours->push_back(m_nodes[(_gridWidth*y) + x]);

          x = i + 1;
          y = j - 1;
          neighbours->push_back(m_nodes[(_gridWidth*y) + x]);

          x = i + 1;
          y = j;
          neighbours->push_back(m_nodes[(_gridWidth*y) + x]);
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
          neighbours->push_back(m_nodes[(_gridWidth*y) + x]);

          x = i;
          y = j - 1;
          neighbours->push_back(m_nodes[(_gridWidth*y) + x]);

          x = i + 1;
          y = j;
          neighbours->push_back(m_nodes[(_gridWidth*y) + x]);

          x = i + 1;
          y = j + 1;
          neighbours->push_back(m_nodes[(_gridWidth*y) + x]);

          x = i;
          y = j + 1;
          neighbours->push_back(m_nodes[(_gridWidth*y) + x]);

          x = i - 1;
          y = j + 1;
          neighbours->push_back(m_nodes[(_gridWidth*y) + x]);
        }

        //enclosed even
        else
        {
          x = i - 1;
          y = j - 1;
          neighbours->push_back(m_nodes[(_gridWidth*y) + x]);

          x = i;
          y = j - 1;
          neighbours->push_back(m_nodes[(_gridWidth*y) + x]);

          x = i + 1;
          y = j - 1;
          neighbours->push_back(m_nodes[(_gridWidth*y) + x]);

          x = i + 1;
          y = j;
          neighbours->push_back(m_nodes[(_gridWidth*y) + x]);

          x = i;
          y = j + 1;
          neighbours->push_back(m_nodes[(_gridWidth*y) + x]);

          x = i - 1;
          y = j;
          neighbours->push_back(m_nodes[(_gridWidth*y) + x]);
        }
      }
      m_nodes[(j*_gridWidth) + i]->setChildList(neighbours);
    }
  }

//  for(int i = 0; i < m_nodes.size(); i++)
//  {
//    std::cout<<(*m_nodes[i]).getID()<< " has neighbours:"<<std::endl;
//    for(Node::NodeList::iterator it = m_nodes[i]->getChildList()->begin(); it != m_nodes[i]->getChildList()->end(); it++)
//    {
//      std::cout<<(*it)->getID()<<std::endl;
//    }
//    std::cout<<std::endl;
//  }

}

//-------------------------------------------------------------------//

NodeManagerPtr NodeManager::create(
    int _gridWidth,
    int _gridHeight,
    int _hexagonSize,
    ngl::Vec3 _origin)
{
  NodeManagerPtr a(new NodeManager(_gridWidth, _gridHeight, _hexagonSize, _origin));
  return a;
}

//-------------------------------------------------------------------//

NodeManager::~NodeManager()
{
  // default dtor
}

//-------------------------------------------------------------------//

void NodeManager::update()
{
  for(int i = 0; i < m_nodes.size(); i++)
  {
    m_nodes[i]->update();
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

void NodeManager::drawSelection()
{
  for(int i = 0; i < m_nodes.size(); i++)
  {
    m_nodes[i]->drawSelection();
  }
}

//-------------------------------------------------------------------//

Node::NodeList NodeManager::findPath(NodePtr _start, NodePtr _goal) const
{
  // From http://en.wikipedia.org/wiki/A*_search_algorithm
  // THIS FUNCTION COULD PROBABLY BE SIMPLIFIED

  // this keeps track of which nodes relate to which paths, this way we can
  // access PathNode data via the Node. This is useful as children are stored
  // as Nodes rather than path nodes
  std::map<NodePtr, PathNodePtr> allPathNodes;

  PathNodePtr start = PathNode::create(
                      _start,
                      0,
                      heuristicPath(_start, _goal)
                      );
  allPathNodes[_start] = start;
  PathNodeList closedSet;
  PathNodeList openSet;

  openSet.push_back(start);
  while(openSet.size() > 0)
  {
    // Current node to work on. This should be the node with the lowest fScore
    // in the openSet
    PathNodePtr current = *openSet.begin();

    // If we've found the goal
    if(current->m_node == _goal)
    {
      // Generate path and return
      Node::NodeList outputPath = reconstructPath(current, _start);
      return outputPath;
    }
    // Take current from openSet and move it into closedSet
    openSet.remove(current);
    closedSet.push_back(current);

    // Go through children of current
    Node::NodeListPtr children = current->m_node->getChildList();
    for(
        Node::NodeList::iterator it = children->begin();
        it != children->end();
        ++it)
    {
      if((*it)->isOccupied())
      {
        continue;
      }

      PathNodePtr child;
      //Get PathNode affiliated with node
      std::map<NodePtr, PathNodePtr>::iterator childIt = allPathNodes.find(*it);
      //If it couldn't find it create one and insert into map
      if(childIt == allPathNodes.end())
      {
        // Create an new PathNode that corresponds to the child node. (i.e put
        // it on the system)
        child = PathNode::create(*it, 0, 0);
        allPathNodes[*it] = child;
      }
      else
      {
        // Set child to the value in the iterator
        child = childIt->second;
      }
      if(checkListForNode(child, closedSet))
      {
        continue;
      }
      int tentativeGScore = child->m_gScore + m_centerDist;
      bool inOpenSet = checkListForNode(child, openSet);
      if(!inOpenSet || tentativeGScore <= child->m_gScore)
      {
        child->m_parent = current;
        child->m_gScore = tentativeGScore;
        child->m_fScore = tentativeGScore + heuristicPath(child->m_node, _goal);
        if(!inOpenSet)
        {
          //Add to openSet
          openSet.push_back(child);
        }
        //sort the set so that the top one will be chosen
        openSet.sort();
      }
    }
  }

  // Failed to find a valid path
  return Node::NodeList();
}

//-------------------------------------------------------------------//

float NodeManager::heuristicPath(NodePtr _start, NodePtr _goal) const
{

  ngl::Vec3 distVec =  _start->getPos() - _goal->getPos();
  // THIS SHOULD USE SQUARED DISTANCE FOR SPEED INCREASE
  return distVec.length();
}

Node::NodeList NodeManager::reconstructPath(
    PathNodePtr _current,
    NodePtr _start,
    Node::NodeList _currentList
    ) const
{
  // Add the current node to the list
  _currentList.push_back(_current->m_node);
  // if we've got back to the start
  if(_current->m_node == _start)
  {
    // Finish
    return _currentList;
  }
  // Keep searching from the parent
  _currentList = reconstructPath(_current->m_parent, _start, _currentList);
  return _currentList;
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

Node::NodeList NodeManager::findPathFromPos(
    ngl::Vec3 _start,
    ngl::Vec3 _goal) const
{
  //need to find the start and finish nodes in m_nodes from the vec3s.
  NodePtr start = getNodeFromPos(_start);
  NodePtr goal = getNodeFromPos(_goal);

  return findPath(start, goal);
}

NodePtr NodeManager::getNodeFromPos(ngl::Vec3 _pos) const
{
  std::cout<<std::endl;

  float x = _pos.m_x;
  float y = _pos.m_z;

  //clamp between values within the grid
  x = x < 0 ? 0 : (x > (m_gridWidth-1)*m_hexagonSize ? (m_gridWidth-1)*m_hexagonSize : x);
  y = y < 0 ? 0 : (y > (m_gridHeight-1)*(m_hexagonSize * (sqrt(3)/2)) ? (m_gridHeight-1)*(m_hexagonSize * (sqrt(3)/2)) : y);

  //transform into coordinate space
  x /= m_hexagonSize;
  y /= (m_hexagonSize*(sqrt(3)/2));

  //round to nearest int
  x = floor(x + 0.5);
  y = floor(y + 0.5);

  std::cout<<x<<std::endl;
  std::cout<<y<<std::endl;

  //calculate the index of the nearest based on x and y
  int index = (y * m_gridWidth) + x;

  std::cout<<_pos<< " closest is: ("<<x<<", "<<y<<") with coords: "<<(*m_nodes[index]).getPos()<<std::endl;

  return m_nodes[index];
}

NodePtr NodeManager::getNodeFromCoords(int _x, int _y) const
{
  return m_nodes[(_y*m_gridWidth) + _x];
}
