#ifndef ENTITYFACTORY_H
#define ENTITYFACTORY_H

#include "dynamicentity.h"
#include "staticentity.h"
#include "node.h"
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
  /// @brief typedef to manage callbacks for DynamicEntity creation
  //-------------------------------------------------------------------//

  typedef EntityPtr (*dynamicEntityCallBack)(
        const ngl::Vec3 &_pos,
        const ngl::Vec3 &_aim,
        unsigned int _id
        );

  //-------------------------------------------------------------------//
  /// @brief typedef to manage callbacks for DynamicEntity creation
  //-------------------------------------------------------------------//
  typedef EntityPtr (*staticEntityCallBack)(
        NodePtr _node,
        unsigned int _id
        );

  //typedef void (*initCallBack)();

  //-------------------------------------------------------------------//
  /// @brief typedef to hold the map of all the possible types
  //-------------------------------------------------------------------//

  typedef std::map<std::string, EntityFactory::dynamicEntityCallBack>
      DynamicEntityTypeMap;

  //-------------------------------------------------------------------//
  /// @brief typedef to hold the map of all the possible types
  //-------------------------------------------------------------------//
  typedef std::map<std::string, EntityFactory::staticEntityCallBack>
      StaticEntityTypeMap;

public:
  //-------------------------------------------------------------------//
  /// @brief constructor
  //-------------------------------------------------------------------//

  inline EntityFactory(){;}

  //-------------------------------------------------------------------//
  /// @brief destructor
  //-------------------------------------------------------------------//

  inline ~EntityFactory(){;}

  //-------------------------------------------------------------------//
  /// @brief this method registers all the possible Entity types. This
  /// could be done externally but it can be useful to do it all in one
  /// go
  //-------------------------------------------------------------------//

  static void initialiseFactory();

  //-------------------------------------------------------------------//
  /// @brief add the specified type and constuct method to the list of
  /// possible types
  /// @param[in] _type a string referring to the type's name
  /// @param[in] _cb the callback method (the create method of the class)
  //-------------------------------------------------------------------//

  static void registerDynamicEntity(
        const std::string _type,
        dynamicEntityCallBack _cb
        );

  //-------------------------------------------------------------------//
  /// @brief add the specified type and constuct method to the list of
  /// possible types
  /// @param[in] _type a string referring to the type's name
  /// @param[in] _cb the callback method (the create method of the class)
  //-------------------------------------------------------------------//

  static void registerStaticEntity(
        const std::string _type,
        staticEntityCallBack _cb
        );

  //-------------------------------------------------------------------//
  /// @brief remove the specified type from the list of possible types
  /// @param[in] _type a string referring to the type that should be
  /// removed
  //-------------------------------------------------------------------//

  static void unregisterDynamicEntity(const std::string &_type);

  //-------------------------------------------------------------------//
  /// @brief remove the specified type from the list of possible types
  /// @param[in] _type a string referring to the type that should be
  /// removed
  //-------------------------------------------------------------------//

  static void unregisterStaticEntity(const std::string &_type);

  //-------------------------------------------------------------------//
  /// @brief create DynamicEntity and return pointer to it
  /// @param[in] _type type of DynamicEntity to create
  /// @param[in] _pos initital position of enemy
  /// @param[in] _aim intitial aim of enemy
  //-------------------------------------------------------------------//
  static DynamicEntityPtr createDynamicEntity(
        const std::string &_type,
        const ngl::Vec3 &_pos,
        const ngl::Vec3 &_aim
        );

  //-------------------------------------------------------------------//
  /// @brief create StaticEntity and return pointer to it
  /// @param[in] _type type of StaticEntity to create
  /// @param[in] _node which node to create the StaticEntity on
  //-------------------------------------------------------------------//

  static StaticEntityPtr createStaticEntity(
        const std::string &_type,
        NodePtr _node
        );

protected:
  //-------------------------------------------------------------------//
  /// @brief map of all possible DynamicEntity type names to their corresponding
  /// create method
  //-------------------------------------------------------------------//
  static DynamicEntityTypeMap s_dynamicEntityTypes;

  //-------------------------------------------------------------------//
  /// @brief map of all possible StaticEntity type names to their corresponding
  /// create method
  //-------------------------------------------------------------------//
  static StaticEntityTypeMap s_staticEntityTypes;
};

#endif // ENTITYFACTORY_H
