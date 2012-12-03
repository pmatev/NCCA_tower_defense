#include "include/game.h"
#include <iostream>
#include <ngl/Camera.h>


Game* Game::s_instance = 0;

//-------------------------------------------------------------------//
Game::Game()
{
}
//-------------------------------------------------------------------//
Game::~Game()
{
}
//-------------------------------------------------------------------//
Game* Game::instance()
{
    if(s_instance == 0)
    {
        s_instance = new Game();
    }
    return s_instance;

}
//-------------------------------------------------------------------//
void Game::destroy()
{
    if (s_instance)
    {
          delete s_instance;
    }
}
//-------------------------------------------------------------------//
unsigned int Game::registerID(EntityPtr _e)
{
    m_currentID++;

    m_IDMap[m_currentID] = _e;

    return m_currentID;
}
//-------------------------------------------------------------------//
void Game::unregisterID(const unsigned int _i)
{
    m_IDMap.erase(_i);
}

//-------------------------------------------------------------------//
EntityPtr Game::getEntityByID(const unsigned int _i)
{
    return m_IDMap.find(_i)->second;
}


//-------------------------------------------------------------------//
void Game::run()
{
    // game logic code
}
//-------------------------------------------------------------------//
void Game::update(const double _t)
{
    // update code by timestep _t
}
//-------------------------------------------------------------------//
void Game::draw()
{
    // draw code

}
//-------------------------------------------------------------------//
