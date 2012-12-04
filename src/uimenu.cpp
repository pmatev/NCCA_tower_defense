#include "uimenu.h"
#include "game.h"
#include <iostream>
#include <boost/function.hpp>
#include <boost/bind.hpp>



//-------------------------------------------------------------------//

UIMenu::UIMenu()
{

}

UIButtonPtr UIMenu::returnClickedElement(const unsigned int _ID)
{
    buttonsMap::iterator it = m_buttons.find(_ID);

    return it->second;

}


//-------------------------------------------------------------------//

UIMenu::~UIMenu()
{

}


//-------------------------------------------------------------------//

void UIMenu::draw() const
{
    //drawing method
}

//-------------------------------------------------------------------//

void UIMenu::alignBottom()
{
   //will align the uimenu to the bottom of the window
}

//-------------------------------------------------------------------//


//void UIMenu::createButtonTest(ngl::Vec2 _pos, std::string _imageFile)
//{

//    m_buttonTest = UIButtonPtr(new UIButton(_pos, _imageFile));

//    m_buttonTest->execute = boost::bind(&UIMenu::printTest, this);

//    m_buttonTest->execute();



//}


//-------------------------------------------------------------------//

void UIMenu::printTest()
{
    std::cout<<"it's working and the filename is "<<std::endl;
}





