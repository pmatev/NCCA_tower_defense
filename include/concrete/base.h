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
public:
  //-------------------------------------------------------------------//
  /// @brief a parameterised creator
  /// @param [in] _linkedNode, the node to place the base on
  //-------------------------------------------------------------------//

  static BasePtr create(NodePtr _linkedNode, unsigned int _id);

  void stateInit();
  void update(const double _dt);
//  void draw();
//  void drawSelection();
  void generateMesh();
  void filterViewVolume(EntityRecordWCList &o_localEntities);

  //-------------------------------------------------------------------//
  /// @brief a method to generate the view box
  //-------------------------------------------------------------------//

  void generateViewBBox();

protected:

  //-------------------------------------------------------------------//
  /// @brief a parameterised constructor
  /// @param [in] _linkedNode, the node to place the base on
  //-------------------------------------------------------------------//

  Base(NodePtr _linkedNode, unsigned int _id);
};

#endif // BASE_H
