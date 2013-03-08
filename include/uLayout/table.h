#ifndef TABLE_H
#define TABLE_H


#include <ngl/Vec2.h>
#include "uielement.h"
#include <boost/function.hpp>
#include <boost/bind.hpp>
#include "fwd/uibutton.h"
#include "fwd/ui.h"
#include "fwd/table.h"
#include "text.h"
#include "uLayout/row.h"
#include "window.h"
#include "ngl/ShaderLib.h"


//-------------------------------------------------------------------//
/// @file table.h
/// @brief menu for the ui layout. it inherits from uielement
/// @author Luke Gravett
/// @version 1
/// @date 25/02/13
/// Revision History :
/// Initial Version 25/02/13
/// @class Table
//-------------------------------------------------------------------//


class Table : public UIElement
{

public:

    enum AlignType {RIGHT, LEFT, TOP, BOTTOM, CENTREX,CENTREY};

    //-------------------------------------------------------------------//
    /// @brief overloaded constructor
    /// @param [in] position of table
    /// @param [in] name of table
    /// @param [in] string of image path file
    /// @param [in] stores a pointer to its parent
    //-------------------------------------------------------------------//
    Table(ngl::Vec2 _pos,
          std::string _name,
          std::string _imageFile,
          UI *_parent);

    //-------------------------------------------------------------------//
    /// @brief default destructor
    //-------------------------------------------------------------------//
    ~Table();

    //-------------------------------------------------------------------//
    /// @brief creates rows in the table
    /// @param [in] int value specifying the number of rows to create
    //-------------------------------------------------------------------//
    void createRows(int _numRows);

    //-------------------------------------------------------------------//
    /// @brief creates columns in rows
    /// @param [in] value of the row you want to add columns too
    /// @param [in] number of columns to add
    //-------------------------------------------------------------------//
    void createColumns(int _row,int _numColumns);

    //-------------------------------------------------------------------//
    /// @brief overloaded constructor
    /// @param [in] position of table
    /// @param [in] name of table
    /// @param [in] string of image path file
    //-------------------------------------------------------------------//
    void createElement(int _row,int _column, UIElementPtr _element);

    //-------------------------------------------------------------------//
    /// @brief if a create button then it checks if it is affordable if it
    /// set the flag to render it differently
    //-------------------------------------------------------------------//
    void checkButtonAffordable();

    //-------------------------------------------------------------------//
    /// @brief draws the table
    //-------------------------------------------------------------------//
    void draw();

    //-------------------------------------------------------------------//
    /// @brief tells the rows to set their columns positions
    //-------------------------------------------------------------------//
    void setRowPositions();

    //-------------------------------------------------------------------//
    /// @brief sets the tables position
    /// @param [in] position value for the table position
    //-------------------------------------------------------------------//
    void setPosition(ngl::Vec2 _pos);

    //-------------------------------------------------------------------//
    /// @brief goes through and resizes the table based on the rows sizes
    //-------------------------------------------------------------------//
    void setSize();

    //-------------------------------------------------------------------//
    /// @brief aligns the menu to screen edges
    /// @param [in] enum which will specify where to align the table to
    //-------------------------------------------------------------------//
    void screenAlignment(AlignType _alignment);

    //-------------------------------------------------------------------//
    /// @brief sets whether the table will be drawn as will as its rows
    /// @param [in] true ro false value specifying whether it is viewable
    //-------------------------------------------------------------------//
    inline void setBackground(bool _visible) {m_backgroundVisible = _visible;}

    //-------------------------------------------------------------------//
    /// @brief gets the specified element
    /// @param [in] row where element is stored
    /// @param [in] column where the element is store
    //-------------------------------------------------------------------//
    UIElementWPtr getElement(int _row, int _column);

    //-------------------------------------------------------------------//
    /// @brief sets the elements text if it is a text element
    /// @param [in] row the text is in
    /// @param [in] column the text is in
    /// @param [in] the text to store in it
    //-------------------------------------------------------------------//
    void setText(int _row, int _column, const char *_text);

    //-------------------------------------------------------------------//
    /// @brief sets whether the entire table is drawn including its rows
    /// @param [in] true false value specifying whether it is drawable
    //-------------------------------------------------------------------//
    void setDrawable(bool _drawable) {m_isDrawable = _drawable;}

    //-------------------------------------------------------------------//
    /// @brief function to create a create tower button
    /// @param [in] row where to create the button
    /// @param [in] column within the row to create it in
    /// @param [in] initial position of element
    /// @param [in] image file name
    /// @param [in] name of element
    /// @param [in] pointer to this table
    /// @param [in] cost of the tower
    /// @param [in] string containing the towers type the button will create
    /// @param [in] x size of button
    /// @param [in] y size of button
    //-------------------------------------------------------------------//
    void createTowerButton
    (
            int _row,
            int _column,
            ngl::Vec2 _pos,
            std::string _imageFile,
            std::string _name,
            TablePtr _parent,
            int _cost,
            std::string _towerType,
            float _maxX,
            float _maxY
            );

    //-------------------------------------------------------------------//
    /// @brief function to create a text ui
    /// @param [in] row where to create the button
    /// @param [in] column within the row to create it in
    /// @param [in] initial position of element
    /// @param [in] text to be drawn
    /// @param [in] path to font file
    /// @param [in] size of font
    /// @param [in] name of text element
    //-------------------------------------------------------------------//
    void createText
    (
            int _row,
            int _column,
            ngl::Vec2 _pos,
            const char *_text,
            const char *_fontFile,
            int _ptsize,
            std::string _name
            );

    //-------------------------------------------------------------------//
    /// @brief function to create a table
    //-------------------------------------------------------------------//
    void createTable();

    //-------------------------------------------------------------------//
    /// @brief function to create a standard button
    /// @param [in] row where to create the button
    /// @param [in] column within the row to create it in
    /// @param [in] initial position of element
    /// @param [in] name of element
    /// @param [in] stores a pointer to the table
    /// @param [in] x size of button
    /// @param [in] y size of button
    //-------------------------------------------------------------------//
    void createButton
    (
            int _row,
            int _column,
            ngl::Vec2 _pos,
            std::string _imageFile,
            std::string _name,
            TablePtr _parent,
            float _maxX,
            float _maxY
            );

protected:

    typedef std::vector<RowPtr> RowVector;

    //-------------------------------------------------------------------//
    /// @brief stores tables position
    //-------------------------------------------------------------------//
    ngl::Vec2 m_position;

    //-------------------------------------------------------------------//
    /// @brief vector container containg pointers to the rows
    //-------------------------------------------------------------------//
    RowVector m_rows;



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

#endif // TABLE_H
