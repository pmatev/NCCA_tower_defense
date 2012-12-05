#include "nodemanager.h"

//-------------------------------------------------------------------//

NodeManager::NodeManager(int _gridWidth, int _gridHeight, int _hexagonSize) :
  m_centerDist(_hexagonSize * 1.732)
{
  // create all the necessary node
  for(int i = 0; i < _gridWidth; i++)
  {
    for(int j = 0; j < _gridHeight; j++)
    {
      NodePtr node(
            new Node(
              ngl::Vec3(i * _hexagonSize, 0,
                        j * (_hexagonSize * (sqrt(3)/2))
                        )
              )
            );
      m_nodes.push_back(node);
    }
  }

  //loop through again and set neighbours
  for(int i = 0; i < _gridWidth; i++)
  {
    for(int j = 0; j < _gridHeight; j++)
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
          y = j - 1;
          neighbours->push_back(m_nodes[(_gridWidth*y) + x]);

          x = i - 1;
          y = j;
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
        if(i%2 != 2)
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
        if(i%2 != 2)
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
          y = j + 1;
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
}

//-------------------------------------------------------------------//

NodeManagerPtr NodeManager::create(
    int _gridWidth,
    int _gridHeight,
    int _hexagonSize)
{
  NodeManagerPtr a(new NodeManager(_gridWidth, _gridHeight, _hexagonSize));
  return a;
}

//-------------------------------------------------------------------//

NodeManager::~NodeManager()
{
  // default dtor
}

//-------------------------------------------------------------------//

Node::NodeList NodeManager::pathFind(NodePtr _start, NodePtr _goal) const
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
