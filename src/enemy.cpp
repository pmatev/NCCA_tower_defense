#include "enemy.h"
#include "nodemanager.h"
#include "game.h"
#include "boost/utility.hpp"

//-------------------------------------------------------------------//

Enemy::Enemy(
    const ngl::Vec3 &_pos,
    const ngl::Vec3 &_aim,
    unsigned int _id
    ) :
  DynamicEntity(_pos,_aim,ENEMY, _id)
{
  if(generateTempPath())
  {
    finalisePath();

    std::cout<<"Path is of size: "<< m_pathNodes.size() <<std::endl;
    std::cout<<"Base is: "<< Game::instance()->getBasePos() <<std::endl;
    std::cout<<"Start is: "<< m_pos <<std::endl;
    for(Node::NodeList::iterator i = m_pathNodes.begin(); i != m_pathNodes.end(); i++)
    {
      std::cout<<"#"<< (*i)->getID()<<" "<<(*i)->getPos()<<std::endl;
    }
  }
  //Get an initial path for the entity
  //m_pathNodes = updatePath();

  //std::cout<<

  //EnvironmentWeakPtr nm = Game::instance()->getEnvironmentWeakPtr();
  //std::cout<<nm.lock()->getBasePos()<<std::endl;
}

//-------------------------------------------------------------------//

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

//-------------------------------------------------------------------//

void Enemy::finalisePath()
{
  m_pathNodes = m_tempPathNodes;
  m_tempPathNodes.clear();
}

//-------------------------------------------------------------------//

Node::NodeList Enemy::getPath() const
{
  return m_pathNodes;
}

//-------------------------------------------------------------------//

ngl::Vec3 Enemy::getVectorToNearestNodeInPath()
{
  NodePtr nearestNode;
  NodePtr parentNode;
  float nearestDistance = 100000;

  ngl::Vec3 finalVector;

  for(Node::NodeList::reverse_iterator it = m_pathNodes.rbegin();
      it != m_pathNodes.rend();
      it++)
  {
    //get the position of the node
    ngl::Vec3 targetPos = (*it)->getPos();
    //calculate the distance between that node and this one
    float newDistance = sqrt(((targetPos.m_x - m_pos.m_x)*(targetPos.m_x - m_pos.m_x)) +
                             ((targetPos.m_y - m_pos.m_y)*(targetPos.m_y - m_pos.m_y)) +
                             ((targetPos.m_z - m_pos.m_z)*(targetPos.m_z - m_pos.m_z)));

    if(newDistance < nearestDistance)
    {
      //this is the closest node we've found
      nearestDistance = newDistance;
      nearestNode = (*it);
      //if the closest node is NOT at the end
      if(boost::next(it) != m_pathNodes.rend())
      {
        parentNode = (*boost::next(it));
      } else
      {
        parentNode.reset();
      }
    }
  }

  //get the parent node of the nearestNode as long as we're not at the end.
  if(parentNode)
  {
    //return dir vector between parentNode and nearestNode

    finalVector = parentNode->getPos() - nearestNode->getPos();
  } else
  {
    //as we're one from the end, return dir vec between nearestNode
    //and the current position
    finalVector = nearestNode->getPos() - m_pos;
  }

  //std::cout<<finalVector<<std::endl;
  if(finalVector.length())
  {
    finalVector.normalize();
  }

  return finalVector;
}
