#include <boost/pointer_cast.hpp>

#include "entityfactory.h"
#include "concrete/testenemy.h"
#include "concrete/testturret.h"
#include "concrete/bullet.h"
#include "game.h"

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

//-------------------------------------------------------------------//

void EntityFactory::initialiseFactory()
{
  // This is where all different types are registered
  registerDynamicEntity("TestEnemy", TestEnemy::create);
  registerDynamicEntity("Bullet", Bullet::create);
  registerStaticEntity("TestTurret", TestTurret::create);
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


void EntityFactory::unregisterDynamicEntity(const std::string &_type)
{
  s_dynamicEntityTypes.erase(_type);
}

void EntityFactory::unregisterStaticEntity(const std::string &_type)
{
  s_staticEntityTypes.erase(_type);
}



//-------------------------------------------------------------------//

DynamicEntityPtr EntityFactory::createDynamicEntity(
    const std::string &_type,
    const ngl::Vec3 &_pos,
    const ngl::Vec3 &_aim
    )
{
  DynamicEntityTypeMap::iterator it = s_dynamicEntityTypes.find(_type);
  if(it != s_dynamicEntityTypes.end())
  {
    // get an instance of the Game class

    Game* game = Game::instance();

    //get an id for the entity

    unsigned int id = game->getID();
    // This runs the create function for the specified type and casts the output
    // to a DynamicEntityPtr
    DynamicEntityPtr de = boost::dynamic_pointer_cast<DynamicEntity>(
          (it->second)(
            _pos,
            _aim,
            id
            )
          );

    //register the entity with the game

    game->registerID(de,id);

    //then return the pointer

    return de;
  }
  return DynamicEntityPtr();
}

//-------------------------------------------------------------------//


StaticEntityPtr EntityFactory::createStaticEntity(
    const std::string &_type,
    NodePtr _node
    )
{
  StaticEntityTypeMap::iterator it = s_staticEntityTypes.find(_type);
  if(it != s_staticEntityTypes.end())
  {
    // get an instance of the Game class

    Game* game = Game::instance();

    //get an id for the entity

    unsigned int id = game->getID();

    // This runs the create function for the specified type and casts the output
    // to StaticEntityPtr
    StaticEntityPtr se = boost::dynamic_pointer_cast<StaticEntity>
        ((it->second)(
           _node,
           id
           ));

    //register the entity with the game

    game->registerID(se,id);
    //then return the pointer

    return se;


  }
  return StaticEntityPtr();
}

//-------------------------------------------------------------------//
