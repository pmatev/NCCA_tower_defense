#ifndef ENVIRONMENT_H
#define ENVIRONMENT_H

#include "smartpointers.h"

#include "staticentity.h"
#include "nodemanager.h"
#include "concrete/base.h"

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
        int _baseY,
        int _dbGridSizeX,
        int _dbGridSizeZ,
        const std::vector<ngl::Vec2> &_spawnCoords
        );

  //-------------------------------------------------------------------//
  /// @brief dtor
  //-------------------------------------------------------------------//

  ~Environment();

  //-------------------------------------------------------------------//
  /// @brief update all turrets
  /// @param [in] _dt, the timestep
  //-------------------------------------------------------------------//

  void update(const double _dt);

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

  NodeManagerWPtr getNodeManagerWeakPtr();

  void recalculateSearchTree();

  //-------------------------------------------------------------------//
  /// @brief get a weak pointer to a vector of weak pointer to the nodes
  /// that should be used for spawning.
  //-------------------------------------------------------------------//

  Node::NodeWVecWPtr getSpawnNodes() const;

  //-------------------------------------------------------------------//
  /// @brief check that all spawn nodes have valid paths to the base
  //-------------------------------------------------------------------//

  bool checkSpawnNodePaths() const;

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

  //-------------------------------------------------------------------//
  /// @brief possible spawn points for waves. This is stored here so that
  /// path checking can make sure these nodes have valid paths and they cannot
  /// themselves be occupied by towers.
  //-------------------------------------------------------------------//

  Node::NodeWVecPtr m_spawnNodes;

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
        int _dbGridSizeZ,
        const std::vector<ngl::Vec2> &_spawnCoords
        );
};

#endif // ENVIRONMENT_H
