#ifndef TESTENEMY_H
#define TESTENEMY_H

#include "enemy.h"
#include "smartpointers.h"

//-------------------------------------------------------------------//
/// @file TestEnemy.h
/// @brief CONCRETE TYPE This is a simple example of a TestEnemy class
/// @author Jared Auty
/// @version 1
/// @date 22/11/12
/// Revision History :
/// Initial Version 22/11/12
/// @class TestEnemy
//-------------------------------------------------------------------//

DECLARESMART(TestEnemy)

class TestEnemy : public Enemy
{
public:

  //-------------------------------------------------------------------//
  /// @brief creator
  /// @param[in] _damage, damage that TestEnemy can do
  /// @param[in] _maxVelocity, maximum velocity an TestEnemy can travel at
  /// @param[in] _pos, initital position of TestEnemy
  /// @param[in] _initialVelocity, the starting velocity of the TestEnemy
  //-------------------------------------------------------------------//
  static EntityPtr create(
      float _damage,
      float _maxVelocity,
      const ngl::Vec3 & _pos,
      float _initialVelocity,
      const ngl::Vec3 &_aim
      );


  void generateMesh();


  //-------------------------------------------------------------------//
  /// @brief draw the object
  //-------------------------------------------------------------------//

  void draw() ;

  //-------------------------------------------------------------------//
  /// @brief draw the object based on id
  //-------------------------------------------------------------------//

  void drawSelection() ;

protected:
  //-------------------------------------------------------------------//
  /// @brief ctor
  /// @param[in] _damage, damage that TestEnemy can do
  /// @param[in] _maxVelocity, maximum velocity an TestEnemy can travel at
  /// @param[in] _pos, initital position of TestEnemy
  /// @param[in] _initialVelocity, the starting velocity of the TestEnemy
  //-------------------------------------------------------------------//

  TestEnemy(
      float _damage,
      float _maxVelocity,
      const ngl::Vec3 &_pos,
      float _initialVelocity,
      const ngl::Vec3 &_aim
      );

  //-------------------------------------------------------------------//
  /// @brief works out which direction the TestEnemy should go in next
  /// @param[out] new vector for TestEnemy to travel in
  //-------------------------------------------------------------------//

  ngl::Vec3 brain();

  bool m_active;
};

#endif // TESTENEMY_H
