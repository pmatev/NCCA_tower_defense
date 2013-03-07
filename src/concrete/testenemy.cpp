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
  initialiseMesh("enemy");
  publish();
  //  m_active = false;

  m_damage = 5;
  m_velocity = 0;
  m_maxVelocity = 2.0;
  m_maxAccn = 20;
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

ngl::Vec3 TestEnemy::brain()
{
  ngl::Vec3 steeringDirection = m_steering->calculate();
  // TEST value (tells it to just go forward)
  //return getPathVec() * 0.01;
  return steeringDirection;
}

//-------------------------------------------------------------------//


void TestEnemy::filterViewVolume(EntityRecordWCList &o_localEntities)
{
  Q_UNUSED(o_localEntities);
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

