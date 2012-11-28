#ifndef ENTITY_H
#define ENTITY_H

#include <boost/shared_ptr.hpp>
#include <ngl/Vec3.h>

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
  /// @brief a method which will publish the entity's position to the
  /// central database
  //-------------------------------------------------------------------//

  void publish();

  //-------------------------------------------------------------------//
  /// @brief method to return the health value
  /// @param [out] m_health, the health value of the entity
  //-------------------------------------------------------------------//

  inline float getHealth() const {return m_health;}

protected:

  //-------------------------------------------------------------------//
  /// @brief the vector to store the position of the entity
  //-------------------------------------------------------------------//

  ngl::Vec3 m_pos;

  //-------------------------------------------------------------------//
  /// @brief the health value of the entity
  //-------------------------------------------------------------------//

  float m_health;
};

typedef boost::shared_ptr<Entity> EntityPtr;

#endif // ENTITY_H
