#ifndef UI_H
#define UI_H

#include "staticentity.h"
#include "uielement.h"
#include "entityfactory.h"
#include <boost/bind.hpp>
#include <boost/function.hpp>
#include "fwd/ui.h"
#include "fwd/table.h"
#include "fwd/uwindow.h"
#include "fwd/uibutton.h"




//-------------------------------------------------------------------//
/// @file ui.h
/// @brief the ui class manages the creation of all the ui aspects
/// and windows
/// @author Luke Gravett
/// @version 1
/// @date 28/11/12
/// Revision History :
/// Initial Version 28/11/12
/// @class UI
//-------------------------------------------------------------------//


class UI
{
    typedef std::map<unsigned int, UIElementPtr> elementsMap;
    typedef  boost::function<void()> functionPtr;
public:

    //-------------------------------------------------------------------//
    /// @brief the default constructor
    //-------------------------------------------------------------------//
    UI();

    //-------------------------------------------------------------------//
    /// @brief the destructor
    //-------------------------------------------------------------------//
    ~UI();

    //-------------------------------------------------------------------//
    /// @brief draw element
    //-------------------------------------------------------------------//
    void draw();

    //-------------------------------------------------------------------//
    /// @brief draw all elements with constant shader for selection
    //-------------------------------------------------------------------//
    void drawSelection();

    //-------------------------------------------------------------------//
    /// @brief see if a element has been clicked in the m_IDMap and return it
    //-------------------------------------------------------------------//
    UIElementPtr checkUIClicked(const unsigned int _ID);

    //-------------------------------------------------------------------//
    /// @brief the function which is run when the left mouse button is
    /// clicked down
    /// @param [in] _ID, the colourID given by clickEvent from window.h
    //-------------------------------------------------------------------//
    void mouseLeftUp(const unsigned int _ID);

    //-------------------------------------------------------------------//
    /// @brief the function which is run when the mouse is moved
    /// @param [in] _ID, the colourID given by clickEvent from window.h
    //-------------------------------------------------------------------//
    void mouseMoveEvent(const unsigned int _ID);

    //-------------------------------------------------------------------//
    /// @brief register UIElement into IDMap
    /// @param [in] _element takes in a new uielement
    /// @param [in] _ID id of the element
    //-------------------------------------------------------------------//
    void registerID(UIElementPtr _element, unsigned int _ID);

    //-------------------------------------------------------------------//
    /// @brief unregister UIElement via ID
    /// @param [in] _ID takes in the id of the element you want to unregister
    //-------------------------------------------------------------------//
    void unregisterID(const unsigned int _ID);

    //-------------------------------------------------------------------//
    /// @brief creates a new menu
    /// @param [in] _menu takes in a tableptr to create a new object and store
    /// in m_menus
    //-------------------------------------------------------------------//
    void createMenu(TablePtr _menu);

    //-------------------------------------------------------------------//
    /// @brief creates a new window
    /// @param [in] _pos takes a uiwindow in and stores it within m_windows
    /// @param [in] _name name of the element
    /// @param [in] _imageFile name of texture to be applied to element
    /// @param [in] _parent point to its parent
    /// @param [in] size of window
    //-------------------------------------------------------------------//
    void createWindow
    (
        ngl::Vec2 _pos,
        std::string _name,
        std::string _imageFile,
        UI *_parent,
        ngl::Vec2 _size
        );

    //-------------------------------------------------------------------//
    /// @brief searches the m_menus map and returns the object with the name
    /// specified in the parameters
    /// @param [in] _name takes in a string to the name of the menu you are trying
    /// to access
    //-------------------------------------------------------------------//
    TablePtr getMenu(std::string _name);

    //-------------------------------------------------------------------//
    /// @brief searches the m_uwindows map and returns the object with the name
    /// specified in the parameters
    /// @param [in] _name takes in a string to the name of the window you are trying
    /// to access
    //-------------------------------------------------------------------//
    UWindowPtr getUWindow(std::string _name);

    //-------------------------------------------------------------------//
    /// @brief goes through menus and checks the towers the buttons create
    /// are affordable
    //-------------------------------------------------------------------//
    void checkButtonAffordable();

    //-------------------------------------------------------------------//
    /// @brief initializes and creates the tower create menu
    //-------------------------------------------------------------------//
    void createTowerMenu();

    //-------------------------------------------------------------------//
    /// @brief initializes and creates the upgrade menu
    //-------------------------------------------------------------------//
    void createUpgradeMenu();

    //-------------------------------------------------------------------//
    /// @brief creates the heads up display for score and money
    //-------------------------------------------------------------------//
    void createDisplayScoreMenu();

