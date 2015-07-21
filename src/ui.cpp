#include "window.h"
#include "game.h"
#include "renderer.h"
#include "boost/lexical_cast.hpp"
#include "fwd/entity.h"
#include "ui.h"
#include "uibutton.h"
#include "costbutton.h"
#include "uLayout/uwindow.h"



UI::UI():
    m_creationMode(false)
{

}

//-------------------------------------------------------------------//
UI::~UI()
{

}

//-------------------------------------------------------------------//

void UI::registerID(UIElementPtr _e, unsigned int _ID)
{
    m_IDMap[_ID] = _e;
}

//-------------------------------------------------------------------//

void UI::unregisterID(const unsigned int _ID)
{
    m_IDMap.erase(_ID);
}

//-------------------------------------------------------------------//
void UI::draw()
{

    for(MenuMap::iterator it = m_menus.begin();
        it != m_menus.end();
        ++it)
    {
        TablePtr drawEl = (*it).second;
        drawEl->draw();
    }

    for(UWindowMap::iterator it = m_windows.begin();
        it != m_windows.end();
        ++it)
    {
        UWindowPtr drawEl = (*it).second;
        drawEl->draw();
    }

}

//-------------------------------------------------------------------//
void UI::update(const double _dt)
{
    //updating the score board text

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

    menu->setText(2,0,final.c_str());
    menu->setText(3,0,finalMoney.c_str());
    menu->setText(4,0,finalHealth.c_str());

    //checks to see if the buttons are affordable
    checkButtonAffordable();

    // updates the animation of the elements
    updateAnimation(_dt);

}

//-------------------------------------------------------------------/
void UI::setCreationMode(bool _creation)
{

    if(_creation)
    {
        setButtonState(m_tmpTowerButtonID, CREATEON);
        m_creationMode = _creation;
    }
    else
    {
        setButtonState(m_tmpTowerButtonID, DEFAULT);
        m_creationMode = _creation;
    }
}

//-------------------------------------------------------------------//
bool UI::setButtonState(const unsigned int _ID, ButtonState _state)
{
    UIElementPtr element = checkUIClicked(_ID);

    if(element)
    {
        UIButtonPtr button = boost::dynamic_pointer_cast<UIButton>(element);

        if(button)
        {
            button->setState(_state);
            return true;
        }
    }
    return false;
}

//-------------------------------------------------------------------//
//-------------------------Mouse Events------------------------------//
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
void UI::creationModeClick(const unsigned int _ID)
{
    //if the we are in creation mode we need to do a series of checks

    Game* game = Game::instance();
    EntityPtr entityClick;
    entityClick = game->getEntityByID(_ID).lock();

    //check that it is a valid entity and it is a node and it can be afforded

    if(entityClick &&
            entityClick->getGeneralType() == NODE
            )
    {
        Game* game = Game::instance(); //get instance of game
        NodePtr node = boost::dynamic_pointer_cast<Node>(entityClick);

        if((game->getPlayerCurrency()-m_tmpCost) >= 0)

            //if the player can afford to build the turret

        {

            //try to create tower and if it can build it
            bool isCreated = game->tryToCreateTower((m_tmptowerType),
                                                    node
                                                    );
            if(isCreated == true) // if the tower was built
            {
                game->addCurrency(-m_tmpCost); // update player currency
                node->setHighlighted(0);

                if(game->getPlayerCurrency()-m_tmpCost < 0)
                    // if there is no money left come out of creation mode
                {
                    setCreationMode(false);
                    setHighlighted(m_currentlyHighlighted, 0);
                }
            }
            else
            {
                node->setHighlighted(2); //cannot be placed down there so make red
            }
        }
        else //you dont have enough money come out of creation mode
        {
            setCreationMode(false);
            setHighlighted(m_currentlyHighlighted, 0);
        }
    }

    //else if it is a turret come out of creation mode and go to uprgade menu

    else if(entityClick && entityClick->getGeneralType()==TURRET)
    {
        setCreationMode(false);
        turretClicked(_ID);
        setHighlighted(m_currentlyHighlighted, 0);
    }

    //else check the ui to see if other buttons have been pressed

    else
    {
        UIElementPtr element = checkUIClicked(_ID);

        if(element && element->getType() == CREATEBUTTON) // if it is a create button
        {
            CostButtonPtr button = boost::dynamic_pointer_cast<CostButton>(element);

            if(button && button->getID() == m_tmpTowerButtonID)

                //if the button is the same as what has already been pressed
            {
                setCreationMode(false);
                setHighlighted(m_currentlyHighlighted, 0);
            }
            else if(button && button->getAffordable() == true)

                //if it is affordable

            {
                button->execute();
                m_tmpCost = button->getCost();
                setButtonState(_ID, CREATEON);
                setButtonState(m_tmpTowerButtonID, DEFAULT);
                m_tmpTowerButtonID = _ID;
            }
        }

        else if(element) // if it is another element check to see if it is a button
            //and if so execute the command
        {
            UIButtonPtr button = boost::dynamic_pointer_cast<UIButton>(element);

            if(button)
            {
                button->execute();
                //setCreationMode(false);
            }
        }
    }
}

