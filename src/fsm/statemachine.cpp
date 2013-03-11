#include "fsm/statemachine.h"

StateMachine::StateMachine(EntityWPtr _owner):
  m_owner(_owner),
  m_currentState(0),
  m_globalState(0),
  m_previousState(0)
{
}

void StateMachine::update()
{
  if(m_globalState)
  {
    m_globalState->execute(m_owner);
  }

  if(m_currentState)
  {
    m_currentState->execute(m_owner);
  }
}

void StateMachine::setCurrentState(State* _state)
{
  m_currentState = _state;
}

void StateMachine::setGlobalState(State* _state)
{
  m_globalState = _state;

}

void StateMachine::setPreviousState(State* _state)
{
  m_previousState = _state;
}

void StateMachine::changeState(State* _state)
{
  //record the current state
  m_previousState = m_currentState;
  m_currentState->exit(m_owner);
  m_currentState = _state;
  m_currentState->enter(m_owner);
}

void StateMachine::changeToPreviousState()
{
  changeState(m_previousState);
}

StateMachine::~StateMachine()
{
  std::cout<<"Deleting state machine"<<std::endl;
}
