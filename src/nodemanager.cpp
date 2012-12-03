#include "nodemanager.h"

//-------------------------------------------------------------------//

NodeManager::NodeManager()
{
  // create all the necessary nodes
}

//-------------------------------------------------------------------//

NodeManagerPtr NodeManager::create()
{
  NodeManagerPtr a(new NodeManager());
  return a;
}

//-------------------------------------------------------------------//

NodeManager::~NodeManager()
{
  // default dtor
}
