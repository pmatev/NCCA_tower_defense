#include <boost/foreach.hpp>
#include "include/concrete/grenade.h"
#include "include/fsm/states/projectilestates.h"
#include "ngl/ShaderLib.h"
#include "projectilemanager.h"
//-------------------------------------------------------------------//

Grenade::Grenade(
    const ngl::Vec3 &_pos,
    const ngl::Vec3 &_aim,
    unsigned int _id
    ):
  Projectile(_pos, _aim, _id),
  m_gravity(-9.81),
  m_horizontalSpeed(5)
{
  m_damage =50;
  m_maxSpeed = 100;
  m_maxAccn = 100;
  m_velocity = m_aimVector;

  initialiseMesh("bullet");
  publish();
}

//-------------------------------------------------------------------//

EntityPtr Grenade::create(
    const ngl::Vec3 &_pos,
    const ngl::Vec3 &_aim,
    unsigned int _id
    )
{
  EntityPtr grenade(new Grenade(_pos,_aim, _id));
  grenade->stateInit();
  return grenade;
}

//-------------------------------------------------------------------//

void Grenade::stateInit()
{
  //state machine
  m_stateMachine = new StateMachine(EntityWPtr(shared_from_this()));
  m_stateMachine->setCurrentState(Move::instance());
  m_stateMachine->setPreviousState(Move::instance());
  m_stateMachine->setGlobalState(0);
}

//-------------------------------------------------------------------//

void Grenade::draw()
{
  Renderer *r = Renderer::instance();

  ngl::ShaderLib *shader = ngl::ShaderLib::instance();

  (*shader)["Constant"]->use();
  r->loadMatrixToShader(m_transformStack.getCurrentTransform().getMatrix(), "Constant");

  shader->setShaderParam4f("colour", 1,0,0,1);

  r->draw("bullet", "Constant");
}

//-------------------------------------------------------------------//

ngl::Vec3 Grenade::brain()
{
  // for the moment just have the bullet follow it's aim

  return ngl::Vec3(0, m_gravity, 0) * m_mass;
}

//-------------------------------------------------------------------//

void Grenade::filterViewVolume(EntityRecordWCList &o_localEntities)
{
  Q_UNUSED(o_localEntities);
}


Grenade::~Grenade()
{
  if(m_parent)
  {
    m_parent->addExplosion(100, 40, 3, m_pos, 0.5);
  }
}
