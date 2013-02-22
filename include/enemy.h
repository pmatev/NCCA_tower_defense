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
  /// @param [in] __maxVelocity, a float value describing the maximum
  /// velocity of the dynamic entity
  /// @param [in] _pos, a vector containing the initial position in 3D
  /// space of the entity, passed to the entity constructor
  /// @param[in] _initialVelocity, the starting velocity of the enemy
  //-------------------------------------------------------------------//

  Enemy(
        const ngl::Vec3 &_pos,
        const ngl::Vec3 &_aim,
        unsigned int _id
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
  /// @brief returns an aim vector aiming towards the nearest node
  /// in the path
  /// @param[out] an ngl::vec3
  //-------------------------------------------------------------------//
  ngl::Vec3 getVectorToNearestNodeInPath();

  //-------------------------------------------------------------------//
  /// @brief a method to enforce the grid boundaries
  //-------------------------------------------------------------------//

  void enforceGridBoundaries();

protected:

  //-------------------------------------------------------------------//
  /// @brief returns the path influence to be used in the brain
  /// @param[out] an ngl::vec3 towards the next path point
  //-------------------------------------------------------------------//

  ngl::Vec3 getPathVec() const;

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
  /// @brief The distance from a node at which the enemy starts following
  /// the next node (used in getPathVec() )
  //-------------------------------------------------------------------//

  float m_pathTargetThreshold;

};

#endif // ENEMY_H
