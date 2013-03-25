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
  /// @param[in] _info all information relating to the creation of the
  /// environment
  //-------------------------------------------------------------------//

  static EnvironmentPtr create(
        const EnvironmentInfo &_info
        );

  //-------------------------------------------------------------------//
  /// @brief update all turrets
  /// @param [in] _dt the timestep in seconds
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
  //-------------------------------------------------------------------//

  void createTower(
        const std::string &_type,
        NodePtr _centerNode
        );

  //-------------------------------------------------------------------//
  /// @brief remove a tower
  /// @param[in] _tower iterator to the tower
  //-------------------------------------------------------------------//
  void removeTower(StaticEntityList::iterator _tower);

  //-------------------------------------------------------------------//
  /// @brief get the position of the base
  /// @return position of base
  //-------------------------------------------------------------------//
  ngl::Vec3 getBasePos();

  //-------------------------------------------------------------------//
  /// @brief get health value of base
  /// @return health of base
  //-------------------------------------------------------------------//
  float getBaseHealth() const ;

  //-------------------------------------------------------------------//
  /// @brief get a weak pointer to the node manager
  /// @return weak pointer to the node manager
  //-------------------------------------------------------------------//
  NodeManagerWPtr getNodeManagerWeakPtr();

  //-------------------------------------------------------------------//
  /// @brief recalculate all the path-finding values in NodeManager
  //-------------------------------------------------------------------//
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

  //-------------------------------------------------------------------//
  /// @brief create a hexagon shape out of invisible walls. This can be used
  /// for creating maps in a hexagon shape.
  /// @param[in] _gridX size in X
  /// @param[in] _gridZ size in Z
  /// @param[in] _start the coordinate of the bottom left corner of the hexagon.
  /// @param[out] o_coords the list of coordinates for the invisible walls
  //-------------------------------------------------------------------//
  void createHexagonShape(
        int _gridX,
        int _gridZ,
        const ngl::Vec2 &_start,
        int _size,
        std::list<ngl::Vec2> &o_coords
        );

private:

  //-------------------------------------------------------------------//
  /// @brief ctor
  /// @param[in] _info information relating to Environment creation
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
  /// @param[in] _gridWidth width of the grid
  /// @param[in] _gridHeight height of the grid
  /// @param[in] _hexagonSize size of each hexagon
  /// @param[in] _baseX coord of base in X
  /// @param[in] _baseY coord of base in Y
  /// @param[in] _dbGridX database grid resolution in X
  /// @param[in] _dbGridY database grid resolution in Y
  /// @param[in] _spawnCoords list of coords for each spawn point
  /// @param[in] _inivisibleCoords list of coords for each invisisible wall
  /// @param[in] _wallCoords list of coords for each standard wall
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
  /// @param[in] _gridWidth width of the grid
  /// @param[in] _gridHeight height of the grid
  /// @param[in] _hexagonSize size of each hexagon
  /// @param[in] _baseX coord of base in X
  /// @param[in] _baseZ coord of base in Z
  /// @param[in] _dbGridX database grid resolution in X
  /// @param[in] _dbGridZ database grid resolution in Z
  /// @param[in] _spawnCoords list of coords for each spawn point
  /// @param[in] _inivisibleCoords list of coords for each invisisible wall
  /// @param[in] _wallCoords list of coords for each standard wall
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
  //-------------------------------------------------------------------//
  /// @brief width of the grid
  //-------------------------------------------------------------------//
  int m_gridWidth;

  //-------------------------------------------------------------------//
  /// @brief height of the grid
  //-------------------------------------------------------------------//
  int m_gridHeight;

  //-------------------------------------------------------------------//
  /// @brief size of each hexagon
  //-------------------------------------------------------------------//
  float m_hexagonSize;

  //-------------------------------------------------------------------//
  /// @brief X coord of base
  //-------------------------------------------------------------------//
  int m_baseX;

  //-------------------------------------------------------------------//
  /// @brief Z coord of base
  //-------------------------------------------------------------------//
  int m_baseZ;

  //-------------------------------------------------------------------//
  /// @brief database resolution in X
  //-------------------------------------------------------------------//
  int m_dbGridX;

  //-------------------------------------------------------------------//
  /// @brief database resolution in Z
  //-------------------------------------------------------------------//
  int m_dbGridZ;

  //-------------------------------------------------------------------//
  /// @brief list of spawn coordinates
  //-------------------------------------------------------------------//
  const std::vector<ngl::Vec2> m_spawnCoords;

  //-------------------------------------------------------------------//
  /// @brief list of invisible wall coords
  //-------------------------------------------------------------------//
  const std::vector<ngl::Vec2> m_invisibleCoords;

  //-------------------------------------------------------------------//
  /// @brief list of standard wall coords
  //-------------------------------------------------------------------//
  const std::vector<ngl::Vec2> m_wallCoords;
};

#endif // ENVIRONMENT_H
