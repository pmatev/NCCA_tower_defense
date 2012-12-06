#include "uiSelection.h"

#include "game.h"

UISelection* UISelection::s_instance = 0;


UISelection::UISelection()
{

}


//-------------------------------------------------------------------//

UISelection* UISelection::instance()
{
    if(s_instance == 0)
    {
        s_instance = new UISelection();
    }
    return s_instance;

}

//-------------------------------------------------------------------//

unsigned int UISelection::registerID(UIElementPtr _e)
{
    m_currentID++;

    m_IDMap[m_currentID] = _e;

    return m_currentID;
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

    Game* game = Game::instance();

    return game->getEntityByID(_ID);

}



//-------------------------------------------------------------------//

void UISelection::mouseLeftUp(const unsigned int _ID)
{
    if(m_creationMode == 0)
    {
        UIElementPtr UIClick = checkUIClicked(_ID);

        EntityPtr entityClick;

        if(UIClick)
        {
            entityClick = checkEntityClicked(_ID);

            if(entityClick->getGeneralType() != NODE && entityClick)
            {
                // display the upgrade menu as the tower is selected
                //need to also boost dynamic cast into a static object
                //as I need to make sure that it is a staticEntity
                //so I can upgrade a tower!
            }

        }
        else
        {
            UIClick->isClicked();
        }
    }
    else
    {
        //createStaticEntity(_ID);
    }


}

//-------------------------------------------------------------------//

UISelection::~UISelection()
{
    for(elementsMap::iterator it = m_IDMap.begin();
        it != m_IDMap.end();
        ++it)
    {

    }

}

//-------------------------------------------------------------------//

void UISelection::draw()
{

    for(elementsMap::iterator it = m_IDMap.begin();
        it != m_IDMap.end();
        ++it)
    {
        UIElementPtr drawEl = (*it).second;
        drawEl->draw();

        std::cout<<"\n"<<(drawEl)->getName()<< " drawn"<<std::endl;
    }

}

//-------------------------------------------------------------------//

void UISelection::drawSelection()
{

    for(elementsMap::iterator it = m_IDMap.begin();
        it != m_IDMap.end();
        ++it)
    {
        UIElementPtr drawEl = (*it).second;
        drawEl->drawSelection();

        std::cout<<"\n"<<(drawEl)->getName()<< " drawn selection"<<std::endl;
    }

}


//-------------------------------------------------------------------//

void UISelection::createStaticEntity(const unsigned int _ID)
{
    Game* game = Game::instance();


    //get current node that mouse is on

    //check if the static entity can be placed down

    //call to environment to add entity to list

    //if add was successful delete static entity

    //m_creationMode = 0;
}



//-------------------------------------------------------------------//

void UISelection::createTestMenu()
{
    m_menuTest = UIMenuPtr(new UIMenu(ngl::Vec2 (2,5), "hello", "menuTest"));

    m_menuTest->addButton(UIButtonPtr(new UIButton(ngl::Vec2 (5,8), "hello","buttonTest")));

    m_menuTest->addButton(UIButtonPtr(new UIButton(ngl::Vec2 (5,8), "hello","buttonTest2")));

    m_menuTest->connectEvent(boost::bind(&UISelection::printTest, this), "buttonTest");

    m_menuTest->connectEvent(boost::bind(&UISelection::printTest2, this), "buttonTest2");

    m_menuTest->runCommandTest();

    draw();

    drawSelection();


}


//-------------------------------------------------------------------//
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
