#include "dynamicentity.h"
#include "database.h"
#include "game.h"

//-------------------------------------------------------------------//

DynamicEntity::DynamicEntity(
    const ngl::Vec3 &_pos,
    const ngl::Vec3 &_aim,
    GeneralType _type,
    unsigned int _id
    ):
  Entity(_pos,_type,_id),
  m_aimVector(_aim),
  m_maxAccn(0.1),
  m_prevPos(_pos),
  m_toBeRemoved(false)
{
  //variables initialised before the constructor body
  m_mass = 0.5;
  m_velocity = ngl::Vec3(0.0, 0.0, 0.0);
}

//-------------------------------------------------------------------//

DynamicEntity::~DynamicEntity()
{
  //currently using default destructor
}

//-------------------------------------------------------------------//

void DynamicEntity::prepareForUpdate()
{
//  //generate the view box
//  generateViewBBox();

//  // Get the local entities
//  std::list<GeneralType> types;
//  types.push_back(TURRET);
//  types.push_back(ENEMY);
//  m_localEntities = EntityRecordListPtr(new EntityRecordList());
//  //EntityRecordList localEntities;
//  calculateLocalEntities(*m_localEntities, types);
//  // Filter the entities
//  filterViewVolume(*m_localEntities);
}

//-------------------------------------------------------------------//

void DynamicEntity::update(const double _dt)
{
  move(_dt);
}

void DynamicEntity::move(const double _dt)
{
  //update the state machine
  m_stateMachine->update();

  ngl::Vec3 steeringForce = brain();
  ngl::Vec3 acceleration = (steeringForce) / m_mass;

  //truncate acceleration to max acc
  float accDiff = m_maxAccn / acceleration.length(); //COULD FAIL IF 0
  float accScaleFactor = (accDiff < 1.0) ? accDiff : 1.0;
  acceleration *= accScaleFactor;


  m_velocity += acceleration * _dt;


  //truncate velocity to max speed
  float diff = m_maxVelocity / m_velocity.length(); //COULD FAIL IF 0
  float scaleFactor = (diff < 1.0) ? diff : 1.0;
  m_velocity *= scaleFactor;

  // Add in impulses, we do this after capping max velocities
  m_velocity += (m_currentImpulses / m_mass)*_dt;

  //update position
  m_prevPos = m_pos;
  m_pos += m_velocity * _dt;

  //Damage check
  //Iterate over the neighbours.
  if(m_localEntities)
  {
    EntityRecordWCList::const_iterator iterator;
    for(iterator = m_localEntities->begin();
        iterator != m_localEntities->end();
        ++iterator)
    {
      EntityRecordCPtr recordStrong = iterator->lock();
      if(recordStrong)
      {
        if(recordStrong->m_generalType == TURRET ||
           recordStrong->m_generalType == WALL)
         {
          ngl::Vec3 neighbourPos = ngl::Vec3(recordStrong->m_x,
                                             recordStrong->m_y,
                                             recordStrong->m_z);

          ngl::Vec3 v = neighbourPos - m_pos;

          float obstacleRadius = 1;
          float enemyRadius = 0.3;

          float vMag = v.length();

          if((vMag - enemyRadius) < obstacleRadius)
          {

            m_pos -= (obstacleRadius - vMag + enemyRadius) * v;
          }
        }
      }
    }
  }
  enforceGridBoundaries();
  // make sure velocity is properly integrated
  m_velocity = (m_pos - m_prevPos) / _dt;

  m_transformStack.setPosition(m_pos);

  // Reset impulses
  m_currentImpulses.null();
}

//-------------------------------------------------------------------//

