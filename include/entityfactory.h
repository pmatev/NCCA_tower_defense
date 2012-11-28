#ifndef ENTITYFACTORY_H
#define ENTITYFACTORY_H

#include "dynamicentity.h"
#include "smartpointers.h"
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
//-------------------------------------------------------------------//

DECLARESMART(EntityFactory)

//-------------------------------------------------------------------//

class EntityFactory
{
public:
  //-------------------------------------------------------------------//
  /// @brief typedef to manage callbacks
  //-------------------------------------------------------------------//

  typedef EntityPtr (*createCallBack)(float _damage,float _maxVelocity,const ngl::Vec3 &_pos);

  //-------------------------------------------------------------------//
  /// @brief typedef to hold the map of all the possible types
  //-------------------------------------------------------------------//

  typedef std::map<std::string, EntityFactory::createCallBack> EntityTypeMap;

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
  /// @brief this method registers all the possible Entity types. This
  /// could be done externally but it can be useful to do it all in one
  /// go
  //-------------------------------------------------------------------//

  static void initialiseFactory();

  //-------------------------------------------------------------------//
  /// @brief add the specified type and constuct method to the list of
  /// possible types
  /// @param[in] _type, a string referring to the type's name
  /// @param[in] _cb, the callback method (the create method of the class)
  //-------------------------------------------------------------------//

  static void registerEntity(const std::string _type, createCallBack _cb);

  //-------------------------------------------------------------------//
  /// @brief remove the specified type from the list of possible types
  /// @param[in] _type, a string referring to the type that should be
  /// removed
  //-------------------------------------------------------------------//

  static void unregisterEntity(const std::string _type);

  //-------------------------------------------------------------------//
  /// @brief create DynamicEntity and return pointer to it
  /// @param[in] _type, type of DynamicEntity to create
  /// @param[in] _damage, damage that enemy can do
  /// @param[in] _maxVelocity, maximum velocity an enemy can travel at
  /// @param[in] _pos, initital position of enemy
  //-------------------------------------------------------------------//
  static DynamicEntityPtr createDynamicEntity(
      std::string _type,
      float _damage,
      float _maxVelocity,
      const ngl::Vec3 &_pos
      );

protected:
  static EntityTypeMap s_entityTypes;
};



#endif // ENTITYFACTORY_H
