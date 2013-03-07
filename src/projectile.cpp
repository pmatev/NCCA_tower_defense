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
  ;
}

//-------------------------------------------------------------------//

void Projectile::enforceGridBoundaries()
{
  //get an instance of the database

  Database* db = Database::instance();

  //get the minimum and maximum extents of the grid

  ngl::Vec2 minExts = db->getMinGridExtents();
  ngl::Vec2 maxExts = db->getMaxGridExtents();

  // Collide with ground
  if(m_pos.m_y < -0.01)
  {
    // Make sure it hasn't passed through the plane, this is important for
    // explosions.
    if(m_pos.m_y < 0)
    {
      m_pos.m_y = 0;
    }
    m_health = 0;
    return;
  }
  //check the position of the entity against the boundaries
  //comparison between z and y because x and z are the planar
  //axis but a vec2 has no m_z component

  if (
      m_pos.m_x < minExts.m_x
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

