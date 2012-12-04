#ifndef NODEMANAGER_H
#define NODEMANAGER_H

//-------------------------------------------------------------------//
/// @file nodemanager.h
/// @brief This class manages all the nodes that make up the ground map.
/// This has functionality for path finding.
/// @author Jared Auty
/// @version 1
/// @date 3/12/12
/// Revision History :
/// Initial Version 3/12/12
/// @class NodeManager
/// @struct PathNode
//-------------------------------------------------------------------//

#include "smartpointers.h"

#include "node.h"

DECLARESMART(NodeManager)

class NodeManager
{
protected:

  //-------------------------------------------------------------------//
  /// @brief typedefs for dealing with path finding
  //-------------------------------------------------------------------//

  DECLARESMART(PathNode)

  typedef std::list<PathNodePtr> PathNodeList;

  //-------------------------------------------------------------------//
  /// @brief struct for use in pathFinding (basically just a wrapper for
  /// NodePtr)
  //-------------------------------------------------------------------//

  struct PathNode
  {
    NodePtr m_node;
    PathNodePtr m_parent;
    int m_gScore;
    int m_fScore;

    //-------------------------------------------------------------------//
    /// @brief creator
    /// @param[in] _node, node that it wraps around
    /// @param[in] _gScore, the score relative to how far from the start
    /// @param[in] _fScore, = _gScore + heuristicPathValue
    //-------------------------------------------------------------------//

    static PathNodePtr create(
          NodePtr _node,
          int _gScore,
          int _fScore
          )
    {
      PathNodePtr a(new PathNode(_node, _gScore, _fScore));
      return a;
    }
    inline bool operator<(const  PathNodePtr &_test)
    {
      return m_fScore > _test->m_fScore;
    }

  protected:


    //-------------------------------------------------------------------//
    /// @brief ctor
    /// @param[in] _node, node that it wraps around
    /// @param[in] _gScore, the score relative to how far from the start
    /// @param[in] _fScore, = _gScore + heuristicPathValue
    //-------------------------------------------------------------------//

    PathNode(
          NodePtr _node,
          int _gScore,
          int _fScore
          ):
      m_node(_node),
      m_parent(),
      m_gScore(_gScore),
      m_fScore(_fScore)
    {}
  };

public:
  //-------------------------------------------------------------------//
  /// @brief creator
  //-------------------------------------------------------------------//

  static NodeManagerPtr create(int _gridWidth, int _gridHeight, int _hexagonSize);

  //-------------------------------------------------------------------//
  /// @brief default dtor
  //-------------------------------------------------------------------//

  ~NodeManager();

  //-------------------------------------------------------------------//
  /// @brief Find a path between two nodes ( A* search algorithm)
  //-------------------------------------------------------------------//

  Node::NodeList pathFind(NodePtr _start, NodePtr _goal) const;

protected:

  //-------------------------------------------------------------------//
  /// @brief Shortest possible distance between two nodes
  //-------------------------------------------------------------------//

  int heuristicPath(NodePtr _start, NodePtr _goal) const;

  //-------------------------------------------------------------------//
  /// @brief trace through node parents to create an ordered list of all
  /// the nodes within the path
  /// @param[in] _current, the current PathNode we are working on
  /// @param[in] _start, the smart pointer to the start node
  /// @param[in] _currentList, the current ordered list of all nodes within
  /// the path
  /// @param[out] the ordered list of nodes that make up the path
  //-------------------------------------------------------------------//

  Node::NodeList reconstructPath(
        PathNodePtr _current,
        NodePtr _start,
        Node::NodeList _currentList
        ) const;

  bool checkListForNode(PathNodePtr _node, PathNodeList _list) const;


//  //-------------------------------------------------------------------//
//  /// @brief find the PathNode that stores _node as it's node.
//  /// @param[in] _node, node to look for
//  /// @param[in] _list, list to look through for node
//  /// @param[out] the ordered list of nodes that make up the path
//  //-------------------------------------------------------------------//
//  PathNodePtr findPathNode(NodePtr _node, PathNodeList _list);


protected:

  //-------------------------------------------------------------------//
  /// @brief list of nodes
  //-------------------------------------------------------------------//

  Node::NodeVec m_nodes;


private:

  //-------------------------------------------------------------------//
  /// @brief default ctor
  //-------------------------------------------------------------------//

  NodeManager(int _gridWidth, int _gridHeight, int _hexagonSize);
};

#endif // NODEMANAGER_H