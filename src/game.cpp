#include <iostream>

#include <QtXml/QDomDocument>
#include <QFile>
#include <boost/lexical_cast.hpp>
#include <ngl/NGLInit.h>
#include <ngl/VAOPrimitives.h>
#include <ngl/Camera.h>
#include "ngl/ShaderLib.h"

#include "renderer.h"
#include "entityfactory.h"
#include "window.h"
#include "database.h"
#include "include/game.h"
#include "turret.h"


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

std::vector<ngl::Vec2> Game::getCoordsFromXML(QDomElement _docElem,
                                 std::string _nodeName)
{
  std::vector<ngl::Vec2> coordsVec;

  //Get the spawnPoint nodes
  QDomNodeList coordList = _docElem.elementsByTagName(QString::fromStdString(_nodeName));

  for(int i = 0; i < coordList.count(); i++)
  {
    //The spawn point node
    QDomElement coordNode = coordList.at(i).toElement();

    //Get the children of the spawn point node
    QDomNode coordEntries = coordNode.firstChild();

    int x;
    int y;

    //Loop through the children of spawn point
    while(!coordEntries.isNull())
    {
      //The current child of the spawn point node
      QDomElement coordData = coordEntries.toElement();
      //The child's name
      QString coordDataTagName = coordData.tagName();

      if(coordDataTagName == "x")
      {
        x = boost::lexical_cast<int>(coordData.text().toStdString());
      }
      else if(coordDataTagName == "y")
      {
        y = boost::lexical_cast<int>(coordData.text().toStdString());
      }

      coordEntries = coordEntries.nextSibling();
    }

    coordsVec.push_back(ngl::Vec2(x, y));
  }

  return coordsVec;
}

//-------------------------------------------------------------------//

