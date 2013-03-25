#ifndef GAME_H
#define GAME_H

#include <QtXml/QDomDocument>
#include "fwd/game.h"
#include "fwd/window.h"
#include <map>
#include "entity.h"
#include <SDL.h>
#include <ngl/Light.h>
#include "uielement.h"
#include "node.h"
#include "meshlib.h"
#include "wavemanager.h"
#include "environment.h"
#include "projectilemanager.h"
#include "player.h"
#include "turret.h"


//-------------------------------------------------------------------//
/// @file game.h
/// @brief a class to manage the game state and other game managers
/// to other managers
/// @author Peter Matev, Jared Auty
/// @version 1.2
/// @date 04/12/12
/// Revision History :
/// Initial Version 29/11/12
/// @class Game
/// @class LevelInfo
//-------------------------------------------------------------------//

class Game
{
public: //methods
    //-------------------------------------------------------------------//
    /// @brief returns instance of singleton
    /// @return the static instance of the game
    //-------------------------------------------------------------------//

    static Game* instance();

    //-------------------------------------------------------------------//
    /// @brief method to initialise game
    //-------------------------------------------------------------------//

    void init();

    //-------------------------------------------------------------------//
    /// @brief clear everything and run sceneSetup()
    //-------------------------------------------------------------------//

    void reset();

    //-------------------------------------------------------------------//
    /// @brief clear the game
    //-------------------------------------------------------------------//

    void destroy();

    //-------------------------------------------------------------------//
    /// @brief updates the game state
    /// @param [in] _dt change in time
    //-------------------------------------------------------------------//

    void update(const double _dt);

    //-------------------------------------------------------------------//
    /// @brief draws the current game state
    //-------------------------------------------------------------------//

    void draw();

    //-------------------------------------------------------------------//
    /// @brief draws the selection buffer for current game state
    //-------------------------------------------------------------------//

    void drawSelection();

    //-------------------------------------------------------------------//
    /// @brief returns an ID for an entity
    /// @return a unique identifier
    //-------------------------------------------------------------------//

    unsigned int getID();

    //-------------------------------------------------------------------//
    /// @brief register the id of given Entity and return its ID
    /// @param [in] _e the entity being registered
    /// @param [in] _id the id of the entity
    //-------------------------------------------------------------------//

    void registerID(EntityPtr _e, unsigned int _id);

    //-------------------------------------------------------------------//
    /// @brief unregister Entity via ID
    /// @param [in] _i the id of the entity to unregister
    //-------------------------------------------------------------------//

    void unregisterID(const unsigned int _i);

    //-------------------------------------------------------------------//
    /// @brief return Smart Pointer to Entity via ID.
    /// @param [in] _i the id of the entity
    //-------------------------------------------------------------------//

    EntityWPtr getEntityByID(const unsigned int _i) const;

    //-------------------------------------------------------------------//
    /// @brief try to create a tower on the specified node with the specified
    /// type.
    /// @param[in] _type, the type of tower to create
    /// @param[in] _node, which node to create the tower on
    /// @return whether the creation was successful or not
    //-------------------------------------------------------------------//

    bool tryToCreateTower(const std::string &_type, NodePtr _node);


    //-------------------------------------------------------------------//
    /// @brief sell tower identified by _id
    /// @param[in] _id id of tower
    /// @return the money you receive from the sale
    //-------------------------------------------------------------------//
    void sellTower(const unsigned int _id);

    //-------------------------------------------------------------------//
    /// @brief return base position
    /// @return the bases position
    //-------------------------------------------------------------------//

    ngl::Vec3 getBasePos() const;

    //-------------------------------------------------------------------//
    /// @brief a method to set the hilighted value of the node
    /// @param [in] _id the id of the node
    /// @param [in] _highlighted the highlight value of the node
    //-------------------------------------------------------------------//

    void setNodeHighlighted(int _id, int _highlighted);

    //-------------------------------------------------------------------//
    /// @brief return weak smart pointer to the environment
    /// @return a weak pointer to the environment
    //-------------------------------------------------------------------//

