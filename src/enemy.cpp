#include "enemy.h"
#include "nodemanager.h"
#include "game.h"
#include "boost/utility.hpp"
#include "database.h"
#include "fsm/states/enemystates.h"

//-------------------------------------------------------------------//

Enemy::Enemy(
    const ngl::Vec3 &_pos,
    const ngl::Vec3 &_aim,
    unsigned int _id
    ) :
  DynamicEntity(_pos,_aim,ENEMY, _id),
  m_pathTargetThreshold(1.2) //THIS SHOULD BE A PROPORTION OF THE DISTANCE BETWEEN NODES!!!!!
                             //IF ITS TOO LOW ENEMIES WILL NOT MOVE
{
  if(generateTempPath())
  {
    finalisePath();
  }
}

//-------------------------------------------------------------------//

bool Enemy::generateTempPath()
{
  // THIS IS REALLY MESSY AND NEEDS A COMPLETE REFACTOR, ENEMIES SHOULD NOT HAVE
  // TO ACCESS THE NODEMANAGER!
  EnvironmentPtr env = Game::instance()->getEnvironmentWeakPtr().lock();
  if(env)
  {
    NodeManagerPtr nm = env->getNodeManagerWeakPtr().lock();
    if(nm)
    {
      return nm->findPathFromPos(
            m_tempPathNodes,
            m_pos,
            Game::instance()->getBasePos()
            );
    }
  }
  return false;
}

//-------------------------------------------------------------------//

void Enemy::finalisePath()
{
  m_pathNodes = m_tempPathNodes;
  m_tempPathNodes.clear();
}

//-------------------------------------------------------------------//

Node::NodeWList Enemy::getPath() const
{
  return m_pathNodes;
}

//-------------------------------------------------------------------//

//-------------------------------------------------------------------//

void Enemy::enforceGridBoundaries()
{
  //get an instance of the database

  Database* db = Database::instance();

  //get the minimum and maximum extents of the grid

  ngl::Vec2 minExts = db->getMinGridExtents();
  ngl::Vec2 maxExts = db->getMaxGridExtents();

  //check the position of the entity against the boundaries
  //comparison between z and y because x and z are the planar
  //axis but a vec2 has no m_z component

  if (m_pos.m_x < minExts.m_x)
  {
    //set the x value to the minimum extents of the grid

    m_pos.m_x = minExts.m_x;
  }
  else if (m_pos.m_x > maxExts.m_x)
  {
    //set it to the max

    m_pos.m_x = maxExts.m_x;
  }
  //then check z

  if (m_pos.m_z < minExts.m_y)
  {
    m_pos.m_z = minExts.m_y;
  }
  else if (m_pos.m_z > maxExts.m_y)
  {
    m_pos.m_z = maxExts.m_y;
  }
}

//-------------------------------------------------------------------//

