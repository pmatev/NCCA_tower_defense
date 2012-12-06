#include <boost/pointer_cast.hpp>

#include "entityfactory.h"
#include "concrete/testenemy.h"

EntityFactory::DynamicEntityTypeMap EntityFactory::s_dynamicEntityTypes;
EntityFactory::StaticEntityTypeMap EntityFactory::s_staticEntityTypes;

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
  registerDynamicEntity("TestEnemy", TestEnemy::create);
}

void EntityFactory::registerDynamicEntity(
    const std::string _type,
    dynamicEntityCallBack _cb
    )
{
  s_dynamicEntityTypes[_type] = _cb;
}

void EntityFactory::registerStaticEntity(
    const std::string _type,
    staticEntityCallBack _cb
    )
{
  s_staticEntityTypes[_type] = _cb;
}


void EntityFactory::unregisterDynamicEntity(const std::string _type)
{
  s_dynamicEntityTypes.erase(_type);
}

void EntityFactory::unregisterStaticEntity(const std::string _type)
{
  s_staticEntityTypes.erase(_type);
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
  DynamicEntityTypeMap::iterator it = s_dynamicEntityTypes.find(_type);
  if(it != s_dynamicEntityTypes.end())
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


StaticEntityPtr EntityFactory::createStaticEntity(
    std::string _type,
    NodePtr _node
    )
{
  StaticEntityTypeMap::iterator it = s_staticEntityTypes.find(_type);
  if(it != s_staticEntityTypes.end())
  {
    // This runs the create function for the specified type and casts the output
    // to StaticEntityPtr
    return boost::dynamic_pointer_cast<StaticEntity>((it->second)(
                                                        _node
                                                        ));
  }
  return StaticEntityPtr();
}

//-------------------------------------------------------------------//
