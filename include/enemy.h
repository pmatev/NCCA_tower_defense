#ifndef ENEMY_H
#define ENEMY_H

#include "smartpointers.h"
#include "dynamicentity.h"
#include "node.h"

//-------------------------------------------------------------------//
/// @file enemy.h
/// @brief This is an intermediate class that individual enemies
/// inherit from which sets the m_general type of the entity
/// @author Peter May
/// @version 1
/// @date 4/12/12
/// Revision History :
/// Initial Version 4/12/12
/// @class Enemy
//-------------------------------------------------------------------//

DECLARESMARTLIST(Enemy)

DECLARESMARTVEC(Enemy)

class Enemy : public DynamicEntity
{
public:
  //-------------------------------------------------------------------//
  /// @brief a parameterised constructor
  /// @param [in] _damage, a float to initialise the damage value
  /// @param [in] _maxVelocity, a float value describing the maximum
  /// velocity of the dynamic entity
  /// @param [in] _pos, a vector containing the initial position in 3D
  /// space of the entity, passed to the entity constructor
  /// @param[in] _initialVelocity, the starting velocity of the enemy
  //-------------------------------------------------------------------//

  Enemy(
        const ngl::Vec3 &_pos,
        const ngl::Vec3 &_aim,
        unsigned int _id,
        int _currencyValue,
        float _maxPathDistance
        );

  //-------------------------------------------------------------------//
  /// @brief updates path from node manager
  /// @param[out] the NodeList containing the nodes in the path
  //-------------------------------------------------------------------//
  bool generateTempPath();

  //-------------------------------------------------------------------//
  /// @brief updates path from node manager
  /// @param[out] the NodeList containing the nodes in the path
  //-------------------------------------------------------------------//
  void finalisePath();

  //-------------------------------------------------------------------//
  /// @brief updates path from node manager
  /// @param[out] the NodeList containing the nodes in the path
  //-------------------------------------------------------------------//
  Node::NodeWList getPath() const;

  //-------------------------------------------------------------------//
  /// @brief a method to enforce the grid boundaries
  //-------------------------------------------------------------------//

  void enforceGridBoundaries();


  //-------------------------------------------------------------------//
  /// @brief a method to return the currency value
  /// @param [out] the currency value of the enemy
  //-------------------------------------------------------------------//

  inline int getCurrencyValue() const {return m_currencyValue;}

  //-------------------------------------------------------------------//
  /// @brief a method to detect collisions based on a sphere and the
  /// square distances from the position passed in
  /// @param [in] _pos, the position of the object to check against
  /// @param [in] _radius,the radius of the sphere to check against
  /// @param [out] boolean, whether there was a collision or not
  //-------------------------------------------------------------------//

  bool sphereBBoxCollision(const ngl::Vec3  &_pos,
                           float _radius) const;

  //-------------------------------------------------------------------//
  /// @brief a method to enforce the grid boundaries
  //-------------------------------------------------------------------//

  inline float getPathTargetThreshold(){return m_pathTargetThreshold;}

  //-------------------------------------------------------------------//
  /// @brief set enemy to try to regenerate it's path on the next update
  //-------------------------------------------------------------------//
  inline void needsNewPath(){m_needNewPath = true;}

  //-------------------------------------------------------------------//
  /// @brief prepare for update
  //-------------------------------------------------------------------//
  void prepareForUpdate();

  //-------------------------------------------------------------------//
  /// @brief get the maximum distance the enemy can stray from the path
  //-------------------------------------------------------------------//

  inline float getMaxPathDistance() const {return m_maxPathDistance;}

protected:
  //-------------------------------------------------------------------//
  /// @brief a list containing all the nodes in the path
  //-------------------------------------------------------------------//
  Node::NodeWList m_pathNodes;

  //-------------------------------------------------------------------//
  /// @brief a list temporary location for thepath nodes
  //-------------------------------------------------------------------//
  Node::NodeWList m_tempPathNodes;

  //-------------------------------------------------------------------//
  /// @brief this boolean should be set when the path needs regenerating
  //-------------------------------------------------------------------//

  bool m_needNewPath;

  //-------------------------------------------------------------------//
  /// @brief the maximum distance the enemy can be away from the closest
  /// node in its path without regenerating the path.
  //-------------------------------------------------------------------//

  float m_maxPathDistance;

  //-------------------------------------------------------------------//
  /// @brief The distance from a node at which the enemy starts following
  /// the next node (used in getPathVec() )
  //-------------------------------------------------------------------//

  float m_pathTargetThreshold;

  //-------------------------------------------------------------------//
  /// @brief the amount of currency given to the player when killed
  //-------------------------------------------------------------------//

  int m_currencyValue;
};

#endif // ENEMY_H
