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





class Table : public UIElement
{

public:

    enum AlignType {RIGHT, LEFT, TOP, BOTTOM, CENTREX,CENTREY};

    Table(ngl::Vec2 _pos,
          std::string _name,
          std::string _imageFile,
          UI *_parent);



    ~Table();

    void createRows(int _numRows);

    void createColumns(int _row,int _numColumns);

    void createElement(int _row,int _column, UIElementPtr _element);

    void checkButtonAffordable();

    void draw();

    void setRowPositions();

    void setPosition(ngl::Vec2 _pos);

    void setSize();

    void screenAlignment(AlignType _alignment);

    inline void setBackground(bool _visible) {m_backgroundVisible = _visible;}

    UIElementWPtr getElement(int _row, int _column);

    void setText(int _row, int _column, const char *_text);

    void setDrawable(bool _drawable) {m_isDrawable = _drawable;}

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

    void createTable();

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

    ngl::Vec2 m_position;

    RowVector m_rows;

    bool m_backgroundVisible;

    //-------------------------------------------------------------------//
    /// @brief stores parents information
    //-------------------------------------------------------------------//
    UI *m_parent;

    bool m_isDrawable;

};

#endif // TABLE_H
