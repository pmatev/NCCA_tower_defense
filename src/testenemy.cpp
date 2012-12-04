#include "testenemy.h"

//-------------------------------------------------------------------//

TestEnemy::TestEnemy(
    float _damage,
    float _maxVelocity,
    const ngl::Vec3 & _pos,
    float _initialVelocity,
    const ngl::Vec3 &_aim
    ):
  Enemy(
    _damage,
    _maxVelocity,
    _pos,
    _initialVelocity,
    _aim
    )
{
  // ctor just passes everything to parent class
}

//-------------------------------------------------------------------//

EntityPtr TestEnemy::create(
    float _damage,
    float _maxVelocity,
    const ngl::Vec3 &_pos,
    float _initialVelocity,
    const ngl::Vec3 &_aim
    )
{
  EntityPtr a(
        new TestEnemy(
          _damage,
          _maxVelocity,
          _pos,
          _initialVelocity,
          _aim
          )
        );
  return a;
}

//-------------------------------------------------------------------//

ngl::Vec3 TestEnemy::brain()
{
  // TEST value (tells it to just go forward)
  return ngl::Vec3(1, 0, 0);
}

//-------------------------------------------------------------------//

void TestEnemy::draw() const
{
  // does nothing yet
}

//-------------------------------------------------------------------//

void TestEnemy::drawSelection() const
{
  // Should draw the object with a constant shader based on ID
}

//-------------------------------------------------------------------//