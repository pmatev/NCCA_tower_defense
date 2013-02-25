#include "player.h"

//-------------------------------------------------------------------//

Player::Player(int _startCurrency) :
  m_currency(_startCurrency)
{
  //currently nothing in the constructor
}

//-------------------------------------------------------------------//

PlayerPtr Player::create(int _startCurrency)
{
  PlayerPtr player(new Player(_startCurrency));
  return player;
}

//-------------------------------------------------------------------//

