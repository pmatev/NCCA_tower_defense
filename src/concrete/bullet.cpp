#include "concrete/bullet.h"
#include"include/fsm/states/projectilestates.h"
#include "projectilemanager.h"
#include "ngl/ShaderLib.h"

//-------------------------------------------------------------------//

Bullet::Bullet(
    const ngl::Vec3 &_pos,
    const ngl::Vec3 &_aim,
    unsigned int _id
    ) :
  Projectile(_pos,_aim, _id)
{
  m_damage =10;
  m_maxSpeed = 10;
  m_velocity = m_aimVector;

  initialiseMesh("bullet");
  publish();
}

//-------------------------------------------------------------------//

Bullet::~Bullet()
{
  //currently using default destructor
}

//-------------------------------------------------------------------//

EntityPtr Bullet::create(
    const ngl::Vec3 &_pos,
    const ngl::Vec3 &_aim,
    unsigned int _id
    )
{
  //create and return a smart pointer to the bullet

  EntityPtr bullet(new Bullet(_pos,_aim, _id));
  bullet->stateInit();
  return bullet;
}

//-------------------------------------------------------------------//

void Bullet::stateInit()
{
  //state machine
  m_stateMachine = new StateMachine(EntityWPtr(shared_from_this()));
  m_stateMachine->setCurrentState(Move::instance());
  m_stateMachine->setPreviousState(Move::instance());
  m_stateMachine->setGlobalState(0);
}

//-------------------------------------------------------------------//

void Bullet::draw()
{
  Renderer *r = Renderer::instance();

  ngl::ShaderLib *shader = ngl::ShaderLib::instance();

  (*shader)["Constant"]->use();
  r->loadMatrixToShader(m_transformStack.getCurrentTransform().getMatrix(),
                        "Constant"
                        );

  shader->setShaderParam4f("colour", 1,0.1,0,1);
  shader->setShaderParam1f("textured",0);

  r->draw("bullet", "Constant");
}

//-------------------------------------------------------------------//

ngl::Vec3 Bullet::brain()
{
  // return empty vector

  return ngl::Vec3();
}

//-------------------------------------------------------------------//

void Bullet::filterViewVolume(EntityRecordWCList &o_localEntities)
{
  Q_UNUSED(o_localEntities);
}

//-------------------------------------------------------------------//


