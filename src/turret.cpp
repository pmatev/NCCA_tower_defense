#include "turret.h"
#include "game.h"

//-------------------------------------------------------------------//

Turret::Turret(
    NodePtr _linkedNode,
    unsigned int _id,
    std::string _projectileType
    ):
  StaticEntity(_linkedNode, TURRET,_id),
  m_fov(360),
  m_viewDistance(20),
  m_maxRotationSpeed(0.5),
  m_aim(ngl::Vec3(0.01, 0, 0)),
  m_projectileType(_projectileType),
  m_doShot(false),
  m_dtSinceLastShot(0),
  m_shotWaitTime(0.1),
  m_shotPos(0,0,0),
  m_targetID(-1)
{
  //variables initialised before constructor body called
}


//-------------------------------------------------------------------//

Turret::~Turret()
{
  //currently using default destructor
}

//-------------------------------------------------------------------//

void Turret::update(const double _dt)
{
  //add the dt to the dt since last shot

  m_dtSinceLastShot += _dt/1000;

  //update the state machine
  //m_stateMachine->update();

  // TEST
  // just do whatever the brain says
  m_aim = brain();

  m_aim.normalize();

}

//-------------------------------------------------------------------//

void Turret::fire()
{
  //get a pointer to the game

  Game * game = Game::instance();

  //get a weak pointer to the projectile manager

  ProjectileManagerPtr pm = game->getProjectileManagerWeakPtr().lock();
  if(pm)
  {
    //add a projectile, at the moment starts it at the centre of the turret
    //might need to add some way of setting where the end of the turret's
    //barrel is
    pm->addProjectile(m_projectileType,m_pos,m_aim,m_ID);

    //then set the doFire and time since last shot values back to their default
    // values

    m_doShot = false;

    m_dtSinceLastShot = 0;
  }
}

//-------------------------------------------------------------------//

ngl::Vec3 Turret::getAimVec(const ngl::Vec3 &_pos) const
{
  ngl::Vec3 aim(_pos.m_x-m_pos.m_x,
                   _pos.m_y-m_shotPos.m_y,
                   _pos.m_z-m_pos.m_z);
  std::cout<<"\n";

  return aim;
}

//-------------------------------------------------------------------//

void Turret::getLocalRecordByID(unsigned int _ID, EntityRecord &o_record)
{
  //set up variables

  bool result = false;

  EntityRecordList::iterator listIt = m_localEntities->begin();

  //cycle through

  while (!result && listIt != m_localEntities->end())
  {
    if (listIt->m_id == _ID)
    {

      o_record = (*listIt);
    }
    else
    {
      //increment the iterator

      listIt++;
    }
  }
}

//-------------------------------------------------------------------//

void Turret::getNearestLocalRecord(EntityRecord &o_record)
{

  //set up variables

  float lowestSqDist;
  float tempSqDist;

  if (m_localEntities)
  {
    EntityRecordList::iterator listIt = m_localEntities->begin();

    //set the lowest to the first distance and set the record

    lowestSqDist = (listIt->m_x - m_pos.m_x)*(listIt->m_x - m_pos.m_x)+
        (listIt->m_y - m_pos.m_y)*(listIt->m_y - m_pos.m_y)+
        (listIt->m_z - m_pos.m_z)*(listIt->m_z - m_pos.m_z);

    o_record = (*listIt);

    listIt++;

    //cycle through the rest

    for (;listIt != m_localEntities->end();listIt++)
    {
      //set a the temporary squareDisrance

      tempSqDist = (listIt->m_x - m_pos.m_x)*(listIt->m_x - m_pos.m_x)+
          (listIt->m_y - m_pos.m_y)*(listIt->m_y - m_pos.m_y)+
          (listIt->m_z - m_pos.m_z)*(listIt->m_z - m_pos.m_z);

      //if the calculated value is less than the current one

      if (lowestSqDist > tempSqDist)
      {
        //swap it in and set the output object

        lowestSqDist = tempSqDist;

        o_record =(*listIt);
      }
    }
  }
}

//-------------------------------------------------------------------//

void Turret::setAim(const ngl::Vec3 &_aim)
{
  //at the moment just set the value to the inputted value

  m_aim = _aim;
}

//-------------------------------------------------------------------//

void Turret::prepareForUpdate()
{
  //generate the viewBox
  generateViewBBox();
  // Get the local entities
  std::list<GeneralType> types;
  types.push_back(ENEMY);
  m_localEntities = EntityRecordListPtr(new EntityRecordList());
  calculateLocalEntities(*m_localEntities, types);
  // Filter the entities
  filterViewVolume(*m_localEntities);

  // if the fire boolean is set

  if (m_doShot == true)
  {
    fire();
  }
}

//-------------------------------------------------------------------//
