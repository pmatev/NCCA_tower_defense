#include "uimenu.h"
#include "game.h"


#include <iostream>
#include <boost/function.hpp>
#include <boost/bind.hpp>



//-------------------------------------------------------------------//

UIMenu::UIMenu(ngl::Vec2 _pos,
               std::string _imageFile,
               std::string _name):


UIElement( _pos, _imageFile, _name)

{
    //variables initialised before the constructor body
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

void UIMenu::drawSelection()
{
    //do something
}

//-------------------------------------------------------------------//

void UIMenu::alignBottom()
{
   //will align the uimenu to the bottom of the window when draw has been set
   //up
}



//-------------------------------------------------------------------//

void UIMenu::addButton(UIButtonPtr _button)
{
    m_elements.push_back(_button);
    _button->setPosition(m_pos);
    std::cout<<"\nbutton created"<<std::endl;
}

//-------------------------------------------------------------------//

void UIMenu::isClicked()
{
    //this class needs no execute function but as it is virtual it needs
    //to be implemented
}

//-------------------------------------------------------------------//

void UIMenu::connectEvent(functionPtr _func, std::string _name)
{
    for(elementsMap::iterator it = m_elements.begin();
        it != m_elements.end();
        ++it)
    {

        if(_name == (*it)->getName())
        {

            (*it)->setFunction(_func);
            std::cout<<"\nfunction set"<<std::endl;
            break;
        }

    }
}

//-------------------------------------------------------------------//

void UIMenu::runCommandTest()
{
    for(elementsMap::iterator it = m_elements.begin();
        it != m_elements.end();
        ++it)
    {

        (*it)->isClicked();

    }
}

//-------------------------------------------------------------------//

void UIMenu::setFunction(functionPtr _func)
{
    //displays that this function will not do anything as menus do not have functions
    std::cout<<_func<<"\nyou cannot add a function to a menu class stupid"<<std::endl;

}









