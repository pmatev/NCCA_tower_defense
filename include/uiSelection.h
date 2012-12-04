#ifndef UI_H
#define UI_H

#include "uimenu.h"
#include "entity.h"
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
    void draw() const;


    //-------------------------------------------------------------------//
    /// @brief checks to see if ui has been clicked
    /// @param [in] _ID, the colourID given by clickEvent from game.h
    /// @param [out] m_element, returns and UIElement point from
    /// m_elements or will return 0 if no UI has been clicked
    //-------------------------------------------------------------------//

    UIButtonPtr checkUIClicked(const unsigned int _ID);

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
    void mouseLeftDown(const unsigned int _ID);


    void createTestMen();



protected:

    typedef std::map<unsigned int, UIMenuPtr> menuMap;

    //-------------------------------------------------------------------//
    /// @brief stores all the menus for the game
    //-------------------------------------------------------------------//
    menuMap m_menus;

    UIMenuPtr m_menuTest;

};




#endif // UI_H
