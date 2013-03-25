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
/// @brief menu for the ui layout. it inherits from uielement. Table
/// is the container which holds rows which in turn hold columns. It is
/// a grid like structure and means the table can store other tables and
/// its size is determined by the elements in it
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

    enum AnimState{STOPPED, MOVING, GO, RESIZE, CLOSED};


    //-------------------------------------------------------------------//
    /// @brief overloaded constructor
    /// @param [in] _pos position of table
    /// @param [in] _name name of table
    /// @param [in] _imageFile string of image path file
    /// @param [in] _slideType states the tables slide type
    /// @param [in] _parent stores a pointer to its parent
    //-------------------------------------------------------------------//
    Table(ngl::Vec2 _pos,
          std::string _name,
          std::string _imageFile,
          std::string _slideType,
          UI *_parent
          );

    //-------------------------------------------------------------------//
    /// @brief default destructor
    //-------------------------------------------------------------------//
    ~Table();

    //-------------------------------------------------------------------//
    /// @brief creates rows in the table
    /// @param [in] _numRows int value specifying the number of rows to create
    //-------------------------------------------------------------------//
    void createRows(const int &_numRows);

    //-------------------------------------------------------------------//
    /// @brief creates columns in rows
    /// @param [in] _row value of the row you want to add columns too
    /// @param [in] _numColumns number of columns to add
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
    /// @param [in] _pos position value for the table position
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
    /// @param [in] _alignment enum which will specify where to align the table to
    //-------------------------------------------------------------------//
    void screenAlignment(const AlignType &_alignment);

    //-------------------------------------------------------------------//
    /// @brief sets whether the table will be drawn as will as its rows
    /// @param [in] _visible true or false value specifying whether it is viewable
    //-------------------------------------------------------------------//
    inline void setBackground(bool _visible) {m_backgroundVisible = _visible;}

    //-------------------------------------------------------------------//
    /// @brief gets the specified element
    /// @param [in] _row where element is stored
    /// @param [in] _column where the element is store
    //-------------------------------------------------------------------//
    UIElementWPtr getElement(const int &_row,const int &_column);

    //-------------------------------------------------------------------//
    /// @brief gets an element not in the grid setup
    /// @param [in] _name name of element you want to return
    //-------------------------------------------------------------------//
    std::string getElTexture(std::string _name);

    //-------------------------------------------------------------------//
    /// @brief sets the elements text if it is a text element
    /// @param [in] _row the text is in
    /// @param [in] _column the text is in
    /// @param [in] _text the text to store in it
    //-------------------------------------------------------------------//
    void setText(const int &_row, const int &_column, const char *_text);

    //-------------------------------------------------------------------//
    /// @brief sets whether the entire table is drawn including its rows
    /// @param [in] _drawable true false value specifying whether it is drawable
    //-------------------------------------------------------------------//
    void setDrawable(bool _drawable) {m_isDrawable = _drawable;}

    //-------------------------------------------------------------------//
    /// @brief function to create a cost button
    /// @param [in] _row where to create the button
    /// @param [in] _column within the row to create it in
    /// @param [in] _pos initial position of element
    /// @param [in] _imageFile image file name
    /// @param [in] _name name of element
    /// @param [in] _type pointer to this table
    /// @param [in] _cost cost of the tower
    /// @param [in] _maxX x size of button
    /// @param [in] _maxY y size of button
    //-------------------------------------------------------------------//
    void createCostButton
    (
            const int &_row,
            const int &_column,
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
    /// @param [in] _row where to create the button
    /// @param [in] _column within the row to create it in
    /// @param [in] _pos initial position of element
    /// @param [in] _text text to be drawn
    /// @param [in] _fontFile path to font file
    /// @param [in] _ptsize size of font
    /// @param [in] _name name of text element
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
    /// @brief create any element with absolute positions
    /// @param [in] _element takes in a smart pointer to an element
    //-------------------------------------------------------------------//
    void createAbsoluteElement(const UIElementPtr &_element);

    //-------------------------------------------------------------------//
    /// @brief function to create a standard button
    /// @param [in] _row where to create the button
    /// @param [in] _column within the row to create it in
    /// @param [in] _pos initial position of element
    /// @param [in] _name name of element
    /// @param [in] _type type specifies the type of element
    /// @param [in] _imageFile texture name to draw
    /// @param [in] _maxX x size of element
    /// @param [in] _maxY y size of element
    //-------------------------------------------------------------------//
    void createImageElement
    (
            const int _row,
            const int _column,
            ngl::Vec2 _pos,
            std::string _name,
            ElementType _type,
            std::string _imageFile,
            const int _maxX,
            const int _maxY
            );

    //-------------------------------------------------------------------//
    /// @brief function to create a standard button
    /// @param [in] _row where to create the button
    /// @param [in] _column within the row to create it in
    /// @param [in] _pos initial position of element
    /// @param [in] _imageFile texture name to draw
    /// @param [in] _name name of element
    /// @param [in] _maxX x size of button
    /// @param [in] _maxY y size of button
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
    /// @param [in] _function function to set in the button
    //-------------------------------------------------------------------//
    void setFunction(const int &_row, const int &_column, boost::function<void()> _function);

    //-------------------------------------------------------------------//
    /// @brief overloaded set function used to set functions that are absolute
    /// and not stored in the table
    /// @param [in] _name the button you want to set the function to
    /// @param [in] _function function to set in the button
    //-------------------------------------------------------------------//
    void setFunction(std::string _name, boost::function<void()> _function);

    //-------------------------------------------------------------------//
    /// @brief sets a cost buttons cost
    /// @param [in] _row defines the row the button is in
    /// @param [in] _column defines the column within the row the button is stored in
    /// @param [in] _cost cost to add into the button
    //-------------------------------------------------------------------//
    void setCost(const int &_row, const int &_column, int _cost);

    //-------------------------------------------------------------------//
    /// @brief sets the texture of the element
    /// @param [in] _row defines the row the button is in
    /// @param [in] _column defines the column within the row the button is stored in
    /// @param [in] _textures string with the texture you want to set
    //-------------------------------------------------------------------//
    void setTexture(const int &_row, const int &_column, std::string _texture);

    //-------------------------------------------------------------------//
    /// @brief sets the texture of an element not in a table
    /// @param [in] _name defines the element you want to set
    /// @param [in] _texture string with the texture you want to set
    //-------------------------------------------------------------------//
    void setTexture(std::string _name, std::string _texture);

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

    //-------------------------------------------------------------------//
    /// @brief updates all the elements that are absolute positions
    /// based on how the difference between its position and the menus
    //-------------------------------------------------------------------//
    void updateElPosition();

    //-------------------------------------------------------------------//
    /// @brief sets the tables start position
    /// @param [in] _pos put into m_startPos
    //-------------------------------------------------------------------//
    inline void setStartPos(ngl::Vec2 _pos) {m_startPos = _pos;}

    //-------------------------------------------------------------------//
    /// @brief the tables update function used for animation
    /// @param [in] _dt defines the amount of time in millieseconds since the
    /// last update
    //-------------------------------------------------------------------//
    void update(const double _dt);

    //-------------------------------------------------------------------//
    /// @brief the animation function if the tables slide type is verticle
    /// @param [in] _dt defines the amount of time in millieseconds since the
    /// last update
    //-------------------------------------------------------------------//
    void slideVerticle(const double _dt);

    //-------------------------------------------------------------------//
    /// @brief the animation function if the tables slide type is horizontal
    /// @param [in] _dt defines the amount of time in millieseconds since the
    /// last update
    //-------------------------------------------------------------------//
    void slideHorizontal(const double _dt);

    //-------------------------------------------------------------------//
    /// @brief setter function for m_centreY flag
    /// @param [in] _centre bool used to set m_centreY
    //-------------------------------------------------------------------//
    inline void setCentreYFlag(bool _centre) {m_centreY = _centre;}

    //-------------------------------------------------------------------//
    /// @brief sets up the correct intervals used in the animation which is
    /// while table is in GO state
    //-------------------------------------------------------------------//
    void goStateSetup();

    //-------------------------------------------------------------------//
    /// @brief checks what state the table is in and sets it correctly the starts
    /// the animation
    //-------------------------------------------------------------------//
    void runAnimation();

    //-------------------------------------------------------------------//
    /// @brief used to put the table into the CLOSED state directly
    //-------------------------------------------------------------------//
    void runCloseAnimation();

    //-------------------------------------------------------------------//
    /// @brief checks the current state of the table and sets the correct state
    //-------------------------------------------------------------------//
    void checkState();



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

    //-------------------------------------------------------------------//
    /// @brief states whether the button elements will be centred
    //-------------------------------------------------------------------//
    bool m_centreY;

private:

    //-------------------------------------------------------------------//
    /// @brief speed in seconds you want the table to slide in
    //-------------------------------------------------------------------//
    double m_speed;

    //-------------------------------------------------------------------//
    /// @brief the tables start position at time of animation
    //-------------------------------------------------------------------//
    ngl::Vec2 m_startPos;

    //-------------------------------------------------------------------//
    /// @brief the tables end position or goal position at start of animation
    //-------------------------------------------------------------------//
    ngl::Vec2 m_endPos;

    //-------------------------------------------------------------------//
    /// @brief states whether the table is needing to be animated
    //-------------------------------------------------------------------//
    bool m_isAnimated;

    //-------------------------------------------------------------------//
    /// @brief the interval to move the table in (speed vector)
    //-------------------------------------------------------------------//
    ngl::Vec2 m_interval;

    //-------------------------------------------------------------------//
    /// @brief whther it slide horizontal or vertically
    //-------------------------------------------------------------------//
    std::string m_slideType;

    //-------------------------------------------------------------------//
    /// @brief the state of the table for the animation
    //-------------------------------------------------------------------//
    AnimState m_slideState;

    //-------------------------------------------------------------------//
    /// @brief states whether the tables size has been changed since the
    /// animation
    //-------------------------------------------------------------------//
    bool m_sizeChanged;







};

#endif // TABLE_H
