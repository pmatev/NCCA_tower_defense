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
  /// @brief returns the static instance of the state
  //-------------------------------------------------------------------//

  static Move * instance();

  //-------------------------------------------------------------------//
  /// @brief method called when the current state is entered, currently empty,
  /// implemented to satisfy pure virtual
  /// @param [in] _projectile the projectile which is moving into the state,
  /// unused
  //-------------------------------------------------------------------//

  void enter (EntityWPtr _projectile);

  //-------------------------------------------------------------------//
  /// @brief called every frame that the state is active, currently empty,
  /// implemented to satisfy pure virtual
  /// @param [in] _projectile the projectile which is in the current state,
  /// unused
  //-------------------------------------------------------------------//

  void execute(EntityWPtr _projectile);

  //-------------------------------------------------------------------//
  /// @brief called as the projectile moves into a new state, currently empty,
  /// implemented to satisfy pure virtual
  /// @param [in] _projectile the projectile which is in the leaving the state,
  /// unused
  //-------------------------------------------------------------------//

  void exit(EntityWPtr _projectile);

private: //methods

  //-------------------------------------------------------------------//
  /// @brief private constructor
  //-------------------------------------------------------------------//

  inline Move(){} //currently using default
};

#endif // PROJECTILESTATES_H
