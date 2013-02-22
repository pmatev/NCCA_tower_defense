#include "game.h"
#include "renderer.h"
#include <iostream>
#include <boost/function.hpp>
#include <boost/bind.hpp>
#include "boost/lexical_cast.hpp"
#include "window.h"
#include "uiSelection.h"
#include "uimenu.h"
#include "uibutton.h"



//-------------------------------------------------------------------//

UIMenu::UIMenu(ngl::Vec2 _pos,
               std::string _imageFile,
               std::string _name,
               UISelection *_parent):


UIElement( _pos, _imageFile, _name)


{
  m_parent = _parent;
    //variables initialised before the constructor body
  m_transformStack.setPosition(0,-1,0);

}

//-------------------------------------------------------------------//

UIMenu::~UIMenu()
{
    std::cout<<"menu dtor called"<<std::endl;
    //m_elements.clear();

}


//-------------------------------------------------------------------//

void UIMenu::draw()
{
    glDisable(GL_DEPTH_TEST);
    Renderer *r = Renderer::instance();
    //r->loadMatrixToShaderSS(m_transformStack, "UI");
    setPosition(ngl::Vec2(0,-1));
    r->set2DPosToShader(m_pos, "UI");
    r->draw(m_IDStr, "UI");

//    for(int i=0; i<m_elements.size(); i++)
//    {
//        m_elements[i]->draw();
//    }
    glEnable(GL_DEPTH_TEST);
}


//-------------------------------------------------------------------//

void UIMenu::drawSelection()
{
    Renderer *r = Renderer::instance();

    //Q unused to remove warnings, will be replaced if used

    Q_UNUSED(r);

    //r->loadMatrixToShaderSS(m_transformStack, "Colour");
    //r->drawSelection(m_ID, m_IDStr);

//    for(int i=0; i<m_elements.size(); i++)
//    {
//        m_elements[i]->drawSelection();
//    }
}

//-------------------------------------------------------------------//

void UIMenu::alignBottom()
{
   //will align the uimenu to the bottom of the window when draw has been set
   //up
  m_transformStack.setPosition(0,-1,0);
}



//-------------------------------------------------------------------//

void UIMenu::addButton(ngl::Vec2 _pos,
                       std::string _imageFile,
                       std::string _name)
{
    Window* window = Window::instance();
    UIButtonPtr button = UIButtonPtr(new UIButton(_pos, _imageFile, _name, this));
    m_elements.push_back(button);
    int ID = window->getID();
    m_parent->registerID(button, ID);
    button->setID(ID);
    button->setPosition(m_pos);
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


//-------------------------------------------------------------------//
//-------------------------Test Function-----------------------------//
//-------------------------------------------------------------------//

//void UIMenu::createButtons()
//{
//    UISelection* selection = UISelection::instance();
//    for(int i=0; i<10; i++)
//    {
//        UIButtonPtr _button = (UIButtonPtr(new UIButton(ngl::Vec2 (5,8), "hello",
//                                            "buttonTest"+boost::lexical_cast<std::string>(i))));
//        int ID = selection->registerID(_button);
//        _button->setID(ID);
//        m_elements.push_back(_button);
//        std::cout<<"\nbutton created"<<std::endl;
//    }

//}

//-------------------------------------------------------------------//
//-------------------------------------------------------------------//
//-------------------------------------------------------------------//








