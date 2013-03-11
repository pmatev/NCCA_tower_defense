#include "include/fsm/states/missilesilostate.h"
#include "turret.h"
#include "concrete/missilesilo.h"
#include "game.h"

//-------------------------------------------------------------------//

MissileSiloNormal * MissileSiloNormal::instance()
{
  static MissileSiloNormal normalInstance;
  return &normalInstance;
}

//-------------------------------------------------------------------//

void MissileSiloNormal::enter(EntityWPtr _turret)
{
  Q_UNUSED(_turret);
}

//-------------------------------------------------------------------//

void MissileSiloNormal::execute(EntityWPtr _turret)
{
  EntityPtr strongEntity = _turret.lock();
  // if the pointer exists
  if (strongEntity)
  {
    //cast strong entity pointer to a turret pointer
    MissileSiloPtr turretptr = boost::dynamic_pointer_cast<MissileSilo>(strongEntity);
    if (turretptr)
    {
      if(!turretptr->getHasTarget())
      {
        turretptr->getStateMachine()->changeState(MissileSiloSeek::instance());
      }
      else
      {
        if (turretptr->getShotWaitTime() <= turretptr->getDtSinceShot())
        {
          //set the doShot boolean to true
          turretptr->setDoShot(true);
        }
      }
    }
  }
}

//-------------------------------------------------------------------//

void MissileSiloNormal::exit(EntityWPtr _turret)
{
  Q_UNUSED(_turret);
}

//-------------------------------------------------------------------//

MissileSiloSeek * MissileSiloSeek::instance()
{
  static MissileSiloSeek normalInstance;
  return &normalInstance;
}

//-------------------------------------------------------------------//

void MissileSiloSeek::enter(EntityWPtr _turret)
{
  Q_UNUSED(_turret);
}

//-------------------------------------------------------------------//

void MissileSiloSeek::execute(EntityWPtr _turret)
{
  EntityPtr strongEntity = _turret.lock();
  // if the pointer exists
  if (strongEntity)
  {
    //cast strong entity pointer to a turret pointer
    MissileSiloPtr turretptr = boost::dynamic_pointer_cast<MissileSilo>(strongEntity);
    if (turretptr)
    {
      // Try to find target
      // transition to normal
      turretptr->calculateTarget();
      if(turretptr->getHasTarget())
      {
        turretptr->getStateMachine()->changeState(MissileSiloNormal::instance());
      }
    }
  }
}

//-------------------------------------------------------------------//

void MissileSiloSeek::exit(EntityWPtr _turret)
{
  Q_UNUSED(_turret);
}

//-------------------------------------------------------------------//

MissileSiloBasicUpgrade * MissileSiloBasicUpgrade::instance()
{
  static MissileSiloBasicUpgrade lockOnInstance;

  return &lockOnInstance;
}

//-------------------------------------------------------------------//

void MissileSiloBasicUpgrade::enter(EntityWPtr _turret)
{
  Q_UNUSED(_turret);
}

//-------------------------------------------------------------------//

void MissileSiloBasicUpgrade::execute(EntityWPtr _turret)
{
  //get a strong pointer from the waek pointer passed in
  EntityPtr strongEntity = _turret.lock();

  // if the pointer exists
  if (strongEntity)
  {
    //cast strong entity pointer to a turret pointer
    MissileSiloPtr turretptr = boost::dynamic_pointer_cast<MissileSilo>(strongEntity);
    if (turretptr)
    {
      // Edit all the values
      turretptr->setShotWaitTime(5);
      turretptr->setBasePos(Game::instance()->getBasePos());
      // When this is done it needs to change to the previous state
      StateMachine *sm = strongEntity->getStateMachine();
      if(sm)
      {
        sm->changeToPreviousState();
      }
    }
  }
}

//-------------------------------------------------------------------//

void MissileSiloBasicUpgrade::exit(EntityWPtr _turret)
{
  Q_UNUSED(_turret);
}

//-------------------------------------------------------------------//

MissileSiloAdvancedUpgrade * MissileSiloAdvancedUpgrade::instance()
{
  static MissileSiloAdvancedUpgrade lockOnInstance;

  return &lockOnInstance;
}

//-------------------------------------------------------------------//

void MissileSiloAdvancedUpgrade::enter(EntityWPtr _turret)
{
  Q_UNUSED(_turret);
}

//-------------------------------------------------------------------//

void MissileSiloAdvancedUpgrade::execute(EntityWPtr _turret)
{
  //get a strong pointer from the waek pointer passed in
  EntityPtr strongEntity = _turret.lock();

  // if the pointer exists
  if (strongEntity)
  {
    //cast strong entity pointer to a turret pointer
    TurretPtr turretptr = boost::dynamic_pointer_cast<Turret>(strongEntity);
    if (turretptr)
    {
      // Edit all the values
      turretptr->setShotWaitTime(1);
      // When this is done it needs to change to the previous state
      StateMachine *sm = strongEntity->getStateMachine();
      if(sm)
      {
        sm->changeToPreviousState();
      }
    }
  }
}

//-------------------------------------------------------------------//

void MissileSiloAdvancedUpgrade::exit(EntityWPtr _turret)
{
  Q_UNUSED(_turret);
}
