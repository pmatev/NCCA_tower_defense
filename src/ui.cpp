#include "window.h"
#include "game.h"
#include "renderer.h"
#include "boost/lexical_cast.hpp"
#include "fwd/entity.h"
#include "ui.h"
#include "uibutton.h"
#include "createtowerbutton.h"


UI::UI():
  m_creationMode(false)
{

}

//-------------------------------------------------------------------//
UI::~UI()
{
    std::cout<<"dtor called"<<std::endl;
}

//-------------------------------------------------------------------//

void UI::registerID(UIElementPtr _e, unsigned int _ID)
{
    m_IDMap[_ID] = _e;
}

//-------------------------------------------------------------------//

void UI::unregisterID(const unsigned int _i)
{
    m_IDMap.erase(_i);
}


//-------------------------------------------------------------------//
UIElementPtr UI::checkUIClicked(const unsigned int _ID)
{
    elementsMap::iterator it = m_IDMap.find(_ID);
    if(it == m_IDMap.end())
    {
      return UIElementPtr();
    }
    return it->second;
}

//-------------------------------------------------------------------//

void UI::mouseLeftUp(const unsigned int _ID)
{
    Game *game = Game::instance();
    // if we are in creation mode
    if(m_creationMode == 0)
    {
        UIElementPtr UIClick = checkUIClicked(_ID);

        EntityPtr entityClick;
        std::cout<<_ID<<std::endl;

        if(!UIClick)
        {
            // if it is not a ui that is pressed check if it is an entity

            entityClick = game->getEntityByID(_ID).lock();

            if(!entityClick) // if it is not an entity
            {
              std::cout<<"i am background"<<std::endl;
            }

            else // it is a valid entity
            {
                if(entityClick->getGeneralType() == TURRET)
                {
                    turretClicked(_ID);
                    std::cout<<"turrent clicked"<<std::endl;
                }
            }
        }


        // if the thing that is pressed is a ui element
        else
        {
            if(UIClick->getType() == "create") // if button is a tower create button
            {
                CreateTowerButtonPtr button = boost::dynamic_pointer_cast<CreateTowerButton>(UIClick);
                TablePtr menu = getMenu("upgradeMenu");

                //if the tower is affordable set tmp parameters
                //used in creation mode

                if(button && button->getAffordable() == true) //check it is affordable
                {
                    m_tmpCost = button->getCost();
                    m_tmptowerType = button->getTowertype();
                    m_creationMode = true;
                    std::cout<<"i am GUI"<<std::endl;
                    menu->setDrawable(false);
                }
            }

            else if (UIClick->getType() == "button")

            //if it is a standard button execute command

            {
                UIButtonPtr button = boost::dynamic_pointer_cast<UIButton>(UIClick);
                if(button)
                {
                    button->execute();//run the buttons function
                }
            }
        }
    }

    else //button has already been pressed and can be afforded
    {
        EntityPtr entityClick;
        entityClick = game->getEntityByID(_ID).lock();

        //check that it is a valid entity and it is a node and it can be afforded

        if(entityClick &&
                entityClick->getGeneralType() == NODE &&
                (game->getPlayerCurrency()-m_tmpCost) >= 0
                )
        {
            Game* game = Game::instance(); //get instance of game
            NodePtr node = boost::dynamic_pointer_cast<Node>(entityClick);

            //try to create tower and if it can build it

            bool isCreated = game->tryToCreateTower((m_tmptowerType),
                                                    node
                                                    );
            if(isCreated == true) // if the tower was built
            {
                game->addCurrency(-m_tmpCost); // update player currency
                std::cout<<game->getPlayerCurrency();
                node->setHighlighted(false);
                std::cout<<"tower was created properly"<<std::endl;
            }
            else
            {
                node->setHighlighted(2);
            }

        }

        //else if it is a turret come out of creation mode and go to uprgade menu

        else if(entityClick && entityClick->getGeneralType()==TURRET)
        {
            m_creationMode = 0;
            turretClicked(_ID);
            game->setNodehighlighted(m_highlightedNode, 0);
        }
        //else check the ui to see if other buttons have been pressed

        else
        {
            UIElementPtr element = checkUIClicked(_ID);

            if(element && element->getType() == "create") // if it is a create button
            {
                CreateTowerButtonPtr button = boost::dynamic_pointer_cast<CreateTowerButton>(element);

                if(button && button->getTowertype() == m_tmptowerType)

                    //if the button is the same as what has already been pressed
                {
                    m_creationMode = 0;
                    game->setNodehighlighted(m_highlightedNode, 0);
                }
                else if(button && button->getAffordable() == true)
                    //if it is affordable
                {
                    m_tmptowerType = button->getTowertype();
                }
            }
        }
    }
}

