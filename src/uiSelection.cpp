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

        if(UIClick == 0)
        {
            entityClick = checkEntityClicked(_ID);

            if(entityClick != 0)
            {
                // display the upgrade menu as the tower is selected
            }

        }
        else
        {
            UIClick->isClicked();
        }
    }
    else
    {
        createStaticEntity();
    }


}


//-------------------------------------------------------------------//



UISelection::~UISelection()
{

}



//-------------------------------------------------------------------//

void UISelection::createStaticEntity()
{

    //get current node that mouse is on

    //check if the static entity can be placed down

    //call to environment to add entity to list

    //if add was successful delete static entity

    //m_creationMode = 0;
}



//-------------------------------------------------------------------//

void UISelection::createTestMen()
{
    m_menuTest = UIMenuPtr(new UIMenu(ngl::Vec2 (2,5), "hello", "menuTest"));

    m_menuTest->addButton(UIButtonPtr(new UIButton(ngl::Vec2 (5,8), "hello","buttonTest")));

    m_menuTest->connect(boost::bind(&UISelection::printTest, this), "buttonTest");

    m_menuTest->runCommandTest();


}


//-------------------------------------------------------------------//
void UISelection::printTest()
{
    std::cout<<"it's working and the filename is "<<std::endl;
}


