#ifndef UIMENU_H
#define UIMENU_H


#include <ngl/Vec2.h>
#include "smartpointers.h"
#include "uielement.h"
#include <boost/function.hpp>
#include <boost/bind.hpp>
#include "fwd/uimenu.h"
#include "fwd/uibutton.h"
#include "fwd/uiselection.h"


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



class UIMenu : public UIElement

{

typedef  boost::function<void()> functionPtr;

public:
    //-------------------------------------------------------------------//
    /// @brief the constructor
    //-------------------------------------------------------------------//
    UIMenu(ngl::Vec2 _pos,
           std::string _imageFile,
           std::string _name,
           UISelection *_parent);
    //-------------------------------------------------------------------//
    /// @brief the destructor
    //-------------------------------------------------------------------//
    ~UIMenu();

    //-------------------------------------------------------------------//
    /// @brief draw element
    //-------------------------------------------------------------------//

    void draw() ;

    //-------------------------------------------------------------------//
    /// @brief draw element with constant shader for selection use
    //-------------------------------------------------------------------//
    void drawSelection();



    //-------------------------------------------------------------------//
    /// @brief aligns menu to bottom of window
    //-------------------------------------------------------------------//
    void alignBottom();


    //-------------------------------------------------------------------//
    /// @brief aligns menu to top of window
    //-------------------------------------------------------------------//
    void alignTop();

    //-------------------------------------------------------------------//
    /// @brief aligns menu to left of window
    //-------------------------------------------------------------------//
    void alignLeft();


    //-------------------------------------------------------------------//
    /// @brief aligns menu to right of window
    //-------------------------------------------------------------------//
    void alignRight();


    //-------------------------------------------------------------------//
    /// @brief creates a button within the menu
    /// @param [in] takes vec2 for button position
    /// @param [in] string for image file path for texture
    /// @param [in] string for name of button it wants to create
    //-------------------------------------------------------------------//

    void addButton(ngl::Vec2 _pos,
                   std::string _imageFile,
                   std::string _name);

    //-------------------------------------------------------------------//
    /// @brief connects functions to ui elements
    /// @param [in] boost::function which connects to the ui elements
    /// function parameter
    /// @param [in] string which is the name of the element you are trying
    /// to connect to
    //-------------------------------------------------------------------//
    void connectEvent(functionPtr _func, std::string _name);


    //-------------------------------------------------------------------//
    /// @brief defines the virtual setFubction which in this case prints
    /// out and error message
    /// @param [in] takes in a boost function but does nothing but print it
    /// out as a menu doesn't store a function
    //-------------------------------------------------------------------//

    void setFunction(functionPtr _func);

    //-------------------------------------------------------------------//
    /// @brief returns the id for the element
    /// @param [out] returns the m_ID of the object
    //-------------------------------------------------------------------//
    inline unsigned int getID() const {return m_ID;}

    //-------------------------------------------------------------------//
    /// @brief implement execute function which in this case will do nothing
    //-------------------------------------------------------------------//

    void isClicked();



    //-------------------------------------------------------------------//
    //-------------------------------------------------------------------//
    //-------------------------------------------------------------------//
    void runCommandTest();

    void createButtons();
    //-------------------------------------------------------------------//
    //-------------------------------------------------------------------//
    //-------------------------------------------------------------------//



    typedef std::vector<UIElementPtr> elementsMap;

protected:


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
    /// @brief stores parents information
    //-------------------------------------------------------------------//
    UISelection *m_parent;



    //-------------------------------------------------------------------//
    //-------------------------------------------------------------------//
    //-------------------------------------------------------------------//
    UIButtonPtr m_buttonTest;
    //-------------------------------------------------------------------//
    //-------------------------------------------------------------------//
    //-------------------------------------------------------------------//



};

#endif // UIMENU_H