//-------------------------------------------------------------------//
void UI::mouseLeftUp(const unsigned int _ID)
{
    Game *game = Game::instance();
    Window *window = Window::instance();
    // if we are in creation mode
    if(m_creationMode == 0)
    {
        UIElementPtr UIClick = checkUIClicked(_ID);

        EntityPtr entityClick;

        if(!UIClick)
        {
            // if it is not a ui that is pressed check if it is an entity

            entityClick = game->getEntityByID(_ID).lock();

            if(!entityClick) // if it is not an entity
            {

            }

            else // it is a valid entity
            {
                if(entityClick->getGeneralType() == TURRET)
                {
                    turretClicked(_ID);
                }
            }
        }

        // if the thing that is pressed is a ui element
        else
        {
            if(UIClick->getType() == CREATEBUTTON) // if button is a tower create button
            {
                CostButtonPtr button = boost::dynamic_pointer_cast<CostButton>(UIClick);
                TablePtr menu = getMenu("upgradeMenu");

                //if the tower is affordable set tmp parameters
                //used in creation mode

                if(button && button->getAffordable() == true) //check it is affordable
                {
                    m_tmpTowerButtonID = _ID;
                    m_tmpCost = button->getCost();
                    button->execute();
                    setCreationMode(true);
                    if(window->getScreenWidth() != menu->getPosition().m_x)
                    {
                        menu->runCloseAnimation();
                    }
                }
            }

            else

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
        creationModeClick(_ID);
    }

    //if a button was previously pressed sets its flag back to false
}

//-------------------------------------------------------------------//
void UI::mouseDisablePressedState()
{
    if(m_tmpButtonPressed != 0)
    {
        if(m_tmpButtonPressed == m_tmpTowerButtonID && m_creationMode)
        {
            setButtonState(m_tmpButtonPressed, CREATEON);
        }
        else
        {
            setButtonState(m_tmpButtonPressed, DEFAULT);
        }
        m_tmpButtonPressed = 0;
    }
}

//-------------------------------------------------------------------//
void UI::mouseLeftDown(const unsigned int _ID)
{
    bool successful = setButtonState(_ID, PRESSED);

    if(successful)
    {
        m_tmpButtonPressed = _ID;
    }
}

//-------------------------------------------------------------------//
void UI::turretClicked(const unsigned int _ID)
{
    Game* game = Game::instance();
    EntityPtr entityClick = game->getEntityByID(_ID).lock();

    TablePtr menu = getMenu("upgradeMenu");


    if(entityClick)
    {
        setUpgradeTowerId(_ID);
        //first get the towers next upgrade data

        Turret::UpgradeDataWPtr nextUpgradeDataWeak;
        bool successful = game->getNextUpgrade(nextUpgradeDataWeak,_ID);
        if(successful)
        {
            Turret::UpgradeDataPtr nextData = nextUpgradeDataWeak.lock();
            if(nextData)
            {

                try
                {
                    //set all the menus data

                    UIElementPtr element = menu->getElement(1,1).lock();

                    TablePtr upgradeMenu = boost::dynamic_pointer_cast<Table>(element);

                    std::string cost = boost::lexical_cast<std::string>(nextData->m_cost);
                    std::string cost1 = "Cost : ";
                    std::string finalCost = cost1 + cost;


                    upgradeMenu->setText(2,0,nextData->m_title);
                    upgradeMenu->setText(1,1,finalCost.c_str());
                    upgradeMenu->setText(0,0,nextData->m_description);
                    upgradeMenu->setCost(1,0, nextData->m_cost);


                    menu->setTexture(1,0, nextData->m_texture);


                    upgradeMenu->setSize();

                }

                catch( const boost::bad_lexical_cast & )
                {
                    //unable to convert
                    std::cout<<"can't do this shit"<<std::endl;
                }
            }
        }

        else
        {
            // if there is no more upgrades set the uprgrade menu to state that

            UIElementPtr element = menu->getElement(1,1).lock();

            TablePtr upgradeMenu = boost::dynamic_pointer_cast<Table>(element);
            std::string cost1 = "Cost : N/A";


            upgradeMenu->setText(2,0,"Tower Fully Upgraded");
            upgradeMenu->setText(1,1,cost1.c_str());
            upgradeMenu->setText(0,0,"Tower is maxed");
            upgradeMenu->setCost(1,0,10000000);
            upgradeMenu->setSize();
        }


        Turret::UpgradeDataWPtr currentUpgradeDataWeak;
        // now get the turrets current status

        successful = game->getCurrentUpgrade(currentUpgradeDataWeak,_ID);
        if(successful)
        {
            Turret::UpgradeDataPtr currentData = currentUpgradeDataWeak.lock();
            if(currentData)
            {

                try
                {
                    // set all the menus data

                    UIElementPtr element = menu->getElement(0,1).lock();

                    TablePtr currentMenu = boost::dynamic_pointer_cast<Table>(element);

                    std::string cost = boost::lexical_cast<std::string>(currentData->m_sellValue);
                    cost ="Value : " + cost;

                    currentMenu->setText(2,0,currentData->m_title);
                    currentMenu->setText(1,1,cost.c_str());
                    currentMenu->setText(0,0,currentData->m_description);
                    menu->setTexture(0,0,currentData->m_texture);
                    currentMenu->setSize();

                }
                catch( const boost::bad_lexical_cast & )
                {
                    //unable to convert
                    std::cout<<"can't do this shit"<<std::endl;
                }
            }
        }
    }

    menu->setSize();

    //run the tables animation command to make it slide

    menu->runAnimation();
    menu->setDrawable(true);

}

//-------------------------------------------------------------------//
void UI::mouseMoveEvent(const unsigned int _ID)
{
    EntityPtr entityClick;
    Game* game = Game::instance();

    entityClick = game->getEntityByID(_ID).lock();
    // if it isnt an entity the it may be a ui so run ui hover command

    if(!entityClick)
    {
        uiHover(_ID);
    }
    else // it is a entity
    {
        //if a button was previously being hovered over set its flag to false

        if(m_tmpHoverButton == m_tmpTowerButtonID && m_creationMode)
        {
            setButtonState(m_tmpHoverButton, CREATEON);
        }
        else
        {
            setButtonState(m_tmpHoverButton, DEFAULT);
        }

        GeneralType eType = entityClick->getGeneralType();

        if(eType == TURRET || eType == WALL)
        {
            setHighlighted(m_currentlyHighlighted, 0);
            setHighlighted(_ID, 1);
            m_currentlyHighlighted = _ID;
        }

        //if we are in creation mode then highlight the current node

        if(eType == NODE)
        {
            //set existing nodes flag to false
            setHighlighted(m_currentlyHighlighted, 0);

            if(m_creationMode)
            {
                //set new nodes flag to true
                setHighlighted(_ID, 1);

                m_currentlyHighlighted = _ID;
            }
        }
    }
}
//-------------------------------------------------------------------//
void UI::placeDownStaticEntity(const std::string &_type, NodePtr _node)
{
    Game* game = Game::instance();

    bool isCreated = game->tryToCreateTower(_type, _node);

    if(isCreated == true)
    {
        setCreationMode(false);
    }
}

//-------------------------------------------------------------------//
void UI::uiHover(const unsigned int &_ID)
{

    UIElementPtr element = checkUIClicked(_ID);

    bool inCreateState = false;

    //if the button is in create state and we are in reation mode

    if(m_tmpHoverButton == m_tmpTowerButtonID && m_creationMode)
    {
        inCreateState = true;
    }

    if(!element)
    {
        if(m_tmpHoverButton != 0)
        {
            if(inCreateState)
            {
                // the button is in creation mode so make sure its
                // state doesn't change

                setButtonState(m_tmpHoverButton, CREATEON);
            }
            else
            {
                setButtonState(m_tmpHoverButton, DEFAULT);
            }
            m_tmpHoverButton = 0;
        }
    }

    else
    {
        UIButtonPtr button = boost::dynamic_pointer_cast<UIButton>(element);

        if(button)
        {
            // it isn't the same button and we are not in creation mode

            if(_ID != m_tmpTowerButtonID || !m_creationMode)
            {
                button->setState(HOVER);

                if(_ID != m_tmpHoverButton)
                {
                    if(!inCreateState)
                    {
                        setButtonState(m_tmpHoverButton, DEFAULT);
                    }
                    else
                    {
                        setButtonState(m_tmpHoverButton, CREATEON);
                    }
                    m_tmpHoverButton = _ID;
                }
            }

            else if(m_creationMode)
            {

                if(!inCreateState)
                {
                    setButtonState(m_tmpHoverButton, DEFAULT);
                }
                else
                {
                    setButtonState(m_tmpHoverButton, CREATEON);
                }
            }
        }
    }
}


//-------------------------------------------------------------------//
//--------------------------menu handling----------------------------//
//-------------------------------------------------------------------//


void UI::checkButtonAffordable()
{

    for(MenuMap::iterator it = m_menus.begin();
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
    for(MenuMap::iterator it = m_menus.begin();
        it != m_menus.end();
        ++it)
    {
        TablePtr menu = it->second;
        if(menu->getName() == _name)
        {
            return menu;
        }
    }
    return TablePtr();
}

//-------------------------------------------------------------------//

UWindowPtr UI::getUWindow(std::string _name)
{
    for(UWindowMap::iterator it = m_windows.begin();
        it != m_windows.end();
        ++it)
    {
        UWindowPtr menu = it->second;
        if(menu->getName() == _name)
        {
            return menu;
        }
    }
    return UWindowPtr();
}

//-------------------------------------------------------------------//
void UI::setupUI()
{
    createDisplayScoreMenu();
    createStartMenu();
    createLoseRestartMenu();
    createUpgradeMenu();
    createTowerMenu();
    createInGameSettingsWindow();
}

//-------------------------------------------------------------------//
void UI::createMenu(TablePtr _menu)
{
    Window *window= Window::instance();
    int ID = window->getID();
    _menu->setID(ID);
    registerID(_menu, ID);
    m_menus[_menu->getID()] = _menu;
}

//-------------------------------------------------------------------//
void UI::createWindow
(
        ngl::Vec2 _pos,
        std::string _name,
        std::string _imageFile,
        UI *_parent,
        ngl::Vec2 _size
        )
{
    UWindowPtr menu = UWindowPtr(new UWindow(_pos,_name,_imageFile,_parent,_size));


    Window *window= Window::instance();
    int ID = window->getID();
    menu->setID(ID);
    registerID(menu, ID);
    m_windows[menu->getID()] = menu;

}

//-------------------------------------------------------------------//
//-------------------------menu setup functions----------------------//
//-------------------------------------------------------------------//
void UI::createTowerMenu()
{
    createMenu(TablePtr(new Table(ngl::Vec2 (0,0),

                                  "towerbuildMenu",
                                  "towerPanel",
                                  "up",
                                  this)));

    TablePtr menu = getMenu("towerbuildMenu");

    if (menu)
    {
        menu->createRows(1);
        menu->createColumns(0,3);
        menu->createCostButton
                (
                    0,
                    1,
                    ngl::Vec2 (0,0),
                    "bulletButton",
                    "testTowerCreate",
                    CREATEBUTTON,
                    100,
                    100,
                    100
                    );
        menu->setFunction(0,1, boost::bind(&UI::createTestTowerFunction, this));
        menu->createCostButton
                (
                    0,
                    2,
                    ngl::Vec2 (0,0),
                    "grenadeButton",
                    "missileSiloCreate",
                    CREATEBUTTON,
                    200,
                    100,
                    100
                    );
        menu->setFunction(0,2, boost::bind(&UI::createMissileSiloFunction, this));
        menu->createCostButton
                (
                    0,
                    0,
                    ngl::Vec2 (0,0),
                    "wallButton",
                    "standardWallCreate",
                    CREATEBUTTON,
                    10,
                    100,
                    100
                    );
        menu->setFunction(0,0, boost::bind(&UI::createWallfunction, this));
        menu->createLabel
                (
                    0,
                    1,
                    ngl::Vec2(0,0),
                    "cost $100",
                    "fonts/Roboto-Regular.ttf",
                    15,
                    "testTowerCostText",
                    BOTTOM
                    );
        menu->createLabel
                (
                    0,
                    0,
                    ngl::Vec2(0,0),
                    "cost $10",
                    "fonts/Roboto-Regular.ttf",
                    15,
                    "wallcostText",
                    BOTTOM
                    );
        menu->createLabel
                (
                    0,
                    2,
                    ngl::Vec2(0,0),
                    "cost $200",
                    "fonts/Roboto-Regular.ttf",
                    15,
                    "missileCostText",
                    BOTTOM
                    );

        menu->createAbsoluteElement
                (
                    UIButtonPtr
                    (
                        new UIButton
                        (ngl::Vec2(0,0),
                         "arrowDownButton",
                         "closeTowerMenuButton",
                         40,
                         20
                         )
                        )
                    );
        menu->setFunction("closeTowerMenuButton", boost::bind(&UI::closeTowerMenuFunction,this));

        menu->setSize();
        menu->screenAlignment(Table::BOTTOM);
        menu->screenAlignment(Table::CENTREX);
        menu->setElementPosition("closeTowerMenuButton", Table::TOPLEFT);
        menu->setDrawable(false);
    }
}


//-------------------------------------------------------------------//
void UI::createDisplayScoreMenu()
{

    createMenu(TablePtr(new Table(ngl::Vec2 (0,0),
                                  "scoreMenu",
                                  "textures/default_texture.png",
                                  "",
                                  this)));

    TablePtr menu = getMenu("scoreMenu");

    std::string score1 = "Score : ";
    std::string score = boost::lexical_cast<std::string>(0);
    std::string final = score1 + score;


    std::string money1 = "Money : ";
    std::string money = boost::lexical_cast<std::string>(0);
    std::string finalMoney = money1 + money;



    menu->createRows(5);
    menu->createColumns(0,1);
    menu->createColumns(1,1);
    menu->createColumns(2,1);
    menu->createColumns(3,1);
    menu->createColumns(4,1);
    menu->createButton
            (
                1,
                0,
                ngl::Vec2(0,0),
                "playButton",
                "playPauseButton",
                50,
                50
                );
    menu->setFunction(1,0,boost::bind(&UI::playPauseFunction,this));

    menu->createButton
            (
                0,
                1,
                ngl::Vec2(0,0),
                "settingsButton",
                "settingsButton",
                50,
                50
                );
    menu->setFunction(0,1,boost::bind(&UI::inGameSettingsFunction,this));
    menu->createText
            (
                2,
                0,
                ngl::Vec2(0,0),
                final.c_str(),
                "fonts/Roboto-Regular.ttf",
                20,
                "score"
                );
    menu->createText
            (
                3,
                0,
                ngl::Vec2(0,0),
                finalMoney.c_str(),
                "fonts/Roboto-Regular.ttf",
                20,
                "money"
                );
    menu->createText
            (
                4,
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
    menu->setDrawable(false);
}

//-------------------------------------------------------------------//
void UI::createUpgradeMenu()
{
    Window* window = Window::instance();
    createMenu(TablePtr(new Table(ngl::Vec2 (0,0),
                                  "upgradeMenu",
                                  "bg_tile",
                                  "left",
                                  this)));




    TablePtr menu = getMenu("upgradeMenu");

    TablePtr nextMenu = TablePtr
            (
                new Table
                (
                    ngl::Vec2 (0,0),
                    "nextMenu",
                    "textures/default_texture.png",
                    "",
                    this
                    )
                );

    TablePtr currentMenu = TablePtr
            (
                new Table
                (
                    ngl::Vec2 (0,0),
                    "currentMenu",
                    "textures/default_texture.png",
                    "",
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

            nextMenu->createCostButton
                    (
                        1,
                        0,
                        ngl::Vec2(0,0),
                        "upgradeButton",
                        "upgradeSmallButton",
                        UPGRADEBUTTON,
                        0,
                        50,
                        50
                        );
            nextMenu->setFunction(1,0, boost::bind(&UI::upgradeButtonCommand, this));
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
            nextMenu->setCentreYFlag(true);
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

            currentMenu->createCostButton
                    (
                        1,
                        0,
                        ngl::Vec2(0,0),
                        "sellButton",
                        "sellButton",
                        SELLBUTTON,
                        0,
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
            currentMenu->setFunction(1,0,boost::bind(&UI::sellTowerFunction, this));
            currentMenu->setCentreYFlag(true);
            currentMenu->setBackground(false);

        }

        menu->createRows(3);
        menu->createColumns(0,2);
        menu->createColumns(1,2);
        menu->createColumns(2,2);
        menu->createTable(1,1,nextMenu);
        menu->createTable(0,1,currentMenu);
        menu->createText
                (
                    2,
                    1,
                    ngl::Vec2(0,0),
                    "Upgrade Menu",
                    "fonts/Roboto-Regular.ttf",
                    16,
                    "upgradeMenuText"
                    );
        menu->createImageElement
                (
                    1,
                    0,
                    ngl::Vec2(0,0),
                    "upgrade2BulletImage",
                    IMAGE,
                    "debug",
                    100,
                    100
                    );

        menu->createImageElement
                (
                    0,
                    0,
                    ngl::Vec2(0,0),
                    "sellBulletImage",
                    IMAGE,
                    "debug",
                    100,
                    100
                    );

        menu->setDrawable(false);
        menu->createButton
                (
                    2,
                    0,
                    ngl::Vec2(0,0),
                    "closeButton",
                    "closeButton",
                    30,
                    30
                    );
        UIElementPtr closeElement = menu->getElement(2,0).lock();

        UIButtonPtr closeButton = boost::dynamic_pointer_cast<UIButton>(closeElement);

        closeButton->setFunction(boost::bind(&UI::closeUpgradeMenuFunction, this));

        menu->setSize();
        menu->setCentreYFlag(true);
        menu->setTileable(true);
        float width = window->getScreenWidth();
        menu->setPosition(ngl::Vec2(width,0));
        menu->setStartPos(menu->getPosition());
        menu->screenAlignment(Table::CENTREY);
        menu->setDrawable(true);
    }

}

//-------------------------------------------------------------------//
void UI::createStartMenu()
{
    Window* window = Window::instance();
    Game *game = Game::instance();

    float height = window->getScreenHeight();
    float width = window->getScreenWidth();

    createWindow
            (
                ngl::Vec2(0,0),
                "startWindow",
                "startScreen",
                this,
                ngl::Vec2(width,height)
                );

    UWindowPtr menu = getUWindow("startWindow");

    float windowYRatio = height/1200;

    if(menu)
    {

        menu->createTable(ngl::Vec2(0,0),"startmenu","background","",this);

        UIElementPtr element = menu->getElement("startmenu");

        if(element)
        {
            TablePtr table =boost::dynamic_pointer_cast<Table>(element);
            if(table)
            {
                table->createRows(2);
                table->createColumns(0,1);
                table->createColumns(1,1);
                table->createButton(1,0, ngl::Vec2(0,0),"startGame","startButton",520,135);
                table->setFunction(1,0, boost::bind(&UI::startGameFunction,this));
                table->createButton(0,1,ngl::Vec2(0,0),"quit", "quitButton", 520,135);
                table->setFunction(0,1, boost::bind(&UI::quitFunction,this));
                table->setSize();
                table->setPosition(ngl::Vec2(0,(height-table->getSize().m_y)-(500*windowYRatio)));
                table->setBackground(false);
            }
        }

        menu->alignElement("startmenu", UWindow::CENTREX);
        game->setPaused(true);
    }
}

//-------------------------------------------------------------------//
void UI::createLoseRestartMenu()
{
    Window* window = Window::instance();

    float height = window->getScreenHeight();
    float width = window->getScreenWidth();

    createWindow
            (
                ngl::Vec2(0,0),
                "loseWindow",
                "gameOverBackground",
                this,
                ngl::Vec2(width,height)
                );

    UWindowPtr uwindow = getUWindow("loseWindow");

    float windowYRatio = height/1200;

    uwindow->createTable
            (
                ngl::Vec2(0,0),
                "losemenu",
                "background",
                "",
                this);

    UIElementPtr element = uwindow->getElement("losemenu");

    if(element)
    {
        TablePtr table =boost::dynamic_pointer_cast<Table>(element);
        if(table)
        {
            table->createRows(3);
            table->createColumns(0,1);
            table->createColumns(1,1);
            table->createColumns(2,1);

            table->createButton(2,0,ngl::Vec2(0,0),"restart","restartButton",520,135);

            table->setFunction(2,0, boost::bind(&UI::resetFunction,this));

            table->createButton(1,0,ngl::Vec2(0,0),"backToStart", "backToStartMenuButton",520,135);

            table->setFunction(1,0,boost::bind(&UI::backToStartFunction,this));

            table->createButton(0,1,ngl::Vec2(0, 0),"quit", "quitButtonLose", 520,135);

            table->setFunction(0,1, boost::bind(&UI::quitFunction,this));

            table->setSize();
            table->setPosition(ngl::Vec2(0,(height-table->getSize().m_y)-(510*windowYRatio)));
            table->setBackground(false);
        }
    }
    uwindow->alignElement("losemenu", UWindow::CENTREX);
    uwindow->setDrawable(false);


}

//-------------------------------------------------------------------//
void UI::createInGameSettingsWindow()
{
    Window* window = Window::instance();

    float width = window->getScreenWidth();

    float height = window->getScreenHeight();

    createWindow
            (
                ngl::Vec2(0,0),
                "inGameSettingsWindow",
                "settingsBackground",
                this,
                ngl::Vec2(width,height)
                );

    UWindowPtr uwindow = getUWindow("inGameSettingsWindow");

    uwindow->createTable
            (
                ngl::Vec2(0,0),
                "settingsmenu",
                "background",
                "",
                this);

    UIElementPtr element = uwindow->getElement("settingsmenu");

    if(element)
    {
        TablePtr table =boost::dynamic_pointer_cast<Table>(element);
        if(table)
        {
            table->createRows(4);
            table->createColumns(0,1);
            table->createColumns(1,1);
            table->createColumns(2,1);
            table->createColumns(3,1);

            table->createButton(3,0,ngl::Vec2(0,0),"restart","restartSettingsButton",520,135);

            table->setFunction(3,0, boost::bind(&UI::resetFunction,this));

            table->createButton(2,0,ngl::Vec2(0,0),"backToStart", "backToStartSettingsButton",520,135);

            table->setFunction(2,0,boost::bind(&UI::backToStartFunction,this));

            table->createButton(1,0,ngl::Vec2(0,0),"backToGame", "closeMenu",520,135);

            table->setFunction(1,0,boost::bind(&UI::backToGameFunction,this));

            table->createButton(0,1,ngl::Vec2(0,0),"quit", "quitButtonSettings", 520,135);

            table->setFunction(0,1, boost::bind(&UI::quitFunction,this));
            table->setSize();
            table->setBackground(false);
        }

        uwindow->alignElement("settingsmenu", UWindow::CENTREX);
        uwindow->alignElement("settingsmenu", UWindow::CENTREY);
    }
    uwindow->setDrawable(false);
}

//-------------------------------------------------------------------//
//--------------------reset and lost functions-----------------------//
//-------------------------------------------------------------------//
void UI::gameLost()
{
    Game *game = Game::instance();
    UWindowPtr uwindow = getUWindow("loseWindow");
    TablePtr towerMenu = getMenu("towerbuildMenu");
    TablePtr menu = getMenu("scoreMenu");
    game->setPaused(true);
    uwindow->setDrawable(true);
    m_gameStart = false;
    towerMenu->setDrawable(false);
    menu->setDrawable(false);
}

//-------------------------------------------------------------------//
void UI::resetUI()
{
    resetMenuPositions();
    m_gameStart = false;
    setCreationMode(false);
    TablePtr towerMenu = getMenu("towerbuildMenu");
    TablePtr menu = getMenu("scoreMenu");
    TablePtr upgradeMenu = getMenu("upgradeMenu");
    towerMenu->setDrawable(true);
    menu->setDrawable(true);
    upgradeMenu->setDrawable(true);
    menu->setTexture(1,0,"playButton");
}

//-------------------------------------------------------------------//
void UI::resetMenuPositions()
{
    for(MenuMap::iterator it = m_menus.begin();
        it != m_menus.end();
        ++it)
    {
        TablePtr table = (*it).second;
        table->setPosition(table->getRestPosition());

    }
    for(UWindowMap::iterator it = m_windows.begin();
        it != m_windows.end();
        ++it)
    {
        UWindowPtr uwindow = (*it).second;
        uwindow->setPosition(uwindow->getRestPosition());
    }
}

//-------------------------------------------------------------------//
//---------------------------button functions------------------------//
//-------------------------------------------------------------------//
void UI::upgradeButtonCommand()
{
    Game* game = Game::instance();
    Window *window = Window::instance();
    TablePtr upgradeMenu = getMenu("upgradeMenu");


    Turret::UpgradeDataWPtr nextUpgradeDataWeak;

    //get the upgrade data for the tower

    bool successful = game->getNextUpgrade(nextUpgradeDataWeak,m_tmpUpgradeTowerID);
    if(successful)
    {
        Turret::UpgradeDataPtr nextData = nextUpgradeDataWeak.lock();
        if(nextData)
        {
            int playerCurrency = game->getPlayerCurrency();

            //check to see if the player has enough money
            if(playerCurrency-nextData->m_cost >= 0)
            {
                //try to upgrade the tower
                successful = game->upgradeTurret(m_tmpUpgradeTowerID);
                if(successful)
                {
                    //turretClicked(m_tmpUpgradeTowerID);
                    game->addCurrency(-nextData->m_cost);
                    if(upgradeMenu->getPosition().m_x != window->getScreenWidth())
                    {
                        upgradeMenu->runCloseAnimation();
                    }
                }
            }
        }
    }
}

//-------------------------------------------------------------------//

void UI::sellTowerFunction()
{
 Game* game = Game::instance();
 game->sellTower(m_tmpUpgradeTowerID);
}

//-------------------------------------------------------------------//
void UI::closeUpgradeMenuFunction()
{
    TablePtr menu = getMenu("upgradeMenu");

    menu->runCloseAnimation();
}

//-------------------------------------------------------------------//
void UI::quitFunction()
{
    Window *window = Window::instance();
    window->quit();
}

//-------------------------------------------------------------------//
void UI::inGameSettingsFunction()
{
    Game* game = Game::instance();
    UWindowPtr uwindow = getUWindow("inGameSettingsWindow");
    TablePtr upgradeMenu = getMenu("upgradeMenu");
    TablePtr createMenu = getMenu("towerbuildMenu");
    upgradeMenu->setDrawable(false);
    createMenu->setDrawable(false);
    uwindow->setDrawable(true);
    if(game->getPaused() == 1)
    {
        game->setPaused(2);
    }
    else
    {
        game->setPaused(1);
    }

}

//-------------------------------------------------------------------//
void UI::backToGameFunction()
{
    Game* game = Game::instance();
    UWindowPtr uwindow = getUWindow("inGameSettingsWindow");
    TablePtr menu = getMenu("scoreMenu");
    TablePtr createMenu = getMenu("towerbuildMenu");
    TablePtr upgradeMenu = getMenu("upgradeMenu");
    upgradeMenu->setDrawable(true);
    createMenu->setDrawable(true);
    uwindow->setDrawable(false);
    if(game->getPaused() ==2)
    {
        game->setPaused(1);
        menu->setTexture(1,0,"playButton");
    }
    else
    {
        game->setPaused(0);
        menu->setTexture(1,0,"pauseButton");
    }

}

//-------------------------------------------------------------------//
void UI::startGameFunction()
{
    Game* game = Game::instance();
    UWindowPtr uwindow = getUWindow("startWindow");
    uwindow->setDrawable(false);
    game->setPaused(false);
    resetUI();
}

//-------------------------------------------------------------------//
void UI::playPauseFunction()
{
    Game *game = Game::instance();

    TablePtr menu = getMenu("scoreMenu");

    if(m_gameStart)
    {
        if(game->getPaused() == false)
        {
            game->setPaused(true);
            menu->setTexture(1,0,"playButton");

        }
        else
        {
            game->setPaused(false);
            menu->setTexture(1,0,"pauseButton");

        }
    }
    else
    {
        game->setPaused(false);
        game->startWaves();
        m_gameStart = true;
        menu->setTexture(1,0,"pauseButton");

    }

}

//-------------------------------------------------------------------//
void UI::resetFunction()
{
    Game *game = Game::instance();
    game->reset();
    UWindowPtr uwindow = getUWindow("loseWindow");
    UWindowPtr uwindowSettings = getUWindow("inGameSettingsWindow");
    resetUI();
    uwindow->setDrawable(false);
    uwindowSettings->setDrawable(false);
}


//-------------------------------------------------------------------//
void UI::backToStartFunction()
{
    Game* game = Game::instance();
    UWindowPtr uwindow = getUWindow("loseWindow");
    UWindowPtr menu = getUWindow("startWindow");
    UWindowPtr uwindowSettings = getUWindow("inGameSettingsWindow");
    uwindow->setDrawable(false);
    menu->setDrawable(true);
    uwindowSettings->setDrawable(false);
    game->reset();
    resetUI();
}

//-------------------------------------------------------------------//
//-----------------------Animation Functions-------------------------//
//-------------------------------------------------------------------//
void UI::updateAnimation(const double &_dt)
{
    TablePtr createMenu = getMenu("towerbuildMenu");
    TablePtr upgradeMenu = getMenu("upgradeMenu");

    createMenu->update(_dt);
    upgradeMenu->update(_dt);

}

//-------------------------------------------------------------------//
void UI::closeTowerMenuFunction()
{

    TablePtr menu = getMenu("towerbuildMenu");

    if(menu->getElTexture("closeTowerMenuButton") == "arrowDownButton")
    {
        menu->setTexture("closeTowerMenuButton", "arrowUpButton");
    }
    else
    {
        menu->setTexture("closeTowerMenuButton", "arrowDownButton");
    }

    menu->runAnimation();
}

void UI::setHighlighted(const unsigned int _id, const int _state)
{
    Game *game = Game::instance();
    EntityPtr entity = game->getEntityByID(_id).lock();

    if(entity)
    {
        entity->setHighlighted(_state);
    }
}
