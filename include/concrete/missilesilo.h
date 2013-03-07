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

  inline void setTargetPos(const ngl::Vec3 &_pos) {m_targetPos = _pos;}

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
  ngl::Vec3 aim(const ngl::Vec3 &_target, float _horizontalSpeed);

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

};

#endif // MISSILESILO_H
