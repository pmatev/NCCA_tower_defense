#ifndef PROJECTILESTATES_H
#define PROJECTILESTATES_H

#include "entity.h"

//-------------------------------------------------------------------//
/// @file projectilestates.h
//-------------------------------------------------------------------//

//-------------------------------------------------------------------//
/// @brief move class, for when a bullet is moving
/// @author Peter May
/// @version 1
/// @date 26/02/2013
/// Revision History :
/// Initial Version 26/02/2013
/// @class Move
//-------------------------------------------------------------------//

class Move : public State
{
public: //methods
  //-------------------------------------------------------------------//
  /// @brief returns the static instance of the state machine
  //-------------------------------------------------------------------//

  static Move * instance();

  //-------------------------------------------------------------------//
  /// @brief method called when the current state is entered
  /// @param [in] _turret, the turret which is moving into the state
  //-------------------------------------------------------------------//

  void enter (EntityWPtr _projectile);

  //-------------------------------------------------------------------//
  /// @brief called every frame that the state is active
  /// @param [in] _turret, the turret which is in the current state
  //-------------------------------------------------------------------//

  void execute(EntityWPtr _projectile);

  //-------------------------------------------------------------------//
  /// @brief called as the turret moves into a new state
  /// @param [in] _turret, the turret which is in the leaving the state
  //-------------------------------------------------------------------//

  void exit(EntityWPtr _projectile);

private: //methods

  //-------------------------------------------------------------------//
  /// @brief private constructor
  //-------------------------------------------------------------------//

  Move(){}
};

#endif // PROJECTILESTATES_H
