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
/// @class EnvironmentInfo
//-------------------------------------------------------------------//

DECLARESMART(Environment)
DECLARESMART(EnvironmentInfo)

class Environment
{

public:

  //-------------------------------------------------------------------//
  /// @brief creator
  //-------------------------------------------------------------------//

  static EnvironmentPtr create(
        const EnvironmentInfo &_info
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

  float getBaseHealth() const ;

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
  //-------------------------------------------------------------------//
  /// @brief make sure that all nodes are are used in the paths between
  /// spawn nodes and the goal are highlighted.
  //-------------------------------------------------------------------//

  void resetSpawnPathHighlighting();

private:

  //-------------------------------------------------------------------//
  /// @brief ctor
  //-------------------------------------------------------------------//

  Environment(
        const EnvironmentInfo &_info
        );
};

//-------------------------------------------------------------------//
/// @brief This is a class to collect together all the data related to creating
/// the environment
//-------------------------------------------------------------------//

class EnvironmentInfo
{
public:
  //-------------------------------------------------------------------//
  /// @brief creator (used for easily creating pointers)
  //-------------------------------------------------------------------//

  inline static EnvironmentInfoPtr create(
      int _gridWidth,
      int _gridHeight,
      float _hexagonSize,
      int _baseX,
      int _baseZ,
      int _dbGridX,
      int _dbGridZ,
      const std::vector<ngl::Vec2> &_spawnCoords,
      const std::vector<ngl::Vec2> &_invisibleCoords,
      const std::vector<ngl::Vec2> &_wallCoords
      )
  {
    EnvironmentInfoPtr a(
          new EnvironmentInfo(
            _gridWidth,
            _gridHeight,
            _hexagonSize,
            _baseX,
            _baseZ,
            _dbGridX,
            _dbGridZ,
            _spawnCoords,
            _invisibleCoords,
            _wallCoords
            )
          );
    return a;
  }
  //-------------------------------------------------------------------//
  /// @brief ctor
  //-------------------------------------------------------------------//

  inline EnvironmentInfo(
      int _gridWidth,
      int _gridHeight,
      float _hexagonSize,
      int _baseX,
      int _baseZ,
      int _dbGridX,
      int _dbGridZ,
      const std::vector<ngl::Vec2> &_spawnCoords,
      const std::vector<ngl::Vec2> &_invisibleCoords,
      const std::vector<ngl::Vec2> &_wallCoords
      ):
    m_gridWidth(_gridWidth),
    m_gridHeight(_gridHeight),
    m_hexagonSize(_hexagonSize),
    m_baseX(_baseX),
    m_baseZ(_baseZ),
    m_dbGridX(_dbGridX),
    m_dbGridZ(_dbGridZ),
    m_spawnCoords(_spawnCoords),
    m_invisibleCoords(_invisibleCoords),
    m_wallCoords(_wallCoords)
  {;}

public:
  int m_gridWidth;
  int m_gridHeight;
  float m_hexagonSize;
  int m_baseX;
  int m_baseZ;
  int m_dbGridX;
  int m_dbGridZ;
  const std::vector<ngl::Vec2> m_spawnCoords;
  const std::vector<ngl::Vec2> m_invisibleCoords;
  const std::vector<ngl::Vec2> m_wallCoords;
};

#endif // ENVIRONMENT_H
