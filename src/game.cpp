#include "include/game.h"
#include <iostream>
#include <ngl/Camera.h>
#include <ngl/NGLInit.h>
#include "renderer.h"
#include <ngl/VAOPrimitives.h>
#include "entityfactory.h"

Game* Game::s_instance = 0;

//-------------------------------------------------------------------//
Game::Game():
  m_currentID(0) // set current ID to
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

    m_waveManager = WaveManager::create();
    m_environment = Environment::create(6, 6, 2, ngl::Vec3(0.0, 0.0, 0.0), 3, 3); // HARD CODED DUE TO PURE LAZINESS, WILL CHANGE VERY SOON :)
}


//-------------------------------------------------------------------//
void Game::destroy()
{
    if (s_instance)
    {
          delete s_instance;
    }
}
//-------------------------------------------------------------------//
unsigned int Game::registerID(EntityPtr _e)
{
    m_currentID++;

    m_IDMap[m_currentID] = _e;

    return m_currentID;
}

//-------------------------------------------------------------------//
void Game::unregisterID(const unsigned int _i)
{
    m_IDMap.erase(_i);
}

//-------------------------------------------------------------------//
EntityPtr Game::getEntityByID(const unsigned int _i)
{
    return m_IDMap.find(_i)->second;
}

//-------------------------------------------------------------------//
void Game::update(const double _t)
{
    // update code by timestep _t
  m_waveManager->update();
  m_environment->update();
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

bool Game::tryToCreateTower(const std::string &_type, NodePtr _node)
{
  // Update all Enemy paths and check that they are all valid
  if(m_waveManager->generatePaths(_node))
  {
    // Tell the environment to create a tower
    m_environment->createTower(_type, _node);

    return true;
  }
  return false;

}

//-------------------------------------------------------------------//




