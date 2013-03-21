#ifndef TABLE_H
#define TABLE_H


#include <ngl/Vec2.h>
#include "uielement.h"
#include <boost/function.hpp>
#include <boost/bind.hpp>
#include "fwd/ui.h"
#include "fwd/table.h"
#include "text.h"
#include "uLayout/row.h"
#include "window.h"
#include "ngl/ShaderLib.h"
#include "uibutton.h"


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

    enum ElementToCornerAlign {TOPRIGHT, TOPLEFT};


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
    void createRows(const int &_numRows);

    //-------------------------------------------------------------------//
    /// @brief creates columns in rows
    /// @param [in] value of the row you want to add columns too
    /// @param [in] number of columns to add
    //-------------------------------------------------------------------//
    void createColumns(const int &_row,const int &_numColumns);

    //-------------------------------------------------------------------//
    /// @brief creates a table
    /// @param [in] _row of the element
    /// @param [in] _column to be placed in
    /// @param [in] _element the table to be stored
    //-------------------------------------------------------------------//
    void createTable(const int &_row,const int &_column, const UIElementPtr &_element);

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
    /// @brief tells the rows to set their columns positions and also tells
    /// column to set elements rest position
    //-------------------------------------------------------------------//
    void setRowPositions();

    //-------------------------------------------------------------------//
    /// @brief tells the rows to set their columns positions but doesnt set
    /// the rest position
    //-------------------------------------------------------------------//
    void updateRowPositions();

    //-------------------------------------------------------------------//
    /// @brief sets the tables position
    /// @param [in] position value for the table position
    //-------------------------------------------------------------------//
    void setPosition(ngl::Vec2 _pos);

    //-------------------------------------------------------------------//
    /// @brief sets an elements position relative to the menu
    /// @param [in] _name the element to set the position
    /// @param [in] _align alignment type
    //-------------------------------------------------------------------//
    void setElementPosition(std::string _name, ElementToCornerAlign _align);

    //-------------------------------------------------------------------//
    /// @brief goes through and resizes the table based on the rows sizes
    //-------------------------------------------------------------------//
    void setSize();

    //-------------------------------------------------------------------//
    /// @brief aligns the menu to screen edges
    /// @param [in] enum which will specify where to align the table to
    //-------------------------------------------------------------------//
    void screenAlignment(const AlignType &_alignment);

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
    UIElementWPtr getElement(const int &_row,const int &_column);

    //-------------------------------------------------------------------//
    /// @brief sets the elements text if it is a text element
    /// @param [in] row the text is in
    /// @param [in] column the text is in
    /// @param [in] the text to store in it
    //-------------------------------------------------------------------//
    void setText(const int &_row, const int &_column, const char *_text);

    //-------------------------------------------------------------------//
    /// @brief sets whether the entire table is drawn including its rows
    /// @param [in] true false value specifying whether it is drawable
    //-------------------------------------------------------------------//
    void setDrawable(bool _drawable) {m_isDrawable = _drawable;}

    //-------------------------------------------------------------------//
    /// @brief function to create a cost button
    /// @param [in] row where to create the button
    /// @param [in] column within the row to create it in
    /// @param [in] initial position of element
    /// @param [in] image file name
    /// @param [in] name of element
    /// @param [in] pointer to this table
    /// @param [in] cost of the tower
    /// @param [in] x size of button
    /// @param [in] y size of button
    //-------------------------------------------------------------------//
    void createCostButton
    (
            const int &_row,
            const int &_column,
            const ngl::Vec2 &_pos,
            const std::string &_imageFile,
            const std::string &_name,
            const std::string &_type,
            const int &_cost,
            const float &_maxX,
            const float &_maxY
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
            const int &_row,
            const int &_column,
            const ngl::Vec2 &_pos,
            const char *_text,
            const char *_fontFile,
            const int &_ptsize,
            const std::string &_name
            );

    //-------------------------------------------------------------------//
    /// @brief function to create a table
    //-------------------------------------------------------------------//
    void createElement(const UIElementPtr &_element);

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
            const int &_row,
            const int &_column,
            const ngl::Vec2 &_pos,
            const std::string &_imageFile,
            const std::string &_name,
            const float &_maxX,
            const float &_maxY
            );

    //-------------------------------------------------------------------//
    /// @brief sets a buttons function
    /// @param [in] _row defines the row the button is in
    /// @param [in] _column defines the column within the row the button is stored in
    /// @param [in] function to set in the button
    //-------------------------------------------------------------------//
    void setFunction(const int &_row, const int &_column, boost::function<void()> _function);

    void setFunction(std::string _name, boost::function<void()> _function);


    //-------------------------------------------------------------------//
    /// @brief sets a cost buttons cost
    /// @param [in] _row defines the row the button is in
    /// @param [in] _column defines the column within the row the button is stored in
    /// @param [in] cost to add into the button
    //-------------------------------------------------------------------//
    void setCost(const int &_row, const int &_column, int _cost);

    //-------------------------------------------------------------------//
    /// @brief sets the texture of the element
    /// @param [in] _row defines the row the button is in
    /// @param [in] _column defines the column within the row the button is stored in
    /// @param [in] string with the texture you want to set
    //-------------------------------------------------------------------//
    void setTexture(const int &_row, const int &_column, std::string _texture);

    //-------------------------------------------------------------------//
    /// @brief sets whether a button has been pressed or not
    /// @param [in] _row defines the row the button is in
    /// @param [in] _column defines the column within the row the button is stored in
    /// @param [in] bool to say whether the button has been pressed or not
    //-------------------------------------------------------------------//
    void setPressed(const int &_row, const int &_column, bool _isPressed);

    //-------------------------------------------------------------------//
    /// @brief centres the elements in the table in the y axis
    //-------------------------------------------------------------------//
    void centreElementsY();

    //-------------------------------------------------------------------//
    /// @brief creates a label for a button stored in the table
    /// @param [in] _row defines the row the button is in
    /// @param [in] _column defines the column within the row the button is stored in
    /// @param [in] _pos
    /// @param [in] _text states the text to be displayed
    /// @param [in] _fontFile font to be used
    /// @param [in] _ptsize font size
    /// @param [in] _name name of element
    /// @param [in] _position states where the label will be positioned relative
    /// to the button
    //-------------------------------------------------------------------//
    void createLabel
    (
        const int &_row,
        const int &_column,
        ngl::Vec2 _pos,
        const char *_text,
        const char *_fontFile,
        int _ptsize,
        std::string _name,
        LabelPosition _position
        );

    inline void setSpeed(double _speed) {m_speed = _speed;}

    inline void setStartPos(ngl::Vec2 _startPos) {m_startPos = _startPos;}

    inline void setEndPos(ngl::Vec2 _endPos) {m_endPos = _endPos;}

    inline void setAnimated(bool _animated) {m_isAnimated = _animated;}

    inline void setInterval(ngl::Vec2 _interval) {m_interval = _interval;}

    inline void setStartTime(double _time) {m_startTime = _time;}

    inline double getStartTime() {return m_startTime;}

    inline ngl::Vec2 getInterval() {return m_interval;}

    inline double getSpeed() {return m_speed;}

    inline ngl::Vec2 getStartPos() {return m_startPos;}

    inline ngl::Vec2  getEndPos() {return m_endPos;}

    inline bool getAnimated() {return m_isAnimated;}

    void updateElPosition();

    void update(const double _dt);

    void slideDown(const double _dt);

    void slideLeft(const double _dt);



protected:

    typedef std::vector<RowPtr> RowVector;

    typedef std::vector<UIElementPtr> ElementVector;

    //-------------------------------------------------------------------//
    /// @brief vector container containg pointers to the rows
    //-------------------------------------------------------------------//
    RowVector m_rows;

    //-------------------------------------------------------------------//
    /// @brief stores elements which have absolute values and are not set
    /// up in the rows system
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

private:

    //-------------------------------------------------------------------//
    double m_speed;

    ngl::Vec2 m_startPos;

    ngl::Vec2 m_endPos;

    bool m_isAnimated;

    ngl::Vec2 m_interval;

    double m_startTime;

    std::string m_slideType;






};

#endif // TABLE_H