    //-------------------------------------------------------------------//
    /// @brief command for when the upgrade button is clicked to upgrade
    /// currently selected tower
    //-------------------------------------------------------------------//
    void upgradeButtonCommand();

    //-------------------------------------------------------------------//
    /// @brief update function which runs the ui's every frame updates e.g.
    /// score
    /// @param [in] _dt time in millieseconds since last update call
    //-------------------------------------------------------------------//
    void update(const double _dt);

    //-------------------------------------------------------------------//
    /// @brief function used by the button in the upgrade menu to close it
    //-------------------------------------------------------------------//
    void closeUpgradeMenuFunction();

    //-------------------------------------------------------------------//
    /// @brief this is ran when a turret is clicked. it initialises the the
    /// upgrade value with its details
    /// @param [in] _ID the id of the element pressed
    //-------------------------------------------------------------------//
    void turretClicked(const unsigned int _ID);

    //-------------------------------------------------------------------//
    /// @brief sets the upgrade tower button id
    /// @param [in] _ID id of element
    //-------------------------------------------------------------------//
    inline void setUpgradeTowerId(int _ID) {m_tmpUpgradeTowerID = _ID;}

    //-------------------------------------------------------------------//
    /// @brief initalise function for the ui
    //-------------------------------------------------------------------//
    void setupUI();

    //-------------------------------------------------------------------//
    /// @brief when in creation mode this checks if the staticEntity can be
    /// placed on node if it can add to the list of towers else wait for
    /// do nothing until next click
    /// @param [in] _type type of tower to create
    /// @param [in] _node node to place the tower on
    //-------------------------------------------------------------------//
    void placeDownStaticEntity(const std::string &_type, NodePtr _node);

    //-------------------------------------------------------------------//
    /// @brief function to run on click event when in creation mode
    /// @param [in] _ID id of thing that is clicked
    //-------------------------------------------------------------------//
    void creationModeClick(const unsigned int _ID);

    //-------------------------------------------------------------------//
    /// @brief function to initialise the start menu
    //-------------------------------------------------------------------//
    void createStartMenu();

    //-------------------------------------------------------------------//
    /// @brief button function used to launch the game
    //-------------------------------------------------------------------//
    void startGameFunction();

    //-------------------------------------------------------------------//
    /// @brief says that the missile silo is wanting to be built
    //-------------------------------------------------------------------//

    inline void createMissileSiloFunction() {m_tmptowerType = "MissileSilo";
                                            m_tmpTowerMesh = "turret_base";}

    //-------------------------------------------------------------------//
    /// @brief says that the test turret is wanting to be built
    //-------------------------------------------------------------------//
    inline void createTestTowerFunction(){m_tmptowerType = "TestTurret";
                                         m_tmpTowerMesh = "turret_base";}

    //-------------------------------------------------------------------//
    /// @brief says that the wall is wanting to be built
    //-------------------------------------------------------------------//
    inline void createWallfunction() {m_tmptowerType ="StandardWall";
                                     m_tmpTowerMesh = "wall";}

    //-------------------------------------------------------------------//
    /// @brief creates the lose window
    //-------------------------------------------------------------------//
    void createLoseRestartMenu();

    //-------------------------------------------------------------------//
    /// @brief used by the restart button to reset the game and ui
    //-------------------------------------------------------------------//
    void resetFunction();

    //-------------------------------------------------------------------//
    /// @brief used by the play pause button to play and pause the game
    //-------------------------------------------------------------------//
    void playPauseFunction();

    //-------------------------------------------------------------------//
    /// @brief this function is run when the players base health is 0
    //-------------------------------------------------------------------//
    void gameLost();

    //-------------------------------------------------------------------//
    /// @brief resets the ui back to the start ready for to start the game
    /// again
    //-------------------------------------------------------------------//
    void resetUI();

    //-------------------------------------------------------------------//
    /// @brief used by the back to start window button to take the player back
    /// to the start menu
    //-------------------------------------------------------------------//
    void backToStartFunction();

    //-------------------------------------------------------------------//
    /// @brief creates the in game settings menu
    //-------------------------------------------------------------------//
    void createInGameSettingsWindow();

    //-------------------------------------------------------------------//
    /// @brief function called when you hit the close menu button in settings
    /// window
    //-------------------------------------------------------------------//
    void backToGameFunction();

    //-------------------------------------------------------------------//
    /// @brief function called when the in games settings button is pressed
    //-------------------------------------------------------------------//
    void inGameSettingsFunction();

    //-------------------------------------------------------------------//
    /// @brief resets all menus and windows back to their rest states
    //-------------------------------------------------------------------//
    void resetMenuPositions();

    //-------------------------------------------------------------------//
    /// @brief quits the game
    //-------------------------------------------------------------------//
    void quitFunction();

