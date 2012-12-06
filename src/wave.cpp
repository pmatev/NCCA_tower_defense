#include "wave.h"

#include "entityfactory.h"

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
  m_enemies.push_back(
          EntityFactory::createDynamicEntity(
            _type,
            _damage,
            _maxVelocity,
            _pos,
            _initialVelocity,
            _aim
          )
        );

}

//-------------------------------------------------------------------//

Wave::EnemyList::iterator Wave::removeEnemy(EnemyList::iterator _it)
{
  // remove it from m_enemies and return the next iterator
  return m_enemies.erase(_it);
}



