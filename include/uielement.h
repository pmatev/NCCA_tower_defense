#ifndef UIELEMENT_H
#define UIELEMENT_H

#include <ngl/Vec2.h>
#include"smartpointers.h"

DECLARESMART(UIElement)

//-------------------------------------------------------------------//
/// @file uielement.h
/// @brief The  base class for all elements which make up the interface
/// @author Luke Gravett
/// @version 1
/// @date 28/11/12
/// Revision History :
/// Initial Version 28/11/12
/// @class UIElement
//-------------------------------------------------------------------//

class UIElement
{
public:
    //-------------------------------------------------------------------//
    /// @brief a parameterised constructor
    /// @param [in] _pos, a Vec2 value for the starting position of the
    /// button
    /// @param [in] _imageFile, a string containing the image file path name
    //-------------------------------------------------------------------//
    UIElement( ngl::Vec2 _pos,
               std::string _imageFile);

    //-------------------------------------------------------------------//
    /// @brief the destructor
    //-------------------------------------------------------------------//
    ~UIElement();

    //-------------------------------------------------------------------//
    /// @brief draw element
    //-------------------------------------------------------------------//

     virtual void draw() const = 0;




protected:

    //-------------------------------------------------------------------//
    /// @brief position of uielement in 2d space
    //-------------------------------------------------------------------//
    ngl::Vec2 m_pos;

    //-------------------------------------------------------------------//
    /// @brief image file used for the button
    //-------------------------------------------------------------------//
    std::string m_imageFile;

};


#endif // UIELEMENT_H
