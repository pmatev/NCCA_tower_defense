#include "include/game.h"
#include <iostream>
#include <ngl/Camera.h>
#include <ngl/NGLInit.h>
#include "renderer.h"
#include <ngl/VAOPrimitives.h>
#include "entityfactory.h"
#include "window.h"
#include "database.h"

Game* Game::s_instance = 0;

//-------------------------------------------------------------------//
Game::Game()
{

}
//-------------------------------------------------------------------//
Game::~Game()
{
    //delete m_light;
}
//-------------------------------------------------------------------//
Game* Game::instance()
{
    if(s_instance == 0)
    {
         s_instance = new Game();
    }
    return s_instance;

}
//-------------------------------------------------------------------//

void Game::init()
{


    //create and initialize the shaders.
    Renderer *render = Renderer::instance();
    render->createShader("Phong",2);
    render->createShader("Colour",2);
    render->createShader("UI", 1);
    //m_light = new ngl::Light(ngl::Vec3(1,2,0),ngl::Colour(1,1,1),ngl::POINTLIGHT);

    //Environment has to be created before the waves, as the enemies query data
    //in environment.
    m_environment = Environment::create(20, 20, 2, ngl::Vec3(0.0, 0.0, 0.0), 0, 0,10,10); // HARD CODED DUE TO PURE LAZINESS, WILL CHANGE VERY SOON :)
    m_waveManager = WaveManager::create();
    m_projectileManager = ProjectileManager::create();

}


//-------------------------------------------------------------------//
void Game::destroy()
{
    //call destroy on the database

    Database* db = Database::instance();

    db->destroy();

    if (s_instance)
    {
          delete s_instance;
    }
}

//-------------------------------------------------------------------//

unsigned int Game::getID()
{
  Window* w = Window::instance();

  return w->getID();
}

//-------------------------------------------------------------------//
void Game::registerID(EntityPtr _e, unsigned int _id)
{
    m_IDMap[_id] = _e;
}

//-------------------------------------------------------------------//
void Game::unregisterID(const unsigned int _i)
{
    m_IDMap.erase(_i);
}

//-------------------------------------------------------------------//
EntityPtr Game::getEntityByID(const unsigned int _i) const
{
  std::map<unsigned int, EntityPtr>::const_iterator it = m_IDMap.find(_i);
  if(it == m_IDMap.end())
  {
    return EntityPtr();
  }
  return it->second;
}

//-------------------------------------------------------------------//
void Game::update(const double _dt)
{
    // update code by timestep _dt
  // 1. clear database records
  // 2. publish dynamic entities (m_wavemanager & m_projectilemanager)
  // 3. update projectiles
  // 4. deal with collisions with enemies
  // 5. update enemies
  // 6. deal with collisions with base
  // 7. update environment

  // 1 //
  Database::instance()->clearRecords();
  // 2 //
  m_waveManager->publish();
  m_projectileManager->publish();
  // 3 //
  m_projectileManager->update(_dt);
  // 4 //
  dealDamage(m_projectileManager->checkCollisions());

  m_projectileManager->checkDeaths();
  // 5 //
  m_waveManager->update(_dt);
  // 6 //
  dealDamage(m_waveManager->checkCollisions());
  // 7 //
  m_environment->update(_dt);
}
//-------------------------------------------------------------------//
void Game::draw()
{
    glClearColor(0.1,0.2,0.3,1.0);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    m_environment->draw();
    m_waveManager->draw();
    m_projectileManager->draw();
}
//-------------------------------------------------------------------//

void Game::drawSelection()
{
  glClearColor(0.0,0.0,0.0,1.0);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  m_environment->drawSelection();
  m_waveManager->drawSelection();
}

//-------------------------------------------------------------------//


bool Game::tryToCreateTower(const std::string &_type, NodePtr _node)
{
  // HARD CODE FALSE SO THAT IT DOESNT BREAK OTHER PEOPLES CODE DURING DEBUGGING
  //return false;
  // Update all Enemy paths and check that they are all valid if _node
  // is occupied

  // quick stupidity check to make sure that the node is not occupied
  if(_node->isOccupied())
  {
    return false;
  }
  // set node to occupied
  _node->setOccupied(true);
  if(m_waveManager->generatePaths(_node))
  {
    // Tell the environment to create a tower
    m_environment->createTower(_type, _node);
    return true;
  }
  // if placing the tower was unsuccessful set the node back to unoccupied
  _node->setOccupied(false);
  return false;

}

//-------------------------------------------------------------------//

ngl::Vec3 Game::getBasePos() const
{
   return m_environment->getBasePos();
}

//-------------------------------------------------------------------//
EnvironmentWeakPtr Game::getEnvironmentWeakPtr()
{
  //EnvironmentWeakPtr a(m_environment);
  EnvironmentWeakPtr a(m_environment);
  return a;
}

//-------------------------------------------------------------------//

void Game::dealDamage(std::list<Collision> _collisionList)
{
  for(
      std::list<Collision>::iterator it = _collisionList.begin();
      it != _collisionList.end();
      ++it
      )
  {
    // Get smart pointer to object
    EntityPtr entity = getEntityByID(it->m_id);
    if(entity)
    {
      entity->dealDamage(it->m_damage);
    }
  }
}

//-------------------------------------------------------------------//

ProjectileManagerWeakPtr Game::getProjectileManagerPtr()
{
  ProjectileManagerWeakPtr a(m_projectileManager);

  return a;
}

//-------------------------------------------------------------------//


