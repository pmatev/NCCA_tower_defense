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

  DECLARESMARTLIST(PathNode)

  //-------------------------------------------------------------------//
  /// @brief struct for use in pathFinding (basically just a wrapper for
  /// NodePtr)
  //-------------------------------------------------------------------//

  struct PathNode
  {
    NodeWPtr m_node;
    PathNodeWPtr m_parent;
    PathNodeWPtr m_child;
    float m_gScore;
    float m_fScore;
    bool m_hasSuccessfulPath;
    float m_successfulPathFScore;

    //-------------------------------------------------------------------//
    /// @brief creator
    /// @param[in] _node, node that it wraps around
    /// @param[in] _gScore, the score relative to how far from the start
    /// @param[in] _fScore, = _gScore + heuristicPathValue
    //-------------------------------------------------------------------//

    static PathNodePtr create(
          NodeWPtr _node,
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
    inline bool operator==(const NodeWPtr _nodeTest)
    {
      NodePtr node = m_node.lock();
      NodePtr nodeTest = _nodeTest.lock();
      if(node && nodeTest)
      {
        return node == nodeTest;
      }
      return false;
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
          NodeWPtr _node,
          float _gScore,
          float _fScore
          ):
      m_node(_node),
      m_parent(),
      m_child(),
      m_gScore(_gScore),
      m_fScore(_fScore),
      m_hasSuccessfulPath(false)
    {}
  };

public:
  //-------------------------------------------------------------------//
  /// @brief creator
  //-------------------------------------------------------------------//

  static NodeManagerPtr create(
        int _gridWidth,
        int _gridHeight,
        float _hexagonSize,
        ngl::Vec3 _origin,
        int _dbGridSizeX,
        int _dbGridSizeZ
        );

  //-------------------------------------------------------------------//
  /// @brief default dtor
  //-------------------------------------------------------------------//

  ~NodeManager();

  void update(const double _dt);

  void draw();

  void resetPathNodes();

  //-------------------------------------------------------------------//
  /// @brief recalculate the search depth for each node. This should be run
  /// whenever a static entity is put down or removed. The search tree is
  /// stored in the nodes themselves in the form of int values (number of hops
  /// till goal) and is used when calculating new paths.
  //-------------------------------------------------------------------//

  void recalculateSearchTree(NodeWPtr _goal);

  //-------------------------------------------------------------------//
  /// @brief Find a path between two nodes ( A* search algorithm)
  //-------------------------------------------------------------------//

  bool getAStar(Node::NodeWList &o_newPath, NodeWPtr _start, NodeWPtr _goal);

  //-------------------------------------------------------------------//
  /// @brief Find a path between two nodes using search tree
  //-------------------------------------------------------------------//

  bool getSearchTreePath(Node::NodeWList &o_newPath, NodeWPtr _start, NodeWPtr _goal);

  //-------------------------------------------------------------------//
  /// @brief Wraps the getAStar method so that coordinates can be
  /// passed in instead of NodePtrs.
  //-------------------------------------------------------------------//

  bool findPathFromPos(Node::NodeWList &o_newPath, ngl::Vec3 _start, ngl::Vec3 _goal);

  //-------------------------------------------------------------------//
  /// @brief Finds the NodePtr closest to the position passed in
  /// @param[in] _pos, the position to use
  /// @param[out] the node closest to the pos passed in
  //-------------------------------------------------------------------//

  NodeWPtr getNodeFromPos(ngl::Vec3 _pos) const;

  //-------------------------------------------------------------------//
  /// @brief Gets node from grid coords
  /// @param[in] _coords the coords to use
  /// @param[out] the node with grids coords _coords
  //-------------------------------------------------------------------//

  NodeWPtr getNodeFromCoords(int _x, int __z) const;

  void drawSelection();

  //-------------------------------------------------------------------//
  /// @brief set all spawn path booleans to false
  //-------------------------------------------------------------------//

  void clearSpawnPathHighlighting();

protected:
  //-------------------------------------------------------------------//
  /// @brief traverse node tree from _node and continue the search on the
  /// child with best search depth.
  /// @param[out] o_newPath add to this list as you go.
  /// @param[in] _depth current depth
  /// @param[in] _node current node we are working on
  //-------------------------------------------------------------------//

  bool traverseChildren(
        Node::NodeWList &o_newPath,
        NodeWPtr _goal,
        NodeWPtr _current,
        bool _isStart = true
        );

  //-------------------------------------------------------------------//
  /// @brief Create the map between nodes and their path-finding counterparts
  //-------------------------------------------------------------------//

  void createPathNodes();

  //-------------------------------------------------------------------//
  /// @brief Shortest possible distance between two nodes
  //-------------------------------------------------------------------//

  float heuristicPath(PathNodeWPtr _start, PathNodeWPtr _goal) const;

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
        Node::NodeWList &io_newPath,
        NodeManager::PathNodeWPtr _current,
        NodeWPtr _start = NodeWPtr(),
        float _fScore = 0.0f
        ) const;

  //-------------------------------------------------------------------//
  /// @brief trace through node children to create an ordered list of all
  /// the nodes within the path from the current point to the goal. This
  /// is used so that path finding can share cached paths between nodes.
  /// @param[in] _current, the current PathNode we are working on
  /// @param[in] _start, the smart pointer to the start node
  /// @param[in] _currentList, the current ordered list of all nodes within
  /// the path
  /// @param[out] the ordered list of nodes that make up the path
  //-------------------------------------------------------------------//

  void reconstructOptimisedPath(
        Node::NodeWList &io_newPath,
        NodeManager::PathNodeWPtr _current,
        NodeWPtr _goal = NodeWPtr()
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

  typedef std::map<NodeWPtr, PathNodePtr> PathNodeMap;

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
  /// @brief map of nodes to path nodes. Path nodes are used as a wrapper
  /// around nodes to give extra functionality for path finding.
  //-------------------------------------------------------------------//

  std::map<NodeWPtr, PathNodePtr> m_pathNodeMap;

  //-------------------------------------------------------------------//
  /// @brief all the path nodes. These are used for path finding.
  //-------------------------------------------------------------------//

  PathNodeList m_pathNodes;

  //-------------------------------------------------------------------//
  /// @brief size of hexagons
  //-------------------------------------------------------------------//

  float m_hexagonSize;

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

  NodeManager(int _gridWidth,
              int _gridHeight,
              float _hexagonSize,
              ngl::Vec3 _origin,
              int _dbGridSizeX,
              int _dbGridSizeZ);
};

#endif // NODEMANAGER_H
