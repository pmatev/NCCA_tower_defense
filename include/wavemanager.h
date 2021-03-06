#ifndef WAVEMANAGER_H
#define WAVEMANAGER_H

#include "wave.h"

//-------------------------------------------------------------------//
/// @file wavemanager.h
/// @brief This class manages the creation of waves. It determines when
/// waves should be created. It holds all the data for creation of waves.
/// the wave manager should only have one wave at a time and manages the
/// time between waves
/// @author Jared Auty
/// @version 1
/// @date 27/11/12
/// Revision History :
/// Initial Version 27/11/12
/// @class WaveManager
//-------------------------------------------------------------------//

DECLARESMART(WaveManager)

class WaveManager
{
public:

  //-------------------------------------------------------------------//
  /// @brief the creator
  /// @param[in] _spawnNodes list of spawn nodes
  /// @param[in] _waveInfo list of wave information
  //-------------------------------------------------------------------//

  static WaveManagerPtr create(
        Node::NodeWVecWPtr _spawnNodes,
        const WaveInfoList &_waveInfo
        );

  //-------------------------------------------------------------------//
  /// @brief update everything
  /// @param [in] _dt the timestep
  //-------------------------------------------------------------------//

  void update(const double _dt);

  //-------------------------------------------------------------------//
  /// @brief publish everything
  //-------------------------------------------------------------------//

  void publish();

  //-------------------------------------------------------------------//
  /// @brief draw everything
  //-------------------------------------------------------------------//

  void draw();

  //-------------------------------------------------------------------//
  /// @brief create new temporary paths for all enemies that are affected
  /// by inserting this tower
  /// @param[in] _node, the node in question
  /// @return whether all the paths were successful or not
  //-------------------------------------------------------------------//

  bool generatePaths(NodeWPtr _node);

  //-------------------------------------------------------------------//
  /// @brief check for collisions with static objects
  /// @return list of Collisions with objects
  //-------------------------------------------------------------------//

  std::list<Damage> checkCollisions() const;

  //-------------------------------------------------------------------//
  /// @brief start creating waves
  //-------------------------------------------------------------------//
  void startWaves();

protected:
  //-------------------------------------------------------------------//
  /// @brief ctor
  /// @param[in] _spawnNodes list of spawn nodes
  /// @param[in] _waveInfo list of wave information
  //-------------------------------------------------------------------//

  WaveManager(Node::NodeWVecWPtr _spawnNodes, const WaveInfoList &_waveInfo);

protected:

  //-------------------------------------------------------------------//
  /// @brief current wave
  //-------------------------------------------------------------------//

  WaveList::iterator m_currentWaveIt;

  //-------------------------------------------------------------------//
  /// @brief all waves
  //-------------------------------------------------------------------//

  WaveList m_waves;

};



#endif // WAVEMANAGER_H
