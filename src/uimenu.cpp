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

void UIMenu::alignBottom()
{
   //will align the uimenu to the bottom of the window
}



//-------------------------------------------------------------------//

void UIMenu::addButton(UIButtonPtr _button)
{
    m_elements.push_back(_button);
    _button->setPosition(m_pos);
    std::cout<<"button created"<<std::endl;
}

//-------------------------------------------------------------------//

void UIMenu::isClicked()
{
    //this class needs no execute function but as it is virtual it needs
    //to be implemented
}

//-------------------------------------------------------------------//

void UIMenu::connect(functionPtr _func, std::string _name)
{
    for(elementsMap::iterator it = m_elements.begin();
        it != m_elements.end();
        ++it)
    {
        std::cout<<"\nrunning through elements"<<std::endl;

        if(_name == (*it)->getName())
        {
            std::cout<<"\nfound name"<<std::endl;
            (*it)->setFunction(_func);
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
        std::cout<<"\nthis is running the function"<<std::endl;
        (*it)->isClicked();
        break;

    }
}


void UIMenu::setFunction(functionPtr _func)
{
    std::cout<<"\nyou cannot add a function to a menu class stupid"<<std::endl;

}









