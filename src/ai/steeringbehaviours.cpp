#include <algorithm>

#include "boost/utility.hpp"

#include "include/ai/steeringbehaviours.h"
#include "node.h"
#include "enemy.h"
#include "entity.h"

//Comperator used to sort the vector
struct PriorityCmp
{
  bool operator()(const std::pair<std::string, int> &lhs,
                  const std::pair<std::string, int> &rhs)
  {
    return lhs.second < rhs.second;
  }
};

SteeringBehaviours::SteeringBehaviours(EntityWPtr _entity):
            m_entity(_entity),
            m_steeringForce(ngl::Vec3(0.0, 0.0, 0.0))
{
  //FollowPath
  BehaviourInfo fp_info;
  fp_info.function = &SteeringBehaviours::FollowPath;
  fp_info.enabled = false;
  fp_info.weighting = 1.0;
  fp_info.priority = 1;
  m_registeredBehaviours["FollowPath"] = fp_info;

  //ObstacleAvoidance
  BehaviourInfo oa_info;
  oa_info.function = &SteeringBehaviours::ObstacleAvoidance;
  oa_info.enabled = false;
  oa_info.weighting = 1.0;
  oa_info.priority = 1;
  m_registeredBehaviours["ObstacleAvoidance"] = oa_info;

  //Seperation
  BehaviourInfo sep_info;
  sep_info.function = &SteeringBehaviours::Seperation;
  sep_info.enabled = false;
  sep_info.weighting = 1.0;
  sep_info.priority = 2;
  m_registeredBehaviours["Seperation"] = sep_info;

  //Cohesion
  BehaviourInfo co_info;
  co_info.function = &SteeringBehaviours::Cohesion;
  co_info.enabled = false;
  co_info.weighting = 1.0;
  co_info.priority = 3;
  m_registeredBehaviours["Cohesion"] = co_info;

  //Alignment
  BehaviourInfo ali_info;
  ali_info.function = &SteeringBehaviours::Alignment;
  ali_info.enabled = false;
  ali_info.weighting = 1.0;
  ali_info.priority = 4;
  m_registeredBehaviours["Alignment"] = ali_info;

}