void Game::setupScene()
{
  //Load configuration
  QFile* file = new QFile("config/config.xml");

  setLost(false);

  //Test if the file failed to open
  if(!file->open(QIODevice::ReadOnly | QIODevice::Text))
  {
    std::cout << "Failed to load XML file." << std::endl;
  }

  //QDomElement stores the XML tree
  QDomDocument document("configDocument");

  //Try to set document's content to the xml file
  if(!document.setContent(file))
  {
    std::cout << "Failed to load XML." << std::endl;
  }

  //Grab the root node
  QDomElement docElem = document.documentElement();

  //Create the meshlib
  MeshLibWPtr w_mesh_lib = MeshLib::instance();
  MeshLibPtr mesh_lib = w_mesh_lib.lock();
  if(mesh_lib)
  {
    std::cout << "initialised meshlib" << std::endl;
    mesh_lib->init();
  }

  //========================================================================//
  //                              SpawnCoords                               //
  //========================================================================//

  //Environment has to be created before the waves, as the enemies query data
  //in environment.

  std::vector<ngl::Vec2> spawnCoords = getCoordsFromXML(docElem,
                                                        "spawnCoord");

  std::vector<ngl::Vec2> invisibleCoords = getCoordsFromXML(docElem,
                                                            "invisibleCoord");

  std::vector<ngl::Vec2> wallCoords = getCoordsFromXML(docElem,
                                                       "wallCoord");

  //========================================================================//
  //                              Environment                               //
  //========================================================================//

  //Get the environment node
  QDomNodeList environmentList = docElem.elementsByTagName("environment");

  //make sure there's only one environment node
  if(environmentList.size() == 1)
  {
    //The environment node
    QDomElement envNode = environmentList.at(0).toElement();

    //Get the children of the environment node
    QDomNode envEntries = envNode.firstChild();

    //Declares the vars used to create the environment
    int gridWidth;
    int gridHeight;
    float hexagonSize;
    int baseX;
    int baseY;
    int dbGridSizeX;
    int dbGridSizeZ;

    //while there's entries in the environment node
    while(!envEntries.isNull())
    {
      //The current child of the environment node
      QDomElement envData = envEntries.toElement();
      //The child's name
      QString envDataTagName = envData.tagName();

      if(envDataTagName == "gridWidth")
      {
        gridWidth = boost::lexical_cast<int>(envData.text().toStdString());
      }
      else if(envDataTagName == "gridHeight")
      {
        gridHeight = boost::lexical_cast<int>(envData.text().toStdString());
      }
      else if(envDataTagName == "hexSize")
      {
        hexagonSize = boost::lexical_cast<int>(envData.text().toStdString());
      }
      else if(envDataTagName == "baseX")
      {
        baseX = boost::lexical_cast<int>(envData.text().toStdString());
      }
      else if(envDataTagName == "baseY")
      {
        baseY = boost::lexical_cast<int>(envData.text().toStdString());
      }
      else if(envDataTagName == "dbGridSizeX")
      {
        dbGridSizeX = boost::lexical_cast<int>(envData.text().toStdString());
      }
      else if(envDataTagName == "dbGridSizeZ")
      {
        dbGridSizeZ = boost::lexical_cast<int>(envData.text().toStdString());
      }

      //Advance to the next child.
      envEntries = envEntries.nextSibling();
    }
    EnvironmentInfo envInfo(
          gridWidth,
          gridHeight,
          hexagonSize,
          baseX,
          baseY,
          dbGridSizeX,
          dbGridSizeZ,
          spawnCoords,
          invisibleCoords,
          wallCoords
          );
    // This should be done to make sure that the database gets initialised
    // correctly, otherwise new environment would publish before the old one
    // has been deleted. When the old one gets deleted it will unpublish the
    // new records
    m_environment.reset();
    m_environment = Environment::create(envInfo);
  }

  //========================================================================//
  //                                 Waves                                  //
  //========================================================================//


  WaveInfoList waveInfos;

  //Get the wave nodes
  QDomNodeList waveList = docElem.elementsByTagName("wave");

  //For each wave node
  for(int i =0; i < waveList.count(); i++)
  {
    //The wave node
    QDomElement waveNode = waveList.at(i).toElement();

    //Get the children of the wave node
    QDomNode waveEntries = waveNode.firstChild();

    Wave::EnemyInfoList creationEnemies;
    float spawnRate;

    //Loops through the wave children
    while(!waveEntries.isNull())
    {
      //The current child of the environment node
      QDomElement waveData = waveEntries.toElement();
      //The child's name
      QString waveDataTagName = waveData.tagName();

      //If its an enemyType we need to loop through its children
      if(waveDataTagName == "enemyTypes")
      {
        //Get the enemy types.
        QDomNodeList enemyTypesList = waveData.elementsByTagName("enemyType");

        //Loop through the enemy types
        for(int j = 0; j < enemyTypesList.count(); j++)
        {
          //The enemy type node
          QDomElement enemyTypeNode = enemyTypesList.at(j).toElement();

          //Get the children of the enemy type node
          QDomNode enemyTypeEntries = enemyTypeNode.firstChild();

          std::string type;
          int count;
          float shield;
          float maxSpeed;

          //This will loop through the enemyType children
          while(!enemyTypeEntries.isNull())
          {
            //The current child of the enemy type node
            QDomElement enemyTypeData = enemyTypeEntries.toElement();
            //The child's name
            QString enemyTypeDataTagName = enemyTypeData.tagName();

            if(enemyTypeDataTagName == "type")
            {
              type = enemyTypeData.text().toStdString();
            }
            else if(enemyTypeDataTagName == "count")
            {
              count = boost::lexical_cast<int>(enemyTypeData.text().toStdString());
            }else if(enemyTypeDataTagName == "shield")
            {
              shield = boost::lexical_cast<float>(enemyTypeData.text().toStdString());
            }else if(enemyTypeDataTagName == "maxSpeed")
            {
              maxSpeed = boost::lexical_cast<float>(enemyTypeData.text().toStdString());
            }

            enemyTypeEntries = enemyTypeEntries.nextSibling();
          }

          //Add a new enemytype
          creationEnemies.push_back(
                Wave::EnemyInfo::create(
                  count,
                  type,
                  shield,
                  maxSpeed
                  )
                );
        }
      }
      else if(waveDataTagName == "spawnRate")
      {
        spawnRate = boost::lexical_cast<float>(waveData.text().toStdString());
      }

      waveEntries = waveEntries.nextSibling();
    }

    waveInfos.push_back(
          WaveInfo::create(
            creationEnemies,
            spawnRate
            )
          );
  }

  m_waveManager = WaveManager::create(m_environment->getSpawnNodes(), waveInfos);

  m_projectileManager = ProjectileManager::create();


  //========================================================================//
  //                                 Player                                 //
  //========================================================================//

  QDomNodeList playerList = docElem.elementsByTagName("player");

  int playerCurrency;

  //make sure there's only one player node
  if(playerList.size() == 1)
  {
    //The player node
    QDomElement playerNode = playerList.at(0).toElement();

    //Get the children of the player node
    QDomNode playerEntries = playerNode.firstChild();

    //Loops through the player children
    while(!playerEntries.isNull())
    {
      //The current child of the environment node
      QDomElement playerData = playerEntries.toElement();
      //The child's name
      QString playerDataTagName = playerData.tagName();

      if(playerDataTagName == "startCurrency")
      {
        playerCurrency = boost::lexical_cast<int>(playerData.text().toStdString());
      }

      playerEntries = playerEntries.nextSibling();
    }
  }

  m_player = Player::create(playerCurrency); //Hard coded now, should probably be set from a file
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
    m_projectileManager->update(_dt);
    // 4 //
    std::list<Damage> damages;
    std::list<Impulse> impulses;
    m_projectileManager->checkCollisions(_dt, damages, impulses);
    dealDamage(damages);
    dealImpulses(impulses);

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



    m_environment->draw();
    m_waveManager->draw();
    m_projectileManager->draw();
}
//-------------------------------------------------------------------//

