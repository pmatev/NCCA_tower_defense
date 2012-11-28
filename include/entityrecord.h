#ifndef ENTITYRECORD_H
#define ENTITYRECORD_H

#include<string>

#include "smartpointers.h"

DECLARESMART(EntityRecord)

//-------------------------------------------------------------------//
/// @file entityrecord.h
/// @brief a data store class used within the database that will be
/// used in the update method
/// @author Peter May
/// @version 1
/// @date 28/11/12
/// Revision History :
/// Initial Version 28/11/12
/// @class EntityRecord
//-------------------------------------------------------------------//

class EntityRecord
{
public: //methods
  //-------------------------------------------------------------------//
  /// @brief create method, creates and returns a boost smart pointer
  /// to an Entity Record
  /// @param [in] _type, the string entity type
  /// @param [in] _x, the x position of the entity
  /// @param [in] _y, the y position of the entity
  /// @param [in] _z, the z position of the entity
  /// @param [out]
  //-------------------------------------------------------------------//

  static EntityRecordPtr create(
      const std::string & _type,
      float _x,
      float _y,
      float _z
      );

public: //attributes
  //-------------------------------------------------------------------//
  /// @brief the enumerated entity type
  //-------------------------------------------------------------------//

  std::string m_type;

  //-------------------------------------------------------------------//
  /// @brief the x position of the entity
  //-------------------------------------------------------------------//

  float m_x;

  //-------------------------------------------------------------------//
  /// @brief the y position of the entity
  //-------------------------------------------------------------------//

  float m_y;

  //-------------------------------------------------------------------//
  /// @brief the z position of the entity
  //-------------------------------------------------------------------//

  float m_z;

protected: //methods
  //-------------------------------------------------------------------//
  /// @brief constructor
  /// @param [in] _type, the string entity type
  /// @param [in] _x, the x position of the entity
  /// @param [in] _y, the y position of the entity
  /// @param [in] _z, the z position of the entity
  //-------------------------------------------------------------------//

  EntityRecord(
      const std::string _type,
      float _x,
      float _y,
      float _z
      );
};

#endif // ENTITYRECORD_H
