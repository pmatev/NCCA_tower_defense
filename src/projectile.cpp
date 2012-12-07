#include "projectile.h"
#include "database.h"

//-------------------------------------------------------------------//

Projectile::Projectile(
    const ngl::Vec3 &_pos,
    const ngl::Vec3 &_aim,
    unsigned int _id
    ) :
  DynamicEntity(_pos,_aim,PROJECTILE, _id)
{

}

//-------------------------------------------------------------------//

Collision Projectile::collisionDetection()
{
  //calculate the desired size of the box to use as the initial filter of
  //entities

  //first calculate the distance travelled in the x direction since the
  //last update and the equivalent y distance

  float xDist = abs(m_pos.m_x - m_prevPos.m_x);
  float yDist = abs(m_pos.m_y - m_prevPos.m_y);

  //then select the largest to be the bBoxSize

  float bBoxSize;

  if (xDist > yDist)
  {
    bBoxSize = xDist*2;
  }
  else
  {
    bBoxSize = yDist*2;
  }
  //create a list of types with just the enemy type in it

  std::list<GeneralType> types;
  types.push_back(ENEMY);

  //call the collision test method and store the result

  Collision c = collisionTest(types,bBoxSize);

  //check if the collision is returning a value

  if (c.m_id != 0)
  {
    //if there is a non 0 value being returned there was a collision
    //and the health of the projectile should be set to 0

    m_health = 0;
  }

  return c;
}

//-------------------------------------------------------------------//

void Projectile::enforceGridBoundaries()
{
  //get an instance of the database

  Database* db = Database::instance();

  //get the minimum and maximum extents of the grid

  ngl::Vec2 minExts = db->getMinGridExtents();
  ngl::Vec2 maxExts = db->getMaxGridExtents();

  //check the position of the entity against the boundaries
  //comparison between z and y because x and z are the planar
  //axis but a vec2 has no m_z component

  if (m_pos.m_x < minExts.m_x
      || m_pos.m_x > maxExts.m_x
      || m_pos.m_z < minExts.m_y
      || m_pos.m_z > maxExts.m_y
      )
  {
    // set the health to 0

    m_health = 0;
  }
}

//-------------------------------------------------------------------//
