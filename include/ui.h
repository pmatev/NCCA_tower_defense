#ifndef UI_H
#define UI_H


#include "staticentity.h"
#include "uielement.h"
#include "entityfactory.h"
#include <boost/bind.hpp>
#include <boost/function.hpp>
#include "fwd/ui.h"
#include "fwd/table.h"


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
    /// @brief see if a element has been clicked in the m_IDMap
    /// @param [out] returns an element pointer which will either contain
    /// the clicked button or an empty one if none were clicked
    //-------------------------------------------------------------------//
    UIElementPtr checkUIClicked(const unsigned int _ID);

    //-------------------------------------------------------------------//
    /// @brief checks to see if an entity has been clicked
    /// @param [in] _ID, the colourID given by clickEvent from game.h
    /// @param [out] returns a pointer to the entity that has been clicked
    /// and will return 0 if nothing is selected
    //-------------------------------------------------------------------//
    EntityWPtr checkEntityClicked();

    //-------------------------------------------------------------------//
    /// @brief the function which is run when the left mouse button is
    /// clicked down
    /// @param [in] _ID, the colourID given by clickEvent from game.h
    //-------------------------------------------------------------------//
    void mouseLeftUp(const unsigned int _ID);

    //-------------------------------------------------------------------//
    /// @brief the function which is run when the mouse is moved
    //-------------------------------------------------------------------//
    void mouseMoveEvent(const unsigned int _ID);

    //-------------------------------------------------------------------//
    /// @brief register UIElement into IDMap
    /// @param [in] takes in a new uielement
    /// @param [out] returns the id for the element
    //-------------------------------------------------------------------//
    void registerID(UIElementPtr _e, unsigned int _ID);

    //-------------------------------------------------------------------//
    /// @brief unregister UIElement via ID
    /// @param [in] takes in the id of the element you want to unregister
    //-------------------------------------------------------------------//
    void unregisterID(const unsigned int _i);

    //-------------------------------------------------------------------//
    /// @brief creates tower into temporary storage to be placed down
    /// @param [in] takes in string refering to type of staticEntity
    /// @param [in] takes in the node which it will be placed on
    //-------------------------------------------------------------------//
    void createTestTower();

    //-------------------------------------------------------------------//
    /// @brief creates a new menu
    /// @param [in] takes in a tableptr to create a new object and store
    /// in m_menus
    //-------------------------------------------------------------------//
    void createMenu(TablePtr _menu);

    //-------------------------------------------------------------------//
    /// @brief searches the m_menus map and returns the object with the name
    /// specified in the parameters
    /// @param [in] takes in a string to the name of the menu you are trying
    /// to access
    /// @param [out] returns a TablePtr with the name specified
    //-------------------------------------------------------------------//
    TablePtr getMenu(std::string _name);

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
    //-------------------------------------------------------------------//
    void updatePlayerInfo();

    //-------------------------------------------------------------------//
    /// @brief function used by the button in the upgrade menu to close it
    //-------------------------------------------------------------------//
    void closeUpgradeMenu();

    //-------------------------------------------------------------------//
    /// @brief this is ran when a turret is clicked. it initialises the the
    /// upgrade value with its details
    //-------------------------------------------------------------------//
    void turretClicked(int _ID);

    //-------------------------------------------------------------------//
    /// @brief sets the upgrade id
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
    /// @param [in] takes in the _ID
    //-------------------------------------------------------------------//
    void placeDownStaticEntity(const std::string &_type, NodePtr _node);

    //-------------------------------------------------------------------//
    /// @brief function to run on click event when in creation mode
    /// @param [in] takes in the _ID
    //-------------------------------------------------------------------//
    void creationModeClick(const unsigned int _ID);

private:

    typedef std::map<unsigned int, TablePtr> MenuMap;


    //-------------------------------------------------------------------//
    /// @brief stores all the menus for the game
    //-------------------------------------------------------------------//
    MenuMap m_menus;

    //-------------------------------------------------------------------//
    /// @brief A map of IDs to element Pointers for game object management.
    //-------------------------------------------------------------------//
    elementsMap m_IDMap;

    //-------------------------------------------------------------------//
    /// @brief temp storage for tower while it is being placed down
    //-------------------------------------------------------------------//
    std::string m_tmptowerType;

    //-------------------------------------------------------------------//
    /// @brief value to say whether we are in creation mode or not
    //-------------------------------------------------------------------//
    bool m_creationMode;

    //-------------------------------------------------------------------//
    /// @brief stores id to highlighted node for selection
    //-------------------------------------------------------------------//
    unsigned int m_highlightedNode;

    //-------------------------------------------------------------------//
    /// @brief stores cost of tower that will be created
    //-------------------------------------------------------------------//
    int m_tmpCost;

    //-------------------------------------------------------------------//
    /// @brief stores the id value of the towers id used for the upgrade menu
    //-------------------------------------------------------------------//
    unsigned int m_tmpUpgradeTowerID;









};




#endif // UI_H
