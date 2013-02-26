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

  //get a strong pointer from the waek pointer passed in

  EntityPtr strongEntity = _turret.lock();

  // if the pointer exists

  if (strongEntity)
  {

  }


}

//-------------------------------------------------------------------//

void Seek::exit(EntityWPtr _turret)
{
  Q_UNUSED(_turret);
}

//-------------------------------------------------------------------//

Approach * Approach::instance()
{
  static Approach approachInstance;

  return &approachInstance;
}

//-------------------------------------------------------------------//

void Approach::enter(EntityWPtr _turret)
{
  Q_UNUSED(_turret);
}

//-------------------------------------------------------------------//

void Approach::execute(EntityWPtr _turret)
{
  //execute

  //get a strong pointer from the waek pointer passed in

  EntityPtr strongEntity = _turret.lock();

  // if the pointer exists

  if (strongEntity)
  {

  }
}

//-------------------------------------------------------------------//

void Approach::exit(EntityWPtr _turret)
{
  Q_UNUSED(_turret);
}

//-------------------------------------------------------------------//

LockOn * LockOn::instance()
{
  static LockOn lockOnInstance;

  return &lockOnInstance;
}

//-------------------------------------------------------------------//

void LockOn::enter(EntityWPtr _turret)
{
  Q_UNUSED(_turret);
}

//-------------------------------------------------------------------//

void LockOn::execute(EntityWPtr _turret)
{
  //execute

  //get a strong pointer from the waek pointer passed in

  EntityPtr strongEntity = _turret.lock();

  // if the pointer exists

  if (strongEntity)
  {

    //cast strong entity pointer to a turret pointer

    TurretPtr turretptr = boost::dynamic_pointer_cast<Turret>(strongEntity);

    if (turretptr)
    {
      //now get the entity record of the target if it's still a local entity

      EntityRecord record;

      // rotate to face the enemy

      turretptr->getNearestLocalRecord(record);

      if (record.m_id != 0)
      {
        //get the aim vector from the method

        ngl::Vec3 aim(turretptr->getAimVec(ngl::Vec3(
                                             record.m_x,
                                             record.m_y,
                                             record.m_z
                                             )));

        turretptr->setAim(aim);
      }

      //if the difference in time is great enough, fire

      if (turretptr->getShotWaitTime() <= turretptr->getDtSinceShot())
      {
        //set the doShot boolean to true

        turretptr->setDoShot(true);
      }
    }
  }
}

//-------------------------------------------------------------------//

void LockOn::exit(EntityWPtr _turret)
{
  Q_UNUSED(_turret);
}

//-------------------------------------------------------------------//
