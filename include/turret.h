#ifndef TURRET_H
#define TURRET_H

#include "staticentity.h"
#include <string>


//-------------------------------------------------------------------//
/// @file turret.h
/// @brief The class for all turrets, static renderable objects with a
/// brain and a view area
/// @author Peter May, Jared Auty
/// @version 1
/// @date 23/11/12
/// Revision History :
/// Initial Version 23/11/12
/// @class Turret
//-------------------------------------------------------------------//

DECLARESMART(Turret)

class Turret : public StaticEntity
{
public:
  //-------------------------------------------------------------------//
  /// @brief a parameterised constructor
  /// @param [in] _fov, a float value defining the field of view of the
  /// turret
  /// @param [in] _viewDistance, a float value defining how far the turret
  /// can see
  /// @param [in] _maxRotationSpeed, float value defining how fast a
  /// turret can rotate
  /// @param [in] _aim, a reference to an ngl vector which defines the
  /// initial aim vector of the turret
  /// @param [in] _linkedNodes, a reference to an stl vector of boost
  /// shared pointers to the nodes that are covered by the static entity
  /// @param [in] _pos, a vector containing the initial position in 3D
  /// space of the entity
  //-------------------------------------------------------------------//

  Turret(
        NodePtr _linkedNode,
        unsigned int _id,
        std::string _projectileType
        );

  //-------------------------------------------------------------------//
  /// @brief destructor
  //-------------------------------------------------------------------//

  ~Turret();

  //-------------------------------------------------------------------//
  /// @brief updates the turret, taking the value returned by brain() into
  /// account.
  /// @param [in] _dt, the timestep
  //-------------------------------------------------------------------//

  void update(const double _dt);

  //-------------------------------------------------------------------//
  /// @brief brain must be implemented in concrete types and returns the
  /// new aim
  /// @param[in] aim vector
  //-------------------------------------------------------------------//

  virtual ngl::Vec3 brain() = 0;

  //-------------------------------------------------------------------//
  /// @brief a method to fire a projectile
  //-------------------------------------------------------------------//

  void fire();

protected:

  //-------------------------------------------------------------------//
  /// @brief value to define the field of view of the turret
  //-------------------------------------------------------------------//

  float m_fov;

  //-------------------------------------------------------------------//
  /// @brief value to define how far a turret can see
  //-------------------------------------------------------------------//

  float m_viewDistance;

  //-------------------------------------------------------------------//
  /// @brief value to define the max rotation speed
  //-------------------------------------------------------------------//

  float m_maxRotationSpeed;

  //-------------------------------------------------------------------//
  /// @brief vector defining the aim vector of the turret
  //-------------------------------------------------------------------//

  ngl::Vec3 m_aim;

  //-------------------------------------------------------------------//
  /// @brief a string to store the type of projectile that the turret shoots
  //-------------------------------------------------------------------//

  std::string m_projectileType;
};

#endif // TURRET_H
