#ifndef MISSILESILOSTATE_H
#define MISSILESILOSTATE_H

#include "entity.h"

//-------------------------------------------------------------------//
/// @file missilesilostates.h
/// @author Jared Auty
/// @version 1
/// @date 7/3/13
/// Revision History :
/// Initial Version 7/3/13
/// @class MissileSiloNormal
//-------------------------------------------------------------------//

//-------------------------------------------------------------------//
/// @brief default state for grenade silo
//-------------------------------------------------------------------//

class MissileSiloNormal : public State
{
public:
  //-------------------------------------------------------------------//
  /// @brief returns the static instance of the state machine
  //-------------------------------------------------------------------//

  static MissileSiloNormal * instance();

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

private:
  //-------------------------------------------------------------------//
  /// @brief private constructor
  //-------------------------------------------------------------------//

  MissileSiloNormal(){}

};

//-------------------------------------------------------------------//
/// @brief default state for grenade silo
//-------------------------------------------------------------------//

class MissileSiloSeek : public State
{
public:
  //-------------------------------------------------------------------//
  /// @brief returns the static instance of the state machine
  //-------------------------------------------------------------------//

  static MissileSiloSeek * instance();

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

private:
  //-------------------------------------------------------------------//
  /// @brief private constructor
  //-------------------------------------------------------------------//

  MissileSiloSeek(){}

};

//-------------------------------------------------------------------//
/// @brief first upgrade class
/// @author Jared Auty
/// @version 1
/// @date 27/02/2013
/// Revision History :
/// Initial Version 27/02/2013
/// @class MissileSiloBasicUpgrade
//-------------------------------------------------------------------//

class MissileSiloBasicUpgrade : public State
{
public:
  //-------------------------------------------------------------------//
  /// @brief returns the static instance of the state machine
  //-------------------------------------------------------------------//

  static MissileSiloBasicUpgrade * instance();

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

  MissileSiloBasicUpgrade(){}
};

//-------------------------------------------------------------------//
/// @brief second upgrade class
/// @author Jared Auty
/// @version 1
/// @date 27/02/2013
/// Revision History :
/// Initial Version 27/02/2013
/// @class MissileSiloAdvancedUpgrade
//-------------------------------------------------------------------//

class MissileSiloAdvancedUpgrade : public State
{
public:
  //-------------------------------------------------------------------//
  /// @brief returns the static instance of the state machine
  //-------------------------------------------------------------------//

  static MissileSiloAdvancedUpgrade * instance();

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

  MissileSiloAdvancedUpgrade(){}
};


#endif // MISSILESILOSTATE_H
