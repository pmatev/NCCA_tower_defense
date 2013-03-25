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

DECLARESMART(Base)

class Base : public StaticEntity
{
public: //methods
  //-------------------------------------------------------------------//
  /// @brief a parameterised creator
  /// @param [in] _linkedNode the node to place the base on
  /// @param [in] _id the unique identifier for the base
  //-------------------------------------------------------------------//

  static BasePtr create(NodePtr _linkedNode, unsigned int _id);

  //-------------------------------------------------------------------//
  /// @brief a method to initialise the statemachine for the base
  //-------------------------------------------------------------------//

  void stateInit();

  //-------------------------------------------------------------------//
  /// @brief the update loop for the base, empty but implemented to satisfy
  /// pure virtual requirements
  /// @param [in] _dt unused, chasnge in time
  //-------------------------------------------------------------------//

  inline void update(const double _dt) {Q_UNUSED(_dt);}

  //-------------------------------------------------------------------//
  /// @brief empty method, implemented to satisfy pure virtual requirements
  /// @param [in] o_localEntities unused input
  //-------------------------------------------------------------------//

  void filterViewVolume(EntityRecordWCList &o_localEntities);

  //-------------------------------------------------------------------//
  /// @brief a method to generate the view box
  //-------------------------------------------------------------------//

  void generateViewBBox();

  //-------------------------------------------------------------------//
  /// @brief a method to draw the base's mesh
  //-------------------------------------------------------------------//

  void draw();

protected: //methods

  //-------------------------------------------------------------------//
  /// @brief a parameterised constructor
  /// @param [in] _linkedNode the node to place the base on
  //-------------------------------------------------------------------//

  Base(NodePtr _linkedNode, unsigned int _id);
};

#endif // BASE_H