//-------------------------------------------------------------------//
void UI::draw()
{

    for(menuMap::iterator it = m_menus.begin();
        it != m_menus.end();
        ++it)
    {
        TablePtr drawEl = (*it).second;
        drawEl->draw();

        //std::cout<<"\n"<<(drawEl)->getName()<< " drawn"<<std::endl;
    }
}

//-------------------------------------------------------------------//
void UI::checkButtonAffordable()
{

    for(menuMap::iterator it = m_menus.begin();
        it != m_menus.end();
        ++it)
    {
        TablePtr costMenu = (*it).second;
        costMenu->checkButtonAffordable();
    }
}

//-------------------------------------------------------------------//

TablePtr UI::getMenu(std::string _name)
{
    for(menuMap::iterator it = m_menus.begin();
        it != m_menus.end();
        ++it)
    {
        TablePtr drawEl = (*it).second;
        if(drawEl->getName() == _name)
        {
           return drawEl;
        }
    }
    return TablePtr();
}

//-------------------------------------------------------------------//
void UI::createMenu(TablePtr _menu)
{
    Window *window= Window::instance();
    int ID = window->getID();
    _menu->setID(ID);
    registerID(_menu, ID);
    m_menus[_menu->getID()] = _menu;
    std::cout<<"menu created"<<std::endl;
}

//-------------------------------------------------------------------//
void UI::placeDownStaticEntity(const std::string &_type, NodePtr _node)
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
void UI::upgradeButtonCommand()
{
    Game* game = Game::instance();

    Turret::UpgradeDataWPtr nextUpgradeDataWeak;
    bool successful = game->getNextUpgrade(nextUpgradeDataWeak,m_tmpUpgradeTowerID);
    if(successful)
    {
        Turret::UpgradeDataPtr nextData = nextUpgradeDataWeak.lock();
        if(nextData)
        {
            int playerCurrency = game->getPlayerCurrency();
            if(playerCurrency-nextData->m_cost >= 0)
            {
                successful = game->upgradeTurret(m_tmpUpgradeTowerID);
                if(successful)
                {
                    turretClicked(m_tmpUpgradeTowerID);
                    std::cout<<"tower successfully upgraded"<<std::endl;
                    game->addCurrency(-nextData->m_cost);
                }
            }
            else
            {
                std::cout<<"not enough money"<<std::endl;
            }
        }
    }
    TablePtr upgradeMenu = getMenu("upgradeMenu");

    upgradeMenu->setDrawable(false);
}

