#ifndef NODE_H
#define NODE_H


#include "ngl/Vec3.h"
#include "smartpointers.h"
#include "entity.h"

//-------------------------------------------------------------------//
/// @file node.h
/// @brief the class which represents each grid location on which a static
/// entity can be placed
/// @author Peter May, Jared Auty
/// @version 1.2
/// @date 3/12/12
/// Revision History :
/// Implementing node traversal functionality 3/12/12
/// Initial Version 22/11/12
/// @class Node
//-------------------------------------------------------------------//

DECLARESMART(Node)

class Node : public Entity
{

public:

  //-------------------------------------------------------------------//
  /// @brief typedefs for list of nodes
  //-------------------------------------------------------------------//

  //-------------------------------------------------------------------//
  /// @brief typedef for list of weak pointers to nodes
  //-------------------------------------------------------------------//
  typedef std::list<NodeWPtr> NodeWList;

  //-------------------------------------------------------------------//
  /// @brief typedef for vector of weak pointers to nodes
  //-------------------------------------------------------------------//
  typedef std::vector<NodeWPtr> NodeWVec;

  //-------------------------------------------------------------------//
  /// @brief typedef for vector of smart pointers to nodes
  //-------------------------------------------------------------------//
  typedef std::vector<NodePtr> NodeVec;

  //-------------------------------------------------------------------//
  /// @brief typedef for smart pointer to list of weak pointers to nodes
  //-------------------------------------------------------------------//
  typedef boost::shared_ptr<NodeWList> NodeWListPtr;

  //-------------------------------------------------------------------//
  /// @brief typedef for smart pointer to vector of weak pointers to nodes
  //-------------------------------------------------------------------//
  typedef boost::shared_ptr<NodeWVec> NodeWVecPtr;

  //-------------------------------------------------------------------//
  /// @brief typedef for weak pointer to list of weak pointers to nodes
  //-------------------------------------------------------------------//
  typedef boost::weak_ptr<NodeWVec> NodeWVecWPtr;

public:

  //-------------------------------------------------------------------//
    /// @brief creator
    /// @param[in] _pos position of node
    /// @param[in] _hexagonSize size of hexagon to render
    //-------------------------------------------------------------------//
  static NodePtr create(const ngl::Vec3 &_pos, float _hexagonSize);

  //-------------------------------------------------------------------//
  /// @brief destructor
  //-------------------------------------------------------------------//

  ~Node();

  //-------------------------------------------------------------------//
  /// @brief virtual generate mesh method
  //-------------------------------------------------------------------//
  void generateMesh();


  //-------------------------------------------------------------------//
  /// @brief virtual update method
  /// @param [in] _dt the timestep in seconds
  //-------------------------------------------------------------------//
  void update(const double _dt);

  //-------------------------------------------------------------------//
  /// @brief get method for the m_isOccupied variable
  /// @return m_isOccupied returns a boolean stating whether the
  /// node is occupied or not
  //-------------------------------------------------------------------//

  inline bool isOccupied() const {return m_isOccupied;}

  //-------------------------------------------------------------------//
  /// @brief set method for the m_isOccupied variable
  /// @param [in] _isOccupied a boolean value to set the occupied flag
  /// to
  //-------------------------------------------------------------------//

  inline void setOccupied(bool _isOccupied) {m_isOccupied = _isOccupied;}

  //-------------------------------------------------------------------//
  /// @brief get the list of children that a node is linked to
  /// @return m_children list of child nodes
  //-------------------------------------------------------------------//

  inline NodeWListPtr getChildList() {return m_children;}

  //-------------------------------------------------------------------//
  /// @brief set the list of children that a node is linked to
  /// @param [in] _children, list of child nodes
  //-------------------------------------------------------------------//

  inline void setChildList(NodeWListPtr _children) {m_children = _children;}

  //-------------------------------------------------------------------//
  /// @brief destroy method
  //-------------------------------------------------------------------//

  void destroy();

  //-------------------------------------------------------------------//
  /// @brief return wether the node has been found during this search
  //-------------------------------------------------------------------//

