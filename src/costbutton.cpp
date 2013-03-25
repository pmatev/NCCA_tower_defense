#include "costbutton.h"
#include "game.h"
#include "texturelib.h"

//---------------------------------------------------------------------//
CostButton::CostButton
(
    ngl::Vec2 _pos,
    std::string _imageFile,
    std::string _name,
    ElementType _type,
    int _cost,
    float _maxX,
    float _maxY
    ):

    UIButton
    (
        _pos,
        _imageFile,
        _name,
        _type,
        _maxX,
        _maxY
        ),
    m_cost(_cost)
{
    checkAffordable();
}

//---------------------------------------------------------------------//
CostButton::~CostButton()
{

}

//---------------------------------------------------------------------//
void CostButton::checkAffordable()
{
    if(Game::instance()->getPlayerCurrency()-m_cost >= 0)
    {
        if(m_buttonState != DISABLE)
        {
            m_buttonState = m_buttonState;
        }
        else
        {
            m_buttonState = DEFAULT;
        }
        m_affordable = true;
    }
    else
    {
        m_buttonState = DISABLE;
        m_affordable = false;
    }
}




