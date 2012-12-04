#include "wave.h"

#include "entityfactory.h"

//-------------------------------------------------------------------//

Wave::Wave(EnemyPairList _enemiesForCreation):
  m_enemiesForCreation(_enemiesForCreation)
{
  // ctor
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
  std::cout<<"updating wave"<<std::endl;
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

void Wave::draw() const
{
  // Go through all the enemies and call their publish
  for(
      EnemyList::const_iterator it = m_enemies.begin();
      it != m_enemies.end();
      ++it
      )
  {
    (*it)->draw();
  }
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
