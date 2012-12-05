#include "dynamicentity.h"

//-------------------------------------------------------------------//

DynamicEntity::DynamicEntity(
    float _damage,
    float _maxVelocity,
    const ngl::Vec3 &_pos,
    float _initialVelocity,
    const ngl::Vec3 &_aim,
    GeneralType _type
    ):
  Entity(_pos,_type),
  m_damage(_damage),
  m_aimVector(_aim),
  m_maxVelocity(_maxVelocity),
  m_currentVelocity(_initialVelocity),
  m_prevPos(_pos)

{
  //variables initialised before the constructor body
}

//-------------------------------------------------------------------//

DynamicEntity::~DynamicEntity()
{
  //currently using default destructor
}

//-------------------------------------------------------------------//

void DynamicEntity::update()
{
  std::cout<<"updating dynamic entity"<<std::endl;
  std::cout<<"now at position"<<m_pos<<std::endl;
  // get the brain vector
  ngl::Vec3 brainVec = brain();
  // based on brain where should it go next
  // FOR TESTING JUST HAVE IT GO EXACTLY WHERE THE BRAIN SAYS
  m_pos += brainVec;

  m_transformStack.setPosition(m_pos);
}

//-------------------------------------------------------------------//

bool DynamicEntity::collisionTest(BBox _wsBBox)
{
  // initialise the return value

  bool result = true;

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
  // return the result

  return result;
}

//-------------------------------------------------------------------//

char DynamicEntity::genClippingCode(const ngl::Vec3 &_point, BBox _wsBBox)
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
    )
{
  //set the return value

  bool result = false;

  //if we are checking against the x plane

  if (_planeExtents.m_minX == _planeExtents.m_minX)
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

  else if (_planeExtents.m_minY == _planeExtents.m_minY)
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

  else if (_planeExtents.m_minZ == _planeExtents.m_minZ)
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
