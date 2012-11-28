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
  //-------------------------------------------------------------------//

  static WaveManagerPtr create();

  //-------------------------------------------------------------------//
  /// @brief the destructor
  //-------------------------------------------------------------------//

  ~WaveManager();

  //-------------------------------------------------------------------//
  /// @brief update everything
  //-------------------------------------------------------------------//

  void update();

  //-------------------------------------------------------------------//
  /// @brief publish everything
  //-------------------------------------------------------------------//

  void publish();

  //-------------------------------------------------------------------//
  /// @brief draw everything
  //-------------------------------------------------------------------//

  void draw() const;

protected:
  //-------------------------------------------------------------------//
  /// @brief ctor
  //-------------------------------------------------------------------//

  WaveManager();

protected:

  //-------------------------------------------------------------------//
  /// @brief current wave
  //-------------------------------------------------------------------//

  WavePtr m_wave;
};



#endif // WAVEMANAGER_H
