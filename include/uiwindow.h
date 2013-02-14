#ifndef UIWINDOW_H
#define UIWINDOW_H


//-------------------------------------------------------------------//
/// @file uiwindow.h
/// @brief The UiWindow is a composite of UIElements and controls every
/// UI which is displayed while game is not running
/// @author Luke Gravett
/// @version 1
/// @date 28/11/12
/// Revision History :
/// Initial Version 28/11/12
/// @class UIWindow
//-------------------------------------------------------------------//



class UIWindow
{
public:
    //-------------------------------------------------------------------//
    /// @brief the constructor
    //-------------------------------------------------------------------//
    UIWindow();

    //-------------------------------------------------------------------//
    /// @brief the destructor
    //-------------------------------------------------------------------//
    ~UIWindow();

    //-------------------------------------------------------------------//
    /// @brief draw element
    //-------------------------------------------------------------------//

    virtual void draw() = 0;
};

#endif // UIWINDOW_H
