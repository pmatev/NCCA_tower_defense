#ifndef ENTITYFACTORY_H
#define ENTITYFACTORY_H

#include <boost/shared_ptr.hpp>

#include "dynamicentity.h"
#include "enemy.h"

//-------------------------------------------------------------------//
/// @file entityfactory.h
/// @brief a class used to create all entities, includes an entity type
/// enum
/// @author Peter May, Jared Auty
/// @version 1
/// @date 27/11/12
/// Revision History :
/// Initial Version 27/11/12
/// @class EntityFactory
/// @enum EntityType
//-------------------------------------------------------------------//

enum EntityType
{
  //-------------------------------------------------------------------//
  //-------------------------TEST-VALUES-------------------------------//
  //-------------------------------------------------------------------//
  ENEMY,
  ENEMYB,
  ENEMYC,
  PROJECTILEA,
  PROJECTILEB
};

//-------------------------------------------------------------------//

class EntityFactory
{
public:
  //-------------------------------------------------------------------//
  /// @brief constructor
  //-------------------------------------------------------------------//

  EntityFactory();

  //-------------------------------------------------------------------//
  /// @brief destructor
  //-------------------------------------------------------------------//

  ~EntityFactory();

  //-------------------------------------------------------------------//
  /// @brief create DynamicEntity and return pointer to it
  /// @param[in] _type, type of DynamicEntity to create
  /// @param[in] _damage, damage that enemy can do
  /// @param[in] _maxVelocity, maximum velocity an enemy can travel at
  /// @param[in] _pos, initital position of enemy
  //-------------------------------------------------------------------//
  static DynamicEntityPtr createDynamicEntity(
      EntityType _type,
      float _damage,
      float _maxVelocity,
      const ngl::Vec3 &_pos
      );
};


typedef boost::shared_ptr<EntityFactory> EntityFactoryPtr;

#endif // ENTITYFACTORY_H
