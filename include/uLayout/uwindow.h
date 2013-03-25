#ifndef UWINDOW_H
#define UWINDOW_H

#include "uielement.h"
#include "smartpointers.h"
#include "window.h"
#include "game.h"
#include "renderer.h"
#include "texturelib.h"
#include "fwd/ui.h"
#include "uibutton.h"
#include "costbutton.h"
#include "fwd/uwindow.h"


//-------------------------------------------------------------------//
/// @file uwindow.h
/// @brief The UWindow inherits from uielements. It is similar to tables
/// class but is only used when the game is not running and contains only
/// absolute elements so that its size is not deteremined by the elements
/// and the elements positions are not defined by its porisition
/// @author Luke Gravett
/// @version 1
/// @date 28/11/12
/// Revision History :
/// Initial Version 28/11/12
/// @class UWindow
//-------------------------------------------------------------------//


class UWindow : public UIElement
{

public:
    enum AlignType {RIGHT, LEFT, TOP, BOTTOM, CENTREX,CENTREY};


    //-------------------------------------------------------------------//
    /// @brief overloaded constructor
    /// @param [in] _pos position of table
    /// @param [in] _name name of table
    /// @param [in] _imageFile string of image path file
    /// @param [in] _parent stores a pointer to its parent
    /// @param [in] _size vec 2 stating the size of the window
    //-------------------------------------------------------------------//
    UWindow(
        ngl::Vec2 _pos,
        std::string _name,
        std::string _imageFile,
        UI *_parent,
        ngl::Vec2 _size
        );

    //-------------------------------------------------------------------//
    /// @brief default destructor
    //-------------------------------------------------------------------//
    ~UWindow();

    //-------------------------------------------------------------------//
    /// @brief function to create a cost button
    /// @param [in] _pos initial position of element
    /// @param [in] _imageFile image file name
    /// @param [in] _name name of element
    /// @param [in] _cost cost of the tower
    /// @param [in] _maxX x size of button
    /// @param [in] _maxY y size of button
    //-------------------------------------------------------------------//
    void createCostButton
            (
                const ngl::Vec2 &_pos,
                const std::string &_imageFile,
                const std::string &_name,
                const ElementType &_type,
                const int &_cost,
                const float &_maxX,
                const float &_maxY
                );

    //-------------------------------------------------------------------//
    /// @brief function to create a text ui
    /// @param [in] _pos initial position of element
    /// @param [in] _text text to be drawn
    /// @param [in] _fontFile path to font file
    /// @param [in] _ptsize size of font
    /// @param [in] _name name of text element
    //-------------------------------------------------------------------//
    void createText
            (
                const ngl::Vec2 &_pos,
                const char *_text,
                const char *_fontFile,
                const int &_ptsize,
                const std::string &_name
                );

    //-------------------------------------------------------------------//
    /// @brief function to create a table
    /// @param [in] _pos intial position of table
    /// @param [in] _name name of table
    /// @param [in] _imageFile texture name for the table
    /// @param [in] _slideType specifies the type of animation the table has
    /// @param [in] _parent stores a pointer to its parent
    //-------------------------------------------------------------------//
    void createTable(const ngl::Vec2 &_pos,
                     const std::string &_name,
                     const std::string &_imageFile,
                     const std::string &_slideType,
                     UI *_parent);

    //-------------------------------------------------------------------//
    /// @brief function to create a standard button
    /// @param [in] _pos initial position of element
    /// @param [in] _imageFile name of texture applied to button
    /// @param [in] _name name of element
    /// @param [in] _maxX x size of button
    /// @param [in] _maxY y size of button
    //-------------------------------------------------------------------//
    void createButton
            (
                const ngl::Vec2 &_pos,
                const std::string &_imageFile,
                const std::string &_name,
                const float &_maxX,
                const float &_maxY
                );

    //-------------------------------------------------------------------//
    /// @brief draw function for the window
    //-------------------------------------------------------------------//
    void draw();

    //-------------------------------------------------------------------//
    /// @brief aligns a specific element to a specific location based on
    /// window location
    /// @param [in] _name string of the name of the element you want align
    /// @param [in] _alignment enum specifying the type of alignment wanted
    //-------------------------------------------------------------------//
    void alignElement(const std::string &_name,const AlignType &_alignment);

    //-------------------------------------------------------------------//
    /// @brief sets whether the entire table is drawn including its rows
    /// @param [in] _drawable true false value specifying whether it is drawable
    //-------------------------------------------------------------------//
    void setDrawable(bool _drawable) {m_isDrawable = _drawable;}

    //-------------------------------------------------------------------//
    /// @brief searches through elements for the name specified and
    /// sets its function if it is a button
    /// @param [in] _name name of button
    /// @param [in] _function function to set in the button
    //-------------------------------------------------------------------//
    void setFunction(const std::string &_name, UIButton::functionPtr _function);

    //-------------------------------------------------------------------//
    /// @brief searches through elements for the name specified and
    /// returns the element if found
    /// @param [in] _name states the element you want to get
    //-------------------------------------------------------------------//
    UIElementPtr getElement(std::string _name);

    private:

    typedef std::vector<UIElementPtr> ElementVector;

    //-------------------------------------------------------------------//
    /// @brief stores the elements in a vector
    //-------------------------------------------------------------------//

    ElementVector m_elements;

    //-------------------------------------------------------------------//
    /// @brief flag to specify if the background will be drawn
    //-------------------------------------------------------------------//
    bool m_backgroundVisible;

    //-------------------------------------------------------------------//
    /// @brief stores parents information
    //-------------------------------------------------------------------//
    UI *m_parent;

    //-------------------------------------------------------------------//
    /// @brief flag to say whether the table will be drawn or not
    //-------------------------------------------------------------------//
    bool m_isDrawable;









};

#endif // UWINDOW_H