bool DynamicEntity::intersectTest(BBox _wsBBox) const
{
  // initialise the return value

  bool result = false;

  //first test if the bounding box passed in overlaps with the
  //bounding box of the entity doing the testing

  //test the x dimension of the bounding box

  if (
      (m_lsMeshBBox.m_maxX+ m_pos.m_x) > _wsBBox.m_minX &&
      (m_lsMeshBBox.m_minX+ m_pos.m_x) < _wsBBox.m_maxX
      )
  {
    //test the y dimension of the bounding box
    if (
        (m_lsMeshBBox.m_maxY+ m_pos.m_y) > _wsBBox.m_minY &&
        (m_lsMeshBBox.m_minY+ m_pos.m_y) < _wsBBox.m_maxY
        )
    {
      //test the z dimension of the bounding box
      if (
          (m_lsMeshBBox.m_maxZ+ m_pos.m_z) > _wsBBox.m_minZ &&
          (m_lsMeshBBox.m_minZ+ m_pos.m_z) < _wsBBox.m_maxZ
          )
      {
        //if all tests were true set the result

        result = true;
      }
    }
  }

  //if the first test didn't find a collision

  if (result == false)
  {

    //second test if the object has passed through the bounding box passed
    //in since the last check. this uses a line clipping algorithm.

    //first assign an integer value as the code for each point, the old
    //position and the new position (index 0 and 1 respectively)

    char code [2] = {0,0};
    code[0] = genClippingCode(m_prevPos,_wsBBox);
    code[1] = genClippingCode(m_pos,_wsBBox);

    //they should not both be within the bounding box but check just to
    //make sure

    if (code[0]==0 || code[1]==0)
    {
      //if one or other of the codes are within the bounding box,
      //set to true. this eventuality should already have been caught
      //but tested in case it wasn't

      result = true;
    }
    else if ((code [0] & code [1]) != 0)
    {
      //otherwise if both points are on the outside of the same boundary

      result = false;
    }
    else
    {
      //check collisions with individual planes

      //check against the minimum x plane

      if (isIntersecting(
            m_pos,
            m_prevPos,
            BBox(
              _wsBBox.m_minX,
              _wsBBox.m_minY,
              _wsBBox.m_minZ,
              _wsBBox.m_minX,
              _wsBBox.m_maxY,
              _wsBBox.m_maxZ
              )
            ))
      {
        result = true;
      }

      //check against the maximum x plane

      else if (isIntersecting(
            m_pos,
            m_prevPos,
            BBox(
              _wsBBox.m_maxX,
              _wsBBox.m_minY,
              _wsBBox.m_minZ,
              _wsBBox.m_maxX,
              _wsBBox.m_maxY,
              _wsBBox.m_maxZ
              )
            ))
      {
        result = true;
      }

      //check against the minimum y plane

      else if (isIntersecting(
            m_pos,
            m_prevPos,
            BBox(
              _wsBBox.m_minX,
              _wsBBox.m_minY,
              _wsBBox.m_minZ,
              _wsBBox.m_maxX,
              _wsBBox.m_minY,
              _wsBBox.m_maxZ
              )
            ))
      {
        result = true;
      }

      //check against the maximum y plane

      else if (isIntersecting(
            m_pos,
            m_prevPos,
            BBox(
              _wsBBox.m_minX,
              _wsBBox.m_maxY,
              _wsBBox.m_minZ,
              _wsBBox.m_maxX,
              _wsBBox.m_maxY,
              _wsBBox.m_maxZ
              )
            ))
      {
        result = true;
      }

      //check against the minimum z plane

      else if (isIntersecting(
            m_pos,
            m_prevPos,
            BBox(
              _wsBBox.m_minX,
              _wsBBox.m_minY,
              _wsBBox.m_minZ,
              _wsBBox.m_maxX,
              _wsBBox.m_maxY,
              _wsBBox.m_minZ
              )
            ))
      {
        result = true;
      }

      //check against the maximum z plane

      else if (isIntersecting(
            m_pos,
            m_prevPos,
            BBox(
              _wsBBox.m_minX,
              _wsBBox.m_minY,
              _wsBBox.m_maxZ,
              _wsBBox.m_maxX,
              _wsBBox.m_maxY,
              _wsBBox.m_maxZ
              )
            ))
      {
        result = true;
      }
    }
  }
  return result;
}

//-------------------------------------------------------------------//

char DynamicEntity::genClippingCode(const ngl::Vec3 &_point, BBox _wsBBox) const
{
  //initialise the variable to return

  char code = 0;

  //generate the code

  if(_point.m_x < _wsBBox.m_minX)
  {
    //if the x position is less than the minimum x extent of the bounding
    //box set the first bit of the code

    code +=1;
  }
  else if(_point.m_x > _wsBBox.m_maxX)
  {
    //if the x position is greater than the maximum x extent of the bounding
    //box set the second bit of the code

    code +=2;
  }

  if(_point.m_y < _wsBBox.m_minY)
  {
    //if the y position is less than the minimum y extent of the bounding
    //box set the first bit of the code

    code +=4;
  }
  else if(_point.m_y > _wsBBox.m_maxY)
  {
    //if the y position is greater than the maximum y extent of the bounding
    //box set the second bit of the code

    code +=8;
  }

  if(_point.m_z < _wsBBox.m_minZ)
  {
    //if the y position is less than the minimum y extent of the bounding
    //box set the first bit of the code

    code +=16;
  }
  else if(_point.m_z > _wsBBox.m_maxZ)
  {
    //if the y position is greater than the maximum y extent of the bounding
    //box set the second bit of the code

    code +=32;
  }

  //return the code

  return code;
}

//-------------------------------------------------------------------//

