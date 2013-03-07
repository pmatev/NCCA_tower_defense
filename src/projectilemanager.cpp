#include <boost/foreach.hpp>
#include "projectilemanager.h"
#include "entityfactory.h"
#include "game.h"

//-------------------------------------------------------------------//
ProjectileManagerPtr ProjectileManager::create()
{
  ProjectileManagerPtr a(new ProjectileManager());
  return a;
}

//-------------------------------------------------------------------//

ProjectileManager::ProjectileManager():
  boost::enable_shared_from_this<ProjectileManager>()
{
  //currently using default
}

//-------------------------------------------------------------------//

ProjectileManager::~ProjectileManager()
{
  //clear out all of the projectiles, unregistering them they are
  //removed

  // if there are projectiles

  if (m_projectiles.size() != 0)
  {
    //initialise the iterator

    ProjectileList::iterator listIt = m_projectiles.begin();

    // cycle through all of the projectiles stored

    for (; listIt != m_projectiles.end();)
    {
        //erase it

        listIt = removeProjectile(listIt);
    }
  }
}

//-------------------------------------------------------------------//

void ProjectileManager::checkCollisions(
    float _dt,
    std::list<Damage> &o_damages,
    std::list<Impulse> &o_impulses
    )
{
  // cycle through all of the projectiles stored

  for (
       ProjectileList::iterator listIt = m_projectiles.begin();
       listIt != m_projectiles.end();
       listIt++
       )
  {
    //call call collision detection on the projectiles
    std::list<GeneralType> types;
    types.push_back(ENEMY);
    Damage c = (*listIt)->collisionTest(types);

    //check if there was a collision

    if (c.m_id != 0)
    {
      //if there was, add it to the list
      (*listIt)->kill();
      o_damages.push_back(c);
    }
  }
  for(
      ExplosionList::iterator it = m_explosions.begin();
      it != m_explosions.end();
      )
  {
    if((*it)->execute(_dt, o_damages, o_impulses))
    {
      it = m_explosions.erase(it);
    }
    else
    {
      ++it;
    }
  }
}

//-------------------------------------------------------------------//

void ProjectileManager::update(const double _dt)
{
  //if there are projectiles

  if (m_projectiles.size() != 0)
  {
    //initialise the iterator

    ProjectileList::iterator listIt = m_projectiles.begin();

    // cycle through all of the projectiles stored

    for (; listIt != m_projectiles.end(); listIt++)
    {
      //call update on the projectiles

      (*listIt)->update(_dt);
    }
  }
}

//-------------------------------------------------------------------//

void ProjectileManager::checkDeaths()
{
  // if there are projectiles

  if (m_projectiles.size() != 0)
  {
    //initialise the iterator

    ProjectileList::iterator listIt = m_projectiles.begin();

    // cycle through all of the projectiles stored

    for (; listIt != m_projectiles.end();)
    {
      //if the health of the projectile is 0

      if ((*listIt)->getHealth() <= 0)
      {
        //call kill

        (*listIt) -> kill();
      }

      if ((*listIt)->getToBeRemoved() == true)
      {
        //remove the projectile

        listIt = removeProjectile(listIt);
      }

      else
      {
        //increment the iterator

        listIt++;
      }
    }
  }
}

//-------------------------------------------------------------------//

ProjectileWPtr ProjectileManager::addProjectile(
    const std::string &_type,
    const ngl::Vec3 &_pos,
    const ngl::Vec3 &_velocity,
    int _emitterID
    )
{
  //create a new type

  ProjectilePtr newProjectile = boost::dynamic_pointer_cast<Projectile>(
        EntityFactory::createDynamicEntity(
          _type,
          _pos,
          _velocity
          )
        );

  // Tell the projectile who its parent is

  newProjectile->setParent(this);
  //add the projectile to the list of projectiles
  newProjectile->setEmitterID(_emitterID);
  newProjectile->setVelocity(_velocity);
  m_projectiles.push_back(newProjectile);
  return ProjectileWPtr(newProjectile);
}

//-------------------------------------------------------------------//

void ProjectileManager::addExplosion(
    float _power,
    float _damage,
    float _radius,
    const ngl::Vec3 &_pos,
    float _lifetime
    )
{
  m_explosions.push_back(
        Explosion::create(
          _power,
          _damage,
          _radius,
          _pos,
          _lifetime
          )
        );
}

//-------------------------------------------------------------------//

ProjectileList::iterator ProjectileManager::removeProjectile(
    ProjectileList::iterator _listIt
    )
{
  //first un-register the entity from the game

  Game* game = Game::instance();
  game->unregisterID((*_listIt)->getID());

  //erase the iterator

  return m_projectiles.erase(_listIt);
}

//-------------------------------------------------------------------//

void ProjectileManager::publish()
{
  //if there are projectiles in the set

  if (m_projectiles.size() != 0)
  {
    //set an iterator to the beginning of the list

    ProjectileList::iterator listIt = m_projectiles.begin();

    //and cycle through each element of the list

    for (; listIt != m_projectiles.end(); listIt++)
    {
      //call publish

      (*listIt)->publish();
    }
  }
}

//-------------------------------------------------------------------//

void ProjectileManager::draw()
{
  // draw all projectiles
  for(
      ProjectileList::iterator it = m_projectiles.begin();
      it != m_projectiles.end();
      ++it
      )
  {
    (*it)->draw();
  }
  // draw explosions
  BOOST_FOREACH(ExplosionPtr explosion, m_explosions)
  {
    explosion->draw();
  }
}

//-------------------------------------------------------------------//

