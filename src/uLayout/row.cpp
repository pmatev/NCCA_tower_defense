#include "uLayout/row.h"
Row::Row()
{

}
Row::Row(const int &_numColumns)

{
   createColumns(_numColumns);
}

Row::~Row()
{

}

void Row::setElement(const int &_column, UIElementPtr _element)
{
    ColumnPtr column = m_columns[_column];
    if(column)
    {
        column->setElement(_element);
        //if the max y value of row is smaller the the cell extend it
        //setSize();
    }
}

void Row::setSize()
{
    m_boundSize = ngl::Vec2(0,0);

    for(ColumnVector::iterator it=m_columns.begin(); it!=m_columns.end(); ++it)
    {
        (*it)->setSize();
        if(m_boundSize.m_y < (*it)->getSize().m_y)
        {
            m_boundSize.m_y = (*it)->getSize().m_y;
        }
        //tally up size of columns
        m_boundSize.m_x += (*it)->getSize().m_x;
    }

}

void Row::createColumns(const int &_numColumns)
{
    for(int i= 0; i <= _numColumns; i++)
    {
        ColumnPtr column = ColumnPtr(new Column());
        if(column)
        {
            m_columns.push_back(column);
        }

    }
}

void Row::setColumnPositions()
{
    ngl::Vec2 position = m_position;

    for(ColumnVector::iterator it=m_columns.begin(); it!=m_columns.end(); ++it)
    {
        (*it)->setPosition(position);
        (*it)->setElementPosition();
        position.m_x += (*it)->getSize().m_x;
        position.m_y = m_position.m_y;
    }
}

void Row::checkAffordable()
{
    for(ColumnVector::iterator it=m_columns.begin(); it!=m_columns.end(); ++it)
    {
        (*it)->checkAffordable();
    }
}

void Row::draw()
{
    for(ColumnVector::iterator it=m_columns.begin(); it!=m_columns.end(); ++it)
    {
        (*it)->draw();
    }

}

void Row::setPosition(ngl::Vec2 _position)
{
    m_position = _position;
    setColumnPositions();
}



