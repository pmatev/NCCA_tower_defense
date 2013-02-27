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
  //q_unused to remove warnings
  Q_UNUSED(_enemy)
}

void Normal::execute(EntityWPtr _enemy)
{
  EntityPtr strong_entity = _enemy.lock();
  if(strong_entity)
  {
    DynamicEntityPtr dyn_entity = boost::dynamic_pointer_cast<DynamicEntity>(strong_entity);
    dyn_entity->getSteeringBehaviours()->enable("ObstacleAvoidance", 1.0, 2);
    //dyn_entity->getSteeringBehaviours()->enable("Cohesion");
    //dyn_entity->getSteeringBehaviours()->enable("Alignment");
    dyn_entity->getSteeringBehaviours()->enable("FollowPath", 1.0, 1);
  }
}

void Normal::exit(EntityWPtr _enemy)
{
  //q_unused to remove warnings
  Q_UNUSED(_enemy)
}
