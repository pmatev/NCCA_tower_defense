#include "turret.h"
#include "game.h"

//-------------------------------------------------------------------//

Turret::Turret(
    NodePtr _linkedNode,
    unsigned int _id,
    std::string _projectileType
    ):
  StaticEntity(_linkedNode, TURRET,_id),
  m_fov(360),
  m_viewDistance(20),
  m_maxRotationSpeed(20),
  m_aim(ngl::Vec3(0.01, 0, 0)),
  m_projectileType(_projectileType)
{
  //variables initialised before constructor body called
}


//-------------------------------------------------------------------//

Turret::~Turret()
{
  //currently using default destructor
}

//-------------------------------------------------------------------//

void Turret::update(const double _dt)
{
  //Q unused to remove warnings, will be replaced if used

  Q_UNUSED(_dt);

  // TEST
  // just do whatever the brain says
  m_aim = brain();
  //fire();
}

//-------------------------------------------------------------------//

void Turret::fire()
{
  //get a pointer to the game

  Game * game = Game::instance();

  //get a weak pointer to the projectile manager

  ProjectileManagerPtr pm = game->getProjectileManagerWeakPtr().lock();
  if(pm)
  {
    //add a projectile, at the moment starts it at the centre of the turret
    //might need to add some way of setting where the end of the turret's
    //barrel is
    pm->addProjectile(m_projectileType,m_pos,m_aim);
  }
}
