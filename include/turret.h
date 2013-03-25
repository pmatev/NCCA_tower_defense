                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                         #ifndef TURRET_H
#define TURRET_H

#include "staticentity.h"
#include <string>


//-------------------------------------------------------------------//
/// @file turret.h
/// @brief The class for all turrets, static renderable objects with a
/// brain and a view area
/// @author Peter May, Jared Auty
/// @version 1
/// @date 23/11/12
/// Revision History :
/// Initial Version 23/11/12
/// @class Turret
//-------------------------------------------------------------------//

DECLARESMART(Turret)

class Turret : public StaticEntity
{
public: //structs and typedefs

  //-------------------------------------------------------------------//
  /// @brief struct to hold data for each upgrade
  //-------------------------------------------------------------------//

  DECLARESMARTVEC(UpgradeData)
  struct UpgradeData
  {
    //-------------------------------------------------------------------//
    /// @brief ctor
    /// @param [in] _title the title of the update
    /// @param [in] _description description text for the upgrade
    /// @param [in] _texture a path to the texture
    /// @param [in] _cost the cost of the upgrade
    /// @param [in] _sellValue money that the user gets back from selling
    //-------------------------------------------------------------------//

    UpgradeData(
          const char *_title,
          const char *_description,
          std::string _texture,
          int _cost,
          int _sellValue
          ):
      m_title(_title),
      m_description(_description),
      m_texture(_texture),
      m_cost(_cost),
      m_sellValue(_sellValue)
    {;}

    //-------------------------------------------------------------------//
    /// @brief creator
    /// @param [in] _title the title of the update
    /// @param [in] _description description text for the upgrade
    /// @param [in] _texture a path to the texture
    /// @param [in] _cost the cost of the upgrade
    /// @param [in] _sellValue money that the user gets back from selling
    //-------------------------------------------------------------------//

    inline static UpgradeDataPtr create(
          const char *_title,
          const char *_description,
          std::string _texture,
          int _cost,
          int _saleValue
          )
    {
      UpgradeDataPtr a(
            new UpgradeData(
              _title,
              _description,
              _texture,
              _cost,
              _saleValue
              )
            );
      return a;
    }
    //-------------------------------------------------------------------//
    /// @brief title of the upgrade
    //-------------------------------------------------------------------//

    const char *m_title;

    //-------------------------------------------------------------------//
    /// @brief description of the upgrade. This will be displayed by the ui
    /// when the user wants to update.
    //-------------------------------------------------------------------//

    const char *m_description;

    //-------------------------------------------------------------------//
    /// @brief This can be used to store a path to a custom texture related
    /// to the upgrade
    //-------------------------------------------------------------------//

    std::string m_texture;

    //-------------------------------------------------------------------//
    /// @brief Cost to upgrade
    //-------------------------------------------------------------------//

    int m_cost;
    //-------------------------------------------------------------------//
    /// @brief Money that the user gets back when they sell
    //-------------------------------------------------------------------//

    int m_sellValue;
  };

public: //methods

  //-------------------------------------------------------------------//
  /// @brief a parameterised constructor
  /// @param [in] _linkedNode a pointer to the linked node
  /// @param [in] _id the unique identifier for the entity
  /// @param [in] _projectileType the type of projectile to emit
  /// @param [in] _viewDistance a float value defining how far the turret
  /// can see
  /// @param [in] _projectileSpeed float value defining how fast a
  /// projectile travels
  //-------------------------------------------------------------------//

  Turret(
        NodePtr _linkedNode,
        unsigned int _id,
        std::string _projectileType,
        float _viewDistance,
        float _projectileSpeed
        );

  //-------------------------------------------------------------------//
  /// @brief destructor
  //-------------------------------------------------------------------//

  ~Turret();

  //-------------------------------------------------------------------//
  /// @brief updates the turret, taking the value returned by brain() into
  /// account.
  /// @param [in] _dt the timestep
  //-------------------------------------------------------------------//

  void update(const double _dt);

  //-------------------------------------------------------------------//
  /// @brief brain must be implemented in concrete types and returns the
  /// new aim
  /// @param[in] aim vector
  //-------------------------------------------------------------------//

  virtual ngl::Vec3 brain() = 0;

  //-------------------------------------------------------------------//
  /// @brief a method to fire a projectile
  //-------------------------------------------------------------------//

  virtual void fire();

  //-------------------------------------------------------------------//
  /// @brief a method to return the doShot boolean
  /// @return whether or not to shoot
  //-------------------------------------------------------------------//

