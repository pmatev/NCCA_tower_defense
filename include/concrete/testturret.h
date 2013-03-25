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
  /// @param [in] _linkedNodes a reference to an stl vector of boost
  /// shared pointers to the nodes that are covered by the static entity
  /// @param[in] _id ID of entity
  //-------------------------------------------------------------------//

  static EntityPtr create(
        NodePtr _linkedNode,
        unsigned int _id
        );

  //-------------------------------------------------------------------//
  /// @brief initialise state values
  //-------------------------------------------------------------------//
  void stateInit();

  //-------------------------------------------------------------------//
  /// @brief a method to generate the view box
  //-------------------------------------------------------------------//

  void generateViewBBox();

  //-------------------------------------------------------------------//
  /// @brief draw function
  //-------------------------------------------------------------------//
  void draw();

protected:

  //-------------------------------------------------------------------//
  /// @brief filter the view volume
  /// @param[out] o_localEntities the list of local entities to be edited
  //-------------------------------------------------------------------//
  void filterViewVolume(EntityRecordWCList &o_localEntities);

  //-------------------------------------------------------------------//
  /// @brief a parameterised ctor
  /// @param [in] _linkedNodes a reference to an stl vector of boost
  /// shared pointers to the nodes that are covered by the static entity
  /// @param[in] _id ID of entity
  //-------------------------------------------------------------------//

  TestTurret(
        NodePtr _linkedNode,
        unsigned int _id
        );

  //-------------------------------------------------------------------//
  /// @brief works out what the turret should do
  //-------------------------------------------------------------------//

  ngl::Vec3 brain();

  //-------------------------------------------------------------------//
  /// @brief a method to update the shot position
  //-------------------------------------------------------------------//

  void updateShotPos();
};



#endif // TESTTURRET_H
