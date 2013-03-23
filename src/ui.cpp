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
void UI::draw()
{

    for(MenuMap::iterator it = m_menus.begin();
        it != m_menus.end();
        ++it)
    {
        TablePtr drawEl = (*it).second;
        drawEl->draw();

        //std::cout<<"\n"<<(drawEl)->getName()<< " drawn"<<std::endl;
    }
    for(UWindowMap::iterator it = m_windows.begin();
        it != m_windows.end();
        ++it)
    {
        UWindowPtr drawEl = (*it).second;
        drawEl->draw();

        //std::cout<<"\n"<<(drawEl)->getName()<< " drawn"<<std::endl;
    }
    //drawTmpTower();
}

//-------------------------------------------------------------------//
void UI::drawTmpTower()
{
    if(m_creationMode)
    {
        Renderer *r = Renderer::instance();
        Game *game = Game::instance();
        ngl::ShaderLib *shader = ngl::ShaderLib::instance();
        EntityPtr entity = game->getEntityByID(m_highlightedNode).lock();

        if(entity && entity->getGeneralType() == NODE)
        {
            if(m_tmpNodePos != entity->getPos())
            {
                m_tmpNodePos = entity->getPos();
            }

            //Draw the turret base
            m_transformStack.pushTransform();
            m_transformStack.setPosition(m_tmpNodePos);

            (*shader)["Constant"]->use();
            r->loadMatrixToShader(m_transformStack.getCurrentTransform().getMatrix(), "Constant");

            shader->setShaderParam4f("colour", 0.1, 0.1, 0.8, 1);

            r->draw(m_tmpTowerMesh, "Constant");
            m_transformStack.popTransform();
        }
    }
}

//-------------------------------------------------------------------//
void UI::update()
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

    menu->setText(2,0,final.c_str());
    menu->setText(3,0,finalMoney.c_str());
    menu->setText(4,0,finalHealth.c_str());

    checkButtonAffordable();
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
void UI::creationModeClick(const unsigned int _ID,ngl::Vec2 _mousePos)
{
    Game* game = Game::instance();
    EntityPtr entityClick;
    entityClick = game->getEntityByID(_ID).lock();

    //get old creation tower incase it need to be used to turn off its
    //m_isPressed

    UIElementPtr element = checkUIClicked(m_tmpTowerButtonID);
    UIButtonPtr oldButton = boost::dynamic_pointer_cast<UIButton>(element);


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
                node->setHighlighted(false);

                if(game->getPlayerCurrency()-m_tmpCost < 0)
                    // if there is no money left come out of creation mode
                {
                    m_creationMode = 0;
                }
            }
            else
            {
                node->setHighlighted(2); //cannot be placed down there so make red
            }
        }
        else //you dont have enough money come out of creation mode
        {
            m_creationMode = 0;
            game->setNodehighlighted(m_highlightedNode, 0);
        }
    }

    //else if it is a turret come out of creation mode and go to uprgade menu

    else if(entityClick && entityClick->getGeneralType()==TURRET)
    {

        m_creationMode = 0;
        oldButton->setPressed(false);
        turretClicked(_ID, _mousePos);
        game->setNodehighlighted(m_highlightedNode, 0);
    }

    //else check the ui to see if other buttons have been pressed

    else
    {
        UIElementPtr element = checkUIClicked(_ID);

        if(element && element->getType() == "create") // if it is a create button
        {
            CostButtonPtr button = boost::dynamic_pointer_cast<CostButton>(element);

            if(button && button->getID() == m_tmpTowerButtonID)

                //if the button is the same as what has already been pressed
            {
                m_creationMode = 0;
                button->setPressed(false);
                game->setNodehighlighted(m_highlightedNode, 0);
            }
            else if(button && button->getAffordable() == true)
                //if it is affordable
            {
                button->execute();
                m_tmpCost = button->getCost();
                button->setPressed(true);
                oldButton->setPressed(false);
                m_tmpTowerButtonID = _ID;
            }
        }

        else if(element) // if it is another element check to see if it is a button
            //and execute the command
        {
            UIButtonPtr button = boost::dynamic_pointer_cast<UIButton>(element);

            if(button)
            {
                button->execute();
                m_creationMode = 0;
                oldButton->setPressed(false);
            }
        }
    }
}

//-------------------------------------------------------------------//

