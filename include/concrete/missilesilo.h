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

class MissileSilo : public Turret
{
public:
  //-------------------------------------------------------------------//
  /// @brief creator
  //-------------------------------------------------------------------//
  static EntityPtr create(
        NodePtr _linkedNode,
        unsigned int _id
        );

  void stateInit();

  //-------------------------------------------------------------------//
  /// @brief a method to generate the view box
  //-------------------------------------------------------------------//

  void generateViewBBox();

  void draw();

  //-------------------------------------------------------------------//
  /// @brief set the position to shoot at. This can be used if you wanted
  /// the user to specify where to shoot.
  //-------------------------------------------------------------------//
  inline void setTargetPos(const ngl::Vec3 &_pos) {m_targetPos = _pos;}

  //-------------------------------------------------------------------//
  /// @brief set the base position
  //-------------------------------------------------------------------//
  inline void setBasePos(const ngl::Vec3 &_pos) {m_basePos = _pos;}

  inline bool getHasTarget() const {return m_hasTarget;}

  //-------------------------------------------------------------------//
  /// @brief find the best target, save it in target pos
  //-------------------------------------------------------------------//
  void calculateTarget();


protected:
  //-------------------------------------------------------------------//
  /// @brief ctor
  //-------------------------------------------------------------------//
  MissileSilo(
        NodePtr _linkedNode,
        unsigned int _id
        );


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

  ngl::Vec3 m_targetPos;

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
