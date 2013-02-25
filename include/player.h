#ifndef PLAYER_H
#define PLAYER_H

#include "smartpointers.h"

//-------------------------------------------------------------------//
/// @file player.h
/// @brief The class which contains information about the player
/// @author Peter May
/// @version 1
/// @date 25/02/2013
/// Revision History :
/// Initial Version 25/02/2013
/// @class Player
//-------------------------------------------------------------------//

DECLARESMART(Player)

class Player
{
public: //methods
  //-------------------------------------------------------------------//
  /// @brief creation method, returns a smart pointer to the object created
  /// @param [in] _startCurrency, the initial amount of money that the
  /// player has
  //-------------------------------------------------------------------//

  static PlayerPtr create(int _startCurrency);

  //-------------------------------------------------------------------//
  /// @brief a method to set the player's currency value
  /// @param [in] _newCurrency, the value to set the currency to
  //-------------------------------------------------------------------//

  inline void setCurrency(int _newCurrency) {m_currency = _newCurrency;}

  //-------------------------------------------------------------------//
  /// @brief a method to add the offset to the currency value, so a
  /// positive number increases the currency ans a negative one decreases
  /// it
  /// @param [in] _offset, the value to offset the currency by
  //-------------------------------------------------------------------//

  inline void addCurrency (int _offset) {m_currency += _offset;}

  //-------------------------------------------------------------------//
  /// @brief a method to return the currency
  /// @param [out] the current currency value
  //-------------------------------------------------------------------//

  inline int getCurrency() const {return m_currency;}

protected: //methods

  //-------------------------------------------------------------------//
  /// @brief a parameterised constructor
  /// @param [in] _startCurrency, the initial amount of money that the
  /// player has
  //-------------------------------------------------------------------//

  Player(int _startCurrency);

protected: //attributes

  //-------------------------------------------------------------------//
  /// @brief The amount of money that the user has to spend
  //-------------------------------------------------------------------//

  int m_currency;

};

#endif // PLAYER_H