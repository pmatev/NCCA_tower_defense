#include "include/game.h"
#include <iostream>
#include <ngl/Text.h>

//-------------------------------------------------------------------//
Game::Game(WindowPtr _parent)
{
    m_parent = _parent;
}
//-------------------------------------------------------------------//
Game::~Game()
{
}
//-------------------------------------------------------------------//
GamePtr Game::create(WindowPtr _parent)
{
    GamePtr a(new Game(_parent));
    return a;
}
//-------------------------------------------------------------------//
void Game::run()
{
    // game logic code
}
//-------------------------------------------------------------------//
void Game::update(const double _t)
{
    //std::cout<<_t<<std::endl;
}
//-------------------------------------------------------------------//
void Game::draw()
{

}
//-------------------------------------------------------------------//