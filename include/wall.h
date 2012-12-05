#ifndef WALL_H
#define WALL_H

#include "staticentity.h"

//-------------------------------------------------------------------//
/// @file wall.h
/// @brief a class for the wall objects
/// @author Peter May
/// @version 1
/// @date 4/12/12
/// Revision History :
/// Initial Version 4/12/12
/// @class Wall
//-------------------------------------------------------------------//

DECLARESMART(Wall)

class Wall : public StaticEntity
{
public:
  //-------------------------------------------------------------------//
  /// @brief a parameterised constructor
  /// @param [in] _linkedNodes, a reference to an stl vector of boost
  /// shared pointers to the nodes that are covered by the static entity
  /// @param [in] _pos, a vector containing the initial position in 3D
  /// space of the entity
  //-------------------------------------------------------------------//

  Wall(
        NodePtr _linkedNode
        );
};

#endif // WALL_H
