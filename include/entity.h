#ifndef ENTITY_H
#define ENTITY_H

#include <ngl/Vec3.h>

#include "smartpointers.h"

//-------------------------------------------------------------------//
/// @file entity.h
/// @brief The base class for all renderable objects in the game
/// @author Peter May
/// @version 1
/// @date 22/11/12
/// Revision History :
/// Initial Version 22/11/12
/// @class Entity
//-------------------------------------------------------------------//

DECLARESMART(Entity)

class Entity
{
public:
  //-------------------------------------------------------------------//
  /// @brief a parameterised constructor
  /// @param [in] _pos, a vector containing the initial position in 3D
  /// space of the entity
  /// @param [in] _health, the initial health value of the entity
  //-------------------------------------------------------------------//

  Entity(const ngl::Vec3 & _pos);


  //-------------------------------------------------------------------//
  /// @brief the destructor
  //-------------------------------------------------------------------//

  ~Entity();

  //-------------------------------------------------------------------//
  /// @brief a virtual method which will update the entity when
  /// implemented in child classes
  //-------------------------------------------------------------------//

  virtual void update()=0;

  //-------------------------------------------------------------------//
  /// @brief a virtual method which will draw the entity when
  /// implemented in child classes
  //-------------------------------------------------------------------//

  virtual void draw() const = 0;

  //-------------------------------------------------------------------//
  /// @brief a virtual method that draws the selection frame (where each
  /// object is rendered with a colour based on it's id)
  //-------------------------------------------------------------------//

  virtual void drawSelection() const = 0;

  //-------------------------------------------------------------------//
  /// @brief a method which will publish the entity's position to the
  /// central database
  //-------------------------------------------------------------------//

  void publish();

  //-------------------------------------------------------------------//
  /// @brief method to return the health value
  /// @param [out] m_health, the health value of the entity
  //-------------------------------------------------------------------//

  inline float getHealth() const {return m_health;}

  //-------------------------------------------------------------------//
  /// @brief method to get the ID of the entity
  //-------------------------------------------------------------------//

  inline unsigned int getID() const {return m_ID;}

protected:

  //-------------------------------------------------------------------//
  /// @brief Identifier for the entity
  //-------------------------------------------------------------------//

  unsigned int m_ID;

  //-------------------------------------------------------------------//
  /// @brief the vector to store the position of the entity
  //-------------------------------------------------------------------//

  ngl::Vec3 m_pos;

  //-------------------------------------------------------------------//
  /// @brief the health value of the entity
  //-------------------------------------------------------------------//

  float m_health;
};


#endif // ENTITY_H