bool DynamicEntity::isIntersecting(
    const ngl::Vec3 &_point1,
    const ngl::Vec3 &_point2,
    BBox _planeExtents
    ) const
{
  //set the return value

  bool result = false;

  //if we are checking against the x plane

  if (_planeExtents.m_minX == _planeExtents.m_maxX)
  {
    //initialise the variable to store the distance along the line
    //that it intersects. working from the known intersection value x
    //we calculate the y and z points of intersection and whether they fit
    //within the boundaries

    float ratio = (_planeExtents.m_minX - _point1.m_x)/
        (_point2.m_x-_point1.m_x);

    //calculate yi and zi

    float yi = _point1.m_y + (_point2.m_y - _point1.m_y)*ratio;
    float zi = _point1.m_z + (_point2.m_z - _point1.m_z)*ratio;

    //finally check if it's within the y and z extents

    if (_planeExtents.m_minY < yi && _planeExtents.m_maxY > yi)
    {
      if (_planeExtents.m_minZ < zi && _planeExtents.m_maxZ > zi)
      {
        result = true;
      }
    }
  }

  //if we are checking against the y plane

  else if (_planeExtents.m_minY == _planeExtents.m_maxY)
  {
    //initialise the variable to store the distance along the line
    //that it intersects. working from the known intersection value y
    //we calculate the x and z points of intersection and whether they fit
    //within the boundaries

    float ratio = (_planeExtents.m_minY - _point1.m_y)/
        (_point2.m_y-_point1.m_y);

    //calculate xi and zi

    float xi = _point1.m_x + (_point2.m_x - _point1.m_x)*ratio;
    float zi = _point1.m_z + (_point2.m_z - _point1.m_z)*ratio;

    //finally check if it's within the x and z extents

    if (_planeExtents.m_minX < xi && _planeExtents.m_maxX > xi)
    {
      if (_planeExtents.m_minZ < zi && _planeExtents.m_maxZ > zi)
      {
        result = true;
      }
    }
  }

  //if we are checking against the z plane

  else if (_planeExtents.m_minZ == _planeExtents.m_maxZ)
  {
    //initialise the variable to store the distance along the line
    //that it intersects. working from the known intersection value z
    //we calculate the x and y points of intersection and whether they fit
    //within the boundaries

    float ratio = (_planeExtents.m_minZ - _point1.m_z)/
        (_point2.m_z-_point1.m_z);

    //calculate xi and yi

    float xi = _point1.m_x + (_point2.m_x - _point1.m_x)*ratio;
    float yi = _point1.m_y + (_point2.m_y - _point1.m_y)*ratio;

    //finally check if it's within the x and y extents

    if (_planeExtents.m_minX < xi && _planeExtents.m_maxX > xi)
    {
      if (_planeExtents.m_minY < yi && _planeExtents.m_maxY > yi)
      {
        result = true;
      }
    }
  }

  //return result

  return result;
}

//-------------------------------------------------------------------//

Damage DynamicEntity::collisionTest(
    std::list<GeneralType> &_types
    ) const
{

  //first generate a list of local entity records
  Database* db = Database::instance();
  EntityRecordWCList localEntities;
  db->getLocalEntities(
        localEntities,
        m_pos.m_x+m_lsMeshBBox.m_minX-0.5,
        m_pos.m_z+m_lsMeshBBox.m_minZ-0.5,
        m_pos.m_x+m_lsMeshBBox.m_maxX+0.5,
        m_pos.m_z+m_lsMeshBBox.m_maxZ+0.5,
        _types
        );

  //then cycle through the list
  EntityRecordWCList::iterator listIt = localEntities.begin();

  //initialise the result and the return collision

  bool result = false;
  Damage c(0,0);

  while(listIt != localEntities.end() && result != true)
  {
    //get the id of the element pointed to by the iterator
    EntityRecordCPtr recordStrong = listIt->lock();
    if(recordStrong)
    {
      unsigned int id = recordStrong->m_id;
      if(id != m_ID)
      {
        //get the relevant information

        //ngl::Vec3 pos (listIt->m_x,listIt->m_y,listIt->m_z);
        Entity::BBox bBox (recordStrong->m_minX,
                           recordStrong->m_minY,
                           recordStrong->m_minZ,
                           recordStrong->m_maxX,
                           recordStrong->m_maxY,
                           recordStrong->m_maxZ);

        //check for collisions between the entity checking and the one
        //it's checking against

        result = intersectTest(bBox);

        if (result == true)
        {
          //set the id of the collision being returned from the null value
          //to the one tested

          c.m_id = id;

          //then set the damage value

          c.m_damage = m_damage;


        }
      }

    }
    //increment the iterator
    listIt++;
  }
  //finally return the collision struct

  return c;
}

//-------------------------------------------------------------------//

void DynamicEntity::generateViewBBox()
{
  // initialise world space view box
  m_wsViewBBox = BBox(
        m_lsMeshBBox.m_minX*4 + m_pos.m_x,
        m_lsMeshBBox.m_minY*4 + m_pos.m_y,
        m_lsMeshBBox.m_minZ*4 + m_pos.m_z,
        m_lsMeshBBox.m_maxX*4 + m_pos.m_x,
        m_lsMeshBBox.m_maxY*4 + m_pos.m_y,
        m_lsMeshBBox.m_maxZ*4 + m_pos.m_z
        );
}

//-------------------------------------------------------------------//

void DynamicEntity::kill()
{
  //at the moment just sets the to be removed boolean to true

  m_toBeRemoved = true;
}

//-------------------------------------------------------------------//
