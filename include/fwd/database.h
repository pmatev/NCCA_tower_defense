#ifndef DATABASE_FWD_H
#define DATABASE_FWD_H

#include <boost/shared_ptr.hpp>
#include <fwd/entity.h>

//-------------------------------------------------------------------//
/// @struct a data structure to store information about a given entity
/// in the database
//-------------------------------------------------------------------//

struct EntityRecord
{
  //-------------------------------------------------------------------//
  /// @brief the entity id
  //-------------------------------------------------------------------//

  unsigned int m_id;

  //-------------------------------------------------------------------//
  /// @brief the enumerated type ID
  //-------------------------------------------------------------------//

  GeneralType m_generalType;

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

  //-------------------------------------------------------------------//
  /// @brief constructor
  /// @param [in] _type, the string entity type
  /// @param [in] _x, the x position of the entity
  /// @param [in] _y, the y position of the entity
  /// @param [in] _z, the z position of the entity
  //-------------------------------------------------------------------//

  EntityRecord(
        unsigned int _id,
        GeneralType _type,
        float _x,
        float _y,
        float _z
        ):
    m_id(_id),
    m_generalType(_type),
    m_x(_x),
    m_y(_y),
    m_z(_z)
  {}
};

//-------------------------------------------------------------------//
/// @typedef a boost shared pointer to a list of entity records
//-------------------------------------------------------------------//

typedef boost::shared_ptr<std::list<EntityRecord> > entityRecordListPtr;

#endif // DATABASE_FWD_H
