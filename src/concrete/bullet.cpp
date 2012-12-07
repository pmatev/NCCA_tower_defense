#include "concrete/bullet.h"

//-------------------------------------------------------------------//

Bullet::Bullet(
    const ngl::Vec3 &_pos,
    const ngl::Vec3 &_aim,
    unsigned int _id
    ) :
  Projectile(_pos,_aim, _id)
{
  m_damage = 20;
  m_maxVelocity = 10;
  m_currentVelocity = 2;
}

//-------------------------------------------------------------------//

BulletPtr Bullet::create(
    const ngl::Vec3 &_pos,
    const ngl::Vec3 &_aim,
    unsigned int _id
    )
{
  //create and return a smart pointer to the bullet

  BulletPtr bullet(new Bullet(_pos,_aim, _id));
  return bullet;
}

//-------------------------------------------------------------------//

void Bullet::draw()
{

}

//-------------------------------------------------------------------//

void Bullet::generateMesh()
{

}


//-------------------------------------------------------------------//

void Bullet::drawSelection()
{

}

//-------------------------------------------------------------------//

ngl::Vec3 Bullet::brain()
{
  // for the moment just have the bullet follow it's aim

  return m_aimVector;
}

//-------------------------------------------------------------------//
