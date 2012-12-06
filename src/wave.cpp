#include "wave.h"

#include <boost/foreach.hpp>

#include "entityfactory.h"
#include "node.h"

//-------------------------------------------------------------------//

Wave::Wave(EnemyPairList _enemiesForCreation):
  m_enemiesForCreation(_enemiesForCreation)
{
  // ctor
  //---------------------------------------------TEST--------------------------------------------------
  // create shit load o enemies!!!
  for(int i=0; i < 10; ++i)
  {
     addEnemy("TestEnemy", 100, 1, ngl::Vec3(0, 0, i*2), 0, ngl::Vec3(0, 0, 0));
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
  // default destructor
}

//-------------------------------------------------------------------//

void Wave::update()
{
//  std::cout<<"updating wave"<<std::endl;
  for(
      EnemyList::iterator it = m_enemies.begin();
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
      // update enemy
      (*it)->update();
      ++it;
    }
  }
  brain();
}

//-------------------------------------------------------------------//

void Wave::publish()
{
  // Go through all the enemies and call their publish
  for(
      EnemyList::iterator it = m_enemies.begin();
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
  // Go through all the enemies and call their publish
  for(
      EnemyList::iterator it = m_enemies.begin();
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
      EnemyList::iterator it = m_enemies.begin();
      it != m_enemies.end();
      ++it
      )
  {
    (*it)->drawSelection();
  }
}


//-------------------------------------------------------------------//

bool Wave::generatePaths(NodePtr _node)
{
  // 1. Find all Enemies affected by _node
  // 2. Go through each Enemy and tell it to generate a new temporary path
  // 3. If all the paths were created successfully tell all enemies to update
        // their paths and return true, else return false
  // 4. Update the map with the new node values

  // 1.
  EnemyListPtr enemyList = m_pathNodes[_node];
    //-----------------------------------------------------------------------------------------------
    //NEED TO CHECK FAIL HERE!!!
    //-----------------------------------------------------------------------------------------------
  // 2.
  BOOST_FOREACH(EnemyPtr it, *enemyList)
  {
    if(!it->generateTempPath())
    {
      return false;
    }
  }
  // 3.
  BOOST_FOREACH(EnemyPtr it, *enemyList)
  {
    it->finalisePath();
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
    float _damage,
    float _maxVelocity,
    const ngl::Vec3 &_pos,
    float _initialVelocity,
    const ngl::Vec3 &_aim
    )
{
  // use EntityFactory to create enemy then save it in m_enemies
  EnemyPtr newEnemy = boost::dynamic_pointer_cast<Enemy>(
        EntityFactory::createDynamicEntity(
        _type,
        _damage,
        _maxVelocity,
        _pos,
        _initialVelocity,
        _aim
      )
    );
  m_enemies.push_back(newEnemy);
  addToPathNodes(newEnemy);

}

//-------------------------------------------------------------------//

EnemyList::iterator Wave::removeEnemy(EnemyList::iterator _it)
{
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
    // THIS SHOULD BE CHANGED SO THAT ENEMIES IS STORED AS
    // A LIST OF ENEMIES RATHER THAN HAVING TO CAST IT EVERY TIME!!!
    addToPathNodes(enemy);
  }
}

void Wave::addToPathNodes(EnemyPtr _enemy)
{
  // Find path
  Node::NodeList path = _enemy->getPath();
  BOOST_FOREACH(NodePtr node, path)
  {
    // Check if Node is in map
    if(m_pathNodes.find(node) == m_pathNodes.end())
    {
      // Add to map
      m_pathNodes[node] = EnemyListPtr(new EnemyList());
    }
    // Add to the enemy to the list
    m_pathNodes[node]->push_back(_enemy);
  }
}


