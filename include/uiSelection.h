#ifndef UI_H
#define UI_H

#include "uimenu.h"
#include "staticentity.h"
#include "uielement.h"
#include "entityfactory.h"
#include <boost/bind.hpp>
#include <boost/function.hpp>

//-------------------------------------------------------------------//
/// @file uiselection.h
/// @brief the ui class manages the creation of all the ui aspects
/// and windows
/// @author Luke Gravett
/// @version 1
/// @date 28/11/12
/// Revision History :
/// Initial Version 28/11/12
/// @class UISelection
//-------------------------------------------------------------------//
DECLARESMART(UISelection)

class UISelection
{
    typedef std::map<unsigned int, UIElementPtr> elementsMap;
    typedef  boost::function<void()> functionPtr;
public:

    //-------------------------------------------------------------------//
    /// @brief the default constructor
    //-------------------------------------------------------------------//
    UISelection();

    //-------------------------------------------------------------------//
    /// @brief the destructor
    //-------------------------------------------------------------------//

    ~UISelection();



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
    EntityPtr checkEntityClicked();


    //-------------------------------------------------------------------//
    /// @brief the function which is run when the left mouse button is
    /// clicked down
    /// @param [in] _ID, the colourID given by clickEvent from game.h
    //-------------------------------------------------------------------//
    void mouseLeftUp(const unsigned int _ID);


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
    /// @param [in] takes in a uimenuptr to create a new object and store
    /// in m_menus
    //-------------------------------------------------------------------//
    void createMenu(UIMenuPtr _menu);


    //-------------------------------------------------------------------//
    /// @brief searches the m_menus map and returns the object with the name
    /// specified in the parameters
    /// @param [in] takes in a string to the name of the menu you are trying
    /// to access
    /// @param [out] returns a UIMenuPtr with the name specified
    //-------------------------------------------------------------------//
    UIMenuPtr getMenu(std::string _name);


    //-------------------------------------------------------------------//
    //-------------------------------------------------------------------//
    //-------------------------------------------------------------------//
    void printTest();

    void printTest2();

    void createTestMenu();

    void createMenu();

    void mouseLeftUpTowerCreate(const unsigned int _ID);

    //-------------------------------------------------------------------//
    //-------------------------------------------------------------------//
    //-------------------------------------------------------------------//



private:

    typedef std::map<unsigned int, UIMenuPtr> menuMap;


    //-------------------------------------------------------------------//
    /// @brief stores all the menus for the game
    //-------------------------------------------------------------------//
    menuMap m_menus;

    //-------------------------------------------------------------------//
    /// @brief A map of IDs to element Pointers for game object management.
    //-------------------------------------------------------------------//
    elementsMap m_IDMap;

    //-------------------------------------------------------------------//
    /// @brief temp storage for tower while it is being placed down
    //-------------------------------------------------------------------//
    std::string m_staticEntityTypeTemp;


    //-------------------------------------------------------------------//
    /// @brief value to say whether we are in creation mode or not
    //-------------------------------------------------------------------//
    bool m_creationMode;


    //-------------------------------------------------------------------//
    /// @brief when in creation mode this checks if the staticEntity can be
    /// placed on node if it can add to the list of towers else wait for
    /// do nothing until next click
    /// @param [in] takes in the _ID
    //-------------------------------------------------------------------//
    void placeDownStaticEntity(const std::string &_type, NodePtr _node);



    //-------------------------------------------------------------------//
    //-------------------------------------------------------------------//
    //-------------------------------------------------------------------//
    UIMenuPtr m_menuTest;


    //-------------------------------------------------------------------//
    //-------------------------------------------------------------------//
    //-------------------------------------------------------------------//




};




#endif // UI_H
