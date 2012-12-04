#ifndef UI_H
#define UI_H

#include "uimenu.h"
#include "entity.h"
#include "uielement.h"

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

    virtual void draw() const = 0;


    //-------------------------------------------------------------------//
    /// @brief checks to see if ui has been clicked
    /// @param [in] _ID, the colourID given by clickEvent from game.h
    /// @param [out] m_element, returns and UIElement point from
    /// m_elements or will return 0 if no UI has been clicked
    //-------------------------------------------------------------------//

    UIElementPtr checkUIClicked(unsigned int _ID);

    //-------------------------------------------------------------------//
    /// @brief checks to see if an entity has been clicked
    /// @param [in] _ID, the colourID given by clickEvent from game.h
    /// @param [out] returns a pointer to the entity that has been clicked
    /// and will return 0 if nothing is selected
    //-------------------------------------------------------------------//

    EntityPtr checkEntityClicked(unsigned int _ID);

    //-------------------------------------------------------------------//
    /// @brief the function which is run when the left mouse button is
    /// clicked down
    /// @param [in] _ID, the colourID given by clickEvent from game.h
    //-------------------------------------------------------------------//
    void mouseLeftDown(unsigned int _ID);

protected:

};




#endif // UI_H
