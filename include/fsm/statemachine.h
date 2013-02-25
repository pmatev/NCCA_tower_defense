#ifndef STATEMACHINE_H
#define STATEMACHINE_H

#include "state.h"
#include "entity.h"

class StateMachine
{
public:
  //----------------------------------------------------------------------------
  /// @brief ctor
  /// @param [in] _owner the parent entity
  //----------------------------------------------------------------------------
  StateMachine(EntityWPtr _owner);
  //----------------------------------------------------------------------------
  /// @brief update is called every frame by the entity
  //----------------------------------------------------------------------------
  void update();
  //----------------------------------------------------------------------------
  /// @brief sets the initial current state
  /// @param [in] _s the state to set to
  //----------------------------------------------------------------------------
  void setCurrentState(State* _state);
  //----------------------------------------------------------------------------
  /// @brief sets the initial global state
  /// @param [in] _s the state to set to
  //----------------------------------------------------------------------------
  void setGlobalState(State* _state);
  //----------------------------------------------------------------------------
  /// @brief sets the initial previous state
  /// @param [in] _s the state to set to
  //----------------------------------------------------------------------------
  void setPreviousState(State* _state);
  //----------------------------------------------------------------------------
  /// @brief changes the state
  /// @param [in] _s the state to set to
  //----------------------------------------------------------------------------
  void changeState(State* _state);

protected:
  //----------------------------------------------------------------------------
  /// @brief the owner of this state machine
  //----------------------------------------------------------------------------
  EntityWPtr m_owner;

  //----------------------------------------------------------------------------
  /// @brief the currently active state
  //----------------------------------------------------------------------------
  State* m_currentState;

  //----------------------------------------------------------------------------
  /// @brief the global state is called every frame, regardless of the currently
  /// active state.
  //----------------------------------------------------------------------------
  State* m_globalState;

  //----------------------------------------------------------------------------
  /// @brief the previously active state.
  //----------------------------------------------------------------------------
  State* m_previousState;
};



#endif // STATEMACHINE_H
