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
    2.0 // max distance from nearest path node
    )

{
  initialiseMesh("enemy");
  publish();
  m_damage = 5;
  m_velocity = 0;
  m_maxSpeed = 2.0;
  m_maxAccn = 20;
  m_mass = 0.1;
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
  m_stateMachine->setCurrentState(TestEnemyNormal::instance());
  m_stateMachine->setPreviousState(TestEnemyNormal::instance());
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
  return steeringDirection;
}

//-------------------------------------------------------------------//


void TestEnemy::filterViewVolume(EntityRecordWCList &o_localEntities)
{
  Q_UNUSED(o_localEntities);
}

//-------------------------------------------------------------------//

void TestEnemy::draw()
{
  Renderer *r = Renderer::instance();
  TextureLib *tex = TextureLib::instance();
  ngl::ShaderLib *shader = ngl::ShaderLib::instance();

  (*shader)["TexturedConst"]->use();
  r->loadMatrixToShader(m_transformStack.getCurrentTransform().getMatrix(), "TexturedConst");

  tex->bindTexture("enemy_AO");
  shader->setShaderParam4f("colourSelect", 0, 0, 0, 0);

  r->draw("enemy", "TexturedConst");

  // draw healthbar
  (*shader)["TexturedConst"]->use();
  m_healthBar->setUVScale(50/m_health,1);
  tex->bindTexture("healthbar");
  m_healthBar->draw("TexturedConst");
}

