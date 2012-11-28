#include "entityrecord.h"

//-------------------------------------------------------------------//

EntityRecord::EntityRecord(
    std::string _type,
    float _x,
    float _y,
    float _z
    ):
  m_type(_type),
  m_x(_x),
  m_y(_y),
  m_z(_z)
{
  //all parameters initialised before constructor body
}

//-------------------------------------------------------------------//

EntityRecordPtr EntityRecord::create(
    const std::string &_type,
    float _x,
    float _y,
    float _z
    )
{
  EntityRecordPtr record(new EntityRecord(_type,_x,_y,_z));
  return record;
}

//-------------------------------------------------------------------//
