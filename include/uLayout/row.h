#ifndef ROW_H
#define ROW_H

#include "uLayout/column.h"
#include "fwd/row.h"


//-------------------------------------------------------------------//
/// @file row.h
/// @brief stored within a table rows contain columns
/// @author Luke Gravett
/// @version 1
/// @date 25/02/13
/// Revision History :
/// Initial Version 25/02/13
/// @class Row
//-------------------------------------------------------------------//
DECLARESMART(Row)

class Row
{
public:
    typedef std::vector<ColumnPtr> ColumnVector;

    //-------------------------------------------------------------------//
    /// @brief overloaded constructor
    /// @param [in] number of columns to create
    //-------------------------------------------------------------------//
    Row(int _numColumns);

    //-------------------------------------------------------------------//
    /// @brief default constructor
    //-------------------------------------------------------------------//
    Row();

    //-------------------------------------------------------------------//
    /// @brief default destructor
    //-------------------------------------------------------------------//
    ~Row();

    //-------------------------------------------------------------------//
    /// @brief returns the rows size
    /// @param [out] returns a vec 2 of the rows size
    //-------------------------------------------------------------------//
    inline ngl::Vec2 getSize() {return m_boundSize;}

    //-------------------------------------------------------------------//
    /// @brief creates columns in the row
    /// @param [in] specifies number of columns to create
    //-------------------------------------------------------------------//
    void createColumns(int _numColumns);

    //-------------------------------------------------------------------//
    /// @brief sets the element in the column
    /// @param [in] column to set the element to
    /// @param [in] element to set
    //-------------------------------------------------------------------//
    void setElement(int _column, UIElementPtr _element);

    //-------------------------------------------------------------------//
    /// @brief sets the rows position
    /// @param [in] vec 2 containg the position value to set the row to
    //-------------------------------------------------------------------//
    void setPosition(ngl::Vec2 _position);

    //-------------------------------------------------------------------//
    /// @brief returns the rows position
    /// @param [out] returns a vec 2 containg the rows position
    //-------------------------------------------------------------------//
    inline ngl::Vec2 getPosition() {return m_position;}

    //-------------------------------------------------------------------//
    /// @brief goes through the rows and tells any columns storing create buttons
    /// to run their command
    //-------------------------------------------------------------------//
    void checkAffordable();

    //-------------------------------------------------------------------//
    /// @brief draw function for row
    //-------------------------------------------------------------------//
    void draw();

    //-------------------------------------------------------------------//
    /// @brief goes through and sets the columns positions
    //-------------------------------------------------------------------//
    void setColumnPositions();

    //-------------------------------------------------------------------//
    /// @brief returns a column
    /// @param [in] column to return
    /// @param [out] returns a smart pointer to the column
    //-------------------------------------------------------------------//
    inline ColumnPtr getColumn(int _column) {return m_columns[_column];}


    //-------------------------------------------------------------------//
    /// @brief returns an element based on the specified column
    /// @param [in] column to return
    /// @param [out] returns a smart pointer to the element within the column
    //-------------------------------------------------------------------//
    inline UIElementWPtr getElement(int _column) {ColumnPtr column = m_columns[_column];
                                                 return column->getElement();}

    //-------------------------------------------------------------------//
    /// @brief sets the rows size
    //-------------------------------------------------------------------//
    void setSize();



private:

    //-------------------------------------------------------------------//
    /// @brief the size of the row
    //-------------------------------------------------------------------//
    ngl::Vec2 m_boundSize;

    //-------------------------------------------------------------------//
    /// @brief position of the row
    //-------------------------------------------------------------------//
    ngl::Vec2 m_position;

    //-------------------------------------------------------------------//
    /// @brief vector containg all of its columns
    //-------------------------------------------------------------------//
    ColumnVector m_columns;

};

#endif // ROW_H
