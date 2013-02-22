#ifndef ENVIRONMENT_H
#define ENVIRONMENT_H

#include "smartpointers.h"

#include "staticentity.h"
#include "nodemanager.h"
#include "base.h"

//-------------------------------------------------------------------//
/// @file environment.h
/// @brief This class manages everything about the environment (that is
/// all of the static entities and the map)
/// @author Jared Auty
/// @version 1
/// @date 3/12/12
/// Revision History :
/// Initial Version 3/12/12
/// @class Environment
//-------------------------------------------------------------------//

DECLARESMART(Environment)
DECLAREWEAKSMART(Environment)

class Environment
{

public:

  //-------------------------------------------------------------------//
  /// @brief creator
  //-------------------------------------------------------------------//

  static EnvironmentPtr create(
        int _gridWidth,
        int _gridHeight,
        int _hexagonSize,
        ngl::Vec3 _origin,
        int _baseX,
        int _baseY,
        int _dbGridSizeX,
        int _dbGridSizeZ);

  //-------------------------------------------------------------------//
  /// @brief dtor
  //-------------------------------------------------------------------//

  ~Environment();

  //-------------------------------------------------------------------//
  /// @brief update all turrets
  //-------------------------------------------------------------------//

  void update();

  //-------------------------------------------------------------------//
  /// @brief call all environment to draw
  //-------------------------------------------------------------------//

  void draw() const;

  //-------------------------------------------------------------------//
  /// @brief draw selection based on IDs
  //-------------------------------------------------------------------//

  void drawSelection() const;

  //-------------------------------------------------------------------//
  /// @brief create new static entity
  /// @param[in] _type, type of tower to create
  /// @param[in] _centerNode, node to create the tower on
  /// @param[out] whether the creation was successful or not
  //-------------------------------------------------------------------//

  void createTower(
        const std::string &_type,
        NodePtr _centerNode
        );

  void removeTower(StaticEntityList::iterator _tower);

  ngl::Vec3 getBasePos();

  NodeManagerWeakPtr getNodeManagerWeakPtr();

protected:


  //-------------------------------------------------------------------//
  /// @brief list of all turrets and walls
  //-------------------------------------------------------------------//

  StaticEntityList m_towers;

  //-------------------------------------------------------------------//
  /// @brief base object
  //-------------------------------------------------------------------//

  BasePtr m_base;

  //-------------------------------------------------------------------//
  /// @brief map object
  //-------------------------------------------------------------------//

  NodeManagerPtr m_nodeMap;

protected:



private:

  //-------------------------------------------------------------------//
  /// @brief ctor
  //-------------------------------------------------------------------//

  Environment(
        int _gridWidth,
        int _gridHeight,
        int _hexagonSize,
        ngl::Vec3 _origin,
        int _baseX,
        int _baseY,
        int _dbGridSizeX,
        int _dbGridSizeZ);
};

#endif // ENVIRONMENT_H
