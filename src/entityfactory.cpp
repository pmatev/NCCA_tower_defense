#include "entityfactory.h"

//-------------------------------------------------------------------//

EntityFactory::EntityFactory()
{
  //currently using default constructor
}

//-------------------------------------------------------------------//

EntityFactory::~EntityFactory()
{
  //currently using default destructor
}

//-------------------------------------------------------------------//

DynamicEntityPtr EntityFactory::createDynamicEntity(
    EntityType _type,
    float _damage,
    float _maxVelocity,
    const ngl::Vec3 &_pos
    )
{
  switch(_type)
  {
    case(ENEMY):
    {
      return Enemy::create(
                          _damage,
                          _maxVelocity,
                          _pos
                          );
    }
  }
  return DynamicEntityPtr();
}

//-------------------------------------------------------------------//
