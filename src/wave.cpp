#include "wave.h"

#include <boost/foreach.hpp>
#include <omp.h>
#include "entityfactory.h"
#include "node.h"
#include "game.h"

//-------------------------------------------------------------------//

Wave::Wave(EnemyPairList _enemiesForCreation):
  m_enemiesForCreation(_enemiesForCreation)
{
  // ctor
  //---------------------------------------------TEST--------------------------------------------------
  // create shit load o enemies!!!
  int numEnemies = 1;
  for(int i=0; i < numEnemies; ++i)
  {
    float randomX = std::rand() / float(RAND_MAX);
    float randomZ = std::rand() / float(RAND_MAX);
    addEnemy("TestEnemy", ngl::Vec3((10 * randomX) + 20, 0, i*(40.0/numEnemies)* randomZ), ngl::Vec3(0, 0, 0));
  }
  //-------------------------------------------END TEST------------------------------------------------
}

//-------------------------------------------------------------------//

WavePtr Wave::create(EnemyPairList _enemiesForCreation)
{
  WavePtr a(new Wave(_enemiesForCreation));
  return a;
}


//-------------------------------------------------------------------//

Wave::~Wave()
{
  // remove all enemies (must use removeEnemy rather than clear as this will
  // ensure that they are unregistered properly)
  for(EnemyVec::iterator it = m_enemies.begin(); it != m_enemies.end();)
  {
    it = removeEnemy(it);
  }
}

//-------------------------------------------------------------------//

void Wave::update(const double _dt)
{
  //  std::cout<<"updating wave"<<std::endl;

  for(
      EnemyVec::iterator it = m_enemies.begin();
      it != m_enemies.end();
      )
  {
    // check health
    if ((*it)->getHealth() <= 0)
    {
      // KILL ENEMY!!!
      it = removeEnemy(it);
    }
    else
    {
      ++it;
    }
  }
#pragma omp parallel
  {
#pragma omp for
    for(
        unsigned long int i = 0;
        i < m_enemies.size();
        ++i
        )
    {
      // update enemy
      (m_enemies[i])->update(_dt);
    }
  }
  brain();
}

//-------------------------------------------------------------------//

void Wave::publish()
{
  // Go through all the enemies and call their publish
  for(
      EnemyVec::iterator it = m_enemies.begin();
      it != m_enemies.end();
      ++it
      )
  {
    (*it)->publish();
  }
}

//-------------------------------------------------------------------//

void Wave::draw()
{
  // Go through all the enemies and draw
  for(
      EnemyVec::iterator it = m_enemies.begin();
      it != m_enemies.end();
      ++it
      )
  {
    (*it)->draw();
  }
}
//-------------------------------------------------------------------//

void Wave::drawSelection()
{
  // Go through all the enemies and call their publish
  for(
      EnemyVec::iterator it = m_enemies.begin();
      it != m_enemies.end();
      ++it
      )
  {
    (*it)->drawSelection();
  }
}


//-------------------------------------------------------------------//

bool Wave::generatePaths(NodeWPtr _node)
{
  // Reset path nodes (for path optimisation)
  EnvironmentPtr env = Game::instance()->getEnvironmentWeakPtr().lock();
  if(env)
  {
    NodeManagerPtr nm = env->getNodeManagerWeakPtr().lock();
    if(nm)
    {
      nm->resetPathNodes();
    }
  }

  // 1. Find all Enemies affected by _node
  // 2. Go through each Enemy and tell it to generate a new temporary path
  // 3. If all the paths were created successfully tell all enemies to update
  // their paths and return true, else return false
  // 4. Update the map with the new node values


  // 1.
  EnemyWVecPtr enemyList = m_pathNodes[_node];
  // if there are no enemies using this node
  if(!enemyList)
  {
    return true;
  }
  // 2.
  bool invalidPath = false;

  for(unsigned long int i = 0; i < enemyList->size(); ++i)
  {
    // This is set to skip computation so that we can shortcut to the end
    // without breaking (breaking doesn't work with "omp for")
    if(invalidPath)
    {
      continue;
    }
    EnemyPtr enemy = (*enemyList)[i].lock();
    if(enemy)
    {
      if(!enemy->generateTempPath())
      {
        invalidPath = true;
      }
    }
  }

  if(invalidPath)
  {
    return false;
  }
  // 3.
  BOOST_FOREACH(EnemyWPtr enemyWeak, *enemyList)
  {
    EnemyPtr enemy = enemyWeak.lock();
    if(enemy)
    {
      enemy->finalisePath();
    }
  }
  // 4.
  // clear list and rebuild
  rebuildPathNodes();
  return true;
}

//-------------------------------------------------------------------//

void Wave::brain()
{
  // Work out which enemies need creating and where
}

//-------------------------------------------------------------------//
void Wave::addEnemy(
    std::string _type,
    const ngl::Vec3 &_pos,
    const ngl::Vec3 &_aim
    )
{
  // use EntityFactory to create enemy then save it in m_enemies
  EnemyPtr newEnemy = boost::dynamic_pointer_cast<Enemy>(
        EntityFactory::createDynamicEntity(
          _type,
          _pos,
          _aim
          )
        );
  m_enemies.push_back(newEnemy);
  addToPathNodes(newEnemy);

}

//-------------------------------------------------------------------//

EnemyVec::iterator Wave::removeEnemy(EnemyVec::iterator _it)
{
  // unregister from game so that the smartptr is freed
  Game::instance()->unregisterID((*_it)->getID());
  // remove it from m_enemies and return the next iterator
  return m_enemies.erase(_it);
}

void Wave::rebuildPathNodes()
{
  // clear map
  m_pathNodes.clear();
  // go through all Enemies
  BOOST_FOREACH(EnemyPtr enemy, m_enemies)
  {
    addToPathNodes(enemy);
  }
}

void Wave::addToPathNodes(EnemyPtr _enemy)
{
  // Find path
  Node::NodeWList path = _enemy->getPath();
  BOOST_FOREACH(NodeWPtr node, path)
  {
    // Check if Node is not in map
    if(m_pathNodes.find(node) == m_pathNodes.end())
    {
      // Add to map
      m_pathNodes[node] = EnemyWVecPtr(new EnemyWVec());
    }
    // Add to the enemy to the list
    m_pathNodes[node]->push_back(_enemy);
  }
}

std::list<Collision> Wave::checkCollisions()
{
  //initialise a list of collisions to return

  std::list<Collision> collisionList;

  // cycle through all of the projectiles stored

  for (
       EnemyVec::iterator listIt = m_enemies.begin();
       listIt != m_enemies.end();
       listIt++
       )
  {
    //call call collision detection on the projectiles
    std::list<GeneralType> types;
    types.push_back(TURRET);
    //    types.push_back(BASE);
    Collision c = (*listIt)->collisionDetection(types);

    //check if there was a collision

    if (c.m_id != 0)
    {
      //if there was, add it to the list
      // This needs to call damage deal and pass in the damage from the collision ----------
      (*listIt)->kill();
      collisionList.push_back(c);
    }
  }
  //finally return the resulting list

  return collisionList;
}


