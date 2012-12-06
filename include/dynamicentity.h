 #ifndef DYNAMICENTITY_H
#define DYNAMICENTITY_H

#include <boost/shared_ptr.hpp>

#include "entity.h"

//-------------------------------------------------------------------//
/// @file dynamicentity.h
/// @brief The base class for all moving renderable objects in the
/// game
/// @author Peter May, Jared Auty
/// @version 1
/// @date 22/11/12
/// Revision History :
/// Initial Version 22/11/12
/// @class DynamicEntity
//-------------------------------------------------------------------//

DECLARESMARTLIST(DynamicEntity)

class DynamicEntity : public Entity
{
public:
  //-------------------------------------------------------------------//
  /// @brief a parameterised constructor
  /// @param [in] _damage, a float to initialise the damage value
  /// @param [in] __maxVelocity, a float value describing the maximum
  /// velocity of the dynamic entity
  /// @param [in] _pos, a vector containing the initial position in 3D
  /// space of the entity, passed to the entity constructor
  /// @param [in] _initialVelocity, the starting velocity of the enemy
  /// @param [in] _aimVector, its initial aim
  /// @param [in] _type, the general type of the entity
  //-------------------------------------------------------------------//

  DynamicEntity(
      float _damage,
      float _maxVelocity,
      const ngl::Vec3 &_pos,
      float _initialVelocity,
      const ngl::Vec3 &_aimVector,
      GeneralType _type
      );

  //-------------------------------------------------------------------//
  /// @brief the destructor
  //-------------------------------------------------------------------//

  ~DynamicEntity();

  //-------------------------------------------------------------------//
  /// @brief update the objects position based on the brain output
  //-------------------------------------------------------------------//

  void update();

  //-------------------------------------------------------------------//
  /// @brief method to check whether or not an object has collided with
  /// a bounding box
  /// @param [in] _wsBBox the world space bounding box to test collisions
  /// against
  /// @param [out] a boolean value describing whether or not a collision
  /// has occured
  //-------------------------------------------------------------------//

  bool collisionTest (BBox _wsBBox);

  //-------------------------------------------------------------------//
  /// @brief a method to generate and return a code for a point based on
  /// its location in space compared to the bounding box
  /// @param [in] _point, the point to generate the code for
  /// @param [in] _wsBBox, the world space bounding box to check against
  /// @param [out]
  //-------------------------------------------------------------------//

  char genClippingCode(const ngl::Vec3& _point, BBox _wsBBox);

  //-------------------------------------------------------------------//
  /// @brief a method to return the point of intersection of a line with
  /// a plane. the plane is perpendicular to one of the axis, and that
  /// axis is defined by whichever pair of extents are equal
  /// @param [in] _point1 the first point of the line
  /// @param [in] _point2 the second point of the line
  /// @param [in] _planeExtents the extents of the plane in world space
  /// @param [out] bool value stating whether or not the line intersects
  /// the plane
  //-------------------------------------------------------------------//
  bool isIntersecting(
        const ngl::Vec3 &_point1,
        const ngl::Vec3 &_point2,
        BBox _planeExtents);

protected:
  //-------------------------------------------------------------------//
  /// @brief a virtual brain method, to be implemented in children
  /// @param [out] a vector which will be used to define the behaviour
  /// of the dynamic entity
  //-------------------------------------------------------------------//

  virtual ngl::Vec3 brain() = 0;

protected:
  //-------------------------------------------------------------------//
  /// @brief a damage value for the dynamic entity
  //-------------------------------------------------------------------//

  float m_damage;

  //-------------------------------------------------------------------//
  /// @brief The the aim vector of the dynamic entity
  //-------------------------------------------------------------------//

  ngl::Vec3 m_aimVector;

  //-------------------------------------------------------------------//
  /// @brief The maximum velocity of the dynamic entity
  //-------------------------------------------------------------------//

  float m_maxVelocity;

  //-------------------------------------------------------------------//
  /// @brief the current velocity of the dynamic entity
  //-------------------------------------------------------------------//

  float m_currentVelocity;

  //-------------------------------------------------------------------//
  /// @brief a vector storing the previous position of the dynamic entity
  //-------------------------------------------------------------------//

  ngl::Vec3 m_prevPos;
};



#endif // DYNAMICENTITY_H
