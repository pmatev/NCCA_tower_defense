#include "include/fsm/states/turretstates.h"
#include "turret.h"

//-------------------------------------------------------------------//

Seek * Seek::instance()
{
  static Seek seekInstance;

  return &seekInstance;
}

//-------------------------------------------------------------------//

void Seek::enter(EntityWPtr _turret)
{
  Q_UNUSED(_turret);
}

//-------------------------------------------------------------------//

void Seek::execute(EntityWPtr _turret)
{
  //execute

  //get a strong pointer from the weak pointer passed in

  EntityPtr strongEntity = _turret.lock();

  // if the pointer exists

  if (strongEntity)
  {

    //cast strong entity pointer to a turret pointer

    TurretPtr turretptr = boost::dynamic_pointer_cast<Turret>(strongEntity);

    if (turretptr)
    {
      //now get the entity record of the target if it's still a local entity

      EntityRecordWCPtr record;

      // rotate to face the enemy

      turretptr->getNearestLocalRecord(record);

      EntityRecordCPtr recordStrong = record.lock();
      if(recordStrong)
      {
        if (recordStrong->m_id != 0)
        {
          //set the target id

          turretptr->setTarget(recordStrong->m_id);

          //and move to lockedOn state

          turretptr->getStateMachine()->changeState(LockedOn::instance());
        }
      }

    }
  }
}

//-------------------------------------------------------------------//

void Seek::exit(EntityWPtr _turret)
{
  Q_UNUSED(_turret);
}

//-------------------------------------------------------------------//

LockedOn * LockedOn::instance()
{
  static LockedOn lockOnInstance;

  return &lockOnInstance;
}

//-------------------------------------------------------------------//

void LockedOn::enter(EntityWPtr _turret)
{
  Q_UNUSED(_turret);
}

//-------------------------------------------------------------------//

void LockedOn::execute(EntityWPtr _turret)
{
  //execute

  //get a strong pointer from the weak pointer passed in

  EntityPtr strongEntity = _turret.lock();

  // if the pointer exists

  if (strongEntity)
  {

    //cast strong entity pointer to a turret pointer

    TurretPtr turretptr = boost::dynamic_pointer_cast<Turret>(strongEntity);

    if (turretptr)
    {
      //now get the entity record of the target if it's still a local entity

      EntityRecordWCPtr record;

      // rotate to face the enemy

      turretptr->getTargetRecord(record);

      EntityRecordCPtr recordStrong = record.lock();
      if(recordStrong)
      {

        //get the aim vector from the method
        ngl::Vec3 aim(
              turretptr->calculateAimVec(
                ngl::Vec3(
                  (recordStrong->m_minX + recordStrong->m_maxX) / 2.0,
                  (recordStrong->m_minY + recordStrong->m_maxY) / 2.0,
                  (recordStrong->m_minZ + recordStrong->m_maxZ) / 2.0
                  ),
                ngl::Vec3(
                  recordStrong->m_velocity[0],
                  recordStrong->m_velocity[1],
                  recordStrong->m_velocity[2]
                  )
                )
              );

        //normalise the aim

        float len = aim.length();
        if(len)
        {
          aim /= len;
        }

        //set the desired aim

        turretptr->setDesiredAim(aim);

        //if the time since the last shot is great enough

        if (turretptr->getShotWaitTime() <= turretptr->getDtSinceShot())
        {
          //set the doShot boolean to true

          turretptr->setDoShot(true);
        }
      }
      else
      {
        //if the target record is no longer in the list

        turretptr->getStateMachine()->changeState(Seek::instance());
      }
    }
  }
}

//-------------------------------------------------------------------//

void LockedOn::exit(EntityWPtr _turret)
{
  Q_UNUSED(_turret);
}

//-------------------------------------------------------------------//

BasicUpgrade * BasicUpgrade::instance()
{
  static BasicUpgrade lockOnInstance;

  return &lockOnInstance;
}

//-------------------------------------------------------------------//

void BasicUpgrade::enter(EntityWPtr _turret)
{
  Q_UNUSED(_turret);
}

//-------------------------------------------------------------------//

void BasicUpgrade::execute(EntityWPtr _turret)
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
      turretptr->setShotWaitTime(0.1);
      turretptr->setRotationAngle(5);
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

void BasicUpgrade::exit(EntityWPtr _turret)
{
  Q_UNUSED(_turret);
}

//-------------------------------------------------------------------//

AdvancedUpgrade * AdvancedUpgrade::instance()
{
  static AdvancedUpgrade lockOnInstance;

  return &lockOnInstance;
}

//-------------------------------------------------------------------//

void AdvancedUpgrade::enter(EntityWPtr _turret)
{
  Q_UNUSED(_turret);
}

//-------------------------------------------------------------------//

void AdvancedUpgrade::execute(EntityWPtr _turret)
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
      turretptr->setProjectileType("Missile");
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

void AdvancedUpgrade::exit(EntityWPtr _turret)
{
  Q_UNUSED(_turret);
}
