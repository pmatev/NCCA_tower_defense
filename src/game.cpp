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
//    ngl::VAOPrimitives *prim = ngl::VAOPrimitives::instance();
//    prim->createSphere("sphere",1.0,20);

    Renderer *render = Renderer::instance();
    render->createShader("Phong");
    render->createShader("Colour");
    //m_light = new ngl::Light(ngl::Vec3(1,2,0),ngl::Colour(1,1,1),ngl::POINTLIGHT);

    //Environment has to be created before the waves, as the enemies query data
    //in environment.
    m_environment = Environment::create(10, 10, 2, ngl::Vec3(0.0, 0.0, 0.0), 8, 8); // HARD CODED DUE TO PURE LAZINESS, WILL CHANGE VERY SOON :)
    m_waveManager = WaveManager::create();

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
EntityPtr Game::getEntityByID(const unsigned int _i)
{
  std::map<unsigned int, EntityPtr>::iterator it = m_IDMap.find(_i);
  if(it == m_IDMap.end())
  {
    return EntityPtr();
  }
  return it->second;
}

//-------------------------------------------------------------------//
void Game::update(const double _t)
{
    // update code by timestep _t
  m_environment->update();
  m_waveManager->update();
}
//-------------------------------------------------------------------//
void Game::draw()
{
    glClearColor(0.1,0.2,0.3,1.0);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    m_environment->draw();
    m_waveManager->draw();
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