  inline bool isFound() const {return m_isFound;}

  //-------------------------------------------------------------------//
  /// @brief tell the node that it has been found
  /// @param[in] _found whether the node has been found or not
  //-------------------------------------------------------------------//

  inline void setFound(bool _found) {m_isFound = _found;}

  //-------------------------------------------------------------------//
  /// @brief find goal search depth of the node (how far to the goal)
  //-------------------------------------------------------------------//

  inline int getSearchDepth() const {return m_searchDepth;}

  //-------------------------------------------------------------------//
  /// @brief set the new search depth for the node
  /// @param[in] _searchDepth new search depth
  //-------------------------------------------------------------------//

  inline void setSearchDepth(int _searchDepth) {m_searchDepth = _searchDepth;}

  //-------------------------------------------------------------------//
  /// @brief is the node in any spawn paths
  //-------------------------------------------------------------------//

  inline bool isInSpawnPath() const {return m_isInSpawnPath;}

  //-------------------------------------------------------------------//
  /// @brief set whether the node is in one of the spawn paths
  /// @param[in] _isInSpawnPath whether the node is in the spawn path or not.
  /// This can be useful for displaying spawn paths
  //-------------------------------------------------------------------//

  inline void setInSpawnPath(bool _isInSpawnPath)
  {
    m_isInSpawnPath = _isInSpawnPath;
  }

  //-------------------------------------------------------------------//
  /// @brief reset the node's path details. This should be run on all nodes
  /// before search depths are calculated.
  //-------------------------------------------------------------------//

  void resetSearchInfo();

  //-------------------------------------------------------------------//
  /// @brief shortcut the prepare for update because it does nothing
  //-------------------------------------------------------------------//
  inline void prepareForUpdate(){;}

  //-------------------------------------------------------------------//
  /// @brief overload drawing so that we can set highlighting based on node
  /// state.
  //-------------------------------------------------------------------//

  void draw();

  //-------------------------------------------------------------------//
  /// @brief geneerate view box
  //-------------------------------------------------------------------//
  void generateViewBBox();

  //-------------------------------------------------------------------//
  /// @brief change the node's visibility
  //-------------------------------------------------------------------//

  void setVisibility(bool _visibility);


protected:
  //-------------------------------------------------------------------//
  /// @brief filter view. This does nothing at the moment
  //-------------------------------------------------------------------//
  void filterViewVolume(EntityRecordWCList &o_localEntities);

  //-------------------------------------------------------------------//
  /// @brief parameterised constructor
  /// @param[in] _pos position of node
  /// @param[in] _hexagonSize size of hexagon to render
  /// @param[in] _id ID of entity
  //-------------------------------------------------------------------//

  Node(const ngl::Vec3 & _pos, float _hexagonSize, unsigned int _id);

protected:
  //-------------------------------------------------------------------//
  /// @brief A boolean flag stating whether the node is occupied or
  /// not
  //-------------------------------------------------------------------//

  bool m_isOccupied;

  //-------------------------------------------------------------------//
  /// @brief List of children for traversal
  //-------------------------------------------------------------------//

  NodeWListPtr m_children;

  //-------------------------------------------------------------------//
  /// @brief Size of the hexagon this node represents
  //-------------------------------------------------------------------//

  float m_hexagonSize;



  //-------------------------------------------------------------------//
  /// @brief whether the node should draw or not
  //-------------------------------------------------------------------//

  bool m_isVisible;

  // PATH FINDING

  //-------------------------------------------------------------------//
  /// @brief has this node been recursed during the current search
  //-------------------------------------------------------------------//

  bool m_isFound;

  //-------------------------------------------------------------------//
  /// @brief ammount of nodes between this node and the goal
  //-------------------------------------------------------------------//

  int m_searchDepth;

  //-------------------------------------------------------------------//
  /// @brief whether the node is in any of the paths between a spawn point
  /// and the base
  //-------------------------------------------------------------------//

  bool m_isInSpawnPath;

};

#endif // NODE_H
