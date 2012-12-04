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

  static NodeManagerPtr create(int _gridWidth, int _gridHeight, int _hexagonSize);

  //-------------------------------------------------------------------//
  /// @brief default dtor
  //-------------------------------------------------------------------//

  ~NodeManager();

protected:

  //-------------------------------------------------------------------//
  /// @brief typedef for a list of nodes
  //-------------------------------------------------------------------//

  typedef std::list<NodePtr> NodeList;
  typedef boost::shared_ptr<std::list<NodePtr> > NodeChildListPtr;

protected:

  //-------------------------------------------------------------------//
  /// @brief list of nodes
  //-------------------------------------------------------------------//

  NodeList m_nodes;

private:

  //-------------------------------------------------------------------//
  /// @brief default ctor
  //-------------------------------------------------------------------//

  NodeManager(int _gridWidth, int _gridHeight, int _hexagonSize);
};

#endif // NODEMANAGER_H