void UI::mouseLeftUp(const unsigned int _ID, ngl::Vec2 _mousePos)
{
    Game *game = Game::instance();
    // if we are in creation mode
    if(m_creationMode == 0)
    {
        UIElementPtr UIClick = checkUIClicked(_ID);

        EntityPtr entityClick;
//        std::cout<<_ID<<std::endl;

        if(!UIClick)
        {
            // if it is not a ui that is pressed check if it is an entity

            entityClick = game->getEntityByID(_ID).lock();

            if(!entityClick) // if it is not an entity
            {

//              std::cout<<"i am background"<<std::endl;

            }

            else // it is a valid entity
            {
                if(entityClick->getGeneralType() == TURRET)
                {
                    turretClicked(_ID, _mousePos);
                }
            }
        }


        // if the thing that is pressed is a ui element
        else
        {
            if(UIClick->getType() == "create") // if button is a tower create button
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
                    button->setPressed(true);
                    m_creationMode = true;

//                    std::cout<<"i am GUI"<<std::endl;

                    menu->setDrawable(false);
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
        creationModeClick(_ID, _mousePos);
    }
}


//-------------------------------------------------------------------//
void UI::turretClicked(const unsigned int _ID,ngl::Vec2 _mousePos)
{
    Game* game = Game::instance();
    EntityPtr entityClick = game->getEntityByID(_ID).lock();

    TablePtr menu = getMenu("upgradeMenu");


    if(entityClick)
    {
        setUpgradeTowerId(_ID);
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


    //menu->setPosition(ngl::Vec2(_mousePos.m_x+3,_mousePos.m_y-menu->getSize().m_y));
    menu->screenAlignment(Table::CENTREY);
    menu->screenAlignment(Table::RIGHT);
    menu->centreElementsY();
    menu->setDrawable(true);
}

//-------------------------------------------------------------------//
void UI::mouseMoveEvent(const unsigned int _ID)
{
    EntityPtr entityClick;
    Game* game = Game::instance();

    entityClick = game->getEntityByID(_ID).lock();

    if(!entityClick)
    {
        uiHover(_ID);
    }
    else
    {
        UIElementPtr oldel = checkUIClicked(m_tmpHoverButton);
        if(oldel)
        {
            UIButtonPtr oldButton = boost::dynamic_pointer_cast<UIButton>(oldel);
            if(oldButton)
            {
                oldButton->setHover(false);
            }
        }

        if(m_creationMode == true)
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
    TablePtr upgradeMenu = getMenu("upgradeMenu");

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
                    //turretClicked(m_tmpUpgradeTowerID);
                    game->addCurrency(-nextData->m_cost);
                    upgradeMenu->setDrawable(false);
                }
            }
            else
            {
                std::cout<<"not enough money"<<std::endl;
            }
        }
    }
}


