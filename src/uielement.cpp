#include "uielement.h"
#include "uiSelection.h"

//-------------------------------------------------------------------//

UIElement::UIElement(ngl::Vec2 _pos,
                     std::string _imageFile,
                     std::string _name):
  m_pos(_pos),
  m_imageFile(_imageFile),
  m_name(_name)

{
    UISelection* selection = UISelection::instance();
    m_ID = selection->registerID(UIElementPtr(this));
}

//-------------------------------------------------------------------//

void UIElement::setPosition(ngl::Vec2 _pos)
{
    m_pos += _pos;
}


//-------------------------------------------------------------------//
void UIElement::draw() const
{
    //need to implement
}



std::string UIElement::getImagefile()
{
    return m_imageFile;
}


UIElement::~UIElement()
{

}
