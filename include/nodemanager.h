#ifndef NODEMANAGER_H
#define NODEMANAGER_H

//-------------------------------------------------------------------//
/// @file nodemanager.h
/// @brief This class manages all the nodes that make up the ground map
/// @author Jared Auty
/// @version 1
/// @date 3/12/12
/// Revision History :
/// Initial Version 3/12/12
/// @class NodeManager
//-------------------------------------------------------------------//

#include "smartpointers.h"

#include "node.h"

DECLARESMART(NodeManager)

class NodeManager
{
public:
  //-------------------------------------------------------------------//
  /// @brief creator
  //-------------------------------------------------------------------//

  static NodeManagerPtr create();

  //-------------------------------------------------------------------//
  /// @brief default dtor
  //-------------------------------------------------------------------//

  ~NodeManager();

protected:

  //-------------------------------------------------------------------//
  /// @brief typedef for a list of nodes
  //-------------------------------------------------------------------//

  typedef std::list<NodePtr> NodeList;

protected:

  //-------------------------------------------------------------------//
  /// @brief list of nodes
  //-------------------------------------------------------------------//

  NodeList m_nodes;

private:

  //-------------------------------------------------------------------//
  /// @brief default ctor
  //-------------------------------------------------------------------//

  NodeManager();
};

#endif // NODEMANAGER_H
