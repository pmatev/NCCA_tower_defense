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
//    std::cout<<"button dtor called"<<std::endl;

}

//-------------------------------------------------------------------//
void UIButton::draw()
{

//IN THIS FUNCTION NEED TO SET UP ISPRESSED RENDER


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
      if(m_hover == false)
      {
          tex->bindTexture(m_imageFile);
      }
      else
      {
          tex->bindTexture(m_imageFile +"Hover");
      }
  }

  if(m_label)
  {
      m_label->draw();
  }
      m_billboard->draw("UI");
//  render->draw(m_IDStr, "UI");
}


//-------------------------------------------------------------------//
void UIButton::createLabel
(
    ngl::Vec2 _pos,
    const char *_text,
    const char *_fontFile,
    int _ptsize,
    std::string _name,
    LabelPosition _position
    )
{

    Window* window = Window::instance();
    int id = window->getID();
    m_label = TextPtr(new Text(_pos,_text,_fontFile,_ptsize,_name));
    m_label->setID(id);
    m_labelPosition = _position;
    std::cout<<"text created"<<std::endl;

    if(m_label)
    {
        if(_position == LEFT)
        {
            m_boundSize.m_x = m_size.m_x+m_label->getSize().m_x;
            if(m_size.m_y > m_label->getSize().m_y)
            {
                m_boundSize.m_y = m_size.m_y;
            }
            else
            {
                m_boundSize.m_y = m_label->getSize().m_y;
            }

        }
        if(_position == RIGHT)
        {

            m_boundSize.m_x = m_size.m_x+m_label->getSize().m_x;

            if(m_size.m_y > m_label->getSize().m_y)
            {
                m_boundSize.m_y = m_size.m_y;
            }
            else
            {
                m_boundSize.m_y = m_label->getSize().m_y;
            }
        }
        if(_position == TOP)
        {

            m_boundSize.m_y = m_size.m_y+m_label->getSize().m_y;
            if(m_size.m_x > m_label->getSize().m_x)
            {
                m_boundSize.m_x = m_size.m_x;
            }
            else
            {
                m_boundSize.m_x = m_label->getSize().m_x;
            }
        }
        if(_position == BOTTOM)
        {
            m_boundSize.m_y = m_size.m_y+m_label->getSize().m_y;
            if(m_size.m_x > m_label->getSize().m_x)
            {
                m_boundSize.m_x = m_size.m_x;
            }
            else
            {
                m_boundSize.m_x = m_label->getSize().m_x;
            }
        }
        setLabelPosition();
    }
}

//-------------------------------------------------------------------//
void UIButton::setPosition(ngl::Vec2 _pos)
{
    if(m_label)
    {
        if(m_labelPosition == LEFT)
        {
            m_pos.m_x = (m_label->getSize().m_x+5)+_pos.m_x;
            m_pos.m_y = _pos.m_y;
        }
        else if(m_labelPosition == RIGHT)
        {
            m_pos = _pos;
        }
        else if(m_labelPosition == TOP)
        {
            m_pos = _pos;

        }
        else if(m_labelPosition == BOTTOM)
        {
            m_pos.m_y = (m_label->getSize().m_y+5)+_pos.m_y;
            m_pos.m_x = _pos.m_x;
        }

        setLabelPosition();
    }
    else
    {
        m_pos = _pos;
    }
}

//-------------------------------------------------------------------//
void UIButton::setLabelPosition()
{
    ngl::Vec2  tmpPos;

    if(m_label)
    {
        if(m_labelPosition == LEFT)
        {
            tmpPos.m_x = (m_pos.m_x)-m_label->getSize().m_x;
            tmpPos.m_y = m_pos.m_y+((m_size.m_y-m_label->getSize().m_y)/2);

        }
        else if(m_labelPosition == RIGHT)
        {
            tmpPos.m_x = (m_pos.m_x+m_size.m_x);
            tmpPos.m_y = m_pos.m_y+((m_size.m_y-m_label->getSize().m_y)/2);

        }
        else if(m_labelPosition == TOP)
        {
            tmpPos.m_y = (m_pos.m_y+m_size.m_y);
            tmpPos.m_x = m_pos.m_x+((m_size.m_x-m_label->getSize().m_x)/2);

        }
        else if(m_labelPosition == BOTTOM)
        {
            tmpPos.m_y = (m_pos.m_y)-m_label->getSize().m_y;
            tmpPos.m_x = m_pos.m_x+((m_size.m_x-m_label->getSize().m_x)/2);
        }

        m_label->setPosition(tmpPos);
    }
}






