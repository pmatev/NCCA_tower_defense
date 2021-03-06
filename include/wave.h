#ifndef WAVE_H
#define WAVE_H

#include <boost/shared_ptr.hpp>

#include "enemy.h"
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
/// @class WaveInfo
//-------------------------------------------------------------------//

DECLARESMARTLIST(Wave)
DECLARESMARTLIST(WaveInfo)

class Wave
{
public:
  DECLARESMART(EnemyInfo)
  //-------------------------------------------------------------------//
  /// @class pair for storing the number and type of a specific enemy
  /// this will be used when creating lists of available enemies for passing
  /// into the wave
  //-------------------------------------------------------------------//

  class EnemyInfo
  {
    public:

    //-------------------------------------------------------------------//
    /// @brief the number of enemies of specific type
    //-------------------------------------------------------------------//

    int m_count;

    //-------------------------------------------------------------------//
    /// @brief the specific enemy type
    //-------------------------------------------------------------------//
    std::string m_type;

    //-------------------------------------------------------------------//
    /// @brief the shield value of the enemies
    //-------------------------------------------------------------------//
    float m_shield;

    //-------------------------------------------------------------------//
    /// @brief maximum speed that an enemy can go
    //-------------------------------------------------------------------//
    float m_maxSpeed;

    public:

    //-------------------------------------------------------------------//
    /// @brief default creator
    /// @param[in] _count number of enemies of this type
    /// @param[in] _type type string for the enemies
    /// @param[in] _shield value of the enemies
    /// @param[in] _maxSpeed maximum speed of the enemies
    //-------------------------------------------------------------------//

    inline static EnemyInfoPtr create(
          int _count,
          const std::string &_type,
          float _shield,
          float _maxSpeed
          )
    {
      EnemyInfoPtr a(new EnemyInfo(_count, _type, _shield, _maxSpeed));
      return a;
    }

    //-------------------------------------------------------------------//
    /// @brief deep copy
    //-------------------------------------------------------------------//

    inline EnemyInfoPtr clone()
    {
      EnemyInfoPtr a(new EnemyInfo(m_count, m_type, m_shield, m_maxSpeed));
      return a;
    }

    protected:

    //-------------------------------------------------------------------//
    /// @brief default ctor
    //-------------------------------------------------------------------//
    EnemyInfo():
      m_count(0),
      m_type(""),
      m_shield(1.0),
      m_maxSpeed(1.0)
    {;}

    //-------------------------------------------------------------------//
    /// @brief paramatized ctor
    /// @param[in] _count number of enemies of this type
    /// @param[in] _type type string for the enemies
    /// @param[in] _shield value of the enemies
    /// @param[in] _maxSpeed maximum speed of the enemies
    //-------------------------------------------------------------------//

    EnemyInfo(
          int _count,
          const std::string &_type,
          float _shield,
          float _maxSpeed
          ):
      m_count(_count),
      m_type(_type),
      m_shield(_shield),
      m_maxSpeed(_maxSpeed)
    {;}

  };

  //-------------------------------------------------------------------//
  /// @brief typedef for lists of EnemyInfos
  //-------------------------------------------------------------------//

  typedef std::list<EnemyInfoPtr> EnemyInfoList;


public:

  //-------------------------------------------------------------------//
  /// @brief creator
  /// @param[in] _enemiesForCreation list of possible enemies the wave
  /// can create
  /// @param[in] _spawnNodes list of weak pointer to spawn nodes
  //-------------------------------------------------------------------//

  static WavePtr create(
        const WaveInfo &_waveInfo,
        Node::NodeWVecWPtr _spawnNodes
        );

  //-------------------------------------------------------------------//
  /// @brief the destructor
  //-------------------------------------------------------------------//

  ~Wave();

  //-------------------------------------------------------------------//
  /// @brief update all the enemies currently in play and work out
  /// which new enemies need creating
  /// @param [in] _dt the timestep in seconds
  //-------------------------------------------------------------------//

  void update(const double _dt);

  //-------------------------------------------------------------------//
  /// @brief call all enemies to publish their state to the database
  //-------------------------------------------------------------------//

  void publish();

  //-------------------------------------------------------------------//
  /// @brief call all enemies to draw
  //-------------------------------------------------------------------//

  void draw();

  //-------------------------------------------------------------------//
  /// @brief call all enemies to draw selection
  //-------------------------------------------------------------------//
    void drawSelection();

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

  std::list<Damage> checkCollisions();

  //-------------------------------------------------------------------//
  /// @brief check if all the enemies have been killed
  //-------------------------------------------------------------------//

  bool isDead() const ;

  //-------------------------------------------------------------------//
  /// @brief reset the wave to its original state
  //-------------------------------------------------------------------//

  void reset();

protected:

