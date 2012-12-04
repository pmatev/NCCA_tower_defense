#include "uiSelection.h"

#include "game.h"


UISelection::UISelection()
{

}

//-------------------------------------------------------------------//

UIButtonPtr UISelection::checkUIClicked(const unsigned int _ID)
{
    UIButtonPtr menuClickCheck;
    UIMenuPtr selectedMenu;

    menuMap::iterator it;

    while(menuClickCheck == 0 && it != m_menus.end())

    {
        selectedMenu = it->second;
        menuClickCheck = selectedMenu->returnClickedElement(_ID);
        it++;
    }

    return menuClickCheck;
}



//-------------------------------------------------------------------//

EntityPtr UISelection::checkEntityClicked(const unsigned int _ID)
{

    Game* game = Game::instance();

    return game->getEntityByID(_ID);

}



//-------------------------------------------------------------------//

void UISelection::mouseLeftDown(const unsigned int _ID)
{
    UIButtonPtr UIClick = checkUIClicked(_ID);

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
        UIClick->execute();
    }
}


//-------------------------------------------------------------------//



UISelection::~UISelection()
{

}


//-------------------------------------------------------------------//

//void UISelection::createTestMen()
//{
//    UIMenu test;

//    test.createButtonTest(ngl::Vec2 (2,2), "testing");

//    UIButtonPtr button = test.getbutton();

//    button->execute = boost::bind(&UIMenu::printTest, &test);

//    button->execute();


//}