    EnvironmentWPtr getEnvironmentWeakPtr();

    //-------------------------------------------------------------------//
    /// @brief a method to return a smart weak pointer to the projectile
    /// manager
    /// @return pointer to the projectile manager
    //-------------------------------------------------------------------//

    ProjectileManagerWPtr getProjectileManagerWeakPtr();

    //-------------------------------------------------------------------//
    /// @brief a method to add the inputted currency to the player's
    /// currency
    /// @param [in] _value, the value to add to the currency
    //-------------------------------------------------------------------//

    inline void addCurrency(int _value) {m_player->addCurrency(_value);}

    //-------------------------------------------------------------------//
    /// @brief returns players score
    /// @return the score that the player achieved
    //-------------------------------------------------------------------//

    inline int getPlayerScore() {return m_player->getScore();}


    //-------------------------------------------------------------------//
    /// @brief method to get the players currency
    /// @return players currency
    //-------------------------------------------------------------------//

    inline int getPlayerCurrency() {return m_player->getCurrency();}

    //-------------------------------------------------------------------//
    /// @brief a method to add the inputted score
    /// @param [in] _value, the value to add to the score
    //-------------------------------------------------------------------//

    inline void addScore(int _value) {m_player->addScore(_value);}

    //-------------------------------------------------------------------//
    /// @brief tell wavemanager to start sending enemies
    //-------------------------------------------------------------------//

    void startWaves();

    //-------------------------------------------------------------------//
    /// @brief returns the bases health
    /// @return the base's health
    //-------------------------------------------------------------------//

    float getBaseHealth() const;

    //-------------------------------------------------------------------//
    /// @brief upgrade the tower with ID _id
    /// @param[in] _id identifier for the tower that should be upgraded.
    //-------------------------------------------------------------------//

    bool upgradeTurret(int _id);

    //-------------------------------------------------------------------//
    /// @brief get the upgrade data about the current upgrade level
    /// @param[out] o_upgradeData this is a weak pointer to the current
    /// upgradeData.
    /// @param[in] _id the id of the turret
    /// @return whether the turret has a current upgrade.
    //-------------------------------------------------------------------//

    bool getCurrentUpgrade(Turret::UpgradeDataWPtr &o_upgradeData, int _id);

    //-------------------------------------------------------------------//
    /// @brief get the upgrade data about the next upgrade level
    /// @param[out] o_upgradeData this is a weak pointer to the next
    /// upgradeData.
    /// @param[in] _id the id of the turret
    /// @return whether the turret has a next upgrade.
    //-------------------------------------------------------------------//

    bool getNextUpgrade(Turret::UpgradeDataWPtr &o_upgradeData, int _id);

    //-------------------------------------------------------------------//
    /// @brief set whether the game is paused or not
    /// @param [in] _paused is a bool which specifies whether the game is
    /// paused or not
    //-------------------------------------------------------------------//

    inline void setPaused(int _paused){m_pause = _paused;}

    //-------------------------------------------------------------------//
    /// @brief returns m_paused variable
    /// @return paused state
    //-------------------------------------------------------------------//

    inline int getPaused() {return m_pause;}

    //-------------------------------------------------------------------//
    /// @brief set whether the game is lost or not
    /// @param [in] _lost is a bool which specifies whether the game is
    /// lost or not
    //-------------------------------------------------------------------//

    inline void setLost(bool _lost) {m_gamelost =_lost;}

    //-------------------------------------------------------------------//
    /// @brief returns m_gameLost bool
    /// @return m_lost is a bool which specifies whether the game is
    /// lost or not
    //-------------------------------------------------------------------//

    inline bool getLost() {return m_gamelost;}

protected: //methods
    //-------------------------------------------------------------------//
    /// @brief hidden ctor for singleton
    //-------------------------------------------------------------------//

    Game();

    //-------------------------------------------------------------------//
    /// @brief hidden destructor
    //-------------------------------------------------------------------//

    ~Game();

