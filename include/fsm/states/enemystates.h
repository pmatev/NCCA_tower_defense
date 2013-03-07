#ifndef ENEMYSTATES_H
#define ENEMYSTATES_H

#include "entity.h"
#include "fsm/state.h"
#include "smartpointers.h"

class TestEnemyNormal : public State
{
public:
  //----------------------------------------------------------------------------
  /// @brief returns the instance of the TestEnemyNormal state
  /// @param [in] _enemy the enemy whose using this state
  //----------------------------------------------------------------------------
  static TestEnemyNormal* instance();

  //----------------------------------------------------------------------------
  /// @brief called when the current state is changed to this state
  /// @param [in] _enemy the enemy whose using this state
  //----------------------------------------------------------------------------
  void enter(EntityWPtr _enemy);

  //----------------------------------------------------------------------------
  /// @brief called every frame the state is active
  /// @param [in] _enemy the enemy whose using this state
  //----------------------------------------------------------------------------
  void execute(EntityWPtr _enemy);

  //----------------------------------------------------------------------------
  /// @brief called just before the current state is changed to another
  /// @param [in] _enemy the enemy whose using this state
  //----------------------------------------------------------------------------
  void exit(EntityWPtr _enemy);

private:
  //----------------------------------------------------------------------------
  /// @brief private constructor
  //----------------------------------------------------------------------------
  TestEnemyNormal(){}
};

#endif // ENEMYSTATES_H
