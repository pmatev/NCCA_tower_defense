#include "boost/utility.hpp"

#include "include/ai/steeringbehaviours.h"
#include "node.h"
#include "enemy.h"

SteeringBehaviours::SteeringBehaviours(EntityWPtr _entity):
            m_entity(_entity),
            m_steeringForce(ngl::Vec3(0.0, 0.0, 0.0))
{
  //register the behaviours
  BehaviourInfo fp_info;
  fp_info.function = &SteeringBehaviours::FollowPath;
  fp_info.enabled = false;
  m_registeredBehaviours["FollowPath"] = fp_info;

  //register the behaviours
  BehaviourInfo test_info;
  test_info.function = &SteeringBehaviours::test;
  test_info.enabled = false;
  m_registeredBehaviours["test"] = test_info;
}

ngl::Vec3 SteeringBehaviours::calculate()
{
  return FollowPath();
  //reset the steering force
  m_steeringForce.null();

  //Interates over the registered behaviours
  typedef std::map<std::string, BehaviourInfo>::iterator rb_iter;

  ngl::Vec3 force = ngl::Vec3(0.0, 0.0, 0.0);
  for(rb_iter iterator = m_registeredBehaviours.begin();
      iterator != m_registeredBehaviours.end();
      iterator++)
  {
    if(iterator->second.enabled)
    {
      //Grabs the function registered to this behaviour
      ngl::Vec3 (SteeringBehaviours::*f)() = iterator->second.function;
      //grab its force
      force = (*this.*f)();

      //return force;
      //if accumulateForce returns false, then there's no
      //more frorce left so return the current steering force.
      if(!accumulateForce(force))
      {
        return m_steeringForce;
      }
    }
  }

  return m_steeringForce;
}

bool SteeringBehaviours::accumulateForce(ngl::Vec3 _force)
{
  EntityPtr strongEntity = m_entity.lock();
  EnemyPtr enemyPtr = boost::dynamic_pointer_cast<Enemy>(strongEntity);

  float forceDiff = enemyPtr->getMaxForce().length() - m_steeringForce.length();

  //if there is no force remaining, return false
  if(forceDiff <= 0)
  {
    return false;
  }

  //if there is enough force left, add it.
  else if(forceDiff >= _force.length())
  {
    m_steeringForce += _force;
  }

  //if there isn't quite enough left, the new force is
  //truncated to the remanining magnitude before being added.
  else if(forceDiff < _force.length() && forceDiff >= 0)
  {
    //truncate velocity to remaining force (forceDiff)
    float trunDiff = forceDiff / _force.length();
    float scaleFactor = (trunDiff < 1.0) ? trunDiff : 1.0;
    _force *= scaleFactor;

    m_steeringForce += _force;
  }

  return true;
}

void SteeringBehaviours::enable(std::string _behaviour)
{
  m_registeredBehaviours[_behaviour].enabled = true;
}

void SteeringBehaviours::disable(std::string _behaviour)
{
  m_registeredBehaviours[_behaviour].enabled = false;
}

// ========================================================================== //
//                                BEHAVIOURS                                  //
// ========================================================================== //

ngl::Vec3 SteeringBehaviours::FollowPath()
{
  // ALGORITHM: Go to nearest node unless you are within a specified distance.
  // If within the specified distance go parent node. If on last node go to
  // center.
  EntityPtr strongEntity = m_entity.lock();
  EnemyPtr enemyPtr = boost::dynamic_pointer_cast<Enemy>(strongEntity);

  Node::NodeWList nodePath = enemyPtr->getPath();

  NodePtr nearestNode;
  NodePtr parentNode;
  float nearestSqrDistance = 10000000000;

  ngl::Vec3 finalVector;

  for(Node::NodeWList::const_iterator it = nodePath.begin();
      it != nodePath.end();
      it++)
  {
    NodePtr currentNode = it->lock();
    if(currentNode)
    {
      //get the position of the node
      ngl::Vec3 targetPos = currentNode->getPos();
      //calculate the distance between that node and this one
      ngl::Vec3 relVec = targetPos - enemyPtr->getPos();
      float newSqrDistance = ((relVec.m_x)*(relVec.m_x)) +
                               ((relVec.m_y)*(relVec.m_y)) +
                               ((relVec.m_z)*(relVec.m_z));

      if(newSqrDistance < nearestSqrDistance)
      {
        //this is the closest node we've found
        nearestSqrDistance = newSqrDistance;
        nearestNode = currentNode;
        //if the closest node is NOT at the end
        if(boost::next(it) != nodePath.end())
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
  if(nearestNode)
  {
    finalVector = nearestNode->getPos() - enemyPtr->getPos();
    float len = finalVector.length();
    if(parentNode && len < enemyPtr->getPathTargetThreshold())
    {
      //return dir vector between parentNode and nearestNode

      // get distance to nearest node and check threshold

      finalVector = parentNode->getPos() - enemyPtr->getPos();
    }
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

ngl::Vec3 SteeringBehaviours::test()
{
  return ngl::Vec3(0.0, 2.0, 0.0);
}