    //-------------------------------------------------------------------//
    /// @brief apply collision damage
    /// @param[in] _collisionList, is of all the entities that have
    /// collided and the damage to be dealt.
    //-------------------------------------------------------------------//

    void dealDamage(const std::list<Damage> &_collisionList);

    //-------------------------------------------------------------------//
    /// @brief apply impulses
    /// @param[in] _impulses list of impulses to be applied to enemies
    //-------------------------------------------------------------------//

    void dealImpulses(const std::list<Impulse> &_impulses);


    //-------------------------------------------------------------------//
    /// @brief setup the whole scene. This is where any scene information
    /// should be read from file, interpreted and initialisd.
    //-------------------------------------------------------------------//

    void setupScene();

    //-------------------------------------------------------------------//
    /// @brief blah blah xml
    /// @param[in] _environment the data corresponding to the environment
    /// @param[in] _waveInfors data corresponding to each wave
    //-------------------------------------------------------------------//

    std::vector<ngl::Vec2> getCoordsFromXML(QDomElement _docElem, std::string _nodeName);

protected: //attributes

    //-------------------------------------------------------------------//
    /// @brief A map of IDs to Entity Pointers for game object management.
    //-------------------------------------------------------------------//

    std::map<unsigned int, EntityWPtr> m_IDMap;

    //-------------------------------------------------------------------//
    /// @brief pointer to the wavemanager
    //-------------------------------------------------------------------//

    WaveManagerPtr m_waveManager;

    //-------------------------------------------------------------------//
    /// @brief pointer to the environment
    //-------------------------------------------------------------------//

    EnvironmentPtr m_environment;

    //-------------------------------------------------------------------//
    /// @brief pointer to the projectile manager
    //-------------------------------------------------------------------//

    ProjectileManagerPtr m_projectileManager;

    //-------------------------------------------------------------------//
    /// @brief pointer to the player object
    //-------------------------------------------------------------------//

    PlayerPtr m_player;

    //-------------------------------------------------------------------//
    /// @brief flag to say whether the game is paused or not
    //-------------------------------------------------------------------//

    int m_pause;

    //-------------------------------------------------------------------//
    /// @brief flag to say whether the game has been lost or not
    //-------------------------------------------------------------------//

    bool m_gamelost;

private: //attributes

    //-------------------------------------------------------------------//
    /// @brief instance pointer for singleton
    //-------------------------------------------------------------------//

    static Game* s_instance;

    //-------------------------------------------------------------------//
    /// @brief a pointer to the light
    //-------------------------------------------------------------------//

    ngl::Light *m_light;
};

//-------------------------------------------------------------------//
/// @class This class collects all the data to do with a level.
//-------------------------------------------------------------------//

DECLARESMART(LevelInfo)

class LevelInfo
{
public:
  //-------------------------------------------------------------------//
  /// @brief create function
  /// @param[in] _environment the data corresponding to the environment
  /// @param[in] _waveInfors data corresponding to each wave
  /// @return a pointer to the level info object
  //-------------------------------------------------------------------//

  inline static LevelInfoPtr create(
        EnvironmentInfoPtr _environment,
        const WaveInfoList &_waveInfos
        )
  {
    LevelInfoPtr a(new LevelInfo(_environment, _waveInfos));
    return a;
  }

protected:
  //-------------------------------------------------------------------//
  /// @brief ctor
  /// @param[in] _environment the data corresponding to the environment
  /// @param[in] _waveInfors data corresponding to each wave
  //-------------------------------------------------------------------//
  LevelInfo(
        EnvironmentInfoPtr _environment,
            const WaveInfoList &_waveInfos
        ):
    m_environment(_environment),
    m_waveInfos(_waveInfos)
  {;}

protected:
  //-------------------------------------------------------------------//
  /// @brief pointer to envrionment data
  //-------------------------------------------------------------------//

  EnvironmentInfoPtr m_environment;

  //-------------------------------------------------------------------//
  /// @brief wave information for each wave
  //-------------------------------------------------------------------//

  WaveInfoList m_waveInfos;

};

#endif // GAME_H
