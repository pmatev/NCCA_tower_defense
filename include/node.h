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

  typedef std::list<NodePtr> NodeList;
  typedef std::vector<NodePtr> NodeVec;

  typedef boost::shared_ptr<NodeList> NodeListPtr;

public:
  //-------------------------------------------------------------------//
  /// @brief parameterised constructor
  /// @param [in] _pos, a const reference to an ngl vector containing the
  /// position with which to create the node
  //-------------------------------------------------------------------//

  Node(const ngl::Vec3 & _pos);

  //-------------------------------------------------------------------//
  /// @brief destructor
  //-------------------------------------------------------------------//

  ~Node();

  //-------------------------------------------------------------------//
  /// @brief virtual update method
  //-------------------------------------------------------------------//
  void update();

  //-------------------------------------------------------------------//
  /// @brief virtual draw method
  //-------------------------------------------------------------------//
  void draw() const;

  //-------------------------------------------------------------------//
  /// @brief virtual draw selection method
  //-------------------------------------------------------------------//
  void drawSelection() const;

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

  inline NodeListPtr getChildList() {return m_children;}

  //-------------------------------------------------------------------//
  /// @brief set the list of children that a node is linked to
  /// @param [in] _children, list of child nodes
  //-------------------------------------------------------------------//
  inline void setChildList(NodeListPtr _children) {m_children = _children;}


protected:
  //-------------------------------------------------------------------//
  /// @brief A boolean flag stating whether the node is occupied or
  /// not
  //-------------------------------------------------------------------//

  bool m_isOccupied;

  //-------------------------------------------------------------------//
  /// @brief List of children for traversal
  //-------------------------------------------------------------------//

  NodeListPtr m_children;


};

#endif // NODE_H
