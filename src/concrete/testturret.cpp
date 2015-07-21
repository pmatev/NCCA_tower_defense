#include <math.h>

#include "include/concrete/testturret.h"
#include "include/fsm/states/turretstates.h"
#include "projectilemanager.h"
#include "renderer.h"
#include "include/concrete/grenade.h"
#include "game.h"
#include "texturelib.h"
#include "window.h"
#include "ngl/ShaderLib.h"

//-------------------------------------------------------------------//
TestTurret::TestTurret(
    NodePtr _linkedNode,
    unsigned int _id
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
                        m_pos.m_y + 0.75,
                        m_pos.m_z);

  initialiseMesh("turret_base");
  publish();
  m_sellValue = 50;
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
  m_stateMachine->setCurrentState(TestTurretBasicUpgrade::instance());
  m_stateMachine->setPreviousState(Seek::instance());

  registerUpgrade(
        TestTurretBasicUpgrade::instance(),
        UpgradeData::create(
          "Initial Upgrade",
          "descriptiony thing",
          std::string("sellBulletImage"),
          0,
          m_sellValue
          )
        );
  registerUpgrade(
        TestTurretAdvancedUpgrade::instance(),
        UpgradeData::create(
          "Super Advanced Upgrade",
          "makes bullets shoot faster",
          std::string("upgrade2BulletImage"),
          100,
          100
          )
        );
}

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
  // filter by square distance
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

        float sqrDist =
            pow(strongRecord->m_x - m_pos.m_x, 2)+
            pow(strongRecord->m_y - m_pos.m_y, 2)+
            pow(strongRecord->m_z - m_pos.m_z, 2);

        if (sqrDist > m_viewDistance*m_viewDistance)
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
  TextureLib *tex = TextureLib::instance();
  ngl::ShaderLib *shader = ngl::ShaderLib::instance();

  //Draw the turret base
  (*shader)["Constant"]->use();

  m_transformStack.pushTransform();
  m_transformStack.setPosition(m_pos);

  ngl::Vec4 colour = ngl::Vec4(0.95,0.95,1.0,1);
  if(m_upgradeIndex == 1)
  {
      colour = ngl::Vec4(0.6,0.7,1,1);
  }

  r->loadMatrixToShader(m_transformStack.getCurrentTransform().getMatrix(), "Constant");
  ngl::Vec3 c = Window::instance()->IDToColour(m_ID);
  c = c/255.0f;

  shader->setShaderParam4f("colour", colour[0], colour[1], colour[2], colour[3]);
  shader->setShaderParam1f("textured",1);
  if(m_highlighted == 1)
  {
      shader->setShaderParam4f("highlightColour", 0.737,0.835,0.925,1);
  }
  shader->setShaderParam4f("colourSelect", c[0], c[1], c[2], 1);

  tex->bindTexture("turret_base");
  r->draw("turret_base", "Constant");
  m_transformStack.popTransform();

  //Draw the cannon
  m_transformStack.pushTransform();
  m_transformStack.setPosition(m_shotPos);
  //Get the rotation based on the aim vector
  float turret_y_rotation = (atan2(m_aim[0], m_aim[2])) * (180 / 3.14159263);
  //float turret_xz_rotation = (atan2(m_aim[1], m_aim[0])) * (180 / 3.14159263);
  m_transformStack.setRotation(ngl::Vec3(0, turret_y_rotation, 0));
  r->loadMatrixToShader(m_transformStack.getCurrentTransform().getMatrix(), "Constant");

  tex->bindTexture("turret_cannon");
  r->draw("turret_cannon", "Constant");

  m_transformStack.popTransform();
  shader->setShaderParam4f("highlightColour", 1,1,1,1);
}
