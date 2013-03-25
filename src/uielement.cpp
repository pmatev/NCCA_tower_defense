#include "uielement.h"
#include "renderer.h"
#include <boost/lexical_cast.hpp>
#include <QImage>
#include "texturelib.h"
#include <ngl/ShaderLib.h>
#include "window.h"

//-------------------------------------------------------------------//

UIElement::UIElement(ngl::Vec2 _pos,
                     std::string _name,
                     ElementType _type,
                     std::string _imageFile):
    m_name(_name),
    m_pos(_pos),
    m_type(_type),
    m_imageFile(_imageFile),
    m_tileable(false)
{
}

//-------------------------------------------------------------------//
void UIElement::setID(unsigned int _ID)
{
  m_ID = _ID;
  m_IDStr = boost::lexical_cast<std::string>(m_ID);
  generateMesh();
}

//-------------------------------------------------------------------//
void UIElement::setPosition(ngl::Vec2 _pos)
{
    m_pos = _pos;
}

//-------------------------------------------------------------------//
void UIElement::draw()
{

    Window *window = Window::instance();
    ngl::ShaderLib *shader=ngl::ShaderLib::instance();

    GLfloat scaleX = 2.0/window->getScreenWidth();
    GLfloat scaleY = 2.0/window->getScreenHeight();


    (*shader)["UI"]->use();

    shader->setRegisteredUniform1f("xpos",m_pos.m_x);
    shader->setRegisteredUniform1f("ypos",m_pos.m_y);
    shader->setRegisteredUniform1f("scaleX",scaleX);
    shader->setRegisteredUniform1f("scaleY",scaleY);

    TextureLib *tex = TextureLib::instance();

    tex->bindTexture(m_imageFile);

    m_billboard->draw("UI");

}

//-------------------------------------------------------------------//
void UIElement::generateMesh()
{


  m_billboard = Billboard::create(Billboard::b2D, ngl::Vec4(0,0,0,1),m_size.m_x, m_size.m_y);

}

//-------------------------------------------------------------------//


UIElement::~UIElement()
{

}
