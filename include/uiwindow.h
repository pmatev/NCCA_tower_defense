#ifndef UIWINDOW_H
#define UIWINDOW_H


//-------------------------------------------------------------------//
/// @file uiwindow.h
/// @brief The UIWIndow class is a window which can contain both UIMenus
/// and UIElements. This class is used for windows which will pause the
/// game
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

    virtual void draw() const = 0;
};

#endif // UIWINDOW_H
