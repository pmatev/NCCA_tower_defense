#ifndef COLUMN_H
#define COLUMN_H

#include "uielement.h"
#include "fwd/column.h"
#include "ngl/Vec2.h"


//-------------------------------------------------------------------//
/// @file column.h
/// @brief the lowest container for the layout structure which stores the element
/// itself
/// @author Luke Gravett
/// @version 1
/// @date 25/02/13
/// Revision History :
/// Initial Version 25/02/13
/// @class Column
//-------------------------------------------------------------------//

class Column
{
public:

    //-------------------------------------------------------------------//
    /// @brief default constructor
    //-------------------------------------------------------------------//
    Column();

    //-------------------------------------------------------------------//
    /// @brief default destructor
    //-------------------------------------------------------------------//
    ~Column();

    //-------------------------------------------------------------------//
    /// @brief returns size of column
    //-------------------------------------------------------------------//
    inline ngl::Vec2 getSize() {return m_size;}

    //-------------------------------------------------------------------//
    /// @brief set the element in the column
    /// @param [in] _element smart pointer to the element
    //-------------------------------------------------------------------//
    void setElement(const UIElementPtr &_element);

    //-------------------------------------------------------------------//
    /// @brief set method for the position
    /// @param [in] _position where you want the column to be
    //-------------------------------------------------------------------//
    inline void setPosition(ngl::Vec2 _position) {m_position = _position;}

    //-------------------------------------------------------------------//
    /// @brief if the column contains a create button then the container will
    /// run the buttons check affordable command
    //-------------------------------------------------------------------//
    void checkAffordable();

    //-------------------------------------------------------------------//
    /// @brief draw function for the column
    //-------------------------------------------------------------------//
    void draw();

    //-------------------------------------------------------------------//
    /// @brief sets the elements position based on the columns position
    /// and also sets the elements rest position
    //-------------------------------------------------------------------//
    void setElementPosition();

    //-------------------------------------------------------------------//
    /// @brief sets the elements position only, based on the columns position
    //-------------------------------------------------------------------//
    void updateElementPosition();

    //-------------------------------------------------------------------//
    /// @brief returns its elements
    //-------------------------------------------------------------------//
    inline UIElementWPtr getElement() {return m_element;}

    //-------------------------------------------------------------------//
    /// @brief sets the columns size
    //-------------------------------------------------------------------//
    void setSize();

    //-------------------------------------------------------------------//
    /// @brief centres the element in the y axis within row
    /// @param [in] _ysize is the size in y of the largest element in the row
    //-------------------------------------------------------------------//
    void centreElement(float &_ySize);



private:

    //-------------------------------------------------------------------//
    /// @brief size of column
    //-------------------------------------------------------------------//
    ngl::Vec2 m_size;

    //-------------------------------------------------------------------//
    /// @brief position of column
    //-------------------------------------------------------------------//
    ngl::Vec2 m_position;

    //-------------------------------------------------------------------//
    /// @brief smart pointer to the element stored in it
    //-------------------------------------------------------------------//
    UIElementPtr m_element;

};

#endif // COLUMN_H
