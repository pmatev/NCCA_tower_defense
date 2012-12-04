#ifndef UIMENU_H
#define UIMENU_H


#include <ngl/Vec2.h>
#include "smartpointers.h"
#include "uibutton.h"


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

    void draw() const;

    //-------------------------------------------------------------------//
    /// @brief see if a element has been clicked
    /// @param [out] returns a button pointer which will either contain
    /// the clicked button or an empty one if none were clicked
    //-------------------------------------------------------------------//

    UIButtonPtr returnClickedElement(const unsigned int _colourID);


    void alignBottom();





    //-------------------------------------------------------------------//
    //-------------------------------------------------------------------//
    //-------------------------------------------------------------------//
    //inline UIButtonPtr getbutton() {return m_buttonTest;}

    void createButtonTest(ngl::Vec2 _pos, std::string _imageFile);

    void printTest();
    //-------------------------------------------------------------------//
    //-------------------------------------------------------------------//
    //-------------------------------------------------------------------//





    typedef std::map<unsigned int, UIButtonPtr> buttonsMap;

protected:

    //-------------------------------------------------------------------//
    /// @brief position of uielement in 2d space
    //-------------------------------------------------------------------//

    ngl::Vec2 m_pos;

    //-------------------------------------------------------------------//
    /// @brief a list of smart pointers to just the buttons contained within
    /// the menu
    //-------------------------------------------------------------------//

    buttonsMap m_buttons;

    //-------------------------------------------------------------------//
    /// @brief flag which specifies whether the menu is displayable or not
    /// for rendering
    //-------------------------------------------------------------------//

    bool m_displayed;

    //-------------------------------------------------------------------//
    /// @brief stores the maximum size in x direction can either be percentage
    /// or pixel value
    //-------------------------------------------------------------------//
    float m_maxBoundsX;


    //-------------------------------------------------------------------//
    /// @brief stores the maximum size in y direction can either be percentage
    /// or pixel value
    //-------------------------------------------------------------------//
    float m_maxBoundsY;



};

#endif // UIMENU_H
