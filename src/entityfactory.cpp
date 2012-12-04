#include <boost/pointer_cast.hpp>

#include "entityfactory.h"
#include "testenemy.h"

EntityFactory::EntityTypeMap EntityFactory::s_entityTypes;

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

void EntityFactory::initialiseFactory()
{
  // This is where all different types are registered
  registerEntity("TestEnemy", TestEnemy::create);
}

void EntityFactory::registerEntity(const std::string _type, createCallBack _cb)
{
  s_entityTypes[_type] = _cb;
}

void EntityFactory::unregisterEntity(const std::string _type)
{
  s_entityTypes.erase(_type);
}


//-------------------------------------------------------------------//

DynamicEntityPtr EntityFactory::createDynamicEntity(
    std::string _type,
    float _damage,
    float _maxVelocity,
    const ngl::Vec3 &_pos,
    float _initialVelocity,
    const ngl::Vec3 &_aim
    )
{
  EntityTypeMap::iterator it = s_entityTypes.find(_type);
  if(it != s_entityTypes.end())
  {
    // This runs the create function for the specified type and casts the output
    // to a DynamicEntityPtr
    return boost::dynamic_pointer_cast<DynamicEntity>((it->second)(
                                                        _damage,
                                                        _maxVelocity,
                                                        _pos,
                                                        _initialVelocity,
                                                        _aim
                                                        ));
  }
  return DynamicEntityPtr();
}

//-------------------------------------------------------------------//
