#include "enemy.h"
#include "nodemanager.h"
#include "game.h"

//-------------------------------------------------------------------//

Enemy::Enemy(
    const ngl::Vec3 &_pos,
    const ngl::Vec3 &_aim,
    unsigned int _id
    ) :
  DynamicEntity(_pos,_aim,ENEMY, _id)
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

