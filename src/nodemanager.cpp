#include "nodemanager.h"

//-------------------------------------------------------------------//

NodeManager::NodeManager(int _gridWidth, int _gridHeight, int _hexagonSize)
{
  // create all the necessary node
  for(int i = 0; i < _gridWidth; i++)
  {
    for(int j = 0; j < _gridHeight; j++)
    {
      NodePtr node(new Node(ngl::Vec3(i * _hexagonSize, 0, j * (_hexagonSize * (sqrt(3)/2)))));
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
          neighbours->push_back(m_nodes[(_gridWidth*x) + y]);

          x = i;
          y = j + 1;
          neighbours->push_back(m_nodes[(_gridWidth*x) + y]);
        }

        //Mid left
        else if(j < _gridHeight-1)
        {
          x = i;
          y = j - 1;
          neighbours->push_back(m_nodes[(_gridWidth*x) + y]);

          x = i + 1;
          y = j - 1;
          neighbours->push_back(m_nodes[(_gridWidth*x) + y]);

          x = i + 1;
          y = j;
          neighbours->push_back(m_nodes[(_gridWidth*x) + y]);

          x = i;
          y = j + 1;
          neighbours->push_back(m_nodes[(_gridWidth*x) + y]);
        }

        //Bottom left
        else
        {
          x = i;
          y = j - 1;
          neighbours->push_back(m_nodes[(_gridWidth*x) + y]);

          x = i + 1;
          y = j - 1;
          neighbours->push_back(m_nodes[(_gridWidth*x) + y]);

          x = i + 1;
          y = j;
          neighbours->push_back(m_nodes[(_gridWidth*x) + y]);
        }
      }

      //Right
      else if(i == _gridWidth-1)
      {
        //Top right
        if(j == 0)
        {
          x = i - 1;
          y = j;
          neighbours->push_back(m_nodes[(_gridWidth*x) + y]);

          x = i;
          y = j + 1;
          neighbours->push_back(m_nodes[(_gridWidth*x) + y]);
        }

        //Mid right
        else if(j < _gridHeight-1)
        {
          x = i;
          y = j - 1;
          neighbours->push_back(m_nodes[(_gridWidth*x) + y]);

          x = i - 1;
          y = j - 1;
          neighbours->push_back(m_nodes[(_gridWidth*x) + y]);

          x = i - 1;
          y = j;
          neighbours->push_back(m_nodes[(_gridWidth*x) + y]);

          x = i;
          y = j + 1;
          neighbours->push_back(m_nodes[(_gridWidth*x) + y]);
        }

        //Bottom right
        else
        {
          x = i - 1;
          y = j;
          neighbours->push_back(m_nodes[(_gridWidth*x) + y]);

          x = i - 1;
          y = j - 1;
          neighbours->push_back(m_nodes[(_gridWidth*x) + y]);

          x = i;
          y = j - 1;
          neighbours->push_back(m_nodes[(_gridWidth*x) + y]);
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
          neighbours->push_back(m_nodes[(_gridWidth*x) + y]);

          x = i - 1;
          y = j + 1;
          neighbours->push_back(m_nodes[(_gridWidth*x) + y]);

          x = i;
          y = j + 1;
          neighbours->push_back(m_nodes[(_gridWidth*x) + y]);

          x = i + 1;
          y = j + 1;
          neighbours->push_back(m_nodes[(_gridWidth*x) + y]);

          x = i + 1;
          y = j;
          neighbours->push_back(m_nodes[(_gridWidth*x) + y]);
        }

        //Upper top
        else
        {
          x = i - 1;
          y = j;
          neighbours->push_back(m_nodes[(_gridWidth*x) + y]);

          x = i;
          y = j + 1;
          neighbours->push_back(m_nodes[(_gridWidth*x) + y]);

          x = i + 1;
          y = j;
          neighbours->push_back(m_nodes[(_gridWidth*x) + y]);
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
          neighbours->push_back(m_nodes[(_gridWidth*x) + y]);

          x = i;
          y = j - 1;
          neighbours->push_back(m_nodes[(_gridWidth*x) + y]);

          x = i + 1;
          y = j;
          neighbours->push_back(m_nodes[(_gridWidth*x) + y]);
        }

        //Upper bottom
        else
        {
          x = i - 1;
          y = j;
          neighbours->push_back(m_nodes[(_gridWidth*x) + y]);

          x = i - 1;
          y = j - 1;
          neighbours->push_back(m_nodes[(_gridWidth*x) + y]);

          x = i;
          y = j - 1;
          neighbours->push_back(m_nodes[(_gridWidth*x) + y]);

          x = i + 1;
          y = j + 1;
          neighbours->push_back(m_nodes[(_gridWidth*x) + y]);

          x = i + 1;
          y = j;
          neighbours->push_back(m_nodes[(_gridWidth*x) + y]);
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
          neighbours->push_back(m_nodes[(_gridWidth*x) + y]);

          x = i;
          y = j - 1;
          neighbours->push_back(m_nodes[(_gridWidth*x) + y]);

          x = i + 1;
          y = j;
          neighbours->push_back(m_nodes[(_gridWidth*x) + y]);

          x = i + 1;
          y = j + 1;
          neighbours->push_back(m_nodes[(_gridWidth*x) + y]);

          x = i;
          y = j + 1;
          neighbours->push_back(m_nodes[(_gridWidth*x) + y]);

          x = i - 1;
          y = j + 1;
          neighbours->push_back(m_nodes[(_gridWidth*x) + y]);
        }

        //enclosed even
        else
        {
          x = i - 1;
          y = j;
          neighbours->push_back(m_nodes[(_gridWidth*x) + y]);

          x = i;
          y = j - 1;
          neighbours->push_back(m_nodes[(_gridWidth*x) + y]);

          x = i + 1;
          y = j;
          neighbours->push_back(m_nodes[(_gridWidth*x) + y]);

          x = i + 1;
          y = j + 1;
          neighbours->push_back(m_nodes[(_gridWidth*x) + y]);

          x = i;
          y = j + 1;
          neighbours->push_back(m_nodes[(_gridWidth*x) + y]);

          x = i - 1;
          y = j + 1;
          neighbours->push_back(m_nodes[(_gridWidth*x) + y]);
        }
      }


      m_nodes[(i*_gridWidth) + j]->setChildList(neighbours);
    }
  }

