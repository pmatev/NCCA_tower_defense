#include "concrete/bullet.h"

//-------------------------------------------------------------------//

Bullet::Bullet(
    float _damage,
    float _maxVelocity,
    const ngl::Vec3 &_pos,
    float _initialVelocity,
    const ngl::Vec3 &_aim
    ) :
  Projectile(_damage, _maxVelocity, _pos, _initialVelocity,_aim)
{

}

//-------------------------------------------------------------------//

BulletPtr Bullet::create(
    float _damage,
    float _maxVelocity,
    const ngl::Vec3 &_pos,
    float _initialVelocity,
    const ngl::Vec3 &_aim
    )
{
  //create and return a smart pointer to the bullet

  BulletPtr bullet(
        new Bullet(
          _damage,
          _maxVelocity,
          _pos,
          _initialVelocity,
          _aim)
        );
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

}

//-------------------------------------------------------------------//
