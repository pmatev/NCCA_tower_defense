#ifndef ROW_H
#define ROW_H

#include "uLayout/column.h"
#include "fwd/row.h"

DECLARESMART(Row)

class Row
{
public:
    typedef std::vector<ColumnPtr> ColumnVector;


    Row(int _numColumns);
    Row();

    ~Row();

    inline ngl::Vec2 getSize() {return m_boundSize;}

    void createColumns(int _numColumns);

    void setElement(int _column, UIElementPtr _element);

    void setPosition(ngl::Vec2 _position);

    inline ngl::Vec2 getPosition() {return m_position;}

    void checkAffordable();

    void draw();

    void setColumnPositions();

    inline ColumnPtr getColumn(int _column) {return m_columns[_column];}

    inline UIElementWPtr getElement(int _column) {ColumnPtr column = m_columns[_column];
                                                 return column->getElement();}

    void setSize();



private:

    ngl::Vec2 m_boundSize;

    ngl::Vec2 m_position;


    ColumnVector m_columns;

};

#endif // ROW_H
