#ifndef DATABASE_H
#define DATABASE_H

#include <vector>
#include <list>
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

  static Database * init(
        int _numCellsX,
        int _numCellsZ,
        float _environMaxX,
        float _environMaxZ,
        float _environMinX,
        float _environMinZ
        );

  //-------------------------------------------------------------------//
  /// @brief static instance method
  /// @param [out] s_instance a pointer to the static instance
  //-------------------------------------------------------------------//

  static Database *instance();

  //-------------------------------------------------------------------//
  /// @brief destroy method
  //-------------------------------------------------------------------//

  void destroy();

  //-------------------------------------------------------------------//
  /// @brief a method to add an entity record to the grid
  /// @param [in] _record a pointer to the record to be added
  //-------------------------------------------------------------------//

  void addRecord (EntityRecordPtr _record);

  //-------------------------------------------------------------------//
  /// @brief a method to return a list of entities that are possible
  /// influences for the object requesting the list based on how a
  /// bounding box of the area visible to the entity intersects with
  /// the grid boundaries
  /// @param [in][out] o_newList, a boost shared pointer to a list of
  /// influences as defined
  /// @param [in] _minX the minimum x value of the bounding box provided
  /// @param [in] _maxX the maximum x value of the bounding box provided
  /// @param [in] _minY the minimum y value of the bounding box provided
  /// @param [in] _maxY the maximum y value of the bounding box provided
  /// @param [in] _typlist a reference to a list of GeneralTypes,
  /// defines which records to return
  //-------------------------------------------------------------------//

  void getLocalEntities (
        EntityRecordWCList &o_newList,
        float _minX,
        float _minZ,
        float _maxX,
        float _maxZ,
        std::list<GeneralType> &_typeList
        )const;

  //-------------------------------------------------------------------//
  /// @brief gets the base record
  /// @param [in][out] o_baseRecord a reference to the const weak pointer
  /// that will be set to point to the base record
  //-------------------------------------------------------------------//

  void getBaseRecord(EntityRecordWCPtr &o_baseRecord);

  //-------------------------------------------------------------------//
  /// @brief method to clear out the dynamic database grids
  //-------------------------------------------------------------------//

  void clearRecords();

  //-------------------------------------------------------------------//
  /// @brief a method to remove an entity record from the appropriate grid
  /// based on the type passed in and the id of the individual entity
  /// @param [in] _generalType, the type of the entity used to establish
  /// which grid to remove the entity from
  /// @param [in] _id, the id of the entity whose corresponding record is
  /// being removed
  //-------------------------------------------------------------------//

  void unPublish (GeneralType _generalType, unsigned int _id);

  //-------------------------------------------------------------------//
  /// @brief a method to return the minimum extents of the grid
  /// @param [out] the minimum extents of the grid
  //-------------------------------------------------------------------//

  inline ngl::Vec2 getMinGridExtents() {
    return ngl::Vec2(
          m_environmentMinX + 1,
          m_environmentMinZ + 1);
  }

  //-------------------------------------------------------------------//
  /// @brief a method to return the maximum extents of the grid
  /// @param [out] the maximum extents of the grid
  //-------------------------------------------------------------------//

  inline ngl::Vec2 getMaxGridExtents() {
    return ngl::Vec2(
          m_environmentMaxX - 1,
          m_environmentMaxZ - 1);
  }

protected: //methods
  //-------------------------------------------------------------------//
  /// @brief constructor
  /// @param [in] _numCellsX, the desired number of cells in the x
  /// direction
  /// @param [in] _numCellsZ, the desired number of cells in the z
  /// direction
  /// @param [in] _environMaxX, the maximum x value of the playable
  /// environment.
  /// @param [in] _environMaxZ, the maximum z value of the playable
  /// environment.
  /// @param [in] _environMinX, the minimum x value of the playable
  /// environment.
  /// @param [in] _environMinZ, the minimum z value of the playable
  /// environment.
  //-------------------------------------------------------------------//

  Database(
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

  ~Database();

protected: //attributes
  //-------------------------------------------------------------------//
  /// @brief this database grid stores the enemies that are uploaded
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

  EntityRecordPtr m_base;

  //-------------------------------------------------------------------//
  /// @brief a varieable to store whether or not the base has been set
  //-------------------------------------------------------------------//

  bool m_isBaseSet;

  //-------------------------------------------------------------------//
  /// @brief unique instance of singleton
  //-------------------------------------------------------------------//

  static Database * s_instance;

  //-------------------------------------------------------------------//
  /// @brief a variable to store the maximum x value of the grid
  //-------------------------------------------------------------------//

  float m_environmentMaxX;

  //-------------------------------------------------------------------//
  /// @brief a variable to store the minimum x value of the grid
  //-------------------------------------------------------------------//

  float m_environmentMinX;

  //-------------------------------------------------------------------//
  /// @brief a variable to store the maximum z value of the grid
  //-------------------------------------------------------------------//

  float m_environmentMaxZ;

  //-------------------------------------------------------------------//
  /// @brief a variable to store the minimum z value of the grid
  //-------------------------------------------------------------------//

  float m_environmentMinZ;

};

#endif // DATABASE_H
