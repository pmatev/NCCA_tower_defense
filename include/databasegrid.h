#ifndef DATABASEGRID_H
#define DATABASEGRID_H

#include <vector>
#include <list>

#include "smartpointers.h"
#include "entity.h"

//-------------------------------------------------------------------//
/// @file databasegrid.h
/// @brief The database grid system, a system that stores entity records
/// used to abstract the data store from the database so thjat more than
/// data store can be used for different types
/// @author Peter May
/// @version 1
/// @date 5/12/12
/// Revision History :
/// Initial Version 5/12/12
/// @class DatabaseGrid
//-------------------------------------------------------------------//

DECLARESMART(DatabaseGrid)

class DatabaseGrid
{
public: //methods
  //-------------------------------------------------------------------//
  /// @brief static create method, returns a pointer to a
  /// new instance of the object created from the inputs.
  /// @param [in] _environMaxX, the maximum x value of the playable
  /// environment.
  /// @param [in] _environMaxZ, the maximum Z value of the playable
  /// environment.
  /// @param [in] _environMinX, the minimum x value of the playable
  /// environment.
  /// @param [in] _environMinZ, the minimum Z value of the playable
  /// environment.
  /// @param [in] _numCellsX, the desired number of cells in the x
  /// direction
  /// @param [in] _numCellsZ, the desired number of cells in the Z
  /// direction
  /// @param [out] s_instance, a smart pointer to the database grid
  /// instance
  //-------------------------------------------------------------------//

  static DatabaseGridPtr create(
        int _numCellsX,
        int _numCellsZ,
        float _environMaxX,
        float _environMaxZ,
        float _environMinX,
        float _environMinZ
        );

  //-------------------------------------------------------------------//
  /// @brief destructor
  //-------------------------------------------------------------------//

  ~DatabaseGrid();

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
  /// @param [in] _minZ, the minimum Z value of the bounding box provided
  /// @param [in] _maxZ, the maximum Z value of the bounding box provided
  /// @param [out] a boost shared pointer to a list of
  /// influences as defined
  //-------------------------------------------------------------------//

  entityRecordListPtr getLocalEntities(
        float _minX,
        float _minZ,
        float _maxX,
        float _maxZ
        )const;

  //-------------------------------------------------------------------//
  /// @brief method to clear out the m_grid cell lists
  //-------------------------------------------------------------------//

  void clearRecords();

  //-------------------------------------------------------------------//
  /// @brief a method to remove a specific entity record based on its ID
  /// @param [in] _id the entity's id to check against the record
  //-------------------------------------------------------------------//

  void unPublish(unsigned int _id);

protected: //methods
  //-------------------------------------------------------------------//
  /// @brief constructor
  /// @param [in] _environMaxX, the maximum x value of the playable
  /// environment.
  /// @param [in] _environMaxZ, the maximum Z value of the playable
  /// environment.
  /// @param [in] _environMinX, the minimum x value of the playable
  /// environment.
  /// @param [in] _environMinZ, the minimum Z value of the playable
  /// environment.
  /// @param [in] _numCellsX, the desired number of cells in the x
  /// direction
  /// @param [in] _numCellsZ, the desired number of cells in the y
  /// direction
  //-------------------------------------------------------------------//

  DatabaseGrid(
        int _numCellsX,
        int _numCellsZ,
        float _environMaxX,
        float _environMaxZ,
        float _environMinX,
        float _environMinZ
        );

protected: //attributes
  //-------------------------------------------------------------------//
  /// @brief a vector of pointers to lists of entity records, the entity
  /// records are oredered by their position in 3D space based on a grid
  /// system to reduce positional checks carried out in each update cycle
  //-------------------------------------------------------------------//

  std::vector<entityRecordListPtr> m_grid;

  //-------------------------------------------------------------------//
  /// @brief The normalisation x scale factor of grid, to enable the entity
  /// records to be assigned a grid location based on a unit grid size
  //-------------------------------------------------------------------//

  float m_scaleX;

  //-------------------------------------------------------------------//
  /// @brief The normalisation Z scale factor of grid, to enable the entity
  /// records to be assigned a grid location based on a unit grid size
  //-------------------------------------------------------------------//

  float m_scaleZ;

  //-------------------------------------------------------------------//
  /// @brief the number of cells in X (cell width/grid width)
  //-------------------------------------------------------------------//

  int m_numCellsX;

  //-------------------------------------------------------------------//
  /// @brief the number of cells in Z (cell width/grid width)
  //-------------------------------------------------------------------//

  int m_numCellsZ;


  //-------------------------------------------------------------------//
  /// @brief the x value of the start point of the environment
  //-------------------------------------------------------------------//

  float m_environMinX;

  //-------------------------------------------------------------------//
  /// @brief the Z value of the start point of the environment
  //-------------------------------------------------------------------//

  float m_environMinZ;
};

#endif // DATABASEGRID_H
