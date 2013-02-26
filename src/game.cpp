#include <ngl/Camera.h>
#include "renderer.h"
#include <ngl/NGLInit.h>
#include <ngl/VAOPrimitives.h>
#include "entityfactory.h"
#include "window.h"
#include "database.h"
#include <iostream>
#include "include/game.h"
#include "ngl/ShaderLib.h"

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

    ngl::ShaderLib *shader = ngl::ShaderLib::instance();

    shader->createShaderProgram("UI");

    shader->attachShader("UIVertex",ngl::VERTEX);
    shader->attachShader("UIFragment",ngl::FRAGMENT);
    shader->loadShaderSource("UIVertex", "shaders/UI.vs");
    shader->loadShaderSource("UIFragment","shaders/UI.fs");

    shader->compileShader("UIVertex");
    shader->compileShader("UIFragment");

    shader->attachShaderToProgram("UI","UIVertex");
    shader->attachShaderToProgram("UI","UIFragment");

    shader->bindAttribute("UI", 0, "inVert");
    shader->bindAttribute("UI",1,"inUV");
    shader->linkProgramObject("UI");


//    glBindFragDataLocation(shader->getProgramID("UI"), 0, "fragColour");


    std::cerr<<glGetError()<<std::endl;

    //m_light = new ngl::Light(ngl::Vec3(1,2,0),ngl::Colour(1,1,1),ngl::POINTLIGHT);
    setupScene();
}

//-------------------------------------------------------------------//

void Game::reset()
{
  // In the future this may need some other code to clear things
  m_IDMap.clear();
  setupScene();
}

//-------------------------------------------------------------------//

void Game::setupScene()
{
  //Environment has to be created before the waves, as the enemies query data
  //in environment.
  //if(!m_environment) // FOR TESTING SO THAT TOWERS ARE NOT REMOVED
  m_environment = Environment::create(20, 20, 2, ngl::Vec3(0.0, 0.0, 0.0), 10, 10,10,10); // HARD CODED DUE TO PURE LAZINESS, WILL CHANGE VERY SOON :)
  m_waveManager = WaveManager::create();
  m_projectileManager = ProjectileManager::create();
  m_player = Player::create(1000); //Hard coded now, should probably be set from a file
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
EntityWPtr Game::getEntityByID(const unsigned int _i) const
{
  std::map<unsigned int, EntityWPtr>::const_iterator it = m_IDMap.find(_i);
  if(it == m_IDMap.end())
  {
    return EntityWPtr();
  }
  return EntityWPtr(it->second);
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
//  m_projectileManager->update(_dt);
//  // 4 //
//  dealDamage(m_projectileManager->checkCollisions());

//  m_projectileManager->checkDeaths();
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
  if(m_waveManager->generatePaths(NodeWPtr(_node)))
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
EnvironmentWPtr Game::getEnvironmentWeakPtr()
{
  //EnvironmentWPtr a(m_environment);
  EnvironmentWPtr a(m_environment);
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
    EntityPtr entity = getEntityByID(it->m_id).lock();
    if(entity)
    {
      entity->dealDamage(it->m_damage);
    }
  }
}

//-------------------------------------------------------------------//

ProjectileManagerWPtr Game::getProjectileManagerWeakPtr()
{
  ProjectileManagerWPtr a(m_projectileManager);

  return a;
}

//-------------------------------------------------------------------//

//-------------------------------------------------------------------//

void Game::setNodehighlighted(int _id, bool _highlighted)
{
    EntityPtr entityClick = getEntityByID(_id).lock();

    Q_UNUSED(_highlighted);
    Q_UNUSED(entityClick);

//    NodePtr node = boost::dynamic_pointer_cast<Node>(entityClick);


//    if(node) // check that it is a valid node
//    {
//        node->setHighlighted(_highlighted); //change highlighted flag

//    }

}