//-------------------------------------------------------------------//
void UI::turretClicked(int _ID)
{
    Game* game = Game::instance();
    EntityPtr entityClick = game->getEntityByID(_ID).lock();

    TablePtr menu = getMenu("upgradeMenu");
    setUpgradeTowerId(_ID);

    if(entityClick)
    {
        Turret::UpgradeDataWPtr nextUpgradeDataWeak;
        bool successful = game->getNextUpgrade(nextUpgradeDataWeak,_ID);
        if(successful)
        {
            Turret::UpgradeDataPtr nextData = nextUpgradeDataWeak.lock();
            if(nextData)
            {

                try
                {
                    UIElementPtr element = menu->getElement(1,1).lock();

                    TablePtr upgradeMenu = boost::dynamic_pointer_cast<Table>(element);

                    std::string cost = boost::lexical_cast<std::string>(nextData->m_cost);
                    std::string cost1 = "Cost : ";
                    std::string finalCost = cost1 + cost;

                    upgradeMenu->setText(2,0,nextData->m_title);
                    upgradeMenu->setText(1,1,finalCost.c_str());
                    upgradeMenu->setText(0,0,nextData->m_description);
                    UIElementPtr button = upgradeMenu->getElement(1,0).lock();
                    //button->setTexture = nextData->m_texture;
                    upgradeMenu->setSize();

                    UIElementPtr upgradeElement = upgradeMenu->getElement(1,0).lock();

                    UIButtonPtr upgradeButton = boost::dynamic_pointer_cast<UIButton>(upgradeElement);

                    upgradeButton->setFunction(boost::bind(&UI::upgradeButtonCommand, this));
                }

                catch( const boost::bad_lexical_cast & )
                {
                    //unable to convert
                    std::cout<<"can't do this shit"<<std::endl;
                }
            }
        }
        Turret::UpgradeDataWPtr currentUpgradeDataWeak;
        successful = game->getCurrentUpgrade(currentUpgradeDataWeak,_ID);
        if(successful)
        {
            Turret::UpgradeDataPtr currentData = currentUpgradeDataWeak.lock();
            if(currentData)
            {

                try
                {
                    UIElementPtr element = menu->getElement(0,1).lock();

                    TablePtr currentMenu = boost::dynamic_pointer_cast<Table>(element);

                    std::string cost = boost::lexical_cast<std::string>(currentData->m_cost);

                    currentMenu->setText(2,0,currentData->m_title);
                    currentMenu->setText(1,1,cost.c_str());
                    currentMenu->setText(0,0,currentData->m_description);
                    UIElementPtr button = currentMenu->getElement(1,0).lock();

                    //button->setTexture = nextData->m_texture;
                    currentMenu->setSize();

                }
                catch( const boost::bad_lexical_cast & )
                {
                    //unable to convert
                    std::cout<<"can't do this shit"<<std::endl;
                }
            }
        }
        menu->setSize();
        menu->setDrawable(true);
        menu->screenAlignment(Table::CENTREY);
        menu->screenAlignment(Table::RIGHT);
    }
}

//-------------------------------------------------------------------//
void UI::mouseMoveEvent(const unsigned int _ID)
{
    if(m_creationMode == true)
    {
        EntityPtr entityClick;
        Game* game = Game::instance();

        entityClick = game->getEntityByID(_ID).lock();


        if(entityClick)
        {

            if(entityClick->getGeneralType() == NODE &&
                    _ID != m_highlightedNode)
            {

                NodePtr node = boost::dynamic_pointer_cast<Node>(entityClick);

                //grab instance of game
                int searchDepth = node->getSearchDepth();

                if(searchDepth == -1)
                {
                    //set existing nodes flag to false
                    game->setNodehighlighted(m_highlightedNode, 0);

                    //set new nodes flag to true
                    game->setNodehighlighted(_ID, 2);
                }
                else
                {
                    //set existing nodes flag to false
                    game->setNodehighlighted(m_highlightedNode, 0);

                    //set new nodes flag to true
                    game->setNodehighlighted(_ID, 1);
                }

                m_highlightedNode = _ID;
            }
        }
    }
}

//-------------------------------------------------------------------//
void UI::setupUI()
{
    createUpgradeMenu();
    createTowerMenu();
    createDisplayScoreMenu();

}

