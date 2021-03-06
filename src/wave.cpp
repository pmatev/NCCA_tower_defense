#include "wave.h"

#include <boost/foreach.hpp>
#include <omp.h>
#include "entityfactory.h"
#include "node.h"
#include "game.h"

//-------------------------------------------------------------------//

Wave::Wave(
    const WaveInfo &_waveInfo,
    Node::NodeWVecWPtr _spawnNodes
    ):
  m_enemiesForCreation(_waveInfo.m_enemiesForCreation),
  m_birthRate(_waveInfo.m_birthRate),
  m_spawnNodes(_spawnNodes),
  m_time(0),
  m_maxActiveEnemies(200)
{
  // Clone the start enemies
  m_totalEnemiesForCreation.clear();
  BOOST_FOREACH(EnemyInfoPtr pair, m_enemiesForCreation)
  {
    m_totalEnemiesForCreation.push_back(pair->clone());
  }
}

//-------------------------------------------------------------------//

void Wave::reset()
{
  m_time = 0;
  // Start again by cloning
  m_enemiesForCreation.clear();
  BOOST_FOREACH(EnemyInfoPtr pair, m_totalEnemiesForCreation)
  {
    m_enemiesForCreation.push_back(pair->clone());
  }
}

//-------------------------------------------------------------------//

WavePtr Wave::create(
    const WaveInfo &_waveInfo,
    Node::NodeWVecWPtr _spawnNodes
    )
{
  WavePtr a(new Wave(_waveInfo, _spawnNodes));
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
  // create new enemies before update
  brain(_dt);

  //set a variable for the currency

  int currencyAdded = 0;
  int scoreAdded = 0;

  for(
      EnemyVec::iterator it = m_enemies.begin();
      it != m_enemies.end();
      )
  {
    // check health
    if ((*it)->getHealth() <= 0)
    {
      // KILL ENEMY!!!
      (*it)->kill();
    }
    if ((*it)->getToBeRemoved() == true)
    {
      //check if it was killed by a player

      if ((*it)->getKilledByUser() == true)
      {
        //add the currency and score to the appropriate variables

        currencyAdded += (*it)->getCurrencyValue();
        scoreAdded += (*it)->getScoreValue();
      }
      it = removeEnemy(it);
    }
    else
    {
      ++it;
    }
  }

  //get a pointer to the game

  Game * game = Game::instance();

  //and add the currency and the score

  game->addCurrency(currencyAdded);
  game->addScore(scoreAdded);

  // Make sure to update local entites
  BOOST_FOREACH(EnemyPtr enemy, m_enemies)
  {
    enemy->prepareForUpdate();
  }

  // parallelise enemy update for multi-threading
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

bool Wave::generatePaths(NodeWPtr _node)
{
  Q_UNUSED(_node)
  BOOST_FOREACH(EnemyPtr enemy, m_enemies)
  {
    if(!enemy->generateTempPath())
    {
      return false;
    }
  }

  BOOST_FOREACH(EnemyPtr enemy, m_enemies)
  {
    enemy->finalisePath();
  }
  return true;
}

//-------------------------------------------------------------------//

void Wave::brain(const double _dt)
{
  // Work out which enemies need creating and where
  // If there are enemies that haven't been created yet then create them at
  // random positions
  m_time += _dt;

  if(m_enemies.size() < m_maxActiveEnemies)
  {
    if(m_time > m_birthRate)
    {
      Node::NodeWVecPtr spawnNodes = m_spawnNodes.lock();
      if(spawnNodes)
      {
        BOOST_FOREACH(EnemyInfoPtr pair, m_enemiesForCreation)
        {
          if(pair->m_count)
          {
            // pick a node to generate on
            int randomInt = std::rand() % spawnNodes->size();
            NodePtr startNode = (*spawnNodes)[randomInt].lock();
            if(startNode)
            {
              addEnemy(
                    pair,
                    startNode->getPos()
                    );
              --pair->m_count;
            }
            // Break so we don't make one of each type
            break;
          }
        }
        m_time = 0;
      }
    }
  }
}

//-------------------------------------------------------------------//
void Wave::addEnemy(
    EnemyInfoCPtr _enemyInfo,
    const ngl::Vec3 &_pos
    )
{
  // use EntityFactory to create enemy then save it in m_enemies
  EnemyPtr newEnemy = boost::dynamic_pointer_cast<Enemy>(
        EntityFactory::createDynamicEntity(
          _enemyInfo->m_type,
          _pos,
          ngl::Vec3()
          )
        );
  newEnemy->setShield(_enemyInfo->m_shield);
  newEnemy->setMaxSpeed(_enemyInfo->m_maxSpeed);
  m_enemies.push_back(newEnemy);
}

//-------------------------------------------------------------------//

EnemyVec::iterator Wave::removeEnemy(EnemyVec::iterator _it)
{
  // unregister from game so that the smartptr is freed
  Game::instance()->unregisterID((*_it)->getID());
  // remove it from m_enemies and return the next iterator
  return m_enemies.erase(_it);
}

//-------------------------------------------------------------------//

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

//-------------------------------------------------------------------//

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

//-------------------------------------------------------------------//

std::list<Damage> Wave::checkCollisions()
{
  //initialise a list of collisions to return

  std::list<Damage> collisionList;

  // cycle through all of the enemies stored

  for (
       EnemyVec::iterator listIt = m_enemies.begin();
       listIt != m_enemies.end();
       listIt++
       )
  {

    Damage c = (*listIt)->baseTest();

    //check if there was a collision

    if (c.m_id != 0)
    {
      //if there was, add it to the list

      collisionList.push_back(c);

      //and kill the emeny using the suicide method
      //so that the player doesn't get the score or
      //currency from the enemy

      (*listIt)->suicide();
    }
  }
  //finally return the resulting list

  return collisionList;
}

//-------------------------------------------------------------------//

bool Wave::isDead() const
{
  // Make sure there are no enemies alive
  if(m_enemies.size() == 0)
  {
    // Make sure there are no enemies left to be created
    BOOST_FOREACH(EnemyInfoPtr pair, m_enemiesForCreation)
    {
      if(pair->m_count != 0)
      {
        return false;
      }
    }
    return true;
  }
  else
  {
    return false;
  }
}

//-------------------------------- WaveInfo ----------------------------------//

WaveInfoPtr WaveInfo::create(
    const Wave::EnemyInfoList &_enemiesForCreation,
    float _birthRate
    )
{
  WaveInfoPtr a(new WaveInfo(_enemiesForCreation, _birthRate));
  return a;
}
