#include "createtowerbutton.h"
#include "game.h"
#include "texturelib.h"

//---------------------------------------------------------------------//
CreateTowerButton::CreateTowerButton(ngl::Vec2 _pos,
                                     std::string _imageFile,
                                     std::string _name,
                                     TablePtr _parent,
                                     int _cost,
                                     std::string _towerType,
                                     float _maxX, float _maxY
                                     ):

    UIButton
    (
        _pos,
        _imageFile,
        _name,
        "create",
        _parent,
        _maxX,
        _maxY
        ),
    m_cost(_cost),
    m_towerType(_towerType)
{
    checkAffordable();
}

//---------------------------------------------------------------------//
CreateTowerButton::~CreateTowerButton()
{

}

//---------------------------------------------------------------------//
void CreateTowerButton::checkAffordable()
{
    if(Game::instance()->getPlayerCurrency()-m_cost >= 0)
    {
        m_affordable = true;
    }
    else
    {
        m_affordable = false;
    }
}