//-------------------------------------------------------------------//
void UI::createTowerBuildMenu()
{
    createMenu(TablePtr(new Table(ngl::Vec2 (0,0),
                                    "towerbuildMenu",
                                    "textures/default_texture.jpg",
                                    this)));

    TablePtr menu = getMenu("towerbuildMenu");

    TablePtr menu2 =TablePtr(new Table(ngl::Vec2 (0,0),
                                       "towerMenu",
                                       "textures/default_texture.jpg",
                                       this));



    if(menu)
    {
        if(menu2)
        {
            menu2->createRows(2);
            menu2->createColumns(0,2);
            menu2->createColumns(1,1);
            menu2->createElement(0,0,CreateTowerButtonPtr(new CreateTowerButton(ngl::Vec2(0,0),"textures/default_texture.jpg","testButton2", menu, 50,"testturret",50,50)));
            menu2->createElement(0,1,CreateTowerButtonPtr(new CreateTowerButton(ngl::Vec2(0,0),"textures/default_texture.jpg","testButton3", menu, 50,"testturret",50,50)));
            menu2->createElement(1,0,TextPtr(new Text(ngl::Vec2(0,0), "hello peeps","fonts/Roboto-Regular.ttf",14,"texttest")));
            menu2->setPosition(ngl::Vec2 (0,0));
            menu2->setBackground(false);
            menu2->setSize();




            menu->createRows(3);
            menu->createColumns(0,2);
            menu->createColumns(1,3);
            menu->createColumns(2,1);
            menu->createElement(0,0,CreateTowerButtonPtr(new CreateTowerButton(ngl::Vec2(0,0),"textures/default_texture.jpg","testButton", menu, 50,"testturret",50,50)));
            menu->createElement(0,1,CreateTowerButtonPtr(new CreateTowerButton(ngl::Vec2(0,0),"textures/default_texture.jpg","button", menu, 50,"testturret",50,50)));
            menu->createElement(1,0,CreateTowerButtonPtr(new CreateTowerButton(ngl::Vec2(0,0),"textures/default_texture.jpg","button2", menu, 50,"testturret", 25,25)));
            menu->createElement(1,1,TextPtr(new Text(ngl::Vec2(0,0), "hello","fonts/Roboto-Regular.ttf",14,"texttest")));
            menu->createElement(1,2,CreateTowerButtonPtr(new CreateTowerButton(ngl::Vec2(0,0),"textures/default_texture.jpg","button3", menu, 50,"testturret", 50,50)));
            menu->createElement(2,0,menu2);
            menu->setSize();
            menu->screenAlignment(Table::BOTTOM);
            menu->screenAlignment(Table::CENTREX);
        }
    }
}

//-------------------------------------------------------------------//
void UI::createTowerMenu()
{
    createMenu(TablePtr(new Table(ngl::Vec2 (0,0),
                                    "towerbuildMenu",
                                    "textures/default_texture.jpg",
                                    this)));

    TablePtr menu = getMenu("towerbuildMenu");

    if (menu)
    {
        menu->createRows(1);
        menu->createColumns(0,3);
        menu->createTowerButton
                (
                    0,
                    0,
                    ngl::Vec2 (0,0),
                    "textures/default_texture.jpg",
                    "testTowerCreate",
                    menu,
                    100,
                    "TestTurret",
                    100,
                    100
                    );
        menu->createTowerButton
                (
                    0,
                    1,
                    ngl::Vec2 (0,0),
                    "textures/default_texture.jpg",
                    "missileSiloCreate",
                    menu,
                    200,
                    "MissileSilo",
                    100,
                    100
                    );
        menu->createTowerButton
                (
                    0,
                    2,
                    ngl::Vec2 (0,0),
                    "textures/default_texture.jpg",
                    "standardWallCreate",
                    menu,
                    10,
                    "StandardWall",
                    100,
                    100
                    );

        menu->setSize();
        menu->screenAlignment(Table::BOTTOM);
        menu->screenAlignment(Table::CENTREX);
    }

}


//-------------------------------------------------------------------//
void UI::createDisplayScoreMenu()
{
    Game* game = Game::instance();

    createMenu(TablePtr(new Table(ngl::Vec2 (0,0),
                                    "scoreMenu",
                                    "textures/default_texture.jpg",
                                    this)));

    TablePtr menu = getMenu("scoreMenu");

    std::string score1 = "Score : ";
    std::string score = boost::lexical_cast<std::string>(game->getPlayerScore());
    std::string final = score1 + score;


    std::string money1 = "Money : ";
    std::string money = boost::lexical_cast<std::string>(game->getPlayerCurrency());
    std::string finalMoney = money1 + money;



    menu->createRows(3);
    menu->createColumns(0,2);
    menu->createColumns(1,2);
    menu->createColumns(2,1);
    menu->createText
            (
                0,
                0,
                ngl::Vec2(0,0),
                final.c_str(),
                "fonts/Roboto-Regular.ttf",
                20,
                "score"
                );
    menu->createText
            (
                1,
                0,
                ngl::Vec2(0,0),
                finalMoney.c_str(),
                "fonts/Roboto-Regular.ttf",
                20,
                "money"
                );
    menu->createText
            (
                2,
                0,
                ngl::Vec2(0,0),
                final.c_str(),
                "fonts/Roboto-Regular.ttf",
                20,
                "base health"
                );
    menu->setBackground(false);
    menu->setSize();
    menu->screenAlignment(Table::LEFT);
    menu->screenAlignment(Table::TOP);
}

