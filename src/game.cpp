#include "include/game.h"
#include <iostream>
#include <ngl/Camera.h>
#include <ngl/NGLInit.h>
#include "renderer.h"
#include <ngl/VAOPrimitives.h>

Game* Game::s_instance = 0;

//-------------------------------------------------------------------//
Game::Game():
  m_currentID(0) // set current ID to
{

}
//-------------------------------------------------------------------//
Game::~Game()
{
    delete m_light;
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

    m_light = new ngl::Light(ngl::Vec3(1,2,0),ngl::Colour(1,1,1),ngl::POINTLIGHT);



    /* -------------------------------------------------- Testing ---------------------------------------------------------- */

    const static GLubyte indices[]=  {
                                        0,1,5,0,4,5, // back
                                        3,2,6,7,6,3, // front
                                        0,1,2,3,2,0, // top
                                        4,5,6,7,6,4, // bottom
                                        0,3,4,4,7,3,
                                        1,5,2,2,6,5
                                     };

    GLfloat vertices[] = {-1,1,-1,
                          1,1,-1,
                          1,1,1,
                          -1,1,1,
                          -1,-1,-1,
                          1,-1,-1,
                          1,-1,1,
                          -1,-1,1
                         };
    GLfloat normals[] = {-1,1,-1,
                          1,1,-1,
                          1,1,1,
                          -1,1,1,
                          -1,-1,-1,
                          1,-1,-1,
                          1,-1,1,
                          -1,-1,1
                         };

    std::vector<vertData> boxData;
    vertData d;
    for(int j=0; j<8; j++)
    {
      d.x = vertices[j*3];
      d.y = vertices[(j*3)+1];
      d.z = vertices[(j*3)+2];
      d.nx = normals[j*3];
      d.ny = normals[(j*3)+1];
      d.nz = normals[(j*3)+2];

      boxData.push_back(d);
    }

    unsigned int meshSize = sizeof(boxData);

    render->createVAO("box");
    render->setIndexedDataToVAO("box",meshSize*boxData.size(), boxData[0].x, sizeof(indices), &indices[0], meshSize);


   // render->loadLightToShader(m_light,"Phong");

    /* ------------------------------------------------- End Testing -------------------------------------------------------------------- */

    m_waveManager = WaveManager::create();
    m_environment = Environment::create(6, 6, 2); // HARD CODED DUE TO PURE LAZINESS, WILL CHANGE VERY SOON :)

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
}
//-------------------------------------------------------------------//
void Game::draw()
{
    glClearColor(0.1,0.2,0.3,1.0);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

   // ngl::VAOPrimitives *prim = ngl::VAOPrimitives::instance();

    Renderer *render = Renderer::instance();

    ngl::ShaderLib *shader = ngl::ShaderLib::instance();
    (*shader)["Phong"]->use();

    ngl::TransformStack tx;
    ngl::Transformation t;
    t.setScale(0.5);
    tx.setGlobal(t);

    render->loadMatrixToShader(tx,"Phong");
    render->draw();


}
//-------------------------------------------------------------------//

bool Game::tryToCreateTower(const std::string &_type, NodePtr _node)
{
  // Update all Enemy paths and check that they are all valid
  if(m_waveManager->generatePaths(_node))
  {
    // Tell the environment to create a tower
    m_environment->createTower(_type, _node);
  }
}

//-------------------------------------------------------------------//




