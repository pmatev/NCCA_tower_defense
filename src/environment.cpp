#include "environment.h"

//-------------------------------------------------------------------//

Environment::Environment():
  m_nodeMap(NodeManager::create())
{
  // default ctor

}

//-------------------------------------------------------------------//

EnvironmentPtr Environment::create()
{
  EnvironmentPtr a(new Environment());
  return a;
}

//-------------------------------------------------------------------//

Environment::~Environment()
{
  //default dtor
}

//-------------------------------------------------------------------//

void Environment::update()
{
  // Go through all the towers and draw
  for(
      TowerList::iterator it = m_towers.begin();
      it != m_towers.end();
      ++it
      )
  {
    (*it)->update();
  }
  // update base
  m_base->update();
}

//-------------------------------------------------------------------//

void Environment::publish()
{
  // Go through all the towers and draw
  for(
      TowerList::iterator it = m_towers.begin();
      it != m_towers.end();
      ++it
      )
  {
    (*it)->publish();
  }
  // publish base details
  m_base->publish();
}

//-------------------------------------------------------------------//

void Environment::draw() const
{
  // Go through all the towers and draw
  for(
      TowerList::const_iterator it = m_towers.begin();
      it != m_towers.end();
      ++it
      )
  {
    (*it)->draw();
  }
  // draw base
  m_base->draw();
}

//-------------------------------------------------------------------//

void Environment::drawSelection() const
{
  // Go through all the towers and draw
  for(
      TowerList::const_iterator it = m_towers.begin();
      it != m_towers.end();
      ++it
      )
  {
    (*it)->drawSelection();
  }
  // draw base
  m_base->drawSelection();
}

//-------------------------------------------------------------------//
