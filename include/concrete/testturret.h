#ifndef TESTTURRET_H
#define TESTTURRET_H

#include "turret.h"
#include "smartpointers.h"

//-------------------------------------------------------------------//
/// @file testturret.h
/// @brief CONCRETE TYPE This is a simple example of a TestTurret class
/// @author Jared Auty
/// @version 1
/// @date 6/12/12
/// Revision History :
/// Initial Version 6/12/12
/// @class TestTurret
//-------------------------------------------------------------------//

DECLARESMART(TestTurret)

class TestTurret : public Turret
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

  static EntityPtr create(
        NodePtr _linkedNode,
        unsigned int _id
        );

  void generateMesh();

  //-------------------------------------------------------------------//
  /// @brief draw the object
  //-------------------------------------------------------------------//

  void draw();

  //-------------------------------------------------------------------//
  /// @brief draw the selection
  //-------------------------------------------------------------------//
  void drawSelection();

protected:

  //-------------------------------------------------------------------//
  /// @brief a parameterised ctor
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

  TestTurret(
        NodePtr _linkedNode,
        unsigned int &_id
        );

  //-------------------------------------------------------------------//
  /// @brief works out what the turret should do
  //-------------------------------------------------------------------//

  ngl::Vec3 brain();
};



#endif // TESTTURRET_H
