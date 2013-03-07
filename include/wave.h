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
  DECLARESMART(EnemyPair)
  //-------------------------------------------------------------------//
  /// @class pair for storing the number and type of a specific enemy
  /// this will be used when creating lists of available enemies for passing
  /// into the wave
  //-------------------------------------------------------------------//

  class EnemyPair
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

    public:

    //-------------------------------------------------------------------//
    /// @brief default creator
    //-------------------------------------------------------------------//

    inline static EnemyPairPtr create(int _count, const std::string &_type)
    {
      EnemyPairPtr a(new EnemyPair(_count, _type));
      return a;
    }

    //-------------------------------------------------------------------//
    /// @brief deep copy
    //-------------------------------------------------------------------//

    inline EnemyPairPtr clone()
    {
      EnemyPairPtr a(new EnemyPair(m_count, m_type));
      return a;
    }

    protected:

    //-------------------------------------------------------------------//
    /// @brief default ctor
    //-------------------------------------------------------------------//
    EnemyPair():
      m_count(0),
      m_type("")
    {;}

    //-------------------------------------------------------------------//
    /// @brief paramatized ctor
    //-------------------------------------------------------------------//

    EnemyPair(int _count, const std::string &_type):
      m_count(_count),
      m_type(_type)
    {;}



  };

  //-------------------------------------------------------------------//
  /// @brief typedef for lists of EnemyPairs
  //-------------------------------------------------------------------//

  typedef std::list<EnemyPairPtr> EnemyPairList;


public:

  //-------------------------------------------------------------------//
  /// @brief creator
  /// @param[in] _enemiesForCreation, list of possible enemies the wave
  /// can create
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
  /// @param [in] _dt, the timestep
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
  /// @param[out] whether all the paths were successful or not
  //-------------------------------------------------------------------//

  bool generatePaths(NodeWPtr _node);

  //-------------------------------------------------------------------//
  /// @brief check for collisions with static objects
  /// @param[out] list of Collisions with objects
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
  //typedef std::list<DynamicEntityPtr> EnemyVec;
  //typedef boost::shared_ptr<EnemyVec> EnemyVecPtr;
protected:

  //-------------------------------------------------------------------//
  /// @brief ctor
  /// @param[in] _enemiesForCreation, list of possible enemies the wave
  /// can creation
  //-------------------------------------------------------------------//

  Wave(
        const WaveInfo &_waveInfo,
        Node::NodeWVecWPtr _spawnNodes
        );

  //-------------------------------------------------------------------//
  /// @brief creates necessarry new enemies, should be called after update
  //-------------------------------------------------------------------//

  void brain(const double _dt);

  //-------------------------------------------------------------------//
  /// @brief add enemy of specific type
  /// @param[in] _type, type of Enemy to create
  /// @param[in] _damage, damage that enemy can do
  /// @param[in] _maxVelocity, maximum velocity an enemy can travel at
  /// @param[in] _pos, initital position of enemy
  //-------------------------------------------------------------------//

  void addEnemy(
        std::string _type,
        const ngl::Vec3 &_pos,
        const ngl::Vec3 &_aim
        );

  //-------------------------------------------------------------------//
  /// @brief remove enemy based on its iterator and return iterator to
  /// next available element
  /// @param[in]  _it, iterator to element to be removed
  /// @param[out] the iterator to the next element in the list after the
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

  EnemyPairList m_enemiesForCreation;

  //-------------------------------------------------------------------//
  /// @brief list of possible enemy types and how many can be created in total.
  /// This is used for resetting the wave. This keeps a copy of how many
  /// of each type of enemy can be created over the whole wave
  //-------------------------------------------------------------------//

  EnemyPairList m_totalEnemiesForCreation;

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



};


//-------------------------------------------------------------------//
/// @brief class to hold information relating to the creation of a wave
//-------------------------------------------------------------------//

class WaveInfo
{
  public:
  static WaveInfoPtr create(
        const Wave::EnemyPairList &_enemiesForCreation,
        float _birthRate
        );
  //-------------------------------------------------------------------//
  /// @brief List of enemy types and corresponding enemy counts
  //-------------------------------------------------------------------//
  Wave::EnemyPairList m_enemiesForCreation;

  //-------------------------------------------------------------------//
  /// @brief time interval between each enemy creation
  //-------------------------------------------------------------------//
  float m_birthRate;

  protected:
  inline WaveInfo(
        const Wave::EnemyPairList &_enemiesForCreation,
        float _birthRate
        ):
    m_enemiesForCreation(_enemiesForCreation),
    m_birthRate(_birthRate)
  {;}
};

#endif // WAVE_H
