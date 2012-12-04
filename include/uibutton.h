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

typedef  boost::function<void()> functionPtr;

class UIButton : public UIElement

{
public:

    //-------------------------------------------------------------------//
    /// @brief ctor
    //-------------------------------------------------------------------//

    UIButton(ngl::Vec2 _pos, std::string _imageFile);


    UIButton();

    //-------------------------------------------------------------------//
    /// @brief dtor
    //-------------------------------------------------------------------//

    ~UIButton();


    void draw() const;


    functionPtr execute;


protected:


    //-------------------------------------------------------------------//
    /// @brief stores a pointer to the function that execute will run
    //-------------------------------------------------------------------//






};

#endif // UIBUTTON_H
