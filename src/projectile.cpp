#include "projectile.h"

//-------------------------------------------------------------------//

Projectile::Projectile(
    float _damage,
    float _maxVelocity,
    const ngl::Vec3 &_pos,
    float _initialVelocity,
    const ngl::Vec3 &_aim
    ) :
  DynamicEntity(
    _damage,
    _maxVelocity,
    _pos,
    _initialVelocity,
    _aim,
    PROJECTILE
    )
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

  //finally call the collision test method and return the result

  return collisionTest(types,bBoxSize);
}

//-------------------------------------------------------------------//
