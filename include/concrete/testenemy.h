#ifndef TESTENEMY_H
#define TESTENEMY_H

#include "enemy.h"
#include "smartpointers.h"

//-------------------------------------------------------------------//
/// @file testEnemy.h
/// @brief CONCRETE TYPE This is a simple example of a TestEnemy class
/// @author Jared Auty
/// @version 1
/// @date 22/11/12
/// Revision History :
/// Initial Version 22/11/12
/// @class TestEnemy
//-------------------------------------------------------------------//

DECLARESMART(TestEnemy)

//-------------------------------------------------------------------//
/// @class TestEnemy this class implements the basic enemy type
//-------------------------------------------------------------------//
class TestEnemy : public Enemy
{
public:

  //-------------------------------------------------------------------//
  /// @brief creator
  /// @param[in] _pos initital position of TestEnemy
  /// @param[in] _aim where the enemy is aiming
  /// @param[in] _id ID of entity
  //-------------------------------------------------------------------//
  static EntityPtr create(
        const ngl::Vec3 &_pos,
        const ngl::Vec3 &_aim,
        unsigned int _id
        );

  //-------------------------------------------------------------------//
  /// @brief destructor
  //-------------------------------------------------------------------//

  ~TestEnemy();

  //-------------------------------------------------------------------//
  /// @brief initialise all the state values
  //-------------------------------------------------------------------//
  void stateInit();

  //-------------------------------------------------------------------//
  /// @brief draw the object
  //-------------------------------------------------------------------//

  void draw();

protected:

  //-------------------------------------------------------------------//
  /// @brief filter the visible entities
  //-------------------------------------------------------------------//
  void filterViewVolume(EntityRecordWCList &o_localEntities);

  //-------------------------------------------------------------------//
  /// @brief ctor
  /// @param[in] _pos initital position of TestEnemy
  /// @param[in] _aim where the enemy is aiming
  /// @param[in] _id ID of entity
  //-------------------------------------------------------------------//

  TestEnemy(
        const ngl::Vec3 &_pos,
        const ngl::Vec3 &_aim,
        unsigned int _id
        );

  //-------------------------------------------------------------------//
  /// @brief works out which direction the TestEnemy should go in next
  /// @param[out] new vector for TestEnemy to travel in
  //-------------------------------------------------------------------//
  ngl::Vec3 brain();
};

#endif // TESTENEMY_H
