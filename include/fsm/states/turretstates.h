#ifndef TURRETSTATES_H
#define TURRETSTATES_H

#include "entity.h"
//-------------------------------------------------------------------//
/// @file turretstates.h
//-------------------------------------------------------------------//

//-------------------------------------------------------------------//
/// @brief Seek class, for when a turret is searching for a target
/// @author Peter May
/// @version 1
/// @date 26/02/2013
/// Revision History :
/// Initial Version 26/02/2013
/// @class Seek
//-------------------------------------------------------------------//

class Seek : public State
{
public: //methods
  //-------------------------------------------------------------------//
  /// @brief returns the static instance of the state machine
  //-------------------------------------------------------------------//

  static Seek * instance();

  //-------------------------------------------------------------------//
  /// @brief method called when the current state is entered
  /// @param [in] _turret, the turret which is moving into the state
  //-------------------------------------------------------------------//

  void enter (EntityWPtr _turret);

  //-------------------------------------------------------------------//
  /// @brief called every frame that the state is active
  /// @param [in] _turret, the turret which is in the current state
  //-------------------------------------------------------------------//

  void execute(EntityWPtr _turret);

  //-------------------------------------------------------------------//
  /// @brief called as the turret moves into a new state
  /// @param [in] _turret, the turret which is in the leaving the state
  //-------------------------------------------------------------------//

  void exit(EntityWPtr _turret);

private: //methods

  //-------------------------------------------------------------------//
  /// @brief private constructor
  //-------------------------------------------------------------------//

  Seek(){}
};

//-------------------------------------------------------------------//
/// @brief Approach class, for when a turret has found a target and
/// is spinning round to aim at it
/// @author Peter May
/// @version 1
/// @date 26/02/2013
/// Revision History :
/// Initial Version 26/02/2013
/// @class Approach
//-------------------------------------------------------------------//

class Approach : public State
{
public: //methods
  //-------------------------------------------------------------------//
  /// @brief returns the static instance of the state machine
  //-------------------------------------------------------------------//

  static Approach * instance();

  //-------------------------------------------------------------------//
  /// @brief method called when the current state is entered
  /// @param [in] _turret, the turret which is moving into the state
  //-------------------------------------------------------------------//

  void enter (EntityWPtr _turret);

  //-------------------------------------------------------------------//
  /// @brief called every frame that the state is active
  /// @param [in] _turret, the turret which is in the current state
  //-------------------------------------------------------------------//

  void execute(EntityWPtr _turret);

  //-------------------------------------------------------------------//
  /// @brief called as the turret moves into a new state
  /// @param [in] _turret, the turret which is in the leaving the state
  //-------------------------------------------------------------------//

  void exit(EntityWPtr _turret);

private: //methods

  //-------------------------------------------------------------------//
  /// @brief private constructor
  //-------------------------------------------------------------------//

  Approach(){}
};

//-------------------------------------------------------------------//
/// @brief LockOn class, for when a turret is aiming at an enemy
/// @author Peter May
/// @version 1
/// @date 26/02/2013
/// Revision History :
/// Initial Version 26/02/2013
/// @class LockOn
//-------------------------------------------------------------------//

class LockOn : public State
{
public:
  //-------------------------------------------------------------------//
  /// @brief returns the static instance of the state machine
  //-------------------------------------------------------------------//

  static LockOn * instance();

  //-------------------------------------------------------------------//
  /// @brief method called when the current state is entered
  /// @param [in] _turret, the turret which is moving into the state
  //-------------------------------------------------------------------//

  void enter (EntityWPtr _turret);

  //-------------------------------------------------------------------//
  /// @brief called every frame that the state is active
  /// @param [in] _turret, the turret which is in the current state
  //-------------------------------------------------------------------//

  void execute(EntityWPtr _turret);

  //-------------------------------------------------------------------//
  /// @brief called as the turret moves into a new state
  /// @param [in] _turret, the turret which is in the leaving the state
  //-------------------------------------------------------------------//

  void exit(EntityWPtr _turret);

private: //methods

  //-------------------------------------------------------------------//
  /// @brief private constructor
  //-------------------------------------------------------------------//

  LockOn(){}
};

//-------------------------------------------------------------------//
/// @brief first upgrade class
/// @author Jared Auty
/// @version 1
/// @date 27/02/2013
/// Revision History :
/// Initial Version 27/02/2013
/// @class BasicUpgrade
//-------------------------------------------------------------------//

class BasicUpgrade : public State
{
public:
  //-------------------------------------------------------------------//
  /// @brief returns the static instance of the state machine
  //-------------------------------------------------------------------//

  static BasicUpgrade * instance();

  //-------------------------------------------------------------------//
  /// @brief method called when the current state is entered
  /// @param [in] _turret, the turret which is moving into the state
  //-------------------------------------------------------------------//

  void enter (EntityWPtr _turret);

  //-------------------------------------------------------------------//
  /// @brief called every frame that the state is active
  /// @param [in] _turret, the turret which is in the current state
  //-------------------------------------------------------------------//

  void execute(EntityWPtr _turret);

  //-------------------------------------------------------------------//
  /// @brief called as the turret moves into a new state
  /// @param [in] _turret, the turret which is in the leaving the state
  //-------------------------------------------------------------------//

  void exit(EntityWPtr _turret);

private: //methods

  //-------------------------------------------------------------------//
  /// @brief private constructor
  //-------------------------------------------------------------------//

  BasicUpgrade(){}
};

//-------------------------------------------------------------------//
/// @brief second upgrade class
/// @author Jared Auty
/// @version 1
/// @date 27/02/2013
/// Revision History :
/// Initial Version 27/02/2013
/// @class AdvancedUpgrade
//-------------------------------------------------------------------//

class AdvancedUpgrade : public State
{
public:
  //-------------------------------------------------------------------//
  /// @brief returns the static instance of the state machine
  //-------------------------------------------------------------------//

  static AdvancedUpgrade * instance();

  //-------------------------------------------------------------------//
  /// @brief method called when the current state is entered
  /// @param [in] _turret, the turret which is moving into the state
  //-------------------------------------------------------------------//

  void enter (EntityWPtr _turret);

  //-------------------------------------------------------------------//
  /// @brief called every frame that the state is active
  /// @param [in] _turret, the turret which is in the current state
  //-------------------------------------------------------------------//

  void execute(EntityWPtr _turret);

  //-------------------------------------------------------------------//
  /// @brief called as the turret moves into a new state
  /// @param [in] _turret, the turret which is in the leaving the state
  //-------------------------------------------------------------------//

  void exit(EntityWPtr _turret);

private: //methods

  //-------------------------------------------------------------------//
  /// @brief private constructor
  //-------------------------------------------------------------------//

  AdvancedUpgrade(){}
};



#endif // TURRETSTATES_H

