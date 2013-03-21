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
    /// @param [in] inputs a string for the name of the element
    /// @param [in] string saying what type of element it is
    /// @param [in] maxX used for size of button
    /// @param [in] maxY used for size of button
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
    /// @param [in] inputs a string for the name of the element
    /// @param [in] string saying what type of element it is
    /// @param [in] maxX used for size of button
    /// @param [in] maxY used for size of button
    //-------------------------------------------------------------------//
    UIButton
    (
            ngl::Vec2 _pos,
            std::string _imageFile,
            std::string _name,
            std::string _type,
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
    /// @brief sets the isPressed parameter
    /// @param[in] bool value to set the ispressed variable
    //-------------------------------------------------------------------//
    inline void setPressed(bool _pressed) {m_isPressed = _pressed;}

    //-------------------------------------------------------------------//
    /// @brief defines the function to be run by the button
    /// @param [in] boost function pointer to the function to be executed by
    /// the button
    //-------------------------------------------------------------------//
    inline void setFunction(functionPtr _func)  {m_execute = _func;}

    //-------------------------------------------------------------------//
    /// @brief runs the buttons function
    //-------------------------------------------------------------------//
    inline void execute() {m_execute();}

    void createLabel
    (
        ngl::Vec2 _pos,
        const char *_text,
        const char *_fontFile,
        int _ptsize,
        std::string _name,
        LabelPosition _position
        );

    void setLabelPosition();

    inline ngl::Vec2 getBoundSize() {return m_boundSize;}

    void setPosition(ngl::Vec2 _pos);

    inline void setHover(bool _hover){m_hover = _hover;}

    inline void update(const double _dt) {Q_UNUSED(_dt);}



protected:

    //-------------------------------------------------------------------//
    /// @brief states whether the button is currently clicked
    //-------------------------------------------------------------------//
    bool m_isPressed;

    //-------------------------------------------------------------------//
    /// @brief states whether the button is in relative or absolute position
    //-------------------------------------------------------------------//
    bool m_relativePos;

    //-------------------------------------------------------------------//
    /// @brief stores the function to be executed by the button
    //-------------------------------------------------------------------//
    functionPtr m_execute;

    TextPtr m_label;

    ngl::Vec2 m_boundSize;

    LabelPosition m_labelPosition;

    bool m_gotLabel;

    bool m_hover;

    bool m_willHover;


};

#endif // UIBUTTON_H
