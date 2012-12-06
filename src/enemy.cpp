#include "enemy.h"
#include "nodemanager.h"
#include "game.h"

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
  generateTempPath();
  finalisePath();
  //Get an initial path for the entity
  //m_pathNodes = updatePath();

  //std::cout<<

  //EnvironmentWeakPtr nm = Game::instance()->getEnvironmentWeakPtr();
  //std::cout<<nm.lock()->getBasePos()<<std::endl;
}

bool Enemy::generateTempPath()
{
  EnvironmentPtr env = Game::instance()->getEnvironmentWeakPtr().lock();
  NodeManagerPtr nm = env->getNodeManagerWeakPtr().lock();
  m_tempPathNodes = nm->findPathFromPos(
        m_pos,
        Game::instance()->getBasePos());

  if(m_tempPathNodes.empty())
  {
    return false;
  }
  return true;
}

void Enemy::finalisePath()
{
  m_pathNodes = m_tempPathNodes;
  m_tempPathNodes.clear();
}

Node::NodeList Enemy::getPath() const
{
  return m_pathNodes;
}

//-------------------------------------------------------------------//

