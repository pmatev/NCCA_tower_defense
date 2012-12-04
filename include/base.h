#ifndef BASE_H
#define BASE_H

#include "staticentity.h"

//-------------------------------------------------------------------//
/// @file base.h
/// @brief a class for the base objects
/// @author Peter May
/// @version 1
/// @date 4/12/12
/// Revision History :
/// Initial Version 4/12/12
/// @class Base
//-------------------------------------------------------------------//

class Base : public StaticEntity
{
public:
  //-------------------------------------------------------------------//
  /// @brief a parameterised constructor
  /// @param [in] _linkedNodes, a reference to an stl vector of boost
  /// shared pointers to the nodes that are covered by the static entity
  /// @param [in] _pos, a vector containing the initial position in 3D
  /// space of the entity
  //-------------------------------------------------------------------//

  Base(
      std::vector<NodePtr> & _linkedNodes,
      const ngl::Vec3 & _pos
      );
};

#endif // BASE_H
