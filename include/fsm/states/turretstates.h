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
  /// @brief returns the static instance of the state
  //-------------------------------------------------------------------//

  static Seek * instance();

  //-------------------------------------------------------------------//
  /// @brief method called when the current state is entered, empty
  /// method, implemented to satisfy pure virtual
  /// @param [in] _turret, the turret which is moving into the state,
  /// unused
  //-------------------------------------------------------------------//

  void enter (EntityWPtr _turret);

  //-------------------------------------------------------------------//
  /// @brief called every frame that the state is active, searches for a
  /// target
  /// @param [in] _turret, the turret which is in the current state
  //-------------------------------------------------------------------//

  void execute(EntityWPtr _turret);

  //-------------------------------------------------------------------//
  /// @brief called as the turret moves into a new state, empty
  /// method, implemented to satisfy pure virtual
  /// @param [in] _turret, the turret which is in the leaving the state,
  /// unused
  //-------------------------------------------------------------------//

  void exit(EntityWPtr _turret);

private: //methods

  //-------------------------------------------------------------------//
  /// @brief private constructor
  //-------------------------------------------------------------------//

  Seek(){}
};

//-------------------------------------------------------------------//
/// @brief LockedOn class, for when a turret is aiming at an enemy
/// @author Peter May
/// @version 1
/// @date 26/02/2013
/// Revision History :
/// Initial Version 26/02/2013
/// @class LockedOn
//-------------------------------------------------------------------//

class LockedOn : public State
{
public:
  //-------------------------------------------------------------------//
  /// @brief returns the static instance of the state
  //-------------------------------------------------------------------//

  static LockedOn * instance();

  //-------------------------------------------------------------------//
  /// @brief method called when the current state is entered, empty
  /// method, implemented to satisfy pure virtual
  /// @param [in] _turret, the turret which is moving into the state,
  /// unused
  //-------------------------------------------------------------------//

  void enter (EntityWPtr _turret);

  //-------------------------------------------------------------------//
  /// @brief called every frame that the state is active, aims towards the
  /// target and shoots
  /// @param [in] _turret, the turret which is in the current state
  //-------------------------------------------------------------------//

  void execute(EntityWPtr _turret);

  //-------------------------------------------------------------------//
  /// @brief called as the turret moves into a new state, empty
  /// method, implemented to satisfy pure virtual
  /// @param [in] _turret, the turret which is in the leaving the state,
  /// unused
  //-------------------------------------------------------------------//

  void exit(EntityWPtr _turret);

private: //methods

  //-------------------------------------------------------------------//
  /// @brief private constructor
  //-------------------------------------------------------------------//

  LockedOn(){}
};

//-------------------------------------------------------------------//
/// @brief first upgrade class
/// @author Jared Auty
/// @version 1
/// @date 27/02/2013
/// Revision History :
/// Initial Version 27/02/2013
/// @class TestTurretBasicUpgrade
//-------------------------------------------------------------------//

class TestTurretBasicUpgrade : public State
{
public:
  //-------------------------------------------------------------------//
  /// @brief returns the static instance of the state
  //-------------------------------------------------------------------//

  static TestTurretBasicUpgrade * instance();

  //-------------------------------------------------------------------//
  /// @brief method called when the current state is entered, empty
  /// method, implemented to satisfy pure virtual
  /// @param [in] _turret, the turret which is moving into the state,
  /// unused
  //-------------------------------------------------------------------//

  void enter (EntityWPtr _turret);

  //-------------------------------------------------------------------//
  /// @brief called every frame that the state is active, sets the
  /// upgrade level and relevant variables
  /// @param [in] _turret, the turret which is in the current state
  //-------------------------------------------------------------------//

  void execute(EntityWPtr _turret);

  //-------------------------------------------------------------------//
  /// @brief called as the turret moves into a new state, empty
  /// method, implemented to satisfy pure virtual
  /// @param [in] _turret, the turret which is in the leaving the state,
  /// unused
  //-------------------------------------------------------------------//

  void exit(EntityWPtr _turret);

private: //methods

  //-------------------------------------------------------------------//
  /// @brief private constructor
  //-------------------------------------------------------------------//

  TestTurretBasicUpgrade(){}
};

//-------------------------------------------------------------------//
/// @brief second upgrade class
/// @author Jared Auty
/// @version 1
/// @date 27/02/2013
/// Revision History :
/// Initial Version 27/02/2013
/// @class TestTurretAdvancedUpgrade
//-------------------------------------------------------------------//

class TestTurretAdvancedUpgrade : public State
{
public:
  //-------------------------------------------------------------------//
  /// @brief returns the static instance of the state
  //-------------------------------------------------------------------//

  static TestTurretAdvancedUpgrade * instance();

  //-------------------------------------------------------------------//
  /// @brief method called when the current state is entered, empty
  /// method, implemented to satisfy pure virtual
  /// @param [in] _turret, the turret which is moving into the state,
  /// unused
  //-------------------------------------------------------------------//

  void enter (EntityWPtr _turret);

  //-------------------------------------------------------------------//
  /// @brief called every frame that the state is active, sets the
  /// upgrade level and relevant variables
  /// @param [in] _turret, the turret which is in the current state
  //-------------------------------------------------------------------//

  void execute(EntityWPtr _turret);

  //-------------------------------------------------------------------//
  /// @brief called as the turret moves into a new state, empty
  /// method, implemented to satisfy pure virtual
  /// @param [in] _turret, the turret which is in the leaving the state,
  /// unused
  //-------------------------------------------------------------------//

  void exit(EntityWPtr _turret);

private: //methods

  //-------------------------------------------------------------------//
  /// @brief private constructor
  //-------------------------------------------------------------------//

  TestTurretAdvancedUpgrade(){}
};



#endif // TURRETSTATES_H

