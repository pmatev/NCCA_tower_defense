#include "uibutton.h"
#include "renderer.h"


//-------------------------------------------------------------------//
UIButton::UIButton(ngl::Vec2 _pos,
                   std::string _imageFile,
                   std::string _name):

UIElement( _pos, _imageFile, _name)
{
    //variables initialised before the constructor body

}



//-------------------------------------------------------------------//


UIButton::~UIButton()
{
    std::cout<<"button dtor called"<<std::endl;

}


//-------------------------------------------------------------------//


void UIButton::draw()
{
  Renderer *r = Renderer::instance();
  r->loadMatrixToShaderSS(m_transformStack, "Phong");
  r->draw(m_IDStr, "Phong");

}


//-------------------------------------------------------------------//

void UIButton::drawSelection()
{
  Renderer *r = Renderer::instance();
  r->loadMatrixToShaderSS(m_transformStack, "Colour");
  r->drawSelection(m_ID, m_IDStr);
}
