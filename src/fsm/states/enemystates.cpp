#include <iostream>
#include <stdlib.h>
#include <time.h>

#include "fsm/states/enemystates.h"
#include "enemy.h"


// TestEnemyNormal //
// ====== //

TestEnemyNormal* TestEnemyNormal::instance()
{
  static TestEnemyNormal instance;

  return &instance;
}

void TestEnemyNormal::enter(EntityWPtr _enemy)
{
  //q_unused to remove warnings
  Q_UNUSED(_enemy)
}

void TestEnemyNormal::execute(EntityWPtr _enemy)
{
  EntityPtr strong_entity = _enemy.lock();
  if(strong_entity)
  {
    DynamicEntityPtr dyn_entity = boost::dynamic_pointer_cast<DynamicEntity>(strong_entity);
    dyn_entity->getSteeringBehaviours()->enable("Seperation", 0.5, 3);
    dyn_entity->getSteeringBehaviours()->enable("ObstacleAvoidance", 1.0, 1);
    dyn_entity->getSteeringBehaviours()->enable("Cohesion", 0.5, 4);
    dyn_entity->getSteeringBehaviours()->enable("Alignment", 1.0, 5);
    dyn_entity->getSteeringBehaviours()->enable("FollowPath", 1.0, 2);
  }
}

void TestEnemyNormal::exit(EntityWPtr _enemy)
{
  //q_unused to remove warnings
  Q_UNUSED(_enemy)
}
