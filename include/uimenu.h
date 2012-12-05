#ifndef UIMENU_H
#define UIMENU_H


#include <ngl/Vec2.h>
#include "smartpointers.h"
#include "uibutton.h"
#include "uielement.h"
#include <boost/function.hpp>
#include <boost/bind.hpp>

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



class UIMenu : public UIElement

{

typedef  boost::function<void()> functionPtr;

public:
    //-------------------------------------------------------------------//
    /// @brief the constructor
    //-------------------------------------------------------------------//
    UIMenu(ngl::Vec2 _pos,
           std::string _imageFile,
           std::string _name);
    //-------------------------------------------------------------------//
    /// @brief the destructor
    //-------------------------------------------------------------------//
    ~UIMenu();

    //-------------------------------------------------------------------//
    /// @brief draw element
    //-------------------------------------------------------------------//

    void draw() const;


    //-------------------------------------------------------------------//
    /// @brief aligns selected object to bottom of menu
    //-------------------------------------------------------------------//

    void alignBottom();


    //-------------------------------------------------------------------//
    /// @brief creates a button within the menu
    /// @param [in] takes in a UIButtonPtr
    //-------------------------------------------------------------------//

    void addButton(UIButtonPtr _button);

    //-------------------------------------------------------------------//
    /// @brief connects functions to ui elements
    /// @param [in] boost::function which connects to the ui elements
    /// function parameter
    /// @param [in] string which is the name of the element you are trying
    /// to connect to
    //-------------------------------------------------------------------//

    void connect(functionPtr _func, std::string _name);


    //-------------------------------------------------------------------//
    /// @brief defines the virtual setFubction which in this case prints
    /// out and error message
    //-------------------------------------------------------------------//

    void setFunction(functionPtr _func);





    //-------------------------------------------------------------------//
    //-------------------------------------------------------------------//
    //-------------------------------------------------------------------//
    void runCommandTest();
    //-------------------------------------------------------------------//
    //-------------------------------------------------------------------//
    //-------------------------------------------------------------------//





    //-------------------------------------------------------------------//
    /// @brief implement execute function which in this case will do nothing
    //-------------------------------------------------------------------//

    void isClicked();





    typedef std::vector<UIElementPtr> elementsMap;

protected:

    //-------------------------------------------------------------------//
    /// @brief position of uielement in 2d space
    //-------------------------------------------------------------------//

    ngl::Vec2 m_pos;

    //-------------------------------------------------------------------//
    /// @brief a list of shared pointers to the all the elements within
    /// the menu
    //-------------------------------------------------------------------//

    elementsMap m_elements;

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



    //-------------------------------------------------------------------//
    //-------------------------------------------------------------------//
    //-------------------------------------------------------------------//
    UIButtonPtr m_buttonTest;
    //-------------------------------------------------------------------//
    //-------------------------------------------------------------------//
    //-------------------------------------------------------------------//



};

#endif // UIMENU_H
