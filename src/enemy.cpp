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
    unsigned int _id,
    int _currencyValue
    ) :
  DynamicEntity(_pos,_aim,ENEMY, _id),
  m_pathTargetThreshold(1.2), //THIS SHOULD BE A PROPORTION OF THE DISTANCE BETWEEN NODES!!!!!
  m_currencyValue(_currencyValue)             //IF ITS TOO LOW ENEMIES WILL NOT MOVE
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

ngl::Vec3 Enemy::getVectorToNearestNodeInPath()
{
  NodePtr nearestNode;
  NodePtr parentNode;
  float nearestSqrDistance = 100000;

  ngl::Vec3 finalVector;

  for(Node::NodeWList::reverse_iterator it = m_pathNodes.rbegin();
      it != m_pathNodes.rend();
      it++)
  {
    NodePtr currentNode = it->lock();
    if(currentNode)
    {
      //get the position of the node
      ngl::Vec3 targetPos = currentNode->getPos();
      //calculate the distance between that node and this one
      float newSqrDistance =
          ((targetPos.m_x - m_pos.m_x)*(targetPos.m_x - m_pos.m_x)) +
          ((targetPos.m_y - m_pos.m_y)*(targetPos.m_y - m_pos.m_y)) +
          ((targetPos.m_z - m_pos.m_z)*(targetPos.m_z - m_pos.m_z));

      if(newSqrDistance < nearestSqrDistance)
      {
        //this is the closest node we've found
        nearestSqrDistance = newSqrDistance;
        nearestNode = currentNode;
        //if the closest node is NOT at the end
        if(boost::next(it) != m_pathNodes.rend())
        {
          parentNode = (*boost::next(it)).lock();
        }
        else
        {
          if(parentNode)
          {
            parentNode.reset();
          }
        }
      }
    }
  }

  //get the parent node of the nearestNode as long as we're not at the end.
  if(parentNode)
  {
    //return dir vector between parentNode and nearestNode

    finalVector = parentNode->getPos() - nearestNode->getPos();
  }
  else
  {
    //as we're one from the end, return dir vec between nearestNode
    //and the current position
    finalVector = nearestNode->getPos() - m_pos;
  }

  //std::cout<<finalVector<<std::endl;
  float len = finalVector.length();
  if(len)
  {
    finalVector/=len;
  }

  return finalVector;
}

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

//-------------------------------------------------------------------//
// JAREDS NEW IMPLEMENTATION OF THE ABOVE PATH VEC CALCULATION
// (FOR TESTING PURPOSES)
ngl::Vec3 Enemy::getPathVec() const
{
  // ALGORITHM: Go to nearest node unless you are within a specified distance.
  // If within the specified distance go parent node. If on last node go to
  // center.
  NodePtr nearestNode;
  NodePtr parentNode;
  float nearestSqrDistance = 10000000000;

  ngl::Vec3 finalVector;

  for(Node::NodeWList::const_reverse_iterator it = m_pathNodes.rbegin();
      it != m_pathNodes.rend();
      it++)
  {
    NodePtr currentNode = it->lock();
    if(currentNode)
    {
      //get the position of the node
      ngl::Vec3 targetPos = currentNode->getPos();
      //calculate the distance between that node and this one
      ngl::Vec3 relVec = targetPos - m_pos;
      float newSqrDistance = ((relVec.m_x)*(relVec.m_x)) +
                               ((relVec.m_y)*(relVec.m_y)) +
                               ((relVec.m_z)*(relVec.m_z));

      if(newSqrDistance < nearestSqrDistance)
      {
        //this is the closest node we've found
        nearestSqrDistance = newSqrDistance;
        nearestNode = currentNode;
        //if the closest node is NOT at the end
        if(boost::next(it) != m_pathNodes.rend())
        {
          parentNode = (*boost::next(it)).lock();
        }
        else
        {
          if(parentNode)
          {
            parentNode.reset();
          }
        }
      }
    }
  }

  //get the parent node of the nearestNode as long as we're not at the end.
  finalVector = nearestNode->getPos() - m_pos;
  float len = finalVector.length();
  if(parentNode && len < m_pathTargetThreshold)
  {
    //return dir vector between parentNode and nearestNode

    // get distance to nearest node and check threshold

    finalVector = parentNode->getPos() - m_pos;
  }
//  else
//  {
//    //as we're one from the end, return dir vec between nearestNode
//    //and the current position
//    finalVector = nearestNode->getPos() - m_pos;
//  }

  //std::cout<<finalVector<<std::endl;
  float newLen = finalVector.length();
  if(newLen)
  {
    finalVector/=newLen;
  }

  return finalVector;
}

//-------------------------------------------------------------------//

bool Enemy::sphereBBoxCollision(const ngl::Vec3 &_pos,
                                float _radius) const
{
  //set up  the return boolean

  bool result = false;

  //first check if the position of the enemy is within the sphere

  //calculate the square distance from the enemy to the sphere

  float sqDist = (_pos.m_x-m_pos.m_x)*(_pos.m_x-m_pos.m_x)+
      (_pos.m_y-m_pos.m_y)*(_pos.m_y-m_pos.m_y)+
      (_pos.m_z-m_pos.m_z)*(_pos.m_z-m_pos.m_z);

  //calculate the radius squared

  float sqRadius = _radius*_radius;

  //if the distance is less than the radius squared

  if (sqRadius >= sqDist)
  {
    //set the result boolean to be true

    result = true;
  }

  else
  {
    //otherwise, clamp position of the sphere within the boundaries
    //of the bounding box, finding the closest point on the bounding
    //box to the sphere object

    float xPos = _pos.m_x;
    float yPos = _pos.m_y;
    float zPos = _pos.m_z;

    //x

    if(xPos > m_lsMeshBBox.m_maxX+m_pos.m_x)
    {
      xPos = m_lsMeshBBox.m_maxX+m_pos.m_x;
    }
    else if (xPos < m_lsMeshBBox.m_minX+m_pos.m_x)
    {
      xPos = m_lsMeshBBox.m_minX+m_pos.m_x;
    }

    //y

    if(yPos > m_lsMeshBBox.m_maxY+m_pos.m_y)
    {
      yPos = m_lsMeshBBox.m_maxY+m_pos.m_y;
    }
    else if (yPos < m_lsMeshBBox.m_minY+m_pos.m_y)
    {
      yPos = m_lsMeshBBox.m_minY+m_pos.m_y;
    }

    //z

    if(zPos > m_lsMeshBBox.m_maxZ+m_pos.m_z)
    {
      zPos = m_lsMeshBBox.m_maxZ+m_pos.m_z;
    }
    else if (zPos < m_lsMeshBBox.m_minZ+m_pos.m_z)
    {
      zPos = m_lsMeshBBox.m_minZ+m_pos.m_z;
    }

    //then check if the squared distance between the point and
    //the sphere is less than the radius squared

    sqDist = (_pos.m_x-xPos)*(_pos.m_x-xPos)+
        (_pos.m_y-yPos)*(_pos.m_y-yPos)+
        (_pos.m_z-zPos)*(_pos.m_z-zPos);

    if (sqRadius>sqDist)
    {
      result = true;
    }

  }

  return result;
}

//-------------------------------------------------------------------//