//  for(int i = 0; i < m_nodes.size(); i++)
//  {
//    std::cout<<m_nodes[i]->getID() << " has pos: " << m_nodes[i]->getPos() << " with neighbours: " <<std::endl;

//    for(Node::NodeList::iterator j = m_nodes[i]->getChildList()->begin(); j != m_nodes[i]->getChildList()->end(); j++)
//    {
//      std::cout<<(*j)->getID() << std::endl;
//    }
//  }

}

//-------------------------------------------------------------------//

NodeManagerPtr NodeManager::create(int _gridWidth, int _gridHeight, int _hexagonSize)
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


  int distBetweenNodes = 1;
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
    PathNodePtr current = *(openSet.begin());

    // If we've found the goal
    if(current->m_node == _goal)
    {
      // Generate path and return
      return reconstructPath(current, _start, Node::NodeList());
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
        // GSCORE AND FSCORE NEED TO BE CALCULATED HERE
        child = PathNode::create(*it, 0, 0);
        allPathNodes[*it] = child;
      }
      else
      {
        child = childIt->second;
      }
      if(checkListForNode(child, closedSet));
      {
        continue;
      }
      int tentativGScore = child->m_gScore + distBetweenNodes;
      bool inOpenSet = checkListForNode(child, openSet);
      if(!inOpenSet || tentativGScore <= child->m_fScore)
      {
        child->m_parent = current;
        child->m_gScore = tentativGScore;
        child->m_fScore = tentativGScore + heuristicPath(child->m_node, _goal);
        if(!inOpenSet)
        {
          //Add to openSet
          openSet.push_back(child);
          //REMEMBER TO SORT openSet
          openSet.sort();
        }
      }
    }
  }
}

//-------------------------------------------------------------------//

int NodeManager::heuristicPath(NodePtr _start, NodePtr _goal) const
{
  // To be implemented
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
  if(_current->m_parent->m_node == _start)
  {
    // Finish
    return _currentList;
  }
  // Keep searching from the parent
  _currentList = reconstructPath(_current->m_parent, _start, _currentList);
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