  inline bool getDoShot() const {return m_doShot;}

  //-------------------------------------------------------------------//
  /// @brief a method to set the doShot boolean
  /// @param [in] _newVal the new boolean value to set the doShot variable
  /// to
  //-------------------------------------------------------------------//

  inline void setDoShot(bool _newVal) {m_doShot = _newVal;}

  //-------------------------------------------------------------------//
  /// @brief addDtSinceShot method, adds a double value to the dt since
  /// shot variable
  /// @param [in] _dt the timestep
  //-------------------------------------------------------------------//

  inline void addDtSinceShot(double _dt) {m_dtSinceLastShot += _dt;}

  //-------------------------------------------------------------------//
  /// @brief a method to set the time since the last shot
  /// @param [in] _dt the timestep
  //-------------------------------------------------------------------//

  inline void setDtSinceShot(double _dt) {m_dtSinceLastShot = _dt;}

  //-------------------------------------------------------------------//
  /// @brief a method to return the time since the last shot
  /// @return the time since the last shot
  //-------------------------------------------------------------------//

  inline double getDtSinceShot() const {return m_dtSinceLastShot;}

  //-------------------------------------------------------------------//
  /// @brief a method to get the min time between shots
  /// @return the time to wait between shots
  //-------------------------------------------------------------------//

  inline double getShotWaitTime() const {return m_shotWaitTime;}

  //-------------------------------------------------------------------//
  /// @brief set the shooting speed
  /// @return _shotWaitTime seconds between shots
  //-------------------------------------------------------------------//

  inline void setShotWaitTime(float _shotWaitTime)
  {
    m_shotWaitTime = _shotWaitTime;
  }

  //-------------------------------------------------------------------//
  /// @brief a method to return the vector required to aim at an inputted
  /// position
  /// @param [in] _pos the position to aim at
  /// @param [in] _velocity the velocity of the target
  /// @return the required vector to aim at the position
  //-------------------------------------------------------------------//

  ngl::Vec3 calculateAimVec(const ngl::Vec3 &_pos,
                            const ngl::Vec3 &_velocity) const;

  //-------------------------------------------------------------------//
  /// @brief a method to update the shot position, pure virtual
  //-------------------------------------------------------------------//

  virtual void updateShotPos() = 0;

  //-------------------------------------------------------------------//
  /// @brief a method to get a record from the local entities
  /// list by it's ID
  /// @param [out] o_record reference to the target entity record
  //-------------------------------------------------------------------//

  void getTargetRecord(EntityRecordWCPtr &o_record);

  //-------------------------------------------------------------------//
  /// @brief a method to get a record from the local entities
  /// list based on the one that is nearest to the current aim
  /// @param [out] o_record a reference to the nearest entity record
  //-------------------------------------------------------------------//

  void getNearestLocalRecord(EntityRecordWCPtr & o_record);

  //-------------------------------------------------------------------//
  /// @brief a method  to set the aim value of the turret
  /// @param [in] _aim the input vector defines the aim
  //-------------------------------------------------------------------//

  void setDesiredAim(const ngl::Vec3 &_aim);

  //-------------------------------------------------------------------//
  /// @brief prepare for update method, overloaded so that it has access
  /// to the fire variables and methods
  //-------------------------------------------------------------------//

  void prepareForUpdate();

  //-------------------------------------------------------------------//
  /// @brief method to return the cosine of the max rotation speed
  /// @return the cos of the rotation speed
  //-------------------------------------------------------------------//

  inline float getCosRotationSpeed() const {return m_cosRotationSpeed;}

  //-------------------------------------------------------------------//
  /// @brief method to return the m_aim Vector
  /// @return the aim vector
  //-------------------------------------------------------------------//

  inline ngl::Vec3 getAim() const{return m_aim;}

  //-------------------------------------------------------------------//
  /// @brief method to set the target id
  /// @return _ID the input id
  //-------------------------------------------------------------------//

  inline void setTarget(unsigned int _ID) {m_targetID = _ID;}

  //-------------------------------------------------------------------//
  /// @brief method to set the rotation value, auto sets the cos val
  /// @param [in] _maxRotation rotation value
  //-------------------------------------------------------------------//

  void setRotationAngle (float _maxRotation);

  //-------------------------------------------------------------------//
  /// @brief set the projectile type
  /// @param [in] _projectileType the type of projectile to emit
  //-------------------------------------------------------------------//

