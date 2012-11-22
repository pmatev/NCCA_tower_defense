#ifndef DYNAMICENTITY_H
#define DYNAMICENTITY_H

#include "entity.h"

//-------------------------------------------------------------------//
/// @file dynamicentity.h
/// @brief The base class for all moving renderable objects in the
/// game
/// @author Peter May
/// @version 1
/// @date 22/11/12
/// Revision History :
/// Initial Version 22/11/12
/// @class DynamicEntity
//-------------------------------------------------------------------//

class DynamicEntity : public Entity
{
public:
  //-------------------------------------------------------------------//
  /// @brief a parameterised constructor
  /// @param [in] _damage, a float to initialise the damage value
  /// @param [in] _aimVector, a vector to initialise the aim vector
  /// @param [in] __maxVelocity, a float value describing the maximum
  /// velocity of the dynamic entity
  /// @param [in] _pos, a vector containing the initial position in 3D
  /// space of the entity, passed to the entity constructor
  /// @param [in] _health, the initial health value of the entity,
  /// passed to the entity constructor
  //-------------------------------------------------------------------//

  DynamicEntity(
      float _damage,
      const ngl::vec3 & _aimVector,
      float _maxVelocity,
      const ngl::Vec3 & _pos,
      float _health
      );

  //-------------------------------------------------------------------//
  /// @brief the destructor
  //-------------------------------------------------------------------//

  ~DynamicEntity();

  //-------------------------------------------------------------------//
  /// @brief a virtual brain method, to be implemented in children
  //-------------------------------------------------------------------//

  virtual ngl::Vec3 brain() = 0;

private:
  //-------------------------------------------------------------------//
  /// @brief a damage value for the dynamic entity
  //-------------------------------------------------------------------//

  float m_damage;

  //-------------------------------------------------------------------//
  /// @brief The the aim vector of the dynamic entity
  //-------------------------------------------------------------------//

  ngl::Vec3 m_aimVector;

  //-------------------------------------------------------------------//
  /// @brief The maximum velocity of the dynamic entity
  //-------------------------------------------------------------------//

  float m_maxVelocity;
};

#endif // DYNAMICENTITY_H
