#include "uibutton.h"
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


void UIButton::draw() const
{
    //needs to be implemented

}


//-------------------------------------------------------------------//

void UIButton::drawSelection()
{
    //do something
}