  inline void setProjectileType(const std::string &_projectileType)
  {
    m_projectileType = _projectileType;
  }

  //-------------------------------------------------------------------//
  /// @brief move turret to the next available upgrade
  //-------------------------------------------------------------------//

  bool upgrade();

  //-------------------------------------------------------------------//
  /// @brief get the current sell value of the turret
  //-------------------------------------------------------------------//

  int getSellValue() const {return m_sellValue;}

  //-------------------------------------------------------------------//
  /// @brief get the upgrade data about the current upgrade level
  /// @param[out] o_upgradeData this is a weak pointer to the current
  /// upgradeData.
  /// @return whether the turret has a current upgrade.
  //-------------------------------------------------------------------//

  bool getCurrentUpgrade(UpgradeDataWPtr &o_upgradeData);

  //-------------------------------------------------------------------//
  /// @brief get the upgrade data about the next upgrade level
  /// @param[out] o_upgradeData this is a weak pointer to the next
  /// upgradeData.
  /// @return whether the turret has a next upgrade.
  //-------------------------------------------------------------------//

  bool getNextUpgrade(UpgradeDataWPtr &o_upgradeData);

protected: //methods
  //-------------------------------------------------------------------//
  /// @brief register upgrade with the turret. This enables all the update
  /// transitions
  /// @param[in] _upgradeState the state that should manage the upgrading
  /// @param[in] _data the upgrade data
  //-------------------------------------------------------------------//

  void registerUpgrade(State *_upgradeState, UpgradeDataPtr _data);

protected: //attributes

  //-------------------------------------------------------------------//
  /// @brief value to define the field of view of the turret
  //-------------------------------------------------------------------//

  float m_fov;

  //-------------------------------------------------------------------//
  /// @brief value to define how far a turret can see
  //-------------------------------------------------------------------//

  float m_viewDistance;

  //-------------------------------------------------------------------//
  /// @brief value to define the max rotation speed, stored as angle per
  /// update
  //-------------------------------------------------------------------//

  float m_maxRotationAngle;

  //-------------------------------------------------------------------//
  /// @brief the cosine of the max rotation angle
  //-------------------------------------------------------------------//

  float m_cosRotationSpeed;

  //-------------------------------------------------------------------//
  /// @brief vector defining the aim vector of the turret
  //-------------------------------------------------------------------//

  ngl::Vec3 m_aim;

  //-------------------------------------------------------------------//
  /// @brief a string to store the type of projectile that the turret shoots
  //-------------------------------------------------------------------//

  std::string m_projectileType;

  //-------------------------------------------------------------------//
  /// @brief a boolean to store whether or not to fire at the next
  /// round of updates
  //-------------------------------------------------------------------//

  bool m_doShot;

  //-------------------------------------------------------------------//
  /// @brief the time since the last shot
  //-------------------------------------------------------------------//

  double m_dtSinceLastShot;

  //-------------------------------------------------------------------//
  /// @brief a variable defining how often a turret can shoot
  //-------------------------------------------------------------------//

  double m_shotWaitTime;

  //-------------------------------------------------------------------//
  /// @brief fire position
  //-------------------------------------------------------------------//

  ngl::Vec3 m_shotPos;

  //-------------------------------------------------------------------//
  /// @brief the ID of the target
  //-------------------------------------------------------------------//

  unsigned int m_targetID;

  //-------------------------------------------------------------------//
  /// @brief the desired vector for the aim
  //-------------------------------------------------------------------//

  ngl::Vec3 m_desiredAim;

  //-------------------------------------------------------------------//
  /// @brief the initial speed inputted to the bullet, not necessarily
  /// used at the other end
  //-------------------------------------------------------------------//

  float m_projectileSpeed;

  //-------------------------------------------------------------------//
  /// @brief array of posible upgrade state that a turret can be in
  //-------------------------------------------------------------------//

  std::vector<State*> m_upgrades;

  //-------------------------------------------------------------------//
  /// @brief array of data for each upgrade. This is used in the ui for
  /// showing upgrade information.
  //-------------------------------------------------------------------//

  UpgradeDataVec m_upgradeData;

  //-------------------------------------------------------------------//
  /// @brief current upgrade state, this is an index into s_upgrades
  //-------------------------------------------------------------------//

  unsigned int m_upgradeIndex;

  //-------------------------------------------------------------------//
  /// @brief money that player receives when they sell the turret
  //-------------------------------------------------------------------//
  int m_sellValue;

};


#endif // TURRET_H