    //-------------------------------------------------------------------//
    /// @brief sell a tower
    //-------------------------------------------------------------------//
    void sellTowerFunction();

    //-------------------------------------------------------------------//
    /// @brief used on mouse move event to check if the ui is being hovered
    /// over
    /// @param [in] _ID id of the selected ui
    //-------------------------------------------------------------------//
    void uiHover(const unsigned int &_ID);

    //-------------------------------------------------------------------//
    /// @brief update loop used for handling the animation of the menus
    /// and elements
    /// @param [in] _dt time that has changed since last update
    //-------------------------------------------------------------------//
    void updateAnimation(const double &_dt);

    //-------------------------------------------------------------------//
    /// @brief function called when you click the arrow in the top left corner
    /// of the towerbuild menu. slides the menu down
    //-------------------------------------------------------------------//
    void closeTowerMenuFunction();

    //-------------------------------------------------------------------//
    /// @brief sets the m_creation mode variable and also turns off create
    /// tower button
    /// @param [in] _creation tells what to turn m_creationMode for
    //-------------------------------------------------------------------//
    void setCreationMode(bool _creation);

    //-------------------------------------------------------------------//
    /// @brief sets the buttons state
    /// @param [in] _ID id of the element clicked
    /// @param [in] _state the state to set the button to
    //-------------------------------------------------------------------//
    bool setButtonState(const unsigned int _ID, ButtonState _state);

    //-------------------------------------------------------------------//
    /// @brief mouse left down event function
    /// @param [in] _ID id of element
    //-------------------------------------------------------------------//
    void mouseLeftDown(const unsigned int _ID);

    //-------------------------------------------------------------------//
    /// @brief sets the button which is pressed back to its default state
    /// @param [in] id of element
    //-------------------------------------------------------------------//
    void mouseDisablePressedState();

    void setHighlighted(const unsigned int _id, const int _state);


private:

    typedef std::map<unsigned int, TablePtr> MenuMap;

    typedef std::map<unsigned int, UWindowPtr> UWindowMap;


    //-------------------------------------------------------------------//
    /// @brief stores all the menus for the game
    //-------------------------------------------------------------------//
    MenuMap m_menus;

    //-------------------------------------------------------------------//
    /// @brief stores all the windows for the game
    //-------------------------------------------------------------------//
    UWindowMap m_windows;

    //-------------------------------------------------------------------//
    /// @brief A map of IDs to element Pointers for game object management.
    //-------------------------------------------------------------------//
    elementsMap m_IDMap;

    //-------------------------------------------------------------------//
    /// @brief value to say whether we are in creation mode or not
    //-------------------------------------------------------------------//
    bool m_creationMode;

    //-------------------------------------------------------------------//
    /// @brief stores id to highlighted node for selection
    //-------------------------------------------------------------------//
    unsigned int m_currentlyHighlighted;

    //-------------------------------------------------------------------//
    /// @brief transform stack used in creation mode for tmp mesh
    //-------------------------------------------------------------------//
    ngl::TransformStack m_transformStack;

    //-------------------------------------------------------------------//
    /// @brief temp storage for tower while it is being placed down
    //-------------------------------------------------------------------//
    std::string m_tmptowerType;

    //-------------------------------------------------------------------//
    /// @brief stores cost of tower that will be created
    //-------------------------------------------------------------------//
    int m_tmpCost;

    //-------------------------------------------------------------------//
    /// @brief stores the id value of the tower button pressed. used for
    /// creation mode checking
    //-------------------------------------------------------------------//
    unsigned int m_tmpTowerButtonID;

    //-------------------------------------------------------------------//
    /// @brief position of node when in creation mode for mesh movement
    //-------------------------------------------------------------------//
    ngl::Vec3 m_tmpNodePos;

    //-------------------------------------------------------------------//
    /// @brief mesh object to be drawn when in creation mode
    //-------------------------------------------------------------------//
    std::string m_tmpTowerMesh;

    //-------------------------------------------------------------------//
    /// @brief stores the id value of the towers id used for the upgrade menu
    //-------------------------------------------------------------------//
    unsigned int m_tmpUpgradeTowerID;

    //-------------------------------------------------------------------//
    /// @brief stores the id value of the button currently hovered over
    //-------------------------------------------------------------------//
    unsigned int m_tmpHoverButton;

    //-------------------------------------------------------------------//
    /// @brief stores the id value of the button currently pressed down
    //-------------------------------------------------------------------//
    unsigned int m_tmpButtonPressed;

    //-------------------------------------------------------------------//
    /// @brief bool stating whether or not the first wave has been initialized
    //-------------------------------------------------------------------//
    bool m_gameStart;
};




#endif // UI_H
