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

  static BasePtr create(NodePtr _linkedNode);

  void update();
  void draw();
  void drawSelection();
  void generateMesh();
  void destroy();

protected:

  //-------------------------------------------------------------------//
  /// @brief a parameterised constructor
  /// @param [in] _linkedNode, the node to place the base on
  //-------------------------------------------------------------------//

  Base(NodePtr _linkedNode);
};

#endif // BASE_H
