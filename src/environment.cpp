#include "environment.h"
#include "entityfactory.h"
#include "game.h"

//-------------------------------------------------------------------//

Environment::Environment(
    int _gridWidth,
    int _gridHeight,
    int _hexagonSize,
    ngl::Vec3 _origin,
    int _baseX,
    int _baseY):
  m_nodeMap(NodeManager::create(
              _gridWidth,
              _gridHeight,
              _hexagonSize,
              _origin))
{
  // default ctor
  // base needs to be initialised here as it fails when putting it in the
  // inititalisation list
  m_base = Base::create(m_nodeMap->getNodeFromCoords(_baseX, _baseY));
}

//-------------------------------------------------------------------//

EnvironmentPtr Environment::create(
    int _gridWidth,
    int _gridHeight,
    int _hexagonSize,
    ngl::Vec3 _origin,
    int _baseX,
    int _baseY)
{
  EnvironmentPtr a(new Environment(
                     _gridWidth,
                     _gridHeight,
                     _hexagonSize,
                     _origin,
                     _baseX,
                     _baseY));
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
      StaticEntityList::iterator it = m_towers.begin();
      it != m_towers.end();
      ++it
      )
  {
    (*it)->update();
  }
  // update base
  m_base->update();
  m_nodeMap->update();
}

//-------------------------------------------------------------------//

void Environment::publish()
{
  // Go through all the towers and draw
  for(
      StaticEntityList::iterator it = m_towers.begin();
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
      StaticEntityList::const_iterator it = m_towers.begin();
      it != m_towers.end();
      ++it
      )
  {
      (*it)->draw();
  }
  // draw base
  m_base->draw();
  m_nodeMap->draw();
}

//-------------------------------------------------------------------//

void Environment::drawSelection() const
{
  // Go through all the towers and draw
  for(
      StaticEntityList::const_iterator it = m_towers.begin();
      it != m_towers.end();
      ++it
      )
  {
    (*it)->drawSelection();
  }
  // draw base
  m_base->drawSelection();
  m_nodeMap->drawSelection();
}

//-------------------------------------------------------------------//

void Environment::createTower(
    const std::string &_type,
    NodePtr _centerNode
    )
{
  // Create the new tower
  m_towers.push_back(EntityFactory::createStaticEntity(
                     _type,
                     _centerNode
                     ));
}

//-------------------------------------------------------------------//


ngl::Vec3 Environment::getBasePos()
{
  return m_base->getPos();
}

//-------------------------------------------------------------------//

NodeManagerWeakPtr Environment::getNodeManagerWeakPtr()
{
  NodeManagerWeakPtr a(m_nodeMap);
  return a;
}