ngl::Vec3 SteeringBehaviours::calculate()
{
  EntityPtr strongEntity = m_entity.lock();

  if(strongEntity)
  {
    EnemyPtr enemyPtr = boost::dynamic_pointer_cast<Enemy>(strongEntity);

    //The local entities are used by the steering behaviours.
    m_localEntities = enemyPtr->getLocalEntities();

    //reset the steering force
    m_steeringForce.null();

    //The individual force from each behaviour
    ngl::Vec3 force = ngl::Vec3(0.0, 0.0, 0.0);

    //Will evntually store the sorted behaviours.
    std::vector<std::pair<std::string, int> > ordered_vector;

    typedef std::map<std::string, BehaviourInfo>::iterator rb_iter;
    for(rb_iter iterator = m_registeredBehaviours.begin();
        iterator != m_registeredBehaviours.end();
        iterator++)
    {
      if(iterator->second.enabled)
      {
        ordered_vector.push_back(std::make_pair(iterator->first,
                                                iterator->second.priority));
      }
    }

    //Sort the vector based on the priority stored in the pair.
    std::sort(ordered_vector.begin(), ordered_vector.end(), PriorityCmp());

    std::vector<std::pair<std::string, int> >::iterator ord_iter;
    for(ord_iter = ordered_vector.begin();
        ord_iter != ordered_vector.end();
        ++ord_iter)
    {
      std::string key = ord_iter->first;

      BehaviourInfo info = m_registeredBehaviours[key];
      //Grabs the function registered to this behaviour
      ngl::Vec3 (SteeringBehaviours::*f)() = info.function;
      //grab its force
      force = (*this.*f)() * info.weighting;

      //if accumulateForce returns false, then there's no
      //more frorce left so return the current steering force.
      if(!accumulateForce(force))
      {
        return m_steeringForce;
      }
    }

//    //Iterates over each behaviour and accumulates their individual
//    //forces.
//    typedef std::map<std::string, BehaviourInfo>::iterator rb_iter;
//    for(rb_iter iterator = m_registeredBehaviours.begin();
//        iterator != m_registeredBehaviours.end();
//        iterator++)
//    {
//      if(iterator->second.enabled)
//      {
//        //Grabs the function registered to this behaviour
//        ngl::Vec3 (SteeringBehaviours::*f)() = iterator->second.function;
//        //grab its force
//        force = (*this.*f)() * iterator->second.weighting;

//        //if accumulateForce returns false, then there's no
//        //more frorce left so return the current steering force.
//        if(!accumulateForce(force))
//        {
//          return m_steeringForce;
//        }
//      }
//    }

    return m_steeringForce;
  }
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

void SteeringBehaviours::enable(std::string _behaviour,
                                float _weighting,
                                int _priority)
{
  m_registeredBehaviours[_behaviour].enabled = true;
  m_registeredBehaviours[_behaviour].weighting = _weighting;
  m_registeredBehaviours[_behaviour].priority = _priority;
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

    // get distance to nearest node and check threshold
    finalVector = nearestNode->getPos() - enemyPtr->getPos();
    float len = finalVector.length();

    if(len > enemyPtr->getMaxPathDistance())
    {
      enemyPtr->needsNewPath();
    }

    if(parentNode && len < enemyPtr->getPathTargetThreshold())
    {
      //return dir vector between parentNode and nearestNode

      // Don't normalise so that the further it moves away from the path the
      // bigger the force
      finalVector = parentNode->getPos() - enemyPtr->getPos();

//      // Normalise
//      float newLen = finalVector.length();
//      if(newLen)
//      {
//        finalVector/=newLen;
//      }
    }
  }
//  else
//  {
//    //as we're one from the end, return dir vec between nearestNode
//    //and the current position
//    finalVector = nearestNode->getPos() - m_pos;
//  }

  //std::cout<<finalVector<<std::endl;



  return finalVector;
}

//Object avoidance
ngl::Vec3 SteeringBehaviours::ObstacleAvoidance()
{
  EntityRecordListPtr localStrongEntities = m_localEntities.lock();

  EntityPtr strongEntity = m_entity.lock();
  EnemyPtr enemyPtr = boost::dynamic_pointer_cast<Enemy>(strongEntity);
  ngl::Vec3 enemyPos = enemyPtr->getPos();
  ngl::Vec3 enemyAim = enemyPtr->getAim();
  ngl::Vec3 feeler = enemyAim * 2;

  //Iterate over the neighbours.
  std::list<EntityRecord>::const_iterator iterator;
  for(iterator = localStrongEntities->begin();
      iterator != localStrongEntities->end();
      ++iterator)
  {
    if(iterator->m_generalType == TURRET)
    {
      //Grab the positions of the neighbour we're looking at.
      ngl::Vec3 neighbourPos = ngl::Vec3(iterator->m_x,
                                         iterator->m_y,
                                         iterator->m_z);
      float neighbourRadius = 1.5;

      ngl::Vec3 a = neighbourPos - enemyPos;
      ngl::Vec3 p = a.dot(feeler) * feeler;
      ngl::Vec3 b = p - a;

      //the condition is true if the enemy needs to avoid
      if(p.length() < feeler.length() &&
         b.length() < neighbourRadius)
      {
        std::cout<<"Steering away from obstacle."<<std::endl;
        return enemyPtr->getMaxForce() * feeler.length() / a.length();
      }
    }
  }

  //std::cout<<"No steering."<<std::endl;
  return ngl::Vec3(0.0, 0.0, 0.0);
}

