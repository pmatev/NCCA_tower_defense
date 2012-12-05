#ifndef UI_H
#define UI_H

#include "uimenu.h"
#include "staticentity.h"
#include "uielement.h"
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
public:

    //-------------------------------------------------------------------//
    /// @brief creates an instance of the class if it does not already exist
    /// @param [out] returns the instance of the class
    //-------------------------------------------------------------------//

    static UISelection* instance();


    //-------------------------------------------------------------------//
    /// @brief the destructor
    //-------------------------------------------------------------------//

    ~UISelection();

    //-------------------------------------------------------------------//
    /// @brief draw element
    //-------------------------------------------------------------------//

    void draw() const;

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

    EntityPtr checkEntityClicked(const unsigned int _ID);

    //-------------------------------------------------------------------//
    /// @brief the function which is run when the left mouse button is
    /// clicked down
    /// @param [in] _ID, the colourID given by clickEvent from game.h
    //-------------------------------------------------------------------//
    void mouseLeftUp(const unsigned int _ID);


    //-------------------------------------------------------------------//
    /// @brief register UIElement into IDMap
    /// @param [out] returns the id for the element
    //-------------------------------------------------------------------//
    unsigned int registerID(UIElementPtr _e);


    //-------------------------------------------------------------------//
    /// @brief unregister UIElement via ID
    //-------------------------------------------------------------------//
    void unregisterID(const unsigned int _i);




    void printTest();







    void createTestMen();



private:

    typedef std::map<unsigned int, UIMenuPtr> menuMap;

    //-------------------------------------------------------------------//
    /// @brief the default constructor
    //-------------------------------------------------------------------//
    UISelection();

    //-------------------------------------------------------------------//
    /// @brief stores all the menus for the game
    //-------------------------------------------------------------------//
    menuMap m_menus;


    UIMenuPtr m_menuTest;

    //-------------------------------------------------------------------//
    /// @brief ID Counter for distributing unique IDs to elements.
    //-------------------------------------------------------------------//
    unsigned int m_currentID;

    //-------------------------------------------------------------------//
    /// @brief A map of IDs to element Pointers for game object management.
    //-------------------------------------------------------------------//
    elementsMap m_IDMap;

    //-------------------------------------------------------------------//
    /// @brief stores the instance of the class
    //-------------------------------------------------------------------//
    static UISelection* s_instance;

    //-------------------------------------------------------------------//
    /// @brief temp storage for tower while it is being placed down
    //-------------------------------------------------------------------//
    EntityPtr m_createdEntity;


    //-------------------------------------------------------------------//
    /// @brief value to say whether we are in creation mode or not
    //-------------------------------------------------------------------//
    int m_creationMode;

    //-------------------------------------------------------------------//
    /// @brief when in creation mode this checks if the staticEntity can be
    /// placed on node if it can add to the list of towers else wait for
    /// do nothing until next click
    //-------------------------------------------------------------------//
    void createStaticEntity();



};




#endif // UI_H
