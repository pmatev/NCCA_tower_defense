#ifndef STATICENTITY_H
#define STATICENTITY_H

#include <vector>

#include "entity.h"
#include "node.h"

//-------------------------------------------------------------------//
/// @file staticentity.h
/// @brief The base class for all un-moving renderable objects in the
/// game
/// @author Peter May, Jared Auty
/// @version 1
/// @date 23/11/12
/// Revision History :
/// Initial Version 23/11/12
/// @class StaticEntity
//-------------------------------------------------------------------//

DECLARESMARTLIST(StaticEntity)

class StaticEntity : public Entity
{
public:
  //-------------------------------------------------------------------//
  /// @brief a parameterised constructor
  /// @param [in] _linkedNode, a smart pointer to the linked node
  /// @param [in] _type, the general type of the entity
  /// @param[in] _id ID of entity
  //-------------------------------------------------------------------//

  StaticEntity(
        NodePtr _linkedNode,
        GeneralType _type,
        unsigned int _id
        );

  //-------------------------------------------------------------------//
  /// @brief destructor
  //-------------------------------------------------------------------//

  ~StaticEntity();

  //-------------------------------------------------------------------//
  /// @brief a method to increment the level of the static entity
  //-------------------------------------------------------------------//

  inline void incrementLevel () {m_level++;}

  //-------------------------------------------------------------------//
  /// @brief a method to decrement the level of the static entity
  //-------------------------------------------------------------------//

  inline void decrementLevel () {m_level--;}

  //-------------------------------------------------------------------//
  /// @brief get the node that the entity is sitting on
  //-------------------------------------------------------------------//

  inline NodeWPtr getLinkedNode() const {return m_linkedNode;}

  //-------------------------------------------------------------------//
  /// @brief recalculate the local entites
  //-------------------------------------------------------------------//
  virtual void prepareForUpdate();

protected:
  //-------------------------------------------------------------------//
  /// @brief The upgrade level of the static entity
  //-------------------------------------------------------------------//

  float m_level;

  //-------------------------------------------------------------------//
  /// @brief a list of pointers to the nodes that are covered by the
  /// static entity
  //-------------------------------------------------------------------//

  NodeWPtr m_linkedNode;
};

#endif // STATICENTITY_H
