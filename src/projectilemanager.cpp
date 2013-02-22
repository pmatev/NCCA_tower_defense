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

ProjectileManager::ProjectileManager()
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

std::list<Collision> ProjectileManager::checkCollisions()
{
  //initialise a list of collisions to return

  std::list<Collision> collisionList;



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
    Collision c = (*listIt)->collisionDetection(types);

    //check if there was a collision

    if (c.m_id != 0)
    {
      //if there was, add it to the list
      (*listIt)->kill();
      collisionList.push_back(c);
    }
  }
  //finally return the resulting list

  return collisionList;
}

//-------------------------------------------------------------------//

void ProjectileManager::update()
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

      (*listIt)->update();
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
        //erase it

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

void ProjectileManager::addProjectile(
    std::string &_type,
    const ngl::Vec3 &_pos,
    const ngl::Vec3 &_aim
    )
{
  //create a new type

  ProjectilePtr newProjectile = boost::dynamic_pointer_cast<Projectile>(
        EntityFactory::createDynamicEntity(
          _type,
          _pos,
          _aim
          )
        );

  //add the projectile to the list of projectiles

  m_projectiles.push_back(newProjectile);
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
  // Go through all the enemies and call their publish
  for(
      ProjectileList::iterator it = m_projectiles.begin();
      it != m_projectiles.end();
      ++it
      )
  {
    (*it)->draw();
  }
}

//-------------------------------------------------------------------//

