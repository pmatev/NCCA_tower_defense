#include "uiSelection.h"
#include "window.h"
#include "game.h"
#include "fwd/entity.h"
#include "renderer.h"
#include "boost/lexical_cast.hpp"
#include "window.h"



UISelection::UISelection():
  m_creationMode(false)
{

}





//-------------------------------------------------------------------//
UISelection::~UISelection()
{
    std::cout<<"dtor called"<<std::endl;



}



//-------------------------------------------------------------------//

void UISelection::registerID(UIElementPtr _e, unsigned int _ID)
{

    m_IDMap[_ID] = _e;

}


//-------------------------------------------------------------------//

void UISelection::unregisterID(const unsigned int _i)
{
    m_IDMap.erase(_i);
}



//-------------------------------------------------------------------//

UIElementPtr UISelection::checkUIClicked(const unsigned int _ID)
{
    elementsMap::iterator it = m_IDMap.find(_ID);

    return it->second;
}



//-------------------------------------------------------------------//

EntityPtr UISelection::checkEntityClicked(const unsigned int _ID)
{

    Game *game = Game::instance();
//    Window *window = Window::instance();
//    Renderer *r = Renderer::instance();

//    game->drawSelection();

//    ngl::Vec3 pixel = r->readColourSelection(_event.x, _event.y);
//    unsigned int id = window->colourToID(pixel);

    return game->getEntityByID(_ID);

}



//-------------------------------------------------------------------//

void UISelection::mouseLeftUp(const unsigned int _ID)
{
    if(m_creationMode == 0)
    {
        UIElementPtr UIClick = checkUIClicked(_ID);

        EntityPtr entityClick;

        if(!UIClick)
        {
            entityClick = checkEntityClicked(_ID);

            if(entityClick->getGeneralType() != NODE && !entityClick)
            {
              std::cout<<"yes tower"<<std::endl;
                //display the upgrade menu as the tower is selected
                //need to also boost dynamic cast into a static object
                //as I need to make sure that it is a staticEntity
                //so I can upgrade a tower!
            }
            else
            {
              std::cout<<"no tower"<<std::endl;
            }

        }
        else
        {
            //UIClick->isClicked();
            std::cout<<"i am GUI"<<std::endl;
        }
    }
    else
    {
        //createStaticEntity(_ID);
    }
}


//-------------------------------------------------------------------//

void UISelection::draw()
{

    for(menuMap::iterator it = m_menus.begin();
        it != m_menus.end();
        ++it)
    {
        UIMenuPtr drawEl = (*it).second;
        drawEl->draw();

        //std::cout<<"\n"<<(drawEl)->getName()<< " drawn"<<std::endl;
    }

}

//-------------------------------------------------------------------//

void UISelection::drawSelection()
{

    for(menuMap::iterator it = m_menus.begin();
        it != m_menus.end();
        ++it)
    {
        UIElementPtr drawEl = (*it).second;
        drawEl->drawSelection();

        //std::cout<<"\n"<<(drawEl)->getName()<< " drawn selection"<<std::endl;
    }

}


//-------------------------------------------------------------------//

UIMenuPtr UISelection::getMenu(std::string _name)
{
    for(menuMap::iterator it = m_menus.begin();
        it != m_menus.end();
        ++it)
    {
        UIMenuPtr drawEl = (*it).second;
        if(drawEl->getName() == _name)
        {
            return drawEl;

        }

    }
}


//-------------------------------------------------------------------//

void UISelection::createMenu(UIMenuPtr _menu)
{
    Window *window= Window::instance();
    int ID = window->getID();
    _menu->setID(ID);
    registerID(_menu, ID);
    m_menus[_menu->getID()] = _menu;
    std::cout<<"\nmenu created"<<std::endl;
}



//-------------------------------------------------------------------//

void UISelection::createStaticEntity(const unsigned int _ID)
{
//    Game* game = Game::instance();


    //get current node that mouse is on

    //check if the static entity can be placed down

    //call to environment to add entity to list

    //if add was successful delete static entity

    //m_creationMode = 0;
}




void UISelection::printTest()
{
    std::cout<<"\nthis is the test function "<<std::endl;
}


//-------------------------------------------------------------------//
void UISelection::printTest2()
{
    std::cout<<"\nThis is test function number 2 "<<std::endl;
}


//-------------------------------------------------------------------//
void UISelection::createTower(std::string _type,
                                  NodePtr _node)
{

    // need to check this as jarad is unsure of creating a hard copy
    m_staticEntityTemp = EntityFactory::createStaticEntity( _type,  _node);

}


//-------------------------------------------------------------------//
//-------------------------Test Function-----------------------------//
//-------------------------------------------------------------------//

void UISelection::createTestMenu()
{
    createMenu(UIMenuPtr(new UIMenu(ngl::Vec2 (2,5), "hello", "menuTest",this)));

    getMenu("menuTest")->addButton(UIButtonPtr(new UIButton(ngl::Vec2 (5,8), "hello","buttonTest")));

    getMenu("menuTest")->addButton(UIButtonPtr(new UIButton(ngl::Vec2 (5,8), "hello","buttonTest2")));

    getMenu("menuTest")->connectEvent(boost::bind(&UISelection::printTest, this), "buttonTest");

    getMenu("menuTest")->connectEvent(boost::bind(&UISelection::printTest2, this), "buttonTest2");

    getMenu("menuTest")->runCommandTest();


}

//-------------------------------------------------------------------//
//-------------------------------------------------------------------//
//-------------------------------------------------------------------//


//-------------------------------------------------------------------//
//-------------------------Test Function-----------------------------//
//-------------------------------------------------------------------//
//void UISelection::createMenu()
//{
//    Window *window = Window::instance();

//    for(int i=0; i<10; i++)
//    {
//        UIMenuPtr _menu = (UIMenuPtr(new UIMenu(ngl::Vec2 (2,5), "hello", "menuTest"+
//                                           boost::lexical_cast<std::string>(i))));
//        int ID = window->registerID(_menu);
//        _menu->setID(ID);

//        m_menus[_menu->getID()] = _menu;
//        std::cout<<"\nmenu created"<<std::endl;
//        _menu->createButtons();
//    }

//}
//-------------------------------------------------------------------//
//-------------------------------------------------------------------//
//-------------------------------------------------------------------//

