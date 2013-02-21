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
DECLAREWEAKSMART(NodeManager)

class NodeManager
{
protected:

  //-------------------------------------------------------------------//
  /// @brief typedefs for dealing with path finding
  //-------------------------------------------------------------------//

  DECLARESMARTLIST(PathNode)

  //-------------------------------------------------------------------//
  /// @brief struct for use in pathFinding (basically just a wrapper for
  /// NodePtr)
  //-------------------------------------------------------------------//

  struct PathNode
  {
    NodePtr m_node;
    PathNodePtr m_parent;
    float m_gScore;
    float m_fScore;

    //-------------------------------------------------------------------//
    /// @brief creator
    /// @param[in] _node, node that it wraps around
    /// @param[in] _gScore, the score relative to how far from the start
    /// @param[in] _fScore, = _gScore + heuristicPathValue
    //-------------------------------------------------------------------//

    static PathNodePtr create(
          NodePtr _node,
          float _gScore,
          float _fScore
          )
    {
      PathNodePtr a(new PathNode(_node, _gScore, _fScore));
      return a;
    }
    inline bool operator<(const  PathNode &_test)
    {
      return m_fScore < _test.m_fScore;
    }

    //-------------------------------------------------------------------//
    /// @brief little wrapper so that we can sort lists of pointers
    //-------------------------------------------------------------------//

    inline static bool compare(
          const PathNodePtr &_first,
          const PathNodePtr &_second
          )
    {
      return (*_first) < (*_second);
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
          float _gScore,
          float _fScore
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

  static NodeManagerPtr create(
        int _gridWidth,
        int _gridHeight,
        int _hexagonSize,
        ngl::Vec3 _origin
        );

  //-------------------------------------------------------------------//
  /// @brief default dtor
  //-------------------------------------------------------------------//

  ~NodeManager();

  void update();

  void draw();

  //-------------------------------------------------------------------//
  /// @brief Find a path between two nodes ( A* search algorithm)
  //-------------------------------------------------------------------//

  bool getAStar(Node::NodeList &o_newPath, NodePtr _start, NodePtr _goal) const;

  //-------------------------------------------------------------------//
  /// @brief Wraps the getAStar method so that coordinates can be
  /// passed in instead of NodePtrs.
  //-------------------------------------------------------------------//

  bool findPathFromPos(Node::NodeList &o_newPath, ngl::Vec3 _start, ngl::Vec3 _goal) const;

  //-------------------------------------------------------------------//
  /// @brief Finds the NodePtr closest to the position passed in
  /// @param[in] _pos, the position to use
  /// @param[out] the node closest to the pos passed in
  //-------------------------------------------------------------------//

  NodePtr getNodeFromPos(ngl::Vec3 _pos) const;

  //-------------------------------------------------------------------//
  /// @brief Gets node from grid coords
  /// @param[in] _coords the coords to use
  /// @param[out] the node with grids coords _coords
  //-------------------------------------------------------------------//

  NodePtr getNodeFromCoords(int _x, int _y) const;

  void drawSelection();

protected:

  //-------------------------------------------------------------------//
  /// @brief Shortest possible distance between two nodes
  //-------------------------------------------------------------------//

  float heuristicPath(NodePtr _start, NodePtr _goal) const;

  //-------------------------------------------------------------------//
  /// @brief trace through node parents to create an ordered list of all
  /// the nodes within the path
  /// @param[in] _current, the current PathNode we are working on
  /// @param[in] _start, the smart pointer to the start node
  /// @param[in] _currentList, the current ordered list of all nodes within
  /// the path
  /// @param[out] the ordered list of nodes that make up the path
  //-------------------------------------------------------------------//

  void reconstructPath(
        Node::NodeList &io_newPath,
        NodeManager::PathNodePtr _current,
        NodePtr _start = NodePtr()
        ) const;

  //-------------------------------------------------------------------//
  /// @brief check a _list to see if it contains _node
  /// @param[in] _node, the node to search for
  /// @param[in] _list, the list to search in
  /// @param[out] whether it's contained in the list or not. true if
  /// contained, false if not
  //-------------------------------------------------------------------//

  bool checkListForNode(PathNodePtr _node, PathNodeList _list) const;


protected:

  //-------------------------------------------------------------------//
  /// @brief static member for caching hexagon factor sqrt(3)/2
  //-------------------------------------------------------------------//
  static float s_hexFactor;

  //-------------------------------------------------------------------//
  /// @brief list of nodes
  //-------------------------------------------------------------------//

  Node::NodeVec m_nodes;

  //-------------------------------------------------------------------//
  /// @brief size of hexagons
  //-------------------------------------------------------------------//

  int m_hexagonSize;

  //-------------------------------------------------------------------//
  /// @brief grid width
  //-------------------------------------------------------------------//

  int m_gridWidth;

  //-------------------------------------------------------------------//
  /// @brief grid height
  //-------------------------------------------------------------------//

  int m_gridHeight;

  //-------------------------------------------------------------------//
  /// @brief origin
  //-------------------------------------------------------------------//

  ngl::Vec3 m_origin;

  //-------------------------------------------------------------------//
  /// @brief distance between the centers of any two adjacent nodes
  //-------------------------------------------------------------------//

  float m_centerSqrDist;


private:

  //-------------------------------------------------------------------//
  /// @brief default ctor
  //-------------------------------------------------------------------//

  NodeManager(int _gridWidth, int _gridHeight, int _hexagonSize, ngl::Vec3 _origin);
};

#endif // NODEMANAGER_H
