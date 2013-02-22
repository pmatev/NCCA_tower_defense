#include "window.h"
#include "game.h"
#include "renderer.h"
#include "boost/lexical_cast.hpp"
#include "fwd/entity.h"
#include "uiSelection.h"
#include "uibutton.h"


UISelection::UISelection():
  m_creationMode(false)
//  m_selectedNode(NodePtr())
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
    if(it == m_IDMap.end())
    {
      return UIElementPtr();
    }
    return it->second;
}




//-------------------------------------------------------------------//

EntityWPtr UISelection::checkEntityClicked()
{

    Game *game = Game::instance();
    Window *window = Window::instance();

    unsigned int id = window->getIDFromGameSelection();

    return game->getEntityByID(id);
}






//-------------------------------------------------------------------//
void UISelection::mouseLeftUp(const unsigned int _ID)
{


    if(m_creationMode == 0)
    {
        UIElementPtr UIClick = checkUIClicked(_ID);

        EntityPtr entityClick;
        std::cout<<_ID<<std::endl;
        if(!UIClick)
        {
            entityClick = checkEntityClicked().lock();

            if(!entityClick)
            {
              std::cout<<"i am background"<<std::endl;
            }
            else
            {
              switch(entityClick->getGeneralType())
              {
              case NODE: std::cout<<"i am node"<<std::endl; break;
              case  ENEMY: std::cout<<"i am enemy"<<std::endl; break;
              case  TURRET: std::cout<<"i am turret"<<std::endl;break;
              case  BASE: std::cout<<"i am base"<<std::endl;break;
              case PROJECTILE: break;
              case WALL: break;



              }//display the upgrade menu as the tower is selected
                //need to also boost dynamic cast into a static object
                //as I need to make sure that it is a staticEntity
                //so I can upgrade a tower!
            }
        }
        else
        {
            UIClick->isClicked();
            std::cout<<"i am GUI"<<std::endl;
        }
    }

    else
    {
        EntityPtr entityClick;

        entityClick = checkEntityClicked().lock();

        if(!entityClick)
        {
            if(entityClick->getGeneralType() == NODE)
            {
                placeDownStaticEntity(
                           m_staticEntityTypeTemp,
                           boost::dynamic_pointer_cast<Node>(entityClick)
                            );
            }
        }
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

        return UIMenuPtr();
    }

    return UIMenuPtr();
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

void UISelection::placeDownStaticEntity(const std::string &_type, NodePtr _node)
{
    Game* game = Game::instance();

    bool isCreated = game->tryToCreateTower(_type, _node);

    if(isCreated == true)
    {
        m_creationMode = false;

        std::cout<<"tower was created properly"<<std::endl;
    }
}


//-------------------------------------------------------------------//

void UISelection::mouseMoveEvent()
{
    if(m_creationMode == true)
    {
        EntityPtr entityClick;

        entityClick = checkEntityClicked().lock();

        if(entityClick)
        {
            int id = entityClick->getID();

            if(entityClick->getGeneralType() == NODE &&
                    id != m_highlightedNode)
            {

                std::cout<<entityClick->getID()<<std::endl;

                //grab instance of game
                Game* game = Game::instance();

                //set existing nodes flag to false
                game->setNodehighlighted(m_highlightedNode, false);

                //set new nodes flag to true
                game->setNodehighlighted(id, true);

                m_highlightedNode = id;
            }
        }
    }
}




//-------------------------------------------------------------------//
//----------------------Test Function for Jared----------------------//
//-------------------------------------------------------------------//
void UISelection::mouseLeftUpTowerCreate(const unsigned int _ID)
{

    UIElementPtr UIClick = checkUIClicked(_ID);

    EntityPtr entityClick;
    std::cout<<_ID<<std::endl;
    if(!UIClick)
    {
        entityClick = checkEntityClicked().lock();

        if(!entityClick)
        {
          std::cout<<"i am background"<<std::endl;
        }
        else
        {
            if(entityClick->getGeneralType() == NODE)
            {
                Game* game = Game::instance();

                NodePtr node = boost::dynamic_pointer_cast<Node>(entityClick);

                bool isCreated = game->tryToCreateTower("TestTurret",
                                                         node);

                if(isCreated == true)
                {
                    //m_creationMode = 0;

                    std::cout<<"tower was created properly"<<std::endl;
                }

            }
            else
            {
                std::cout<<"i'm not a node"<<std::endl;
            }

        }

    }
    else
    {
//        UIClick->isClicked();
        std::cout<<"i am GUI"<<std::endl;
    }
}

//-------------------------------------------------------------------//
//-------------------------------------------------------------------//
//-------------------------------------------------------------------//



//-------------------------------------------------------------------//
//-------------------------Test Function-----------------------------//
//-------------------------------------------------------------------//

void UISelection::printTest()
{
    m_staticEntityTypeTemp = "testTurret";
    std::cout<<m_staticEntityTypeTemp<<std::endl;
}



//-------------------------------------------------------------------//
//-------------------------Test Function-----------------------------//
//-------------------------------------------------------------------//

void UISelection::printTest2()
{
    std::cout<<"\nThis is test function number 2 "<<std::endl;
}


//-------------------------------------------------------------------//
//-------------------------Test Function-----------------------------//
//-------------------------------------------------------------------//

void UISelection::createTestTower()
{

    m_creationMode = true;
    m_staticEntityTypeTemp = "testTurret";
}

//-------------------------------------------------------------------//
//-------------------------Test Function-----------------------------//
//-------------------------------------------------------------------//

void UISelection::createTestMenu()
{
    createMenu(UIMenuPtr(new UIMenu(ngl::Vec2 (2,5), "hello", "menuTest",this)));

    UIMenuPtr menu = getMenu("menuTest");
    if(!menu)
    {
        std::cout<<"not a menu in UISelection"<<std::endl;
    }
    else
    {
//        menu->addButton(ngl::Vec2 (5,3), "hello", "buttonTest");

//        menu->connectEvent(boost::bind(&UISelection::printTest, this), "buttonTest");

//        menu->runCommandTest();
    }
}




