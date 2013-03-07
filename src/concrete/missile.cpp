#include <boost/foreach.hpp>
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
  Projectile(_pos, _aim, _id),
  m_gravity(-9.81),
  m_horizontalSpeed(5)
{
  m_damage =50;
  m_maxVelocity = 100;
  m_maxAccn = 100;
  m_velocity = m_aimVector;

  initialiseMesh("bullet");
  publish();
}

//-------------------------------------------------------------------//

void Missile::setVelocity(const ngl::Vec3 _velocity)
{
  Q_UNUSED(_velocity);
  calculateTarget();
  aim();
}

//-------------------------------------------------------------------//

void Missile::calculateTarget()
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
  m_targetPos = averagePos;
  std::cout<<"Found target "<<m_targetPos<<std::endl;
}

//-------------------------------------------------------------------//

void Missile::aim()
{
  // this presumes that the start and target are on the same plane ------------------------

  // Make sure to adjust the aimVector so that we hit the target
  ngl::Vec3 relVec =  m_targetPos - m_pos;
  // Find the different in height
  float heightDiff =  relVec[1];
  relVec[1] = 0;

  ngl::Vec3 vX;
  float len = relVec.length();
  if(len)
  {
    vX = (relVec / len) * m_horizontalSpeed;
  }
  // velocity in x

  float timeToHit = len / m_horizontalSpeed;

  // velocity in y
  ngl::Vec3 vY(
        0,
        (heightDiff - (m_gravity/2.0)*timeToHit*timeToHit) / timeToHit,
        0
        );

  m_velocity = vX + vY;
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

  // Test code to render the targets for each missile -------------------------------------

  ngl::Mat4 testMat;
  testMat.translate(m_targetPos.m_x, m_targetPos.m_y, m_targetPos.m_z);
  r->loadMatrixToShader(testMat, "Constant");
  shader->setShaderParam4f("colour", 1,1,1,1);
  r->draw("bullet", "Constant");
}

//-------------------------------------------------------------------//

ngl::Vec3 Missile::brain()
{
  // for the moment just have the bullet follow it's aim

  return ngl::Vec3(0, m_gravity, 0) * m_mass;

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
    m_parent->addExplosion(100, 10, 5, m_pos);
  }
}
