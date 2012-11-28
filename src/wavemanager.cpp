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
void WaveManager::update()
{
  m_wave->update();
}

//-------------------------------------------------------------------//
void WaveManager::publish()
{
  m_wave->publish();
}

//-------------------------------------------------------------------//
void WaveManager::draw() const
{
  m_wave->draw();
}