//-------------------------------------------------------------------//
void UI::updatePlayerInfo()
{
    Game* game = Game::instance();
    std::string score1 = "Score : ";
    std::string score = boost::lexical_cast<std::string>(game->getPlayerScore());
    std::string final = score1 + score;


    std::string money1 = "Money : ";
    std::string money = boost::lexical_cast<std::string>(game->getPlayerCurrency());
    std::string finalMoney = money1 + money;

    std::string health1 = "Base Health : ";
    std::string health = boost::lexical_cast<std::string>(game->getBaseHealth());
    std::string finalHealth = health1 + health;

    TablePtr menu = getMenu("scoreMenu");

    menu->setText(0,0,final.c_str());
    menu->setText(1,0,finalMoney.c_str());
    menu->setText(2,0,finalHealth.c_str());

    checkButtonAffordable();
}


//-------------------------------------------------------------------//
void UI::createUpgradeMenu()
{
    createMenu(TablePtr(new Table(ngl::Vec2 (0,0),
                                    "upgradeMenu",
                                    "textures/default_texture.jpg",
                                    this)));

    TablePtr menu = getMenu("upgradeMenu");

    TablePtr nextMenu = TablePtr
            (
                new Table
                (
                    ngl::Vec2 (0,0),
                    "nextMenu",
                    "textures/default_texture.jpg",
                    this
                    )
                );

    TablePtr currentMenu = TablePtr
            (
                new Table
                (
                    ngl::Vec2 (0,0),
                    "currentMenu",
                    "textures/default_texture.jpg",
                    this
                    )
                );

    if(menu)
    {
        if(nextMenu)
        {
            nextMenu->createRows(3);
            nextMenu->createColumns(0,1);
            nextMenu->createColumns(1,2);
            nextMenu->createColumns(2,1);
            nextMenu->createText
                    (
                        2,
                        0,
                        ngl::Vec2 (0,0),
                        "Upgraded Tower ",
                        "fonts/Roboto-Regular.ttf",
                        15,
                        "nextTitle"
                        );

            nextMenu->createButton
                    (
                        1,
                        0,
                        ngl::Vec2(0,0),
                        "textures/default_texture.jpg",
                        "upgradeSmallButton",
                        menu,
                        50,
                        50
                        );
            nextMenu->createText
                    (
                        1,
                        1,
                        ngl::Vec2 (0,0),
                        "$50",
                        "fonts/Roboto-Regular.ttf",
                        15,
                        "nextCost"
                        );
            nextMenu->createText
                    (
                        0,
                        0,
                        ngl::Vec2 (0,0),
                        "this tower will be awesome and i want this to be long",
                        "fonts/Roboto-Regular.ttf",
                        13,
                        "nextDescription"
                        );
            nextMenu->setSize();
            nextMenu->setBackground(false);

        }

        if(currentMenu)
        {
            currentMenu->createRows(3);
            currentMenu->createColumns(0,1);
            currentMenu->createColumns(1,2);
            currentMenu->createColumns(2,1);
            currentMenu->createText
                    (
                        2,
                        0,
                        ngl::Vec2 (0,0),
                        "Current Tower",
                        "fonts/Roboto-Regular.ttf",
                        15,
                        "currentTitle"
                        );

            currentMenu->createButton
                    (
                        1,
                        0,
                        ngl::Vec2(0,0),
                        "textures/default_texture.jpg",
                        "sellButton",
                        menu,
                        50,
                        50
                        );
            currentMenu->createText
                    (
                        1,
                        1,
                        ngl::Vec2 (0,0),
                        "$50",
                        "fonts/Roboto-Regular.ttf",
                        15,
                        "sellCost"
                        );
            currentMenu->createText
                    (
                        0,
                        0,
                        ngl::Vec2 (0,0),
                        "this is the current tower",
                        "fonts/Roboto-Regular.ttf",
                        13,
                        "currentDescription"
                        );
            currentMenu->setSize();
            currentMenu->setBackground(false);

        }

        menu->createRows(3);
        menu->createColumns(0,2);
        menu->createColumns(1,2);
        menu->createColumns(2,1);
        menu->createElement(1,1,nextMenu);
        menu->createElement(0,1,currentMenu);
        menu->createButton
                (
                    1,
                    0,
                    ngl::Vec2(0,0),
                    "textures/default_texture.jpg",
                    "upgradeButton",
                    menu,
                    100,
                    100
                    );
        menu->createButton
                (
                    0,
                    0,
                    ngl::Vec2(0,0),
                    "textures/default_texture.jpg",
                    "currentButton",
                    menu,
                    100,
                    100
                    );
        menu->setSize();
        menu->screenAlignment(Table::CENTREY);
        menu->screenAlignment(Table::RIGHT);
        menu->setDrawable(false);
        menu->createButton
                (
                    2,
                    0,
                    ngl::Vec2(0,0),
                    "textures/default_texture.jpg",
                    "closeButton",
                    menu,
                    30,
                    30
                    );
        UIElementPtr closeElement = menu->getElement(2,0).lock();

        UIButtonPtr closeButton = boost::dynamic_pointer_cast<UIButton>(closeElement);

        closeButton->setFunction(boost::bind(&UI::closeUpgradeMenu, this));
    }

}