  //-------------------------------------------------------------------//
  /// @brief ctor
  /// @param[in] _enemiesForCreation list of possible enemies the wave
  /// can creation
  /// @param[in] _spawnNodes list of weak pointer to spawn nodes
  //-------------------------------------------------------------------//

  Wave(
        const WaveInfo &_waveInfo,
        Node::NodeWVecWPtr _spawnNodes
        );

  //-------------------------------------------------------------------//
  /// @brief creates necessarry new enemies, should be called after update
  /// @param [in] _dt the timestep in seconds
  //-------------------------------------------------------------------//

  void brain(const double _dt);

  //-------------------------------------------------------------------//
  /// @brief add enemy of specific type
  /// @param[in] _enemyInfo info for enemy type
  /// @param[in] _pos, initital position of enemy
  //-------------------------------------------------------------------//

  void addEnemy(
         EnemyInfoCPtr _enemyInfo,
        const ngl::Vec3 &_pos
        );

  //-------------------------------------------------------------------//
  /// @brief remove enemy based on its iterator and return iterator to
  /// next available element
  /// @param[in]  _it iterator to element to be removed
  /// @return the iterator to the next element in the list after the
  /// element has been removed
  //-------------------------------------------------------------------//

  EnemyVec::iterator removeEnemy(EnemyVec::iterator _it);

  //-------------------------------------------------------------------//
  /// @brief goes through all the Enemies, asks for their paths and compiles
  /// the result into m_usedNodes
  //-------------------------------------------------------------------//

  void rebuildPathNodes();

  //-------------------------------------------------------------------//
  /// @brief Add Enemies path to the map of all paths
  /// @param[in] _enemy, Enemy to insert
  //-------------------------------------------------------------------//

  void addToPathNodes(EnemyPtr _enemy);

protected:
  //-------------------------------------------------------------------//
  /// @brief list of all currently active enemies
  //-------------------------------------------------------------------//

  EnemyVec m_enemies;

  //-------------------------------------------------------------------//
  /// @brief list of possible enemy types and how many can be created currently
  //-------------------------------------------------------------------//

  EnemyInfoList m_enemiesForCreation;

  //-------------------------------------------------------------------//
  /// @brief list of possible enemy types and how many can be created in total.
  /// This is used for resetting the wave. This keeps a copy of how many
  /// of each type of enemy can be created over the whole wave
  //-------------------------------------------------------------------//

  EnemyInfoList m_totalEnemiesForCreation;

  //-------------------------------------------------------------------//
  /// @brief approximate time between between enemy creation
  //-------------------------------------------------------------------//

  float m_birthRate;

  //-------------------------------------------------------------------//
  /// @brief vector of nodes that can be spawned on.
  //-------------------------------------------------------------------//

  Node::NodeWVecWPtr m_spawnNodes;

  //-------------------------------------------------------------------//
  /// @brief map of all Nodes currently being used for paths and their
  /// corresponding list of Enemies. This list must be updated whenever
  /// an enemy updates it's path
  //-------------------------------------------------------------------//

  std::map<NodeWPtr, EnemyWVecPtr> m_pathNodes;

  //-------------------------------------------------------------------//
  /// @brief internal time value for managing enemy creation (in seconds)
  //-------------------------------------------------------------------//

  float m_time;

  //-------------------------------------------------------------------//
  /// @brief maximum number of enemies that can be on the field at any one
  /// point.
  //-------------------------------------------------------------------//
  unsigned int m_maxActiveEnemies;

};


//-------------------------------------------------------------------//
/// @brief class to hold information relating to the creation of a wave
//-------------------------------------------------------------------//

class WaveInfo
{
public:
  //-------------------------------------------------------------------//
  /// @brief creator
  /// @param[in] _enemiesForCreation list of enemies that can be created
  /// @param[in] _birthRate how fast the enemies are created
  //-------------------------------------------------------------------//
  static WaveInfoPtr create(
      const Wave::EnemyInfoList &_enemiesForCreation,
      float _birthRate
      );

  //-------------------------------------------------------------------//
  /// @brief List of enemy types and corresponding enemy counts
  //-------------------------------------------------------------------//
  Wave::EnemyInfoList m_enemiesForCreation;

  //-------------------------------------------------------------------//
  /// @brief time interval between each enemy creation
  //-------------------------------------------------------------------//
  float m_birthRate;

protected:
  //-------------------------------------------------------------------//
  /// @brief constructor
  /// @param[in] _enemiesForCreation list of enemies that can be created
  /// @param[in] _birthRate how fast the enemies are created
  //-------------------------------------------------------------------//
  inline WaveInfo(
      const Wave::EnemyInfoList &_enemiesForCreation,
      float _birthRate
      ):
    m_enemiesForCreation(_enemiesForCreation),
    m_birthRate(_birthRate)
  {;}
};

#endif // WAVE_H
