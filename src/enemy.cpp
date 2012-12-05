#include "enemy.h"
#include "nodemanager.h"

//-------------------------------------------------------------------//

Enemy::Enemy(
    float _damage,
    float _maxVelocity,
    const ngl::Vec3 &_pos,
    float _initialVelocity,
    const ngl::Vec3 &_aim
    ) :
  DynamicEntity(_damage,_maxVelocity,_pos,_initialVelocity,_aim,ENEMY)
{
  //Get an initial path for the entity
  //m_pathNodes = NodeManager::pathFind()
}

//-------------------------------------------------------------------//

