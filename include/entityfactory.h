#ifndef ENTITYFACTORY_H
#define ENTITYFACTORY_H

#include <boost/shared_ptr.hpp>

//-------------------------------------------------------------------//
/// @file entityfactory.h
/// @brief a class used to create all entities, includes an entity type
/// enum
/// @author Peter May
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
  ENEMYA,
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
};


typedef boost::shared_ptr<EntityFactory> EntityFactoryPtr;

#endif // ENTITYFACTORY_H
