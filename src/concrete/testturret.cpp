#include <math.h>

#include "include/concrete/testturret.h"
#include "include/fsm/states/turretstates.h"
#include "renderer.h"

#include "window.h"
#include "ngl/ShaderLib.h"

//-------------------------------------------------------------------//
TestTurret::TestTurret(
    NodePtr _linkedNode,
    unsigned int &_id
    ):
  Turret(
    _linkedNode,
    _id,
    std::string("Bullet"),
    20,
    15
    )
{
  m_fov = 360;
  m_viewDistance = 10;
  setRotationAngle(0.5);
  m_shotPos = ngl::Vec3(m_pos.m_x,
                        m_pos.m_y + 1.3,
                        m_pos.m_z);
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
  a->stateInit();

  return a;
}

//-------------------------------------------------------------------//

void TestTurret::stateInit()
{
  m_stateMachine = new StateMachine(EntityWPtr(shared_from_this()));
  m_stateMachine->setCurrentState(BasicUpgrade::instance());
  m_stateMachine->setPreviousState(Seek::instance());

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
  return m_desiredAim;
}

//-------------------------------------------------------------------//

void TestTurret::filterViewVolume(EntityRecordWCList &o_localEntities)
{
  if(o_localEntities.size()!= 0)
  {
    //generate an iterator to cycle through the list

    EntityRecordWCList::iterator listIt = o_localEntities.begin();

    while (listIt != o_localEntities.end())
    {
      EntityRecordCPtr strongRecord = listIt->lock();
      if(strongRecord)
      {
        //check if the square dist is greater than the view distance
        // squared

        float sqDist =
            pow(strongRecord->m_x - m_pos.m_x, 2)+
            pow(strongRecord->m_y - m_pos.m_y, 2)+
            pow(strongRecord->m_z - m_pos.m_z, 2);

        if (sqDist > m_viewDistance*m_viewDistance)
        {
          //if it is bigger, remove it from the local entities

          listIt = o_localEntities.erase(listIt);
        }
        else
        {
          //increment the local entities list

          listIt++;
        }
      }
    }
  }
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
        m_lsMeshBBox.m_minX*m_viewDistance + m_pos.m_x,
        m_lsMeshBBox.m_minY*m_viewDistance + m_pos.m_y,
        m_lsMeshBBox.m_minZ*m_viewDistance + m_pos.m_z,
        m_lsMeshBBox.m_maxX*m_viewDistance + m_pos.m_x,
        m_lsMeshBBox.m_maxY*m_viewDistance + m_pos.m_y,
        m_lsMeshBBox.m_maxZ*m_viewDistance + m_pos.m_z
        );
}

//-------------------------------------------------------------------//

void TestTurret::draw()
{
  Renderer *r = Renderer::instance();

  ngl::ShaderLib *shader = ngl::ShaderLib::instance();

  m_transformStack.pushTransform();
  m_transformStack.setPosition(m_pos);
  r->loadMatrixToShader(m_transformStack.getCurrentTransform().getMatrix(), "Phong");
  std::cout << m_aim << std::endl;
  (*shader)["Phong"]->use();
  ngl::Vec3 c = Window::instance()->IDToColour(m_ID);
  c = c/255.0f;

  shader->setShaderParam4f("colourSelect", c[0], c[1], c[2], 1);

  shader->setShaderParam4f("colour", 0.1, 0.1, 0.8, 1);

  r->draw("turret_base", "Phong");
  m_transformStack.popTransform();

  m_transformStack.pushTransform();
  m_transformStack.setPosition(m_shotPos);
  m_transformStack.setRotation(ngl::Vec3(0, (atan(m_aim[0] / m_aim[2])) * (180 / 3.14159263), 0));
  r->loadMatrixToShader(m_transformStack.getCurrentTransform().getMatrix(), "Phong");
  (*shader)["Phong"]->use();

  shader->setShaderParam4f("colourSelect", c[0], c[1], c[2], 1);

  shader->setShaderParam4f("colour", 0.1, 0.1, 0.8, 1);

  r->draw("turret_cannon", "Phong");
  m_transformStack.popTransform();
}
