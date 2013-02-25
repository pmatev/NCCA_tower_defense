#include <iostream>
#include <stdlib.h>
#include <time.h>

#include "fsm/states/enemystates.h"
#include "enemy.h"


// Normal //
// ====== //

Normal* Normal::instance()
{
  static Normal instance;

  return &instance;
}

void Normal::enter(EntityWPtr _enemy)
{
}

void Normal::execute(EntityWPtr _enemy)
{
  EntityPtr strong_entity = _enemy.lock();
  if(strong_entity)
  {
    DynamicEntityPtr dyn_entity = boost::dynamic_pointer_cast<DynamicEntity>(strong_entity);
    dyn_entity->getSteeringBehaviours()->enable("FollowPath");
  }
}

void Normal::exit(EntityWPtr _enemy)
{
}
