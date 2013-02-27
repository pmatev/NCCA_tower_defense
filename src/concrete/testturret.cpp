#include "include/concrete/testturret.h"
#include "include/fsm/states/turretstates.h"
#include "renderer.h"

//-------------------------------------------------------------------//
TestTurret::TestTurret(
    NodePtr _linkedNode,
    unsigned int &_id
    ):
  Turret(
    _linkedNode,
    _id,
    std::string("Bullet")
    )
{
  m_fov = 90;
  m_viewDistance = 10;
  m_maxRotationSpeed = 3;
  // pass everything into the turret
  generateMesh();
  publish();
}

//-------------------------------------------------------------------//

EntityPtr TestTurret::create(
    NodePtr _linkedNode,
    unsigned int _id
    )
{
  // pass everything to the ctor
  EntityPtr a(
        new TestTurret(
          _linkedNode,
          _id
          )
        );
  a->init();

  return a;
}

//-------------------------------------------------------------------//

void TestTurret::init()
{
  m_stateMachine = new StateMachine(EntityWPtr(shared_from_this()));
  m_stateMachine->setCurrentState(BasicUpgrade::instance());
  m_stateMachine->setPreviousState(LockOn::instance());
  //m_stateMachine->setGlobalState(0);

  registerUpgrade(
        BasicUpgrade::instance(),
        UpgradeData::create(
          std::string("Initial Upgrade"),
          std::string("descriptiony thing"),
          std::string("test.jpg"),
          0
          )
        );
  registerUpgrade(
        AdvancedUpgrade::instance(),
        UpgradeData::create(
          std::string("Super Advanced Upgrade"),
          std::string("other descriptiony thing\nmakes bullets shoot faster"),
          std::string("otherTest.jpg"),
          100
          )
        );
}

//-------------------------------------------------------------------//

void TestTurret::generateMesh()
{
  const static GLubyte indices[]=  {
    0,1,5,0,4,5, // back
    3,2,6,7,6,3, // front
    0,1,2,3,2,0, // top
    4,5,6,7,6,4, // bottom
    0,3,4,4,7,3,
    1,5,2,2,6,5
  };

  GLfloat vertices[] = {-0.5,0.5,-0.5,
                        0.5,0.5,-0.5,
                        0.5,0.5,0.5,
                        -0.5,0.5,0.5,
                        -0.5,-0.5,-0.5,
                        0.5,-0.5,-0.5,
                        0.5,-0.5,0.5,
                        -0.5,-0.5,0.5
                       };
  GLfloat normals[] = {1,0,0.5,
                       1,0,0.5,
                       1,0,0.5,
                       1,0,0.5,
                       1,0,1,
                       1,0,1,
                       1,0,1,
                       1,0,1
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

    boxData.push_back(d);
  }


  //call top generate the mesh bounding box

  generateLsBBox(boxData);

  Renderer *render = Renderer::instance();

  render->createVAO(m_IDStr, GL_TRIANGLES);

  render->setIndexedDataToVAO(
        m_IDStr,
        sizeof(Renderer::vertData)*boxData.size(),
        3,
        boxData[0].x,
        sizeof(indices),
        &indices[0],
        sizeof(indices)/sizeof(GLubyte)
        );
}

//-------------------------------------------------------------------//

//void TestTurret::draw()
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

//void TestTurret::drawSelection()
//{
//  Renderer *r = Renderer::instance();
//  //m_transformStack.setScale(0.5, 0.5, 0.5);
//  r->loadMatrixToShader(m_transformStack, "Colour");

//  r->drawSelection(m_ID, m_IDStr);
//}

//-------------------------------------------------------------------//

ngl::Vec3 TestTurret::brain()
{
  // do something
  // return test aim
  m_stateMachine->update();
  return m_aim;
}

//-------------------------------------------------------------------//

void TestTurret::filterViewVolume(EntityRecordList &o_localEntities)
{
  Q_UNUSED(o_localEntities);
}

//-------------------------------------------------------------------//

void TestTurret::updateShotPos()
{
  // currently just seting the position to the position of the turret

  m_shotPos = m_pos;
}

//-------------------------------------------------------------------//

void TestTurret::generateViewBBox()
{
  // initialise world space view box
  m_wsViewBBox = BBox(
        m_lsMeshBBox.m_minX*10 + m_pos.m_x,
        m_lsMeshBBox.m_minY*10 + m_pos.m_y,
        m_lsMeshBBox.m_minZ*10 + m_pos.m_z,
        m_lsMeshBBox.m_maxX*10 + m_pos.m_x,
        m_lsMeshBBox.m_maxY*10 + m_pos.m_y,
        m_lsMeshBBox.m_maxZ*10 + m_pos.m_z
        );
}
//-------------------------------------------------------------------//
