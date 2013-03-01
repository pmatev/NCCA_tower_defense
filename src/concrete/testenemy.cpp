#include <boost/foreach.hpp>
#include "ngl/ShaderLib.h"
#include "texturelib.h"
#include "window.h"
#include "concrete/testenemy.h"
#include "renderer.h"
#include "fsm/states/enemystates.h"
//-------------------------------------------------------------------//

TestEnemy::TestEnemy(
    const ngl::Vec3 & _pos,
    const ngl::Vec3 &_aim,
    unsigned int _id
    ):
  Enemy(
    _pos,
    _aim,
    _id,
    5, // currency value
    20, //score value
    3.0 // max distance from nearest path node
    )

{
  // ctor just passes everything to parent class
  // HACKY TESTING HERE
  generateMesh();
  //  m_active = false;

  m_damage = 5;
  m_velocity = 0;
  m_maxVelocity = 2.0;
  m_maxForce = ngl::Vec3(5, 5, 5);
}

//-------------------------------------------------------------------//

TestEnemy::~TestEnemy()
{
  //currently using default
}

void TestEnemy::stateInit()
{
  //state machine
  m_stateMachine = new StateMachine(EntityWPtr(shared_from_this()));
  m_stateMachine->setCurrentState(Normal::instance());
  m_stateMachine->setPreviousState(Normal::instance());
  m_stateMachine->setGlobalState(0);

  //steering behaviours
  m_steering = new SteeringBehaviours(EntityWPtr(shared_from_this()));
}

//-------------------------------------------------------------------//

EntityPtr TestEnemy::create(
    const ngl::Vec3 &_pos,
    const ngl::Vec3 &_aim,
    unsigned int _id
    )
{
  EntityPtr a(new TestEnemy(_pos,_aim, _id));
  a->stateInit();

  return a;
}

//-------------------------------------------------------------------//

void TestEnemy::generateMesh()
{
  const static GLubyte indices[]=  {
                                      0,1,5,0,4,5, // back
                                      3,2,6,7,6,3, // front
                                      0,1,2,3,2,0, // top
                                      4,5,6,7,6,4, // bottom
                                      0,3,4,4,7,3,
                                      1,5,2,2,6,5
                                   };

  GLfloat vertices[] = {-0.3,0.3,-0.3,
                        0.3,0.3,-0.3,
                        0.3,0.3,0.3,
                        -0.3,0.3,0.3,
                        -0.3,-0.3,-0.3,
                        0.3,-0.3,-0.3,
                        0.3,-0.3,0.3,
                        -0.3,-0.3,0.3
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


  GLfloat uvs[] = { 0.0, 0.0,
                    0.0, 0.0,
                    0.0, 0.0,
                    0.0, 0.0,
                    0.0, 0.0,
                    0.0, 0.0,
                    1.0, 1.0,
                    1.0, 1.0
                    };


  std::vector<Renderer::vertData> boxData;
  Renderer::vertData d;
  for(int j=0; j<8; j++)
  {
    d.x = vertices[j*3];
    d.y = vertices[(j*3)+1];
    d.z = vertices[(j*3)+2];
    d.nx = normals[j*3];
    d.ny = normals[(j*3)+1];
    d.nz = normals[(j*3)+2];
    d.u = uvs[j*2];
    d.v = uvs[j*2+1];


    boxData.push_back(d);
  }


  //call top generate the mesh bounding box

  generateLsBBox(boxData);

  Renderer *render = Renderer::instance();

  render->createVAO(m_IDStr, GL_TRIANGLES);

//  render->setIndexedDataToVAO(
//        m_IDStr,
//        sizeof(Renderer::vertData)*boxData.size(),
//        3,
//        boxData[0].x,
//        sizeof(indices),
//        &indices[0],
//        sizeof(indices)/sizeof(GLubyte)
//        );

  VAOPtr vao = render->getVAObyID(m_IDStr);
  vao->bind();

  vao->setIndexedData(sizeof(Renderer::vertData)*boxData.size(),
                      boxData[0].x,
                      sizeof(indices),
                      &indices[0],
                      GL_UNSIGNED_BYTE,
                      GL_STATIC_DRAW);

  // vert position attribute
  vao->setVertexAttributePointer(0,3,GL_FLOAT,sizeof(Renderer::vertData),0);
  // vert normals attribute
  vao->setVertexAttributePointer(1,3,GL_FLOAT,sizeof(Renderer::vertData),3);

  vao->setVertexAttributePointer(2,2,GL_FLOAT,sizeof(Renderer::vertData),6);

  vao->setNumIndices(sizeof(indices)/sizeof(GLubyte));

  vao->unbind();
}

//-------------------------------------------------------------------//

ngl::Vec3 TestEnemy::brain()
{
  ngl::Vec3 steeringDirection = m_steering->calculate();
  // TEST value (tells it to just go forward)
  //return getPathVec() * 0.01;
  return steeringDirection;
}

//-------------------------------------------------------------------//

//void TestEnemy::draw()
//{
//    Renderer *r = Renderer::instance();

//    // draw to selection buffer
//    r->bindFrameBuffer("Selection");
//    r->loadMatrixToShader("Colour");
//    r->draw(m_IDStr, "Colour");

//    // draw to default buffer (screen)
//    r->bindFrameBuffer(0);
//    r->loadMatrixToShader(m_transformStack, "Phong");
//    r->draw(m_IDStr, "Phong");

//}

//-------------------------------------------------------------------//

//void TestEnemy::drawSelection()
//{
//  Renderer *r = Renderer::instance();
//  //m_transformStack.setScale(0.3, 0.3, 0.3);
//  r->loadMatrixToShader(m_transformStack, "Colour");

//  r->drawSelection(m_ID, m_IDStr);
//}

//-------------------------------------------------------------------//

void TestEnemy::filterViewVolume(EntityRecordWCList &o_localEntities)
{
  //Q_UNUSED(o_localEntities);
//  float maxSqrDist = 2;

//  for(
//      EntityRecordWCList::iterator it = o_localEntities.begin();
//      it != o_localEntities.end();
//      )
//  {
//    bool remove = false;
//    EntityRecordCPtr recordStrong = it->lock();
//    if(recordStrong)
//    {
//      if(recordStrong->m_generalType == ENEMY)
//      {

//      }
//      else
//      {
//        remove = true;
//      }
//    }
//    if(remove)
//    {
//      it = o_localEntities.erase(it);
//    }
//    else
//    {
//      ++it;
//    }
//  }
}

//-------------------------------------------------------------------//

void TestEnemy::draw()
{
  Renderer *r = Renderer::instance();
  TextureLib *tex = TextureLib::instance();
  ngl::ShaderLib *shader = ngl::ShaderLib::instance();

  (*shader)["Constant"]->use();
  r->loadMatrixToShader(m_transformStack.getCurrentTransform().getMatrix(), "Constant");

  shader->setShaderParam4f("colour", 0.1, 0.1, 0.8, 1);
  shader->setShaderParam4f("colourSelect", 0, 0, 0, 0);

  r->draw("enemy", "Constant");

  // draw healthbar
  (*shader)["TexturedConstant"]->use();
  m_healthBar->setUVScale(50/m_health);
  tex->bindTexture("healthbar");
  m_healthBar->draw("TexturedConstant");
}

