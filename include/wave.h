#ifndef WAVE_H
#define WAVE_H

#include <boost/shared_ptr.hpp>

#include "dynamicentity.h"
#include "entityfactory.h"

//-------------------------------------------------------------------//
/// @file wave.h
/// @brief This class is responsible for managing all the enemies within
/// a specific wave. A wave is defined by a period of time when a specific
/// set of enemies is created. The wave acts like a commander and may in
/// the future contain AI to control creation of enemies.
/// @author Jared Auty
/// @version 1
/// @date 27/11/12
/// Revision History :
/// Initial Version 27/11/12
/// @class Wave
//-------------------------------------------------------------------//

class Wave;

//-------------------------------------------------------------------//
/// @brief typedef for shared pointer to Wave
//-------------------------------------------------------------------//

typedef boost::shared_ptr<Wave> WavePtr;

class Wave
{
public:
  //-------------------------------------------------------------------//
  /// @struct pair for storing the number and type of a specific enemy
  /// this will be used when creating lists of available enemies for passing
  /// into the wave
  //-------------------------------------------------------------------//

  struct EnemyPair
  {
    //-------------------------------------------------------------------//
    /// @brief the number of enemies of specific type
    //-------------------------------------------------------------------//

    int m_count;

    //-------------------------------------------------------------------//
    /// @brief the specific enemy type
    //-------------------------------------------------------------------//
    EntityType m_type;
  };

  //-------------------------------------------------------------------//
  /// @brief typedef for lists of EnemyPairs
  //-------------------------------------------------------------------//

  typedef std::list<EnemyPair> EnemyPairList;

public:

  //-------------------------------------------------------------------//
  /// @brief creator
  /// @param[in] _enemiesForCreation, list of possible enemies the wave
  /// can create
  //-------------------------------------------------------------------//

  static WavePtr create(EnemyPairList _enemiesForCreation);

  //-------------------------------------------------------------------//
  /// @brief the destructor
  //-------------------------------------------------------------------//

  ~Wave();

  //-------------------------------------------------------------------//
  /// @brief update all the enemies currently in play and work out
  /// which new enemies need creating
  //-------------------------------------------------------------------//

  void update();

  //-------------------------------------------------------------------//
  /// @brief call all enemies to publish their state to the database
  //-------------------------------------------------------------------//

  void publish();

  //-------------------------------------------------------------------//
  /// @brief call all enemies to draw
  //-------------------------------------------------------------------//

  void draw() const;

protected:

  //-------------------------------------------------------------------//
  /// @brief typedef for list of Enemies
  //-------------------------------------------------------------------//

  typedef std::list<DynamicEntityPtr> EnemyList;

protected:

  //-------------------------------------------------------------------//
  /// @brief ctor
  /// @param[in] _enemiesForCreation, list of possible enemies the wave
  /// can creation
  //-------------------------------------------------------------------//

  Wave(EnemyPairList _enemiesForCreation);

  //-------------------------------------------------------------------//
  /// @brief creates necessarry new enemies, should be called after update
  //-------------------------------------------------------------------//

  void brain();

  //-------------------------------------------------------------------//
  /// @brief add enemy of specific type
  /// @param[in] _type, type of Enemy to create
  /// @param[in] _damage, damage that enemy can do
  /// @param[in] _maxVelocity, maximum velocity an enemy can travel at
  /// @param[in] _pos, initital position of enemy
  //-------------------------------------------------------------------//

  void addEnemy(
                EntityType _type,
                float _damage,
                float _maxVelocity,
                const ngl::Vec3 &_pos
                );

  //-------------------------------------------------------------------//
  /// @brief remove enemy based on its iterator and return iterator to
  /// next available element
  /// @param[in]  _it, iterator to element to be removed
  /// @param[out] the iterator to the next element in the list after the
  /// element has been removed
  //-------------------------------------------------------------------//

  EnemyList::iterator removeEnemy(EnemyList::iterator _it);

protected:
  //-------------------------------------------------------------------//
  /// @brief list of all currently active enemies
  //-------------------------------------------------------------------//

  EnemyList m_enemies;

  //-------------------------------------------------------------------//
  /// @brief list of possible enemy types
  //-------------------------------------------------------------------//

  EnemyPairList m_enemiesForCreation;
};


#endif // WAVE_H