//-------------------------------------------------------------------//
void UI::closeUpgradeMenu()
{
    TablePtr menu = getMenu("upgradeMenu");
    menu->setDrawable(false);
}



//-------------------------------------------------------------------//
//-------------------------------------------------------------------//
//-------------------------------------------------------------------//


//-------------------------------------------------------------------//
//-------------------------Test Function-----------------------------//
//-------------------------------------------------------------------//

//void UI::mouseLeftUp(const unsigned int _ID)
//{

//    Game *game = Game::instance();

//    UIElementPtr UIClick = checkUIClicked(_ID);

//    EntityPtr entityClick;
//    std::cout<<_ID<<" ";
//    if(!UIClick)
//    {
//        entityClick = game->getEntityByID(_ID).lock();

//        if(!entityClick)
//        {
//          std::cout<<"i am background"<<std::endl;
//        }
//        else
//        {
//            if(entityClick->getGeneralType() == NODE)
//            {
//                Game* game = Game::instance();

//                NodePtr node = boost::dynamic_pointer_cast<Node>(entityClick);

//                bool isCreated = game->tryToCreateTower("TestTurret",
//                                                         node);

//                if(isCreated == true)
//                {
//                    //m_creationMode = 0;

//                    std::cout<<"tower was created properly"<<std::endl;
//                }

//            }
//            else
//            {
//                std::cout<<"i'm not a node"<<std::endl;
//            }
//            if(entityClick->getGeneralType() == TURRET)
//            {
//              Game* game = Game::instance();

//              Turret::UpgradeDataWPtr upgradeDataWeak;
//              bool successful = game->upgrateTurret(_ID);
//              if(successful)
//              {
//                successful = game->getCurrentUpgrade(upgradeDataWeak,_ID);
//              }
//              if(successful)
//              {
//                Turret::UpgradeDataPtr data = upgradeDataWeak.lock();
//                if(data)
//                {
//                  std::cout<<"Upgrading to "<<std::endl;
//                  std::cout<<"   "<<data->m_title<<std::endl;
//                  std::cout<<"   "<<data->m_description<<std::endl;
//                  std::cout<<"   "<<data->m_cost<<std::endl;
//                }
//              }
//            }

//        }

//    }
//    else
//    {
////        UIClick->isClicked();
//        std::cout<<"i am GUI"<<std::endl;
//    }
//}

//-------------------------------------------------------------------//
//-------------------------------------------------------------------//
//-------------------------------------------------------------------//


void UI::createTestTower()
{
    m_creationMode = true;
    m_tmptowerType = "testTurret";
}


void UI::displayUpgradeMenu(const unsigned int _ID)
{
    Game* game = Game::instance();
    Turret::UpgradeDataWPtr upgradeDataWeak;
                  bool successful = game->upgradeTurret(_ID);
                  if(successful)
                  {
                    successful = game->getCurrentUpgrade(upgradeDataWeak,_ID);
                  }
                  if(successful)
                  {
                    Turret::UpgradeDataPtr data = upgradeDataWeak.lock();
                    if(data)
                    {
                      std::cout<<"Upgrading to "<<std::endl;
                      std::cout<<"   "<<data->m_title<<std::endl;
                      std::cout<<"   "<<data->m_description<<std::endl;
                      std::cout<<"   "<<data->m_cost<<std::endl;
                    }
                  }
}





