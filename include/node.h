#ifndef NODE_H
#define NODE_H

#include <ngl/Vec3.h>
//-------------------------------------------------------------------//
/// @file node.h
/// @brief the class which represents each grid location on which a static
/// entity can be placed
/// @author Peter May
/// @version 1
/// @date 22/11/12
/// Revision History :
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
  /// @brief parameterised constructor
  /// @param [in] _posX, the X position with which to create the node
  /// @param [in] _posY, the Y position with which to create the node
  /// @param [in] _posZ, the Z position with which to create the node
  //-------------------------------------------------------------------//

  Node(float _posX, float _posY, float _posZ);

  //-------------------------------------------------------------------//
  /// @brief destructor
  //-------------------------------------------------------------------//

  ~Node();

  //-------------------------------------------------------------------//
  /// @brief get method for the m_isOccupied variable
  //-------------------------------------------------------------------//

  inline bool getIsOccupied() {return m_isOccupied;}

  //-------------------------------------------------------------------//
  /// @brief set method for the m_isOccupied variable
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

#endif // NODE_H
