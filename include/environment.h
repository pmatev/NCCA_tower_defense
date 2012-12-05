#ifndef ENVIRONMENT_H
#define ENVIRONMENT_H

#include "smartpointers.h"

#include "staticentity.h"
#include "nodemanager.h"

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
        int _baseY);

  //-------------------------------------------------------------------//
  /// @brief dtor
  //-------------------------------------------------------------------//

  ~Environment();

  //-------------------------------------------------------------------//
  /// @brief update all turrets
  //-------------------------------------------------------------------//

  void update();

  //-------------------------------------------------------------------//
  /// @brief call all turrets to publish
  //-------------------------------------------------------------------//

  void publish();

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

  void createTower(const std::string &_type, NodePtr _centerNode);

protected:


  //-------------------------------------------------------------------//
  /// @brief list of all turrets and walls
  //-------------------------------------------------------------------//

  StaticEntityList m_towers;

  //-------------------------------------------------------------------//
  /// @brief base object
  //-------------------------------------------------------------------//

  StaticEntityPtr m_base;

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
        int _baseY);
};

#endif // ENVIRONMENT_H
