#ifndef DATABASE_FWD_H
#define DATABASE_FWD_H

#include <boost/shared_ptr.hpp>
#include <fwd/entity.h>

DECLARESMART(EntityRecord)

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

  union
  {
    struct
    {
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

    };
    float m_pos[3];
  };

  union
  {
    struct
    {
      //-------------------------------------------------------------------//
      /// @brief the x position of the entity
      //-------------------------------------------------------------------//

      float m_velX;

      //-------------------------------------------------------------------//
      /// @brief the y position of the entity
      //-------------------------------------------------------------------//

      float m_velY;

      //-------------------------------------------------------------------//
      /// @brief the z position of the entity
      //-------------------------------------------------------------------//

      float m_velZ;
    };

    //-------------------------------------------------------------------//
    /// @brief for dynamic entities velocity of entity
    //-------------------------------------------------------------------//

    float m_velocity[3];

    //-------------------------------------------------------------------//
    /// @brief for static entities aim of entity
    //-------------------------------------------------------------------//

    float m_aim[3];
  };

  //-------------------------------------------------------------------//
  /// @brief the bounding box of the enemy
  //-------------------------------------------------------------------//

  float m_minX;
  float m_maxX;
  float m_minY;
  float m_maxY;
  float m_minZ;
  float m_maxZ;

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
        float _z,
        float _velX,
        float _velY,
        float _velZ,
        float _minX,
        float _maxX,
        float _minY,
        float _maxY,
        float _minZ,
        float _maxZ
        ):
    m_id(_id),
    m_generalType(_type),
    m_x(_x),
    m_y(_y),
    m_z(_z),
    m_velX(_velX),
    m_velY(_velY),
    m_velZ(_velZ),
    m_minX(_minX),
    m_maxX(_maxX),
    m_minY(_minY),
    m_maxY(_maxY),
    m_minZ(_minZ),
    m_maxZ(_maxZ)
  {}

  //-------------------------------------------------------------------//
  /// @brief constructor
  //-------------------------------------------------------------------//

  EntityRecord():
    m_id(0),
    m_generalType(ENEMY),
    m_x(0),
    m_y(0),
    m_z(0),
    m_velX(0),
    m_velY(0),
    m_velZ(0),
    m_minX(0),
    m_maxX(0),
    m_minY(0),
    m_maxY(0),
    m_minZ(0),
    m_maxZ(0)
  {}
};

//-------------------------------------------------------------------//
/// @typedef a boost shared pointer to a list of entity records
//-------------------------------------------------------------------//

typedef std::list<EntityRecord> EntityRecordList;

typedef boost::shared_ptr<EntityRecordList> EntityRecordListPtr;

typedef boost::weak_ptr<EntityRecordList> EntityRecordListWPtr;

#endif // DATABASE_FWD_H
