#include "uLayout/column.h"
#include "costbutton.h"


Column::Column()
{

}

Column::~Column()
{

}


void Column::setElementPosition()
{
    if(m_element)
    {
        ngl::Vec2 tmpPos;
        tmpPos.m_x = m_position.m_x + 5;
        tmpPos.m_y = m_position.m_y + 5;
        m_element->setPosition(tmpPos);
    }


}

void Column::setElement(const UIElementPtr &_element)
{
    m_element = _element;


    setElementPosition();
    m_element->generateMesh();

}

void Column::checkAffordable()
{
    if(m_element)
    {
        if(m_element->getType() == "create" || m_element->getType() == "upgrade")
        {
            CostButtonPtr createButton = boost::dynamic_pointer_cast<CostButton>(m_element);

            if(createButton)
            {
                createButton->checkAffordable();
            }
        }
        else if(m_element->getType() == "table")
        {
            TablePtr table = boost::dynamic_pointer_cast<Table>(m_element);

            if(table)
            {
                table->checkButtonAffordable();
            }
        }
    }
}

void Column::draw()
{
    if(m_element)
    {
            m_element->draw();
    }
}

void Column::setSize()
{
   if(m_element)
   {
       m_size = m_element->getSize();
       m_size.m_x += 10;
       m_size.m_y += 10;
   }
}





