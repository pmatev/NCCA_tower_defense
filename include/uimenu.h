#ifndef UIMENU_H
#define UIMENU_H


#include <ngl/Vec2.h>
#include "smartpointers.h"
#include "uielement.h"


//-------------------------------------------------------------------//
/// @file uimenu.h
/// @brief The UIMenu class conatins UIelements for use within the game
/// to interact with the running game
/// @author Luke Gravett
/// @version 1
/// @date 28/11/12
/// Revision History :
/// Initial Version 28/11/12
/// @class UIMenu
//-------------------------------------------------------------------//
DECLARESMART(UIMenu)

class UIMenu

{
public:
    //-------------------------------------------------------------------//
    /// @brief the constructor
    //-------------------------------------------------------------------//
    UIMenu();
    //-------------------------------------------------------------------//
    /// @brief the destructor
    //-------------------------------------------------------------------//
    ~UIMenu();

    //-------------------------------------------------------------------//
    /// @brief draw element
    //-------------------------------------------------------------------//

    virtual void draw() const = 0;

    //-------------------------------------------------------------------//
    /// @brief see if a element has been clicked
    //-------------------------------------------------------------------//

    UIElementPtr returnClickedElement(const unsigned int _colourID);

    typedef std::map<unsigned int, UIElementPtr> elementsMap;

protected:

    //-------------------------------------------------------------------//
    /// @brief position of uielement in 2d space
    //-------------------------------------------------------------------//

    ngl::Vec2 m_pos;

    //-------------------------------------------------------------------//
    /// @brief a list of smart pointers to UIElements contained within
    /// the menu
    //-------------------------------------------------------------------//

    elementsMap m_elements;






};

#endif // UIMENU_H
