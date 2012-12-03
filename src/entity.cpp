#include "entity.h"

#include "game.h"

//-------------------------------------------------------------------//

Entity::Entity(const ngl::Vec3 & _pos):
  m_pos(_pos),
  m_health(100.0)
{
  // Initialise id and register with game
  Game* game = Game::instance();
  // register instance with Game
  m_ID = game->registerID(EntityPtr(this));
}

//-------------------------------------------------------------------//

Entity::~Entity()
{
  //currently using default destructor
}

//-------------------------------------------------------------------//

void Entity::publish()
{
  //yet to be implemented
}

//-------------------------------------------------------------------//
