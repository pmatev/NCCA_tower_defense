#include "turret.h"
#include "game.h"
#include <cmath>
#include<ngl/Quaternion.h>
#include <boost/foreach.hpp>


#define PI 3.14159265

//-------------------------------------------------------------------//

Turret::Turret(
    NodePtr _linkedNode,
    unsigned int _id,
    std::string _projectileType,
    float _viewDistance,
    float _projectileSpeed
    ):
  StaticEntity(_linkedNode, TURRET,_id),
  m_fov(360),
  m_viewDistance(_viewDistance),
  m_maxRotationAngle(2),            //default values
  m_cosRotationSpeed(cos(m_maxRotationAngle*PI/180)),
  m_aim(ngl::Vec3(1, 0, 0)),
  m_projectileType(_projectileType),
  m_doShot(false),
  m_dtSinceLastShot(0),
  m_shotWaitTime(0.1),
  m_shotPos(0,0,0),
  m_targetID(0),
  m_desiredAim(m_aim),
  m_projectileSpeed(_projectileSpeed),
  m_upgradeIndex(0)

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

  //call the brain

  m_stateMachine->update();

  //check the dot product

  float angleDot = m_aim.dot(m_desiredAim);

  // if it's greater than the stored cosine of the max rotation
  //speed angle implying that the desired aim vector is within the
  //rotation limits

  if (angleDot > m_cosRotationSpeed)
  {
    m_aim = m_desiredAim;
  }

  // if the angle is too big but is less than 90 degrees, do a quarternion
  //rotation of the vector around the normal to the two vectors, if it is
  //more than 90 degrees, just rotate around the z axis

  else
  {
    //calculate the components for the quarternion

    float rotInRads = (m_maxRotationAngle*PI/180);

    //then calculate sine and cos theta/2

    float rotVal = cos(rotInRads);
    float sinTheta = sin(rotInRads/2);

    //initialise the x y and z vale

    float xVal;
    float yVal;
    float zVal;

    //get the normal of the two vectors

    ngl::Vec3 normal = m_desiredAim.cross(m_aim);

    //if the angle is less than 90

    if (angleDot >= 0)
    {
      //ensure unit normal

      float len = normal.length();
      if(len)
      {
        normal /= len;
      }

      //then set the x,y, and z components

      xVal = normal.m_x*sinTheta;
      yVal = normal.m_y*sinTheta;
      zVal = normal.m_z*sinTheta;
    }

    //if it's not enforce rotation around the y axis

    else
    {
      //set up x and z vals to = 0

      xVal = 0;
      zVal = 0;

      //otherwise determine if the normal is pointing up or down,
      //and follow that, default behaviour if the vectors are opposite is
      //to use -y as the axis

      if (normal.m_y > 0 && angleDot != 0)
      {
        yVal = sinTheta;
      }
      else
      {
        yVal = -sinTheta;
      }

    }
    //generate the quarternion axis

    ngl::Quaternion axisQuart (rotVal,xVal,yVal,zVal);

    //and rotate the point by the quarternion

    axisQuart.rotatePoint(axisQuart,m_aim);

    //std::cout<<"quarternionRotated: "<<m_aim.m_x<<m_aim.m_y<<m_aim.m_z<<"\n";
  }


  float len = m_aim.length();
  if(len)
  {
      m_aim /= len;
  }

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
    //ensure normailsed aim

    float len = m_aim.length();
    if(len)
    {
        m_aim /= len;
    }

    //add a projectile, at the moment starts it at the centre of the turret
    //might need to add some way of setting where the end of the turret's
    //barrel is
    pm->addProjectile(m_projectileType,m_pos,m_aim*m_projectileSpeed,m_ID);

    //then set the doFire and time since last shot values back to their default
    // values

    m_doShot = false;

    m_dtSinceLastShot = 0;
  }
}

//-------------------------------------------------------------------//

ngl::Vec3 Turret::calculateAimVec(const ngl::Vec3 &_pos,
                                  const ngl::Vec3 &_velocity) const
{

  //calculate how long it will take for the projectile to reach
  //the current position of the enemy

  //calculate the predicted velocity of the projectile

  ngl::Vec3 aim ((_pos.m_x-m_pos.m_x),
                               (_pos.m_y-m_pos.m_y),
                               (_pos.m_z-m_pos.m_z)
                               );

  ngl::Vec3 predictedVelocity = aim;

  float len = predictedVelocity.length();
  if(len)
  {
      predictedVelocity /= len;
  }

  predictedVelocity *= m_projectileSpeed;

  //then calculate how many seconds it will take for the projectile
  //to reach the enemy

  float time = 0;

  if (predictedVelocity.m_x != 0)
  {
    time = aim.m_x/predictedVelocity.m_x;
  }
  else if (predictedVelocity.m_y != 0)
  {
    time = aim.m_y/predictedVelocity.m_y;
  }
  else if (predictedVelocity.m_z != 0)
  {
    time = aim.m_z/predictedVelocity.m_z;
  }

  //then add the velocity multiplied by that time to the position

  ngl::Vec3 aimPoint = _pos+_velocity*time;

  //then calculate the vector to that point

  ngl::Vec3 aimVec(aimPoint.m_x-m_pos.m_x,
                   aimPoint.m_y-m_shotPos.m_y,
                   aimPoint.m_z-m_pos.m_z);

  return aimVec;
}

