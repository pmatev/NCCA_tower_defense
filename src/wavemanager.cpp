#include "wavemanager.h"

//-------------------------------------------------------------------//

WaveManager::WaveManager():
  m_wave(Wave::create(Wave::EnemyPairList()))
{
  // TEST CREATES DEFAULT WAVE
}

//-------------------------------------------------------------------//

WaveManagerPtr WaveManager::create()
{
  WaveManagerPtr a(new WaveManager());
  return a;
}

WaveManager::~WaveManager()
{
  // dtor
}

//-------------------------------------------------------------------//
void WaveManager::update(const double _dt)
{
  m_wave->update(_dt);
}

//-------------------------------------------------------------------//
void WaveManager::publish()
{
  m_wave->publish();
}

//-------------------------------------------------------------------//
void WaveManager::draw()
{
  m_wave->draw();
}

void WaveManager::drawSelection()
{
  m_wave->drawSelection();
}

//-------------------------------------------------------------------//

bool WaveManager::generatePaths(NodePtr _node)
{
  return m_wave->generatePaths(_node);
}

//-------------------------------------------------------------------//

std::list<Collision> WaveManager::checkCollisions() const
{
  return m_wave->checkCollisions();
}
