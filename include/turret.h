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
public:

  //-------------------------------------------------------------------//
  /// @brief class to hold data for each update
  //-------------------------------------------------------------------//
  DECLARESMARTVEC(UpgradeData)
  struct UpgradeData
  {
    //-------------------------------------------------------------------//
    /// @brief ctor
    //-------------------------------------------------------------------//
    UpgradeData(
          const char *_title,
          const char *_description,
          std::string _texture,
          int _cost
          ):
      m_title(_title),
      m_description(_description),
      m_texture(_texture),
      m_cost(_cost)
    {;}

    //-------------------------------------------------------------------//
    /// @brief creator
    //-------------------------------------------------------------------//

    inline static UpgradeDataPtr create(
          const char *_title,
          const char *_description,
          std::string _texture,
          int _cost
          )
    {
      UpgradeDataPtr a(
            new UpgradeData(
              _title,
              _description,
              _texture,
              _cost
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
  };

  //-------------------------------------------------------------------//
  /// @brief a parameterised constructor
  /// @param [in] _fov, a float value defining the field of view of the
  /// turret
  /// @param [in] _viewDistance, a float value defining how far the turret
  /// can see
  /// @param [in] _maxRotationSpeed, float value defining how fast a
  /// turret can rotate
  /// @param [in] _aim, a reference to an ngl vector which defines the
  /// initial aim vector of the turret
  /// @param [in] _linkedNodes, a reference to an stl vector of boost
  /// shared pointers to the nodes that are covered by the static entity
  /// @param [in] _pos, a vector containing the initial position in 3D
  /// space of the entity
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
  /// @param [in] _dt, the timestep
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
  //-------------------------------------------------------------------//

  inline bool getDoShot() const {return m_doShot;}

  //-------------------------------------------------------------------//
  /// @brief a method to set the doShot boolean
  //-------------------------------------------------------------------//

  inline void setDoShot(bool _newVal) {m_doShot = _newVal;}

  //-------------------------------------------------------------------//
  /// @brief addDtSinceShot method, adds a double value to the dt since
  /// shot variable
  //-------------------------------------------------------------------//

  inline void addDtSinceShot(double _dt) {m_dtSinceLastShot += _dt;}

  //-------------------------------------------------------------------//
  /// @brief a method to set the time since the last shot
  //-------------------------------------------------------------------//

  inline void setDtSinceShot(double _dt) {m_dtSinceLastShot = _dt;}

  //-------------------------------------------------------------------//
  /// @brief a method to return the time since the last shot
  //-------------------------------------------------------------------//

  inline double getDtSinceShot() const {return m_dtSinceLastShot;}

  //-------------------------------------------------------------------//
  /// @brief a method to get the min time between shots
  //-------------------------------------------------------------------//

  inline double getShotWaitTime() const {return m_shotWaitTime;}

  //-------------------------------------------------------------------//
  /// @brief set the shooting speed
  /// @param[in] _shotWaitTime seconds between shots
  //-------------------------------------------------------------------//
  inline void setShotWaitTime(float _shotWaitTime)
  {
    m_shotWaitTime = _shotWaitTime;
  }

  //-------------------------------------------------------------------//
  /// @brief a method to return the vector required to aim at an inputted
  /// position
  /// @param [in] _pos the position to aim at
  /// @param [out] the required vector to aim at the position
  //-------------------------------------------------------------------//

  ngl::Vec3 calculateAimVec(const ngl::Vec3 &_pos,
                            const ngl::Vec3 &_velocity) const;

  //-------------------------------------------------------------------//
  /// @brief a method to update the shot position
  //-------------------------------------------------------------------//

  virtual void updateShotPos() = 0;

  //-------------------------------------------------------------------//
  /// @brief a method to get a record from the local entities
  /// list by it's ID
  /// @param [in] _ID the id to search by
  /// @param [out] reference to the entity record
  //-------------------------------------------------------------------//

  void getTargetRecord(EntityRecordWCPtr &o_record);

  //-------------------------------------------------------------------//
  /// @brief a method to get a record from the local entities
  /// list based on the one that is nearest to the current aim
  /// @param [out] a reference to the entity record
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
  //-------------------------------------------------------------------//

  inline float getCosRotationSpeed() const {return m_cosRotationSpeed;}

  //-------------------------------------------------------------------//
  /// @brief method to return the m_aim Vector
  //-------------------------------------------------------------------//

  inline ngl::Vec3 getAim() const{return m_aim;}

  //-------------------------------------------------------------------//
  /// @brief method to set the target id
  //-------------------------------------------------------------------//

  inline void setTarget(unsigned int _ID) {m_targetID = _ID;}

  //-------------------------------------------------------------------//
  /// @brief method to set the rotation value, auto sets the cos val
  /// @param [in] _maxRotation rotation value
  //-------------------------------------------------------------------//

  void setRotationAngle (float _maxRotation);

  //-------------------------------------------------------------------//
  /// @brief set the projectile type
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

protected:

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

protected:
  //-------------------------------------------------------------------//
  /// @brief register upgrade with the turret. This enables all the update
  /// transitions
  /// @param[in] _upgradeState the state that should manage the upgrading
  //-------------------------------------------------------------------//

  void registerUpgrade(State *_upgradeState, UpgradeDataPtr _data);

};


#endif // TURRET_H
