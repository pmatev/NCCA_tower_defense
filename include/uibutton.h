#ifndef UIBUTTON_H
#define UIBUTTON_H

#include "smartpointers.h"
#include "uielement.h"
#include <boost/function.hpp>
#include <boost/bind.hpp>

//-------------------------------------------------------------------//
/// @file uibutton.h
/// @brief The button class used for ui buttons to run function,
/// inherits from uielement class
/// @author Luke Gravett
/// @version 1
/// @date 03/12/12
/// Revision History :
/// Initial Version 03/12/12
/// @class UIButton
//-------------------------------------------------------------------//

DECLARESMART(UIButton)



class UIButton : public UIElement

{
public:

    //-------------------------------------------------------------------//
    /// @brief a parameterised constructor
    /// @param [in] _pos, a Vec2 value for the starting position of the
    /// button
    /// @param [in] _imageFile, a string containing the image file path name
    /// @param [in] inputs a string for the name of the element
    //-------------------------------------------------------------------//

    UIButton(ngl::Vec2 _pos, std::string _imageFile,
             std::string _name);

    //-------------------------------------------------------------------//
    /// @brief default ctor
    //-------------------------------------------------------------------//

    UIButton();

    //-------------------------------------------------------------------//
    /// @brief dtor
    //-------------------------------------------------------------------//

    ~UIButton();


    //-------------------------------------------------------------------//
    /// @brief defines the virtual setFubction which in this case prints
    /// out and error message
    /// @param [in] takes in a boost function and stores it within the button
    //-------------------------------------------------------------------//

    inline void setFunction(functionPtr _func)  {m_execute = _func;}

    //-------------------------------------------------------------------//
    /// @brief executes the buttons command
    //-------------------------------------------------------------------//

    inline void isClicked() {m_execute();}



    //-------------------------------------------------------------------//
    /// @brief draws the button
    //-------------------------------------------------------------------//

    void draw();


    void drawSelection();







};

#endif // UIBUTTON_H