//-------------------------------------------------------------------//
void UI::uiHover(const unsigned int &_ID)
{

    UIElementPtr element = checkUIClicked(_ID);
    UIElementPtr oldel = checkUIClicked(m_tmpHoverButton);

    if(!element)
    {
        if(oldel)
        {
            UIButtonPtr oldButton = boost::dynamic_pointer_cast<UIButton>(oldel);
            if(oldButton)
            {
                oldButton->setHover(false);
                //set orginial hover flag to 0 then set the new one to 1
            }
        }
    }

    else
    {
        UIButtonPtr button = boost::dynamic_pointer_cast<UIButton>(element);

        if(button)
        {
            if(button->getType() != "create")
            {
                button->setHover(true);

                if(button->getID() != m_tmpHoverButton)
                {
                    m_tmpHoverButton = _ID;
                    if(oldel)
                    {
                        UIButtonPtr oldButton = boost::dynamic_pointer_cast<UIButton>(oldel);
                        if(oldButton)
                        {
                            oldButton->setHover(false);
                            //set orginial hover flag to 0 then set the new one to 1
                        }
                    }
                }
            }
            else
            {
              //
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
    setUpAnimation();
}

//-------------------------------------------------------------------//
void UI::createMenu(TablePtr _menu)
{
    Window *window= Window::instance();
    int ID = window->getID();
    _menu->setID(ID);
    registerID(_menu, ID);
    m_menus[_menu->getID()] = _menu;
    std::cout<<_menu->getName()<<" created"<<std::endl;
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
    std::cout<<menu->getName()<<" create"<<std::endl;

}

//-------------------------------------------------------------------//
//-------------------------menu setup functions----------------------//
//-------------------------------------------------------------------//
void UI::createTowerMenu()
{
    createMenu(TablePtr(new Table(ngl::Vec2 (0,0),
                                    "towerbuildMenu",
                                    "bg_tile",
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
                    "machineGunButton",
                    "testTowerCreate",
                    "create",
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
                    "create",
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
                    "create",
                    10,
                    100,
                    100
                    );
        menu->setFunction(0,0, boost::bind(&UI::createWallfunction, this));
        menu->createLabel
                (
                    0,
                    1,
                    (0,0),
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
                    (0,0),
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
                    (0,0),
                    "cost $200",
                    "fonts/Roboto-Regular.ttf",
                    15,
                    "missileCostText",
                    BOTTOM
                    );

        menu->createElement
                (
                    UIButtonPtr
                    (
                        new UIButton
                        (ngl::Vec2(0,0),
                         "closeButton",
                         "closeTowerMenuButton",
                         40,
                         20
                         )
                        )
                    );
        menu->setFunction("closeTowerMenuButton", boost::bind(&UI::closeTowerMenuFunction,this));

        menu->setSize();
        std::cout<<"menu size"<<menu->getSize();
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
                "settingButton",
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
    createMenu(TablePtr(new Table(ngl::Vec2 (0,0),
                                    "upgradeMenu",
                                    "bg_tile",
                                    this)));



    TablePtr menu = getMenu("upgradeMenu");

    TablePtr nextMenu = TablePtr
            (
                new Table
                (
                    ngl::Vec2 (0,0),
                    "nextMenu",
                    "textures/default_texture.png",
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
                        "upgrade",
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
                        "sell",
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
            currentMenu->setBackground(false);

        }

        menu->createRows(3);
        menu->createColumns(0,2);
        menu->createColumns(1,2);
        menu->createColumns(2,1);
        menu->createTable(1,1,nextMenu);
        menu->createTable(0,1,currentMenu);
        menu->createButton
                (
                    1,
                    0,
                    ngl::Vec2(0,0),
                    "upgradeButton",
                    "upgradeButton",
                    100,
                    100
                    );

        menu->createButton
                (
                    0,
                    0,
                    ngl::Vec2(0,0),
                    "startButton",
                    "currentButton",
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
                    "closeButton",
                    "closeButton",
                    30,
                    30
                    );
        UIElementPtr closeElement = menu->getElement(2,0).lock();

        UIButtonPtr closeButton = boost::dynamic_pointer_cast<UIButton>(closeElement);

        closeButton->setFunction(boost::bind(&UI::closeUpgradeMenuFunction, this));
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
                "bg_tile",
                this,
                ngl::Vec2(width,height)
                );

    UWindowPtr menu = getUWindow("startWindow");

    if(menu)
    {

        menu->createTable(ngl::Vec2(0,0),"startmenu","background",this);

        UIElementPtr element = menu->getElement("startmenu");

        if(element)
        {
            TablePtr table =boost::dynamic_pointer_cast<Table>(element);
            if(table)
            {
                table->createRows(2);
                table->createColumns(0,1);
                table->createColumns(1,1);
                table->createButton(1,0, ngl::Vec2(0,0),"startMenuButton","startButton",700,150);

                table->setFunction(1,0, boost::bind(&UI::startGameFunction,this));

                table->createButton(0,1,ngl::Vec2(0,0),"quitGameMenuButton", "quitButton", 700,150);
                table->setFunction(0,1, boost::bind(&UI::quitFunction,this));
                table->setSize();
                table->setPosition(ngl::Vec2(0,(height-table->getSize().m_y)-200));
                table->setBackground(false);
            }
        }


        menu->createText
                (
                    ngl::Vec2 (0,menu->getSize().m_y-125),
                    "Welcome To Tower Defence",
                    "fonts/Roboto-Regular.ttf",
                    60,
                    "welcomeText"
                    );

        menu->alignElement("welcomeText",UWindow::CENTREX);       
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
                "background",
                this,
                ngl::Vec2(width,height)
                );

    UWindowPtr uwindow = getUWindow("loseWindow");

    uwindow->createText
            (
                ngl::Vec2 (0,window->getScreenHeight()-100),
                "You have lost",
                "fonts/Roboto-Regular.ttf",
                60,
                "loseText"
                );

    uwindow->createTable(ngl::Vec2(0,0),"losemenu","background",this);

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

            table->createButton(2,0,ngl::Vec2(0,0),"restartMenuButton","restartButton",700,150);

            table->setFunction(2,0, boost::bind(&UI::resetFunction,this));

            table->createButton(1,0,ngl::Vec2(0,0),"backToStartMenuButton", "backToStartMenuButton",700,150);

            table->setFunction(1,0,boost::bind(&UI::backToStartFunction,this));

            table->createButton(0,1,ngl::Vec2(0, 0),"quitGameMenuButton", "quitButtonLose", 700,150);

            table->setFunction(0,1, boost::bind(&UI::quitFunction,this));

            table->setSize();
            table->setBackground(false);
        }
    }
    uwindow->alignElement("loseText",UWindow::CENTREX);

    uwindow->alignElement("losemenu", UWindow::CENTREX);
    uwindow->alignElement("losemenu",UWindow::CENTREY);

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
                "background",
                this,
                ngl::Vec2(width,height)
                );

    UWindowPtr uwindow = getUWindow("inGameSettingsWindow");

    uwindow->createButton(ngl::Vec2(0,height-250),"restartMenuButton","restartSettingsButton",700,150);

    uwindow->alignElement("restartSettingsButton", UWindow::CENTREX);

    uwindow->setFunction("restartSettingsButton", boost::bind(&UI::resetFunction,this));

    uwindow->createButton(ngl::Vec2(0,height-420),"backToStartMenuButton", "backToStartSettingsButton",700,150);

    uwindow->setFunction("backToStartSettingsButton",boost::bind(&UI::backToStartFunction,this));

    uwindow->alignElement("backToStartSettingsButton", UWindow::CENTREX);

    uwindow->createButton(ngl::Vec2(0,height-590),"backToGameButton", "closeMenu",700,150);

    uwindow->setFunction("closeMenu",boost::bind(&UI::closeMenuFunction,this));

    uwindow->alignElement("closeMenu", UWindow::CENTREX);

    uwindow->createButton(ngl::Vec2(0, height-760),"quitGameMenuButton", "quitButtonSettings", 700,150);

    uwindow->setFunction("quitButtonSettings", boost::bind(&UI::quitFunction,this));

    uwindow->alignElement("quitButtonSettings", UWindow::CENTREX);

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
    Game *game = Game::instance();
    update();
    resetMenuPositions();
    m_gameStart = false;
    game->setPaused(false);
    TablePtr towerMenu = getMenu("towerbuildMenu");
    TablePtr menu = getMenu("scoreMenu");
    towerMenu->setDrawable(true);
    menu->setDrawable(true);
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


        //std::cout<<"\n"<<(drawEl)->getName()<< " drawn"<<std::endl;
    }
    for(UWindowMap::iterator it = m_windows.begin();
        it != m_windows.end();
        ++it)
    {
        UWindowPtr uwindow = (*it).second;
        uwindow->setPosition(uwindow->getRestPosition());
        //std::cout<<"\n"<<(drawEl)->getName()<< " drawn"<<std::endl;
    }
}

//-------------------------------------------------------------------//
//---------------------------button functions------------------------//
//-------------------------------------------------------------------//
void UI::closeUpgradeMenuFunction()
{
    TablePtr menu = getMenu("upgradeMenu");
    menu->setDrawable(false);
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
    TablePtr createMenu = getMenu("towerbuildMenu");
    createMenu->setDrawable(false);
    uwindow->setDrawable(true);
    game->setPaused(true);
}

//-------------------------------------------------------------------//
void UI::closeMenuFunction()
{
    Game* game = Game::instance();
    UWindowPtr uwindow = getUWindow("inGameSettingsWindow");
    TablePtr menu = getMenu("scoreMenu");
    TablePtr createMenu = getMenu("towerbuildMenu");
    createMenu->setDrawable(true);
    uwindow->setDrawable(false);
    game->setPaused(false);
    menu->setTexture(1,0,"pauseButton");

}

//-------------------------------------------------------------------//
void UI::startGameFunction()
{
    Game *game = Game::instance();
    game->setPaused(false);
    UWindowPtr uwindow = getUWindow("startWindow");
    uwindow->setDrawable(false);
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

    createMenu->update(_dt);

}

//-------------------------------------------------------------------//
void UI::setUpAnimation()
{
    TablePtr createMenu = getMenu("towerbuildMenu");

    ngl::Vec2 endPos = (0,0);
    endPos.m_x = createMenu->getPosition().m_x;
    endPos.m_y = createMenu->getStartPos().m_y-createMenu->getSize().m_y;
    createMenu->setEndPos(endPos);
    createMenu->setSpeed(0.2);
    createMenu->setInterval(ngl::Vec2(0,0));
}

//-------------------------------------------------------------------//
void UI::closeTowerMenuFunction()
{
    std::cout<<"the button has been clicked"<<std::endl;
    TablePtr createMenu = getMenu("towerbuildMenu");

    ngl::Vec2 startPos = createMenu->getStartPos();
    ngl::Vec2 endPos = createMenu->getEndPos();

    if(createMenu->getPosition()== endPos)
    {
        createMenu->setStartPos(endPos);
        createMenu->setEndPos(startPos);
        startPos = createMenu->getStartPos();
        endPos = createMenu->getEndPos();
    }

    ngl::Vec2 interval;
    interval.m_y= (endPos.m_y-startPos.m_y)/createMenu->getSpeed();
    interval.m_x = 0;
    createMenu->setInterval(interval);
    createMenu->setAnimated(true);
}



