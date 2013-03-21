#include "include/fsm/states/projectilestates.h"

//-------------------------------------------------------------------//

Move * Move::instance()
{
  static Move MoveInstance;

  return &MoveInstance;
}

//-------------------------------------------------------------------//

void Move::enter(EntityWPtr _projectile)
{
  Q_UNUSED(_projectile);
}

//-------------------------------------------------------------------//

void Move::execute(EntityWPtr _projectile)
{
  Q_UNUSED(_projectile)
}

//-------------------------------------------------------------------//

void Move::exit(EntityWPtr _projectile)
{
  Q_UNUSED(_projectile);
}

//-------------------------------------------------------------------//
