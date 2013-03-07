#ifndef COLUMN_H
#define COLUMN_H

#include "uielement.h"
#include "fwd/column.h"
#include "ngl/Vec2.h"

class Column
{
public:

    Column();

    ~Column();

    inline ngl::Vec2 getSize() {return m_size;}

    void setElement(UIElementPtr _element);

    inline void setPosition(ngl::Vec2 _position) {m_position = _position;}

    void checkAffordable();

    void draw();

    void setElementPosition();

    inline UIElementWPtr getElement() {return m_element;}

    void setSize();




private:

    ngl::Vec2 m_size;

    ngl::Vec2 m_position;

    UIElementPtr m_element;

};

#endif // COLUMN_H
