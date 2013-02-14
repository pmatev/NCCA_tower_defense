#include "uibutton.h"
#include "renderer.h"
#include "SDL_opengl.h"
#include "uimenu.h"


//-------------------------------------------------------------------//
UIButton::UIButton(ngl::Vec2 _pos,
                   std::string _imageFile,
                   std::string _name, UIMenu *_parent):

UIElement( _pos, _imageFile, _name)

{
  m_parent = _parent;
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
  ngl::Transformation parentTX = m_parent->getTransformStack().getCurrentTransform();
  m_transformStack.setGlobal(parentTX);
  m_transformStack.pushTransform();
    m_transformStack.setPosition(1.0,0.0,-1.0);
  m_transformStack.popTransform();

  Renderer *r = Renderer::instance();
  //r->loadMatrixToShaderSS(m_transformStack, "Phong");
  r->set2DPosToShader(m_pos, "UI");
  r->draw(m_IDStr, "UI");

}


//-------------------------------------------------------------------//

void UIButton::drawSelection()
{
  Renderer *r = Renderer::instance();
  //r->loadMatrixToShaderSS(m_transformStack, "Colour");
  r->drawSelection(m_ID, m_IDStr);
}
