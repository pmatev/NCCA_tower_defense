#ifndef NODE_H
#define NODE_H

#include <boost/shared_ptr.hpp>

#include <ngl/Vec3.h>

//-------------------------------------------------------------------//
/// @file node.h
/// @brief the class which represents each grid location on which a static
/// entity can be placed
/// @author Peter May
/// @version 1.1
/// @date 23/11/12
/// Revision History :
/// 1.1 removed unnecessary ctor 23/11/12
/// Initial Version 22/11/12
/// @class Node
//-------------------------------------------------------------------//

class Node
{
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
  /// @brief get method for the m_isOccupied variable
  /// @param [out]m_isOccupied, returns a boolean stating whether the
  /// node is occupied or not
  //-------------------------------------------------------------------//

  inline bool getIsOccupied() const {return m_isOccupied;}

  //-------------------------------------------------------------------//
  /// @brief set method for the m_isOccupied variable
  /// @param [in] _isOccupied, a boolean value to set the occupied flag
  /// to
  //-------------------------------------------------------------------//

  inline void setIsOccupied(bool _isOccupied) {m_isOccupied = _isOccupied;}

private:
  //-------------------------------------------------------------------//
  /// @brief The position in 3D space of the node
  //-------------------------------------------------------------------//

  ngl::Vec3 m_pos;

  //-------------------------------------------------------------------//
  /// @brief A boolean flag stating whether the node is occupied or
  /// not
  //-------------------------------------------------------------------//

  bool m_isOccupied;

};

typedef boost::shared_ptr<Node> NodePtr;

#endif // NODE_H
