#ifndef NODE_H
#define NODE_H

#include <ngl/Vec3.h>

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

  typedef std::list<NodeWPtr> NodeWList;
  typedef std::vector<NodeWPtr> NodeWVec;
  typedef std::vector<NodePtr> NodeVec;

  typedef boost::shared_ptr<NodeWList> NodeWListPtr;

public:
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
  /// @param [in] _dt, the timestep
  //-------------------------------------------------------------------//
  void update(const double _dt);

  //-------------------------------------------------------------------//
  /// @brief virtual draw method
  //-------------------------------------------------------------------//
  void draw() ;

  //-------------------------------------------------------------------//
  /// @brief virtual draw selection method
  //-------------------------------------------------------------------//
  void drawSelection() ;

  //-------------------------------------------------------------------//
  /// @brief get method for the m_isOccupied variable
  /// @param [out]m_isOccupied, returns a boolean stating whether the
  /// node is occupied or not
  //-------------------------------------------------------------------//

  inline bool isOccupied() const {return m_isOccupied;}

  //-------------------------------------------------------------------//
  /// @brief set method for the m_isOccupied variable
  /// @param [in] _isOccupied, a boolean value to set the occupied flag
  /// to
  //-------------------------------------------------------------------//

  inline void setOccupied(bool _isOccupied) {m_isOccupied = _isOccupied;}

  //-------------------------------------------------------------------//
  /// @brief get the list of children that a node is linked to
  /// @param [out] m_children, list of child nodes
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

protected:
  //-------------------------------------------------------------------//
  /// @brief parameterised constructor
  /// @param [in] _pos, a const reference to an ngl vector containing the
  /// position with which to create the node
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



};

#endif // NODE_H