//Seperation
ngl::Vec3 SteeringBehaviours::Seperation()
{
  //The total repulsion will be a reunning total of the repulsions
  //found for each neighbour
  ngl::Vec3 totalRepulsion = ngl::Vec3(0.0, 0.0, 0.0);

  EntityRecordListPtr localStrongEntities = m_localEntities.lock();

  EntityPtr strongEntity = m_entity.lock();
  EnemyPtr enemyPtr = boost::dynamic_pointer_cast<Enemy>(strongEntity);
  ngl::Vec3 enemyPos = enemyPtr->getPos();

  //Iterate over the neighbours.
  std::list<EntityRecord>::const_iterator iterator;
  for(iterator = localStrongEntities->begin();
      iterator != localStrongEntities->end();
      ++iterator)
  {
    //Grab the positions of the neighbour we're looking at.
    ngl::Vec3 neighbourPos = ngl::Vec3(iterator->m_x,
                                       iterator->m_y,
                                       iterator->m_z);

    //Find the vector between the two positions
    ngl::Vec3 repulsion = enemyPos - neighbourPos;

    float repulsionLength = repulsion.length();
    if(repulsionLength)
    {
      repulsion = repulsion / repulsionLength;

      float squaredDistance =  pow((neighbourPos.m_x - enemyPos.m_x), 2) +
                               pow((neighbourPos.m_y - enemyPos.m_y), 2) +
                               pow((neighbourPos.m_z - enemyPos.m_z), 2);

      //Apply a 1 / r weighting.
      repulsion *= 1 / squaredDistance;

      //Add to the running total
      totalRepulsion += repulsion;
    }
  }

  //return the final summed repulsion.
  return totalRepulsion;
}

//Cohesion
ngl::Vec3 SteeringBehaviours::Cohesion()
{
  //Running sum of the neighbours' positions
  ngl::Vec3 neighbourPosSum = ngl::Vec3(0.0, 0.0, 0.0);

  //The neighbours.
  EntityRecordListPtr localStrongEntities = m_localEntities.lock();

  EntityPtr strongEntity = m_entity.lock();
  EnemyPtr enemyPtr = boost::dynamic_pointer_cast<Enemy>(strongEntity);
  ngl::Vec3 enemyPos = enemyPtr->getPos();

  //Iterate over the neighbours.
  std::list<EntityRecord>::const_iterator iterator;
  for(iterator = localStrongEntities->begin();
      iterator != localStrongEntities->end();
      ++iterator)
  {
    neighbourPosSum += ngl::Vec3(iterator->m_x,
                                 iterator->m_y,
                                 iterator->m_z);
  }

  //Find the average position of the neighbours.
  ngl::Vec3 averagePosition = neighbourPosSum / localStrongEntities->size();

  //Return the vector in the direction of the average position.
  return averagePosition - enemyPos;
}

//Alignment
ngl::Vec3 SteeringBehaviours::Alignment()
{
  //Running sum of the neighbours's velocities
  ngl::Vec3 neighbourVecSum = ngl::Vec3(0.0, 0.0, 0.0);

  //The neighbours.
  EntityRecordListPtr localStrongEntities = m_localEntities.lock();

  EntityPtr strongEntity = m_entity.lock();
  EnemyPtr enemyPtr = boost::dynamic_pointer_cast<Enemy>(strongEntity);
  ngl::Vec3 enemyVel = enemyPtr->getVelocity();

  //Iterate over the neighbours.
  std::list<EntityRecord>::const_iterator iterator;
  for(iterator = localStrongEntities->begin();
      iterator != localStrongEntities->end();
      ++iterator)
  {
    neighbourVecSum += ngl::Vec3(iterator->m_velocity[0],
                                 iterator->m_velocity[1],
                                 iterator->m_velocity[2]);
  }

  //Average velocity of the neighbours
  ngl::Vec3 averageVelocity = neighbourVecSum / localStrongEntities->size();

  //Return he difference between the average and the current velocity
  return averageVelocity - enemyVel;
}
