#include "dynamicentity.h"

//-------------------------------------------------------------------//

DynamicEntity::DynamicEntity(
    float _damage,
    float _maxVelocity,
    const ngl::Vec3 &_pos,
    float _initialVelocity,
    const ngl::Vec3 &_aim, GeneralType _type
    ):
  Entity(_pos,_type),
  m_damage(_damage),
  m_aimVector(_aim),
  m_maxVelocity(_maxVelocity),
  m_currentVelocity(_initialVelocity)

{
  //variables initialised before the constructor body
}

//-------------------------------------------------------------------//

DynamicEntity::~DynamicEntity()
{
  //currently using default destructor
}

//-------------------------------------------------------------------//

void DynamicEntity::update()
{
  std::cout<<"updating dynamic entity"<<std::endl;
  std::cout<<"now at position"<<m_pos<<std::endl;
  // get the brain vector
  ngl::Vec3 brainVec = brain();
  // based on brain where should it go next
  // FOR TESTING JUST HAVE IT GO EXACTLY WHERE THE BRAIN SAYS
  m_pos += brainVec;
}

//-------------------------------------------------------------------//
