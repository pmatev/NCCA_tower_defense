#ifndef UIBUTTON_H
#define UIBUTTON_H

#include "smartpointers.h"
#include "uielement.h"
#include <boost/function.hpp>
#include <boost/bind.hpp>
#include "fwd/uibutton.h"
#include "uLayout/table.h"

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



class UIButton : public UIElement

{

public:


    typedef  boost::function<void()> functionPtr;




    //-------------------------------------------------------------------//
    /// @brief a parameterised constructor
    /// @param [in] _pos, a Vec2 value for the starting position of the
    /// button
    /// @param [in] _imageFile, a string containing the image file path name
    /// @param [in] _name inputs a string for the name of the element
    /// @param [in] _maxX maxX used for size of button
    /// @param [in] _maxY maxY used for size of button
    //-------------------------------------------------------------------//
    UIButton
    (
            ngl::Vec2 _pos,
            std::string _imageFile,
            std::string _name,
            float _maxX,
            float _maxY
            );


    //-------------------------------------------------------------------//
    /// @brief a parameterised constructor
    /// @param [in] _pos, a Vec2 value for the starting position of the
    /// button
    /// @param [in] _imageFile, a string containing the image file path name
    /// @param [in] _name inputs a string for the name of the element
    /// @param [in] _type string saying what type of element it is
    /// @param [in] _maxX used for x size of button
    /// @param [in] _maxY used for y size of button
    //-------------------------------------------------------------------//
    UIButton
    (
            ngl::Vec2 _pos,
            std::string _imageFile,
            std::string _name,
            ElementType _type,
            float _maxX,
            float _maxY
            );

    //-------------------------------------------------------------------//
    /// @brief dtor
    //-------------------------------------------------------------------//
    ~UIButton();

    //-------------------------------------------------------------------//
    /// @brief draws the button
    //-------------------------------------------------------------------//
    void draw();

    //-------------------------------------------------------------------//
    /// @brief draws the selection used mouse clicks
    //-------------------------------------------------------------------//
    void drawSelection();

    //-------------------------------------------------------------------//
    /// @brief deafault function for m_execute it does nothing
    //-------------------------------------------------------------------//
    void blankFunction();

    //-------------------------------------------------------------------//
    /// @brief defines the function to be run by the button
    /// @param [in] _func boost function pointer to the function to be executed by
    /// the button
    //-------------------------------------------------------------------//
    inline void setFunction(functionPtr _func)  {m_execute = _func;}

    //-------------------------------------------------------------------//
    /// @brief runs the buttons function
    //-------------------------------------------------------------------//
    inline void execute() {m_execute();}

    //-------------------------------------------------------------------//
    /// @brief function to create a text label
    /// @param [in] _pos initial position of element
    /// @param [in] _text text to be drawn
    /// @param [in] _fontFile path to font file
    /// @param [in] _ptsize size of font
    /// @param [in] _name of text element
    /// @param [in] _position in relation to table
    //-------------------------------------------------------------------//
    void createLabel
    (
        ngl::Vec2 _pos,
        const char *_text,
        const char *_fontFile,
        int _ptsize,
        std::string _name,
        LabelPosition _position
        );

    //-------------------------------------------------------------------//
    /// @brief sets the buttons label position based on the m_label enum
    //-------------------------------------------------------------------//
    void setLabelPosition();

    //-------------------------------------------------------------------//
    /// @brief get function to return the m_boundSize
    //-------------------------------------------------------------------//
    inline ngl::Vec2 getBoundSize() {return m_boundSize;}

    //-------------------------------------------------------------------//
    /// @brief sets the position of the button and the buttons label
    /// if it has one
    /// @param [in] _pos the position you want to set
    //-------------------------------------------------------------------//
    void setPosition(ngl::Vec2 _pos);

    //-------------------------------------------------------------------//
    /// @brief sets the state of the button
    /// @param [in] _state which is an enum and sets m_buttonState
    //-------------------------------------------------------------------//

    inline void setState(ButtonState _state) {m_buttonState = _state;}


protected:


    //-------------------------------------------------------------------//
    /// @brief states whether the button is in relative or absolute position
    //-------------------------------------------------------------------//
    bool m_relativePos;

    //-------------------------------------------------------------------//
    /// @brief stores the function to be executed by the button
    //-------------------------------------------------------------------//
    functionPtr m_execute;

    //-------------------------------------------------------------------//
    /// @brief stores a shared pointer to the buttons label text
    //-------------------------------------------------------------------//
    TextPtr m_label;

    //-------------------------------------------------------------------//
    /// @brief the boundsize is the size of the button including its label
    //-------------------------------------------------------------------//
    ngl::Vec2 m_boundSize;

    //-------------------------------------------------------------------//
    /// @brief enum stating where the label is positioned
    //-------------------------------------------------------------------//
    LabelPosition m_labelPosition;

    //-------------------------------------------------------------------//
    /// @brief states whether the button has a label or not
    //-------------------------------------------------------------------//
    bool m_gotLabel;

    //-------------------------------------------------------------------//
    /// @brief stores the state of the button
    //-------------------------------------------------------------------//
    ButtonState m_buttonState;

};

#endif // UIBUTTON_H
