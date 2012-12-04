#include "testenemy.h"

//-------------------------------------------------------------------//

Enemy::Enemy(
    float _damage,
    float _maxVelocity,
    const ngl::Vec3 & _pos,
    float _initialVelocity
    ):
  DynamicEntity(
    _damage,
    _maxVelocity,
    _pos,
    _initialVelocity
    )
{
  // ctor just passes everything to parent class
}

//-------------------------------------------------------------------//

EntityPtr Enemy::create(
    float _damage,
    float _maxVelocity,
    const ngl::Vec3 &_pos,
    float _initialVelocity
    )
{
  EntityPtr a(
        new Enemy(
          _damage,
          _maxVelocity,
          _pos,
          _initialVelocity
          )
        );
  return a;
}

//-------------------------------------------------------------------//

ngl::Vec3 Enemy::brain()
{
  // TEST value (tells it to just go forward)
  return ngl::Vec3(1, 0, 0);
}

//-------------------------------------------------------------------//

void Enemy::draw() const
{
  // does nothing yet
}

//-------------------------------------------------------------------//

void Enemy::drawSelection() const
{
  // Should draw the object with a constant shader based on ID
}

//-------------------------------------------------------------------//
