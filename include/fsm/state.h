#ifndef STATE_H
#define STATE_H

#include "fwd/entity.h"

class State
{
public:
  inline State(){;}

  //----------------------------------------------------------------------------------------------------------------------
  /// @brief enter is called when the state is first set
  /// @param [in] _entity_type pointer to the enemy who contains the state
  /// machine that this state belongs to.
  //----------------------------------------------------------------------------------------------------------------------
  virtual void enter(EntityWPtr _entity)=0;

  //----------------------------------------------------------------------------------------------------------------------
  /// @brief execute is called every frame the state is active
  /// @param [in] _entity_type pointer to the enemy who contains the state
  /// machine that this state belongs to.
  //----------------------------------------------------------------------------------------------------------------------
  virtual void execute(EntityWPtr _entity)=0;

  //----------------------------------------------------------------------------------------------------------------------
  /// @brief exit is called just before the state is replaced
  /// @param [in] _entity_type pointer to the enemy who contains the state
  /// machine that this state belongs to.
  //----------------------------------------------------------------------------------------------------------------------
  virtual void exit(EntityWPtr _entity)=0;
};

#endif // STATE_H