//-------------------------------------------------------------------//

void Turret::getTargetRecord(EntityRecordWCPtr &o_record)
{
  //set up variables

  bool result = false;

  EntityRecordWCList::iterator listIt = m_localEntities->begin();

  //cycle through

  while (!result && listIt != m_localEntities->end())
  {
    EntityRecordCPtr recordStrong = listIt->lock();
    if(recordStrong)
    {
      if (recordStrong->m_id == m_targetID)
      {

        o_record = (*listIt);

        result = true;
      }
      else
      {
        //increment the iterator

        listIt++;
      }
    }
  }
}

//-------------------------------------------------------------------//

void Turret::getNearestLocalRecord(EntityRecordWCPtr &o_record)
{
  float minSqrDist = 100000000;
    BOOST_FOREACH(EntityRecordWCPtr recordWeak, *m_localEntities)
    {
      EntityRecordCPtr recordStrong = recordWeak.lock();
      if(recordStrong)
      {
        // Find sqr dist
        float sqrDist =
            pow(recordStrong->m_x - m_pos.m_x, 2) +
            pow(recordStrong->m_y - m_pos.m_y, 2) +
            pow(recordStrong->m_z - m_pos.m_z, 2)
              ;
        if(sqrDist < minSqrDist)
        {
          minSqrDist = sqrDist;
          o_record = recordWeak;
        }
      }
    }

//  //set up variables

//  float highestCosRotation;
//  float tempCosRotation;

//  //ensure normalised values in aim vector

//  float len = m_aim.length();
//  if(len)
//  {
//      m_aim /= len;
//  }

//  if (m_localEntities->size()!=0)
//  {
//    EntityRecordWCList::iterator listIt = m_localEntities->begin();


//    //generate the aim vector and initialise it to be the aim
//    //from the turret to the first point

//    ngl::Vec3 aim ((listIt->m_x - m_pos.m_x),
//                   (listIt->m_y - m_pos.m_y),
//                   (listIt->m_z - m_pos.m_z));

//    //normalise the aim

//    float len = aim.length();
//    if(len)
//    {
//        aim /= len;
//    }

//    //set the highest to the first distance and set the record

//    highestCosRotation = aim.dot(m_aim);

//    o_record = (*listIt);

//    listIt++;

//    //cycle through the rest

//    for (;listIt != m_localEntities->end();listIt++)
//    {
//      //set a the temporary cos of the angle

//      tempCosRotation = aim.dot(m_aim);

//      //if the calculated value is less than the current one

//      if (highestCosRotation < tempCosRotation)
//      {
//        //swap it in and set the output object

//        highestCosRotation = tempCosRotation;

//        o_record =(*listIt);
//      }
//    }
//  }
}

//-------------------------------------------------------------------//

void Turret::setDesiredAim(const ngl::Vec3 &_aim)
{
  //at the moment just set the value to the inputted value

  m_desiredAim = _aim;

  //ensure normailsed vector

  float len = m_desiredAim.length();
  if(len)
  {
      m_desiredAim /= len;
  }

}

//-------------------------------------------------------------------//

void Turret::prepareForUpdate()
{
  //generate the viewBox
  generateViewBBox();
  // Get the local entities
  std::list<GeneralType> types;
  types.push_back(ENEMY);
  m_localEntities = EntityRecordWCListPtr(new EntityRecordWCList());
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


void Turret::setRotationAngle (float _maxRotation)
{
  //set the values

  m_maxRotationAngle = _maxRotation;
  m_cosRotationSpeed = cos(m_maxRotationAngle*PI/180);
}

//-------------------------------------------------------------------//

bool Turret::upgrade()
{
  // manage the transition between upgrades
  if(m_upgradeIndex + 1 < m_upgrades.size())
  {
    ++m_upgradeIndex;
    // Check that its not null
    if(m_upgrades[m_upgradeIndex])
    {
      m_stateMachine->changeState(m_upgrades[m_upgradeIndex]);
      return true;
    }
  }
  return false;
}

//-------------------------------------------------------------------//

void Turret::registerUpgrade(State *_upgradeState, UpgradeDataPtr _data)
{
  m_upgrades.push_back(_upgradeState);
  m_upgradeData.push_back(_data);
}

//-------------------------------------------------------------------//

bool Turret::getCurrentUpgrade(UpgradeDataWPtr &o_upgradeData)
{
  if(m_upgradeData.size() != 0 && m_upgradeIndex < m_upgrades.size())
  {
    o_upgradeData = UpgradeDataWPtr(m_upgradeData[m_upgradeIndex]);
    return true;
  }
  return false;
}

//-------------------------------------------------------------------//

bool Turret::getNextUpgrade(UpgradeDataWPtr &o_upgradeData)
{
  if(m_upgradeData.size() != 0 && m_upgradeIndex + 1 < m_upgrades.size())
  {
    o_upgradeData = UpgradeDataWPtr(m_upgradeData[m_upgradeIndex + 1]);
    return true;
  }
  return false;

}

//-------------------------------------------------------------------//