//void Game::drawSelection()
//{
//  glClearColor(0.0,0.0,0.0,1.0);
//  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
//  m_environment->drawSelection();
//  m_waveManager->drawSelection();
//}

//-------------------------------------------------------------------//


bool Game::tryToCreateTower(const std::string &_type, NodePtr _node)
{
  // Update all Enemy paths and check that they are all valid if _node
  // is occupied
  bool status = true;

  // quick stupidity check to make sure that the node is not occupied
  if(_node->isOccupied())
  {
    return false;
  }
  // set node to occupied
  _node->setOccupied(true);
  m_environment->recalculateSearchTree();

  // Check to make sure that all spawn node are accessable
  if(!m_environment->checkSpawnNodePaths())
  {
    status = false;
  }
  else
  {
    if(m_waveManager->generatePaths(NodeWPtr(_node)))
    {
      // Tell the environment to create a tower
      m_environment->createTower(_type, _node);
      status =  true;
    }
    else
    {
      status = false;
    }
  }
  if(!status)
  {
    // if placing the tower was unsuccessful set the node back to unoccupied
    _node->setOccupied(false);
    m_environment->recalculateSearchTree();
  }
  return status;

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


void Game::dealDamage(const std::list<Damage> &_collisionList)
{
  for(
      std::list<Damage>::const_iterator it = _collisionList.begin();
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

void Game::dealImpulses(const std::list<Impulse> &_impulses)
{
  for(
      std::list<Impulse>::const_iterator it = _impulses.begin();
      it != _impulses.end();
      ++it
      )
  {
    // Get smart pointer to object
    EntityPtr entity = getEntityByID(it->m_id).lock();
    if(entity)
    {
      // Impulses can only be applied to dynamic entities so need to cast
      DynamicEntityPtr dynamicEntity = boost::dynamic_pointer_cast<DynamicEntity>(entity);
      if(dynamicEntity)
      {
        dynamicEntity->dealImpulse(it->m_vec);
      }
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

void Game::setNodehighlighted(int _id, int _highlighted)
{
    EntityPtr entityClick = getEntityByID(_id).lock();


    NodePtr node = boost::dynamic_pointer_cast<Node>(entityClick);


    if(node) // check that it is a valid node
    {
        node->setHighlighted(_highlighted); //change highlighted flag
        std::cout<<node->getHighlighted()<<std::endl;

    }

}

//-------------------------------------------------------------------//

void Game::startWaves()
{
  m_waveManager->startWaves();
}

//-------------------------------------------------------------------//

bool Game::upgradeTurret(int _id)
{
  EntityPtr entity = getEntityByID(_id).lock();
  if(entity)
  {
    TurretPtr turret = boost::dynamic_pointer_cast<Turret>(entity);
    if(turret)
    {
      return turret->upgrade();
    }
  }
  return false;
}

//-------------------------------------------------------------------//

bool Game::getCurrentUpgrade(Turret::UpgradeDataWPtr &o_upgradeData, int _id)
{
  EntityPtr entity = getEntityByID(_id).lock();
  if(entity)
  {
    TurretPtr turret = boost::dynamic_pointer_cast<Turret>(entity);
    if(turret)
    {
      return turret->getCurrentUpgrade(o_upgradeData);
    }
  }
  return false;
}

//-------------------------------------------------------------------//

bool Game::getNextUpgrade(Turret::UpgradeDataWPtr &o_upgradeData, int _id)
{
  EntityPtr entity = getEntityByID(_id).lock();
  if(entity)
  {
    TurretPtr turret = boost::dynamic_pointer_cast<Turret>(entity);
    if(turret)
    {
      return turret->getNextUpgrade(o_upgradeData);
    }
  }
  return false;
}


float Game::getBaseHealth() const
{
    return m_environment->getBaseHealth();
}

