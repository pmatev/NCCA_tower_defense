#include "wavemanager.h"
#include <boost/foreach.hpp>

//-------------------------------------------------------------------//

WaveManager::WaveManager(
    Node::NodeWVecWPtr _spawnNodes,
    const WaveInfoList &_waveInfo
    )
{
  // go through _waveInfo and construct waves accordingly
  BOOST_FOREACH(WaveInfoPtr waveInfo, _waveInfo)
  {
    m_waves.push_back(
          Wave::create(
            *waveInfo,
            _spawnNodes
            )
          );
  }
  m_currentWaveIt = m_waves.end();
}

//-------------------------------------------------------------------//

WaveManagerPtr WaveManager::create(
    Node::NodeWVecWPtr _spawnNodes,
    const WaveInfoList &_waveInfo
    )
{
  WaveManagerPtr a(new WaveManager(_spawnNodes, _waveInfo));
  return a;
}

//-------------------------------------------------------------------//

WaveManager::~WaveManager()
{
  // dtor
}

//-------------------------------------------------------------------//
void WaveManager::update(const double _dt)
{
  if(m_currentWaveIt != m_waves.end())
  {
    (*m_currentWaveIt)->update(_dt);
    // If the current wave is dead go to the next wave
    if((*m_currentWaveIt)->isDead())
    {
      ++m_currentWaveIt;
    }
  }
}

//-------------------------------------------------------------------//
void WaveManager::publish()
{
  if(m_currentWaveIt != m_waves.end())
  {
    (*m_currentWaveIt)->publish();
  }
}

//-------------------------------------------------------------------//
void WaveManager::draw()
{
  if(m_currentWaveIt != m_waves.end())
  {
    (*m_currentWaveIt)->draw();
  }
}

//-------------------------------------------------------------------//

bool WaveManager::generatePaths(NodeWPtr _node)
{
  if(m_currentWaveIt != m_waves.end())
  {
    return (*m_currentWaveIt)->generatePaths(_node);
  }
  else
  {
    return true;
  }
}

//-------------------------------------------------------------------//

std::list<Collision> WaveManager::checkCollisions() const
{
  if(m_currentWaveIt != m_waves.end())
  {
    return (*m_currentWaveIt)->checkCollisions();
  }
  else
  {
    return std::list<Collision>();
  }
}

//-------------------------------------------------------------------//

void WaveManager::startWaves()
{

  m_currentWaveIt = m_waves.begin();
}
