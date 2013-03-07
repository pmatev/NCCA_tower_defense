#include "include/concrete/missilesilo.h"
#include "renderer.h"
#include <ngl/ShaderLib.h>
#include <boost/foreach.hpp>
#include "window.h"
#include "fsm/states/missilesilostate.h"
#include "projectilemanager.h"
#include "game.h"
#include "concrete/grenade.h"

//-------------------------------------------------------------------//

MissileSilo::MissileSilo(
    NodePtr _linkedNode,
    unsigned int _id
    ): Turret(
    _linkedNode,
    _id,
    std::string("Grenade"),
    20,
    15
    ),
  m_gravity(-9.81),
  m_hasTarget(false)
{
  m_shotPos = ngl::Vec3(m_pos.m_x,
                        m_pos.m_y + 0.75,
                        m_pos.m_z);
  initialiseMesh("turret_base");
  publish();
}

//-------------------------------------------------------------------//

EntityPtr MissileSilo::create(NodePtr _linkedNode, unsigned int _id)
{
  EntityPtr a(
        new MissileSilo(
          _linkedNode,
          _id
          )
        );
  a->stateInit();
  return a;
}

//-------------------------------------------------------------------//

void MissileSilo::stateInit()
{
  m_stateMachine = new StateMachine(EntityWPtr(shared_from_this()));
  m_stateMachine->setCurrentState(MissileSiloBasicUpgrade::instance());
  m_stateMachine->setPreviousState(MissileSiloSeek::instance());

  registerUpgrade(
        MissileSiloBasicUpgrade::instance(),
        UpgradeData::create(
          "Basic Upgrade",
          "descriptiony thing",
          std::string("test.jpg"),
          0
          )
        );
  registerUpgrade(
        MissileSiloAdvancedUpgrade::instance(),
        UpgradeData::create(
          "Advanced Upgrade",
          "does something awesome",
          std::string("otherTest.jpg"),
          100
          )
        );
}

//-------------------------------------------------------------------//

ngl::Vec3 MissileSilo::brain()
{
  // do something
  // return test aim
  m_stateMachine->update();
  return m_desiredAim;
}

//-------------------------------------------------------------------//

void MissileSilo::filterViewVolume(EntityRecordWCList &o_localEntities)
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

void MissileSilo::calculateTarget()
{
  // Adjust the view size
  float viewSize = 10;
  m_wsViewBBox = BBox(
        m_pos[0] - viewSize,
        m_pos[1] - viewSize,
        m_pos[2] - viewSize,
        m_pos[0] + viewSize,
        m_pos[1] + viewSize,
        m_pos[2] + viewSize
        );
  EntityRecordWCList localEntities;
  std::list<GeneralType> types;
  types.push_back(ENEMY);
  calculateLocalEntities(localEntities, types);

  // Go through localEntities and find the best place to target

  if(localEntities.size() == 0)
  {
    m_hasTarget = false;
    return;
  }
  // to start with just find the average position
  ngl::Vec3 averagePos;
  int numEntities = 0;
  BOOST_FOREACH(EntityRecordWCPtr recordWeak, localEntities)
  {
    EntityRecordCPtr record = recordWeak.lock();
    if(record)
    {
      averagePos += ngl::Vec3(record->m_x,record->m_y, record->m_z);
      ++numEntities;
    }
  }
  if(numEntities != 0)
  {
    averagePos /= numEntities;
  }
  m_hasTarget = true;
  m_targetPos = averagePos;
  return ;
}

//-------------------------------------------------------------------//

ngl::Vec3 MissileSilo::aim(const ngl::Vec3 &_target, float _horizontalSpeed)
{
  // Make sure to adjust the aimVector so that we hit the target
  ngl::Vec3 relVec =  _target - m_shotPos;
  // Find the different in height
  float heightDiff =  relVec[1];
  relVec[1] = 0;

  ngl::Vec3 vX;
  float len = relVec.length();
  if(len)
  {
    vX = (relVec / len) * _horizontalSpeed;
  }
  // velocity in x

  float timeToHit = len / _horizontalSpeed;

  // velocity in y
  ngl::Vec3 vY(
        0,
        (heightDiff - (m_gravity/2.0)*timeToHit*timeToHit) / timeToHit,
        0
        );

  return vX + vY;
}

//-------------------------------------------------------------------//

void MissileSilo::fire()
{

  Game * game = Game::instance();

  //get a weak pointer to the projectile manager

  ProjectileManagerPtr pm = game->getProjectileManagerWeakPtr().lock();
  if(pm)
  {
    float horizontalSpeed = 5; // THIS NEEDS TO BE PROPERLY INSTANTIATED -----------------------------------
    calculateTarget();
    ngl::Vec3 velocity = aim(m_targetPos, horizontalSpeed);

    //add a projectile, at the moment starts it at the centre of the turret
    //might need to add some way of setting where the end of the turret's
    //barrel is
    ProjectilePtr newProjectile = pm->addProjectile(
          m_projectileType,
          m_shotPos,
          velocity,
          m_ID
          ).lock();

    if(newProjectile)
    {
      GrenadePtr grenade = boost::dynamic_pointer_cast<Grenade>(newProjectile);
      if(grenade)
      {
        grenade->setGravity(m_gravity);
      }
    }
    //then set the doFire and time since last shot values back to their default
    // values

    m_doShot = false;

    m_dtSinceLastShot = 0;
  }
}

//-------------------------------------------------------------------//

void MissileSilo::updateShotPos()
{
  // currently just seting the position to the position of the turret

  m_shotPos = m_pos;
}

//-------------------------------------------------------------------//

void MissileSilo::generateViewBBox()
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

void MissileSilo::draw()
{
  Renderer *r = Renderer::instance();

  ngl::ShaderLib *shader = ngl::ShaderLib::instance();

  //Draw the turret base
  m_transformStack.pushTransform();
  m_transformStack.setPosition(m_pos);

  (*shader)["Constant"]->use();
  r->loadMatrixToShader(m_transformStack.getCurrentTransform().getMatrix(), "Constant");
  ngl::Vec3 c = Window::instance()->IDToColour(m_ID);
  c = c/255.0f;

  shader->setShaderParam4f("colour", 0.1, 0.1, 0.8, 1);
  shader->setShaderParam4f("colourSelect", c[0], c[1], c[2], 1);


  r->draw("turret_base", "Constant");
  m_transformStack.popTransform();

  // Test code to render the targets for each grenade -------------------------------------

  ngl::Mat4 testMat;
  testMat.translate(m_targetPos.m_x, m_targetPos.m_y, m_targetPos.m_z);
  r->loadMatrixToShader(testMat, "Constant");
  shader->setShaderParam4f("colour", 1,1,1,1);
  r->draw("bullet", "Constant");
}
