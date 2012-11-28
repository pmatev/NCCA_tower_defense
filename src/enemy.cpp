#include "enemy.h"

//-------------------------------------------------------------------//

Enemy::Enemy(
    float _damage,
    float _maxVelocity,
    const ngl::Vec3 & _pos
    ):
  DynamicEntity(
    _damage,
    _maxVelocity,
    _pos
    )
{
  // ctor just passes everything to parent class
}

//-------------------------------------------------------------------//

EnemyPtr Enemy::create(
    float _damage,
    float _maxVelocity,
    const ngl::Vec3 &_pos
    )
{
  EnemyPtr a(
        new Enemy(
                  _damage,
                  _maxVelocity,
                  _pos
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
