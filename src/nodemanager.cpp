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
      std::cout<<m_nodes.back()->getPos()<<std::endl;
    }
  }

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
