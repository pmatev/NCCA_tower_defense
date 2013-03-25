#ifndef MISSILESILO_H
#define MISSILESILO_H


//-------------------------------------------------------------------//
/// @file missilesilo.h
/// @brief CONCRETE TYPE This is a turret type for launching grenades
/// @author Jared Auty
/// @version 1
/// @date 7/3/13
/// Revision History :
/// Initial Version 7/3/13
/// @class MissileSilo
//-------------------------------------------------------------------//

#include "turret.h"
#include "smartpointers.h"
DECLARESMART(MissileSilo)
//-------------------------------------------------------------------//
/// @class MissileSilo turret that shoots grenades
//-------------------------------------------------------------------//
class MissileSilo : public Turret
{
public:
  //-------------------------------------------------------------------//
  /// @brief creator
  /// @param[in] _linkedNode node that the turret sits on
  /// @param[in] _id ID of entity
  //-------------------------------------------------------------------//
  static EntityPtr create(
        NodePtr _linkedNode,
        unsigned int _id
        );

  //-------------------------------------------------------------------//
  /// @brief initial state machine values
  //-------------------------------------------------------------------//
  void stateInit();

  //-------------------------------------------------------------------//
  /// @brief a method to generate the view box
  //-------------------------------------------------------------------//

  void generateViewBBox();

  //-------------------------------------------------------------------//
  /// @brief draw function
  //-------------------------------------------------------------------//
  void draw();

  //-------------------------------------------------------------------//
  /// @brief set the position to shoot at. This can be used if you wanted
  /// the user to specify where to shoot.
  /// @param[in] _pos new position of target
  //-------------------------------------------------------------------//
  inline void setTargetPos(const ngl::Vec3 &_pos) {m_targetPos = _pos;}

  //-------------------------------------------------------------------//
  /// @brief set the base position
  /// @param[in] _pos new base pos
  //-------------------------------------------------------------------//
  inline void setBasePos(const ngl::Vec3 &_pos) {m_basePos = _pos;}

  //-------------------------------------------------------------------//
  /// @brief check if the missilesilo has a target
  //-------------------------------------------------------------------//
  inline bool getHasTarget() const {return m_hasTarget;}

  //-------------------------------------------------------------------//
  /// @brief find the best target, save it in target pos
  //-------------------------------------------------------------------//
  void calculateTarget();

protected:
  //-------------------------------------------------------------------//
  /// @brief ctor
  /// @param[in] _linkedNode node that the turret is sitting on
  /// @param[in] _id ID of the entity
  //-------------------------------------------------------------------//
  MissileSilo(
        NodePtr _linkedNode,
        unsigned int _id
        );


  //-------------------------------------------------------------------//
  /// @brief filter the view volume of local enetities
  /// @param[out] o_localEntities list of entities to filter.
  //-------------------------------------------------------------------//
  void filterViewVolume(EntityRecordWCList &o_localEntities);

  //-------------------------------------------------------------------//
  /// @brief works out what the turret should do
  //-------------------------------------------------------------------//

  ngl::Vec3 brain();

  //-------------------------------------------------------------------//
  /// @brief a method to update the shot position
  //-------------------------------------------------------------------//

  void updateShotPos();

  //-------------------------------------------------------------------//
  /// @brief adjust the aim vector to hit the target
  /// @param[in] _target target position to aim at
  //-------------------------------------------------------------------//
  ngl::Vec3 aim(const ngl::Vec3 &_target);

  //-------------------------------------------------------------------//
  /// @brief overload fire so that we can calculate target
  //-------------------------------------------------------------------//
  void fire();



protected:
  //-------------------------------------------------------------------//
  /// @brief gravity value
  //-------------------------------------------------------------------//
  float m_gravity;

  //-------------------------------------------------------------------//
  /// @brief position of target
  //-------------------------------------------------------------------//
  ngl::Vec3 m_targetPos;

  //-------------------------------------------------------------------//
  /// @brief whether the silo has a target or not
  //-------------------------------------------------------------------//
  bool m_hasTarget;

  //-------------------------------------------------------------------//
  /// @brief the position of the base can be used when calculating the target
  /// position. Enemies that are near to the base should have a higher priority.
  //-------------------------------------------------------------------//
  ngl::Vec3 m_basePos;

  //-------------------------------------------------------------------//
  /// @brief horizontal speed that missiles fire at towards target
  //-------------------------------------------------------------------//
  float m_horizontalSpeed;

};

#endif // MISSILESILO_H
