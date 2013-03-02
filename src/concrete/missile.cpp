#include "include/concrete/missile.h"
#include "include/fsm/states/projectilestates.h"
#include "ngl/ShaderLib.h"
#include "projectilemanager.h"
//-------------------------------------------------------------------//

Missile::Missile(
    const ngl::Vec3 &_pos,
    const ngl::Vec3 &_aim,
    unsigned int _id
    ):
  Projectile(_pos, _aim, _id)
{
  m_damage =50;
  m_maxVelocity = 10;
  m_velocity = m_aimVector;

  initialiseMesh("bullet");
  publish();
}

//-------------------------------------------------------------------//

EntityPtr Missile::create(
    const ngl::Vec3 &_pos,
    const ngl::Vec3 &_aim,
    unsigned int _id
    )
{
  EntityPtr missile(new Missile(_pos,_aim, _id));
  missile->stateInit();
  return missile;
}

//-------------------------------------------------------------------//

void Missile::stateInit()
{
  //state machine
  m_stateMachine = new StateMachine(EntityWPtr(shared_from_this()));
  m_stateMachine->setCurrentState(Move::instance());
  m_stateMachine->setPreviousState(Move::instance());
  m_stateMachine->setGlobalState(0);
}

//-------------------------------------------------------------------//

void Missile::draw()
{
  Renderer *r = Renderer::instance();

  ngl::ShaderLib *shader = ngl::ShaderLib::instance();

  (*shader)["Constant"]->use();
  r->loadMatrixToShader(m_transformStack.getCurrentTransform().getMatrix(), "Constant");

  shader->setShaderParam4f("colour", 1,0,0,1);

  r->draw("bullet", "Constant");
}

//-------------------------------------------------------------------//

ngl::Vec3 Missile::brain()
{
  // for the moment just have the bullet follow it's aim

  return ngl::Vec3();

  //return m_aimVector;
}

//-------------------------------------------------------------------//

void Missile::filterViewVolume(EntityRecordWCList &o_localEntities)
{
  Q_UNUSED(o_localEntities);
}


Missile::~Missile()
{
  if(m_parent)
  {
    m_parent->addExplosion(1000, 10, 2, m_pos);
  }
}
