#ifndef DATABASE_H
#define DATABASE_H

#include <vector>
#include <list>
#include <ngl/Vec3.h>
#include <QMutexLocker>

#include "smartpointers.h"
#include "fwd/database.h"
#include "databasegrid.h"

DECLARESMART(Database)

//-------------------------------------------------------------------//
/// @file database.h
/// @brief The database class, used to centralise and freeze published
/// variables so that updates can be calculated in parallel
/// @author Peter May
/// @version 1
/// @date 27/11/12
/// Revision History :
/// Initial Version 27/11/12
/// @class Database
//-------------------------------------------------------------------//

class Database
{
public: //methods
  //-------------------------------------------------------------------//
  /// @brief static create method, returns a pointer to a
  /// new instance of the object created from the inputs.
  /// @param [in] _environMaxX, the maximum x value of the playable
  /// environment.
  /// @param [in] _environMaxY, the maximum y value of the playable
  /// environment.
  /// @param [in] _environMinX, the minimum x value of the playable
  /// environment.
  /// @param [in] _environMinY, the minimum y value of the playable
  /// environment.
  /// @param [in] _numCellsX, the desired number of cells in the x
  /// direction
  /// @param [in] _numCellsY, the desired number of cells in the y
  /// direction
  /// @param [out] s_instance, a pointer to the database instance
  //-------------------------------------------------------------------//

  static Database * create(
        int _numCellsX,
        int _numCellsY,
        float _environMaxX,
        float _environMaxY,
        float _environMinX,
        float _environMinY
        );

  //-------------------------------------------------------------------//
  /// @brief static instance method
  /// @param [out] s_instance, a pointer to the static instance
  //-------------------------------------------------------------------//

  static Database *instance();

  //-------------------------------------------------------------------//
  /// @brief destroy method
  //-------------------------------------------------------------------//

  void destroy();

  //-------------------------------------------------------------------//
  /// @brief a method to add an entity record to the grid
  /// @param [in] _type, the type of entity that it is
  /// @param [in] _pos, an ngl vec3 defining the position of the entity
  //-------------------------------------------------------------------//

  void addRecord (EntityRecord _record);

  //-------------------------------------------------------------------//
  /// @brief a method to return a list of entities that are possible
  /// influences for the object requesting the list based on how a
  /// bounding box of the area visible to the entity intersects with
  /// the grid boundaries
  /// @param [in] _minX, the minimum x value of the bounding box provided
  /// @param [in] _maxX, the maximum x value of the bounding box provided
  /// @param [in] _minY, the minimum y value of the bounding box provided
  /// @param [in] _maxY, the maximum y value of the bounding box provided
  /// @param [out] o_influenceList, a boost shared pointer to a list of
  /// influences as defined
  //-------------------------------------------------------------------//

  entityRecordListPtr getLocalEntities (
        float _minX,
        float _minY,
        float _maxX,
        float _maxY,
        std::list<GeneralType> &_typeList
        )const;

  //-------------------------------------------------------------------//
  /// @brief method to clear out the m_grid cell lists
  //-------------------------------------------------------------------//

  void clearRecords();

protected: //methods
  //-------------------------------------------------------------------//
  /// @brief constructor
  /// @param [in] _environMaxX, the maximum x value of the playable
  /// environment.
  /// @param [in] _environMaxY, the maximum y value of the playable
  /// environment.
  /// @param [in] _environMinX, the minimum x value of the playable
  /// environment.
  /// @param [in] _environMinY, the minimum y value of the playable
  /// environment.
  /// @param [in] _numCellsX, the desired number of cells in the x
  /// direction
  /// @param [in] _numCellsY, the desired number of cells in the y
  /// direction
  //-------------------------------------------------------------------//

  Database(
      int _numCellsX,
      int _numCellsY,
      float _environMaxX,
      float _environMaxY,
      float _environMinX,
      float _environMinY
      );

  //-------------------------------------------------------------------//
  /// @brief destructor
  //-------------------------------------------------------------------//

  ~Database();

protected: //attributes
  //-------------------------------------------------------------------//
  /// @brief a vector of pointers to lists of entity records, the entity
  /// records are oredered by their position in 3D space based on a grid
  /// system to reduce positional checks carried out in each update cycle
  /// this database grid stores the enemies that are uploaded
  //-------------------------------------------------------------------//

  DatabaseGridPtr m_enemyGrid;

  //-------------------------------------------------------------------//
  /// @brief this database grid stores the projectiles that are uploaded
  //-------------------------------------------------------------------//

  DatabaseGridPtr m_projectileGrid;

  //-------------------------------------------------------------------//
  /// @brief this database grid stores the turrets that are uploaded
  //-------------------------------------------------------------------//

  DatabaseGridPtr m_turretGrid;

  //-------------------------------------------------------------------//
  /// @brief this database grid stores the walls that are uploaded
  //-------------------------------------------------------------------//

  DatabaseGridPtr m_wallGrid;

  //-------------------------------------------------------------------//
  /// @brief this database grid stores the nodes that are uploaded
  //-------------------------------------------------------------------//

  DatabaseGridPtr m_nodeGrid;

  //-------------------------------------------------------------------//
  /// @brief this variable stores the base
  //-------------------------------------------------------------------//

  EntityRecord m_base;

  //-------------------------------------------------------------------//
  /// @brief a varieable to store whether or not the base has been set
  //-------------------------------------------------------------------//

  bool m_isBaseSet;

  //-------------------------------------------------------------------//
  /// @brief unique instance of singleton
  //-------------------------------------------------------------------//

  static Database * s_instance;

};

#endif // DATABASE_H
