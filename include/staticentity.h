#ifndef STATICENTITY_H
#define STATICENTITY_H

#include <boost/shared_ptr.hpp>
#include <vector>

#include "entity.h"
#include "node.h"

//-------------------------------------------------------------------//
/// @file staticentity.h
/// @brief The base class for all un-moving renderable objects in the
/// game
/// @author Peter May
/// @version 1
/// @date 23/11/12
/// Revision History :
/// Initial Version 23/11/12
/// @class StaticEntity
//-------------------------------------------------------------------//

class StaticEntity : public Entity
{
public:
  //-------------------------------------------------------------------//
  /// @brief a parameterised constructor
  /// @param [in] _linkedNodes, a reference to an stl vector of boost
  /// shared pointers to the nodes that are covered by the static entity
  /// @param [in] _pos, a vector containing the initial position in 3D
  /// space of the entity
  /// @param [in] _health, the initial health value of the entity
  //-------------------------------------------------------------------//

  StaticEntity(
      std::vector<NodePtr> & _linkedNodes,
      const ngl::Vec3 & _pos,
      float _health
      );

  //-------------------------------------------------------------------//
  /// @brief destructor
  //-------------------------------------------------------------------//

  ~StaticEntity();

  //-------------------------------------------------------------------//
  /// @brief a method to increment the level of the static entity
  //-------------------------------------------------------------------//

  inline void incrementLevel () {m_level++;}

  //-------------------------------------------------------------------//
  /// @brief a method to decrement the level of the static entity
  //-------------------------------------------------------------------//

  inline void decrementLevel () {m_level--;}

protected:
  //-------------------------------------------------------------------//
  /// @brief The upgrade level of the static entity
  //-------------------------------------------------------------------//

  float m_level;

  //-------------------------------------------------------------------//
  /// @brief a list of pointers to the nodes that are covered by the
  /// static entity
  //-------------------------------------------------------------------//

  std::vector<NodePtr> m_linkedNodes;
};

typedef boost::shared_ptr<StaticEntity> StaticEntityPtr;

#endif // STATICENTITY_H
