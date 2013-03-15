#include "uibutton.h"
#include "renderer.h"
#include "ngl/ShaderLib.h"
#include "texturelib.h"
#include "window.h"


//-------------------------------------------------------------------//
UIButton::UIButton
(
    ngl::Vec2 _pos,
    std::string _imageFile,
    std::string _name,
    float _maxX,
    float _maxY
    ):

    UIElement( _pos, _name, "button", _imageFile),
    m_isPressed(false)

{
    m_size.m_x = _maxX;
    m_size.m_y = _maxY;
    m_execute = boost::bind(&UIButton::blankFunction
                , this);
}

//-------------------------------------------------------------------//
UIButton::UIButton
(
        ngl::Vec2 _pos,
        std::string _imageFile,
        std::string _name,
        std::string _type,
        float _maxX,
        float _maxY
        ):

UIElement( _pos, _name, _type, _imageFile)

{
m_size.m_x = _maxX;
m_size.m_y = _maxY;
m_execute = boost::bind(&UIButton::blankFunction
            , this);
}

//-------------------------------------------------------------------//
void UIButton::blankFunction()
{

}

//-------------------------------------------------------------------//
UIButton::~UIButton()
{
    std::cout<<"button dtor called"<<std::endl;

}

//-------------------------------------------------------------------//
void UIButton::draw()
{

//IN THIS FUNCTION NEED TO SET UP ISPRESSED RENDER

  glDisable(GL_DEPTH_TEST);

  Renderer *render = Renderer::instance();
  Window *window = Window::instance();
  ngl::ShaderLib *shader=ngl::ShaderLib::instance();

  GLfloat scaleX = 2.0/window->getScreenWidth();
  GLfloat scaleY = 2.0/window->getScreenHeight();


  (*shader)["UI"]->use();

  shader->setRegisteredUniform1f("xpos",m_pos.m_x);
  shader->setRegisteredUniform1f("ypos",m_pos.m_y);
  shader->setRegisteredUniform1f("scaleX",scaleX);
  shader->setRegisteredUniform1f("scaleY",scaleY);

  ngl::Vec3 c = Window::instance()->IDToColour(m_ID);
  shader->setRegisteredUniform4f("colourSelect", c.m_x/255.0f, c.m_y/255.0f, c.m_z/255.0f, 1);

  TextureLib *tex = TextureLib::instance();

  if(m_isPressed == false)
  {
      tex->bindTexture(m_imageFile);

  }

  render->draw(m_IDStr, "UI");

  glEnable(GL_DEPTH_TEST);
}


//-------------------------------------------------------------------//

