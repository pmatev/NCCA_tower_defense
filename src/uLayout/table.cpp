#include "uLayout/table.h"
#include "src/uLayout/row.cpp"
#include "costbutton.h"
#include "texturelib.h"


Table::Table(ngl::Vec2 _pos,
             std::string _name,
             std::string _imageFile,
             std::string _slideType,
             UI *_parent):

    UIElement( _pos, _name, TABLE,_imageFile),



    m_backgroundVisible(true),
    m_parent(_parent),
    m_isDrawable(true),
    m_centreY(false),
    m_startPos(_pos),
    m_isAnimated(false),
    m_slideType(_slideType),
    m_slideState(STOPPED),
    m_sizeChanged(false)
{


}

//-------------------------------------------------------------------//
Table::~Table()
{

}

//-------------------------------------------------------------------//
void Table::createRows(const int &_numRows)
{
    for(int i= 0; i < _numRows; i++)
    {
        RowPtr row = RowPtr(new Row());
        m_rows.push_back(row);
    }
}

//-------------------------------------------------------------------//
void Table::createColumns(const int &_row,const int &_numColumns)
{
    RowPtr row = m_rows[_row];

    row->createColumns(_numColumns);
}

//-------------------------------------------------------------------//
void Table::createTable(const int &_row,const int &_column,const UIElementPtr &_element)
{
    Window* window = Window::instance();

    RowPtr row = m_rows[_row];

    int ID = window->getID();
    m_parent->registerID(_element, ID);
    _element->setID(ID);
    row->setElement(_column, _element);

}

//-------------------------------------------------------------------//
void Table::createAbsoluteElement(const UIElementPtr &_element)
{
    Window* window = Window::instance();

     int ID = window->getID();
     m_parent->registerID(_element, ID);
     _element->setID(ID);
     m_elements.push_back(_element);

}

//-------------------------------------------------------------------//
void Table::createImageElement
(
        const int _row,
        const int _column,
        ngl::Vec2 _pos,
        std::string _name,
        ElementType _type,
        std::string _imageFile,
        const int _maxX,
        const int _maxY
        )
{
    Window* window = Window::instance();

    RowPtr row = m_rows[_row];

    UIElementPtr element = UIElementPtr
            (
                new UIElement
                (
                    _pos,
                    _name,
                    _type,
                    _imageFile
                    )
                );

    int ID = window->getID();
    m_parent->registerID(element, ID);
    element->setSize(ngl::Vec2(_maxX, _maxY));
    element->setID(ID);
    row->setElement(_column, element);
}

//-------------------------------------------------------------------//
void Table::setRowPositions()
{
    ngl::Vec2 position = m_pos;
    for(RowVector::iterator it=m_rows.begin(); it!=m_rows.end(); ++it)
    {
        (*it)->setPosition(position,false);
        position.m_y += (*it)->getSize().m_y;
        position.m_x = m_pos.m_x;
    }
}

//-------------------------------------------------------------------//
void Table::updateRowPositions()
{
    ngl::Vec2 position = m_pos;
    for(RowVector::iterator it=m_rows.begin(); it!=m_rows.end(); ++it)
    {
        (*it)->setPosition(position,true);
        position.m_y += (*it)->getSize().m_y;
        position.m_x = m_pos.m_x;
    }
}
//-------------------------------------------------------------------//
void Table::checkButtonAffordable()
{
    for(unsigned int x =0; x< m_rows.size(); x++)
    {
        RowPtr row = m_rows[x];
        row->checkAffordable();
    }
}

//-------------------------------------------------------------------//
void Table::draw()
{
//IN THIS FUNCTION NEED TO SET UP ISPRESSED RENDER
    if(m_isDrawable)
    {
        glDisable(GL_DEPTH_TEST);
        glEnable(GL_BLEND);

        Window *window = Window::instance();
        ngl::ShaderLib *shader=ngl::ShaderLib::instance();

        if(m_backgroundVisible == true)
        {
            (*shader)["UI"]->use();

            float scaleX = 2.0/window->getScreenWidth();
            float scaleY = 2.0/window->getScreenHeight();

            shader->setShaderParam1f("xpos",m_pos.m_x);
            shader->setShaderParam1f("ypos",m_pos.m_y);
            shader->setShaderParam1f("scaleX",scaleX);
            shader->setShaderParam1f("scaleY",scaleY);
            shader->setShaderParam4f("colourSelect",0,0,0,0);

            TextureLib *tex = TextureLib::instance();
            tex->bindTexture(m_imageFile);
            if(m_tileable)
            {
                TexturePtr texture = tex->getTexture(m_imageFile).lock();
                float scaleUVX = m_size.m_x/texture->getWidth();
                float scaleUVY = m_size.m_y/texture->getHeight();
                m_billboard->setUVScale(scaleUVX, scaleUVY);
            }

            m_billboard->draw("UI");
        }

        //now draw all its elements
        //glDisable(GL_BLEND);

        for(RowVector::iterator it=m_rows.begin(); it!=m_rows.end(); it++)
        {
          (*it)->draw();
        }
        for(ElementVector::iterator it=m_elements.begin(); it!=m_elements.end(); it++)
        {
          (*it)->draw();
        }

        glEnable(GL_DEPTH_TEST);
    }
}



//-------------------------------------------------------------------//
void Table::setPosition(ngl::Vec2 _pos)
{
    m_pos = _pos;
    setRowPositions();
    updateElPosition();
}


//-------------------------------------------------------------------//
void Table::setSize()
{
    m_size = ngl::Vec2(0,0);
    for(RowVector::iterator it=m_rows.begin(); it!=m_rows.end(); ++it)
    {
        (*it)->setSize();

        if(m_size.m_x < (*it)->getSize().m_x)
        {
            m_size.m_x = (*it)->getSize().m_x;
        }
        //tally up size of columns
        m_size.m_y += (*it)->getSize().m_y;
    }
    generateMesh();
}



//-------------------------------------------------------------------//
void Table::screenAlignment(const AlignType &_alignment)
{
    Window* window = Window::instance();

    if(_alignment == RIGHT)
    {
       double width = window->getScreenWidth();
       m_pos.m_x = width-m_size.m_x;

    }
    if(_alignment == LEFT)
    {
        m_pos.m_x = 0;
    }

    if(_alignment == BOTTOM)
    {
        m_pos.m_y = 0;
    }

    if(_alignment == TOP)
    {
        double height = window->getScreenHeight();
        m_pos.m_y = height-m_size.m_y;
    }
    if(_alignment == CENTREX)
    {
        double width = window->getScreenWidth();
        m_pos.m_x = (width/2)-(m_size.m_x/2);
    }
    if(_alignment == CENTREY)
    {
        double height = window->getScreenHeight();
        m_pos.m_y = (height/2)-(m_size.m_y/2);
    }

    setRowPositions();
    m_startPos = m_pos;
    m_restPosition = m_pos;
}


//-------------------------------------------------------------------//
void Table::setText(const int &_row,const int &_column, const char *_text)
{
    UIElementPtr element = m_rows[_row]->getElement(_column).lock();
    if(element)
    {
        TextPtr text = boost::dynamic_pointer_cast<Text>(element);
        if(text)
        {
            text->setText(_text);
        }
    }
}

//-------------------------------------------------------------------//
void Table::createText
(
        const int &_row,
        const int &_column,
        const ngl::Vec2 &_pos,
        const char *_text,
        const char *_fontFile,
        const int &_ptsize,
        const std::string &_name
        )
{
    Window* window = Window::instance();

    RowPtr row = m_rows[_row];

    UIElementPtr element = TextPtr
            (
                new Text
                (
                    _pos,
                    _text,
                    _fontFile,
                    _ptsize,
                    _name
                    )
                );

    int ID = window->getID();
    m_parent->registerID(element, ID);
    element->setID(ID);
    row->setElement(_column, element);

}

//-------------------------------------------------------------------//
void Table::createCostButton
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
        )
{
    Window* window = Window::instance();

    RowPtr row = m_rows[_row];

    UIElementPtr element = CostButtonPtr
            (
                new CostButton
                (
                    _pos,
                    _imageFile,
                    _name,
                    _type,
                    _cost,
                    _maxX,
                    _maxY
                    )
                );

    int ID = window->getID();
    m_parent->registerID(element, ID);
    element->setID(ID);
    row->setElement(_column, element);
}

//-------------------------------------------------------------------//
void Table::createButton
(
        const int &_row,
        const int &_column,
        const ngl::Vec2 &_pos,
        const std::string &_imageFile,
        const std::string &_name,
        const float &_maxX,
        const float &_maxY
        )
{
    Window* window = Window::instance();

    RowPtr row = m_rows[_row];

    UIElementPtr element = UIButtonPtr
            (
                new UIButton
                (
                    _pos,
                    _imageFile,
                     _name,
                    _maxX,
                    _maxY
                    )
                );

    int ID = window->getID();
    m_parent->registerID(element, ID);
    element->setID(ID);
    row->setElement(_column, element);
}

//-------------------------------------------------------------------//
UIElementWPtr Table::getElement(const int &_row, const int &_column)
{
    RowPtr row = m_rows[_row];
    UIElementWPtr element = row->getElement(_column);
    return element;
}

//-------------------------------------------------------------------//
std::string Table::getElTexture(std::string _name)
{
    for(ElementVector::iterator it = m_elements.begin();
        it != m_elements.end();
        ++it)
    {
        UIElementPtr element = (*it);
        if(element->getName() == _name)
        {
           return element->getTexture();
        }
    }
    return "";
}

//-------------------------------------------------------------------//
void Table::setFunction
(
    const int &_row,
    const int &_column,
    boost::function<void()> _function
    )
{
    UIElementPtr element = getElement(_row, _column).lock();

    if(element)
    {
        UIButtonPtr button = boost::dynamic_pointer_cast<UIButton>(element);

        if(button)
        {
            button->setFunction(_function);
        }
    }
}


//-------------------------------------------------------------------//
void Table::setCost(const int &_row, const int &_column, int _cost)
{
    UIElementPtr element = getElement(_row, _column).lock();

    if(element)
    {
        CostButtonPtr button = boost::dynamic_pointer_cast<CostButton>(element);
        if(button)
        {
            button->setCost(_cost);
        }
    }
}

//-------------------------------------------------------------------//
void Table::setTexture(const int &_row, const int &_column, std::string _texture)
{
    UIElementPtr element = getElement(_row, _column).lock();

    if(element)
    {
        element->setTexture(_texture);
    }
}

//-------------------------------------------------------------------//
void Table::setTexture(std::string _name, std::string _texture)
{
    for(ElementVector::iterator it = m_elements.begin();
        it != m_elements.end();
        ++it)
    {
        UIElementPtr element = (*it);
        if(element->getName() == _name)
        {
           element->setTexture(_texture);
        }
    }
}

//-------------------------------------------------------------------//
void Table::centreElementsY()
{

    for(RowVector::iterator it=m_rows.begin(); it!=m_rows.end(); ++it)
    {
        (*it)->centreElementsY();
    }

}

//-------------------------------------------------------------------//
void Table::createLabel
(
    const int &_row,
    const int &_column,
    ngl::Vec2 _pos,
    const char *_text,
    const char *_fontFile,
    int _ptsize,
    std::string _name,
    LabelPosition _position)
{
    UIElementPtr element = getElement(_row, _column).lock();

    if(element)
    {
        UIButtonPtr button = boost::dynamic_pointer_cast<UIButton>(element);
        if(button)
        {
            button->createLabel(_pos,_text,_fontFile,_ptsize,_name,_position);
        }
    }
}

//-------------------------------------------------------------------//
void Table::setFunction(std::string _name, boost::function<void ()> _function)
{
    for(ElementVector::iterator it=m_elements.begin(); it!=m_elements.end(); ++it)
    {
        UIElementPtr element = (*it);
        if(element && element->getName() == _name)
        {
            UIButtonPtr button = boost::dynamic_pointer_cast<UIButton>(element);
            if(button)
            {
                button->setFunction(_function);
            }
        }
    }
}

//-------------------------------------------------------------------//
void Table::setElementPosition(std::string _name, ElementToCornerAlign _align)
{
    for(ElementVector::iterator it=m_elements.begin(); it!=m_elements.end(); ++it)
    {
        UIElementPtr element = (*it);
        if(element && element->getName() == _name)
        {
            ngl::Vec2 tmpPos;
            if(_align == TOPLEFT)
            {
                tmpPos.m_x = m_pos.m_x;
                tmpPos.m_y = m_pos.m_y+m_size.m_y;
            }
            else if(_align == TOPRIGHT)
            {
                tmpPos.m_x = (m_pos.m_x+m_size.m_x)-element->getSize().m_x;
                tmpPos.m_y = m_pos.m_y+m_size.m_y;
            }
            element->setPosition(tmpPos);
            element->setRestPosition(tmpPos);
        }
    }
}

//-------------------------------------------------------------------//
void Table::updateElPosition()
{
    for(ElementVector::iterator it=m_elements.begin(); it!=m_elements.end(); ++it)
    {
        ngl::Vec2 elPos;
        ngl::Vec2 elPosDif;
        elPosDif.m_x = (*it)->getRestPosition().m_x-m_restPosition.m_x;
        elPosDif.m_y = (*it)->getRestPosition().m_y-m_restPosition.m_y;

        if(elPosDif.m_x == 0)
        {
            elPos.m_y = elPosDif.m_y+m_pos.m_y;
            elPos.m_x = m_restPosition.m_x;
        }
        else if(elPosDif.m_y == 0)
        {
            elPos.m_x = elPosDif.m_x+m_pos.m_x;
            elPos.m_y = m_restPosition.m_y;
        }
        else if(elPosDif == 0)
        {
            elPos.m_x = m_restPosition.m_x;
            elPos.m_y = m_restPosition.m_y;
        }
        else
        {
            elPos.m_x = elPosDif.m_x+m_pos.m_x;
            elPos.m_y = elPosDif.m_y+m_pos.m_y;
        }

        (*it)->setPosition(elPos);
    }
}

//-------------------------------------------------------------------//
void Table::update(const double _dt)
{
    if(m_isAnimated == true)
    {
        if(m_slideType == "up")
        {
            slideVerticle(_dt);
        }
        else if(m_slideType == "left")
        {
            slideHorizontal(_dt);
        }
    }
}

//-------------------------------------------------------------------//
void Table::slideHorizontal(const double _dt)
{
    Window* window = Window::instance();
    if(m_slideState == GO)
    {
        if(m_pos == m_endPos && !m_sizeChanged)
        {
            ngl::Vec2 tmpStartPos = m_startPos;
            m_startPos = m_endPos;
            m_endPos = tmpStartPos;
        }
        if(m_sizeChanged)
        {
            m_startPos = m_endPos;
            m_endPos = m_restPosition;
            m_sizeChanged = false;
        }

        goStateSetup();
        if(m_pos.m_x <= window->getScreenWidth()-m_size.m_x)
        {

           m_slideState = STOPPED;
        }
        else
        {
             m_slideState = MOVING;
        }

    }

    else if(m_slideState == MOVING)
    {
        float xPos = m_pos.m_x+(m_interval.m_x*(_dt*0.001));
        m_pos.m_x = xPos;
        setRowPositions();
        updateElPosition();
        centreElementsY();
        if(m_interval.m_x < 0)
        {
            if(m_pos.m_x <= m_endPos.m_x)
            {

                setPosition(m_endPos);
                centreElementsY();
                m_slideState = STOPPED;

            }
        }
        else if(m_interval.m_x > 0)
        {
            if(m_pos.m_x >= m_endPos.m_x)
            {
                setPosition(m_endPos);
                centreElementsY();
                m_slideState = STOPPED;
            }
        }
    }

    else if(m_slideState == CLOSED)
    {
        if(m_pos == m_endPos && !m_sizeChanged)
        {
            ngl::Vec2 tmpStartPos = m_startPos;
            m_startPos = m_endPos;
            m_endPos = tmpStartPos;
        }
        if(m_sizeChanged)
        {
            m_startPos = m_endPos;
            m_endPos = m_restPosition;
            m_sizeChanged = false;
        }

        goStateSetup();

        m_slideState = MOVING;
    }
}


//-------------------------------------------------------------------//
void Table::slideVerticle(const double _dt)
{
    if(m_slideState == GO)
    {
        if(m_pos == m_endPos && !m_sizeChanged)
        {
            ngl::Vec2 tmpStartPos = m_startPos;
            m_startPos = m_endPos;
            m_endPos = tmpStartPos;
        }
        if(m_sizeChanged)
        {
            m_startPos = m_endPos;
            m_endPos = m_restPosition;
            m_sizeChanged = false;
        }
        goStateSetup();
        m_slideState = MOVING;
    }

    else if(m_slideState == MOVING)
    {

        float yPos = m_pos.m_y+(m_interval.m_y*(_dt*0.001));
        m_pos.m_y = yPos;
        setRowPositions();
        updateElPosition();

        if(m_interval.m_y < 0)
        {
            if(m_pos.m_y <= m_endPos.m_y)
            {

                setPosition(m_endPos);
                m_slideState = STOPPED;
            }
        }

        else if(m_interval.m_y > 0)
        {
            if(m_pos.m_y >= m_endPos.m_y)
            {
                setPosition(m_endPos);

                m_slideState = STOPPED;
            }
        }
    }
}

//-------------------------------------------------------------------//
void Table::goStateSetup()
{
    Window* window = Window::instance();

    if(m_slideType == "down" || m_slideType == "up")
    {
        if(m_pos == m_restPosition)
        {
        m_endPos.m_x = m_pos.m_x;
        m_endPos.m_y = m_startPos.m_y-m_size.m_y;
        m_speed = 0.2;
        m_interval.m_y= (m_endPos.m_y-m_startPos.m_y)/m_speed;
        m_interval.m_x = 0;
        }
        else
        {
            m_interval.m_y= (m_endPos.m_y-m_startPos.m_y)/m_speed;
            m_interval.m_x = 0;
        }
    }

    else
    {
        if(m_pos.m_x ==
                window->getScreenWidth())
        {
            m_speed = 0.2;
            m_endPos.m_x = m_restPosition.m_x-m_size.m_x;
            m_endPos.m_y = m_pos.m_y;
            m_interval.m_x= (m_endPos.m_x-m_startPos.m_x)/m_speed;
            m_interval.m_y = 0;
        }

        else if
                (
                 m_pos.m_x !=
                 window->getScreenWidth()-m_size.m_x
                 )
        {
            float xDif =(window->getScreenWidth()-m_size.m_x)-m_pos.m_x;
            m_endPos.m_x = m_pos.m_x + xDif;
            m_endPos.m_y = m_pos.m_y;
            m_interval.m_x= (m_endPos.m_x-m_startPos.m_x)/0.01;
            m_interval.m_y = 0;
            m_sizeChanged = true;
        }
        else
        {
            m_interval.m_x= (m_endPos.m_x-m_startPos.m_x)/m_speed;
            m_interval.m_y = 0;
        }

    }
}

//-------------------------------------------------------------------//
void Table::runAnimation()
{

    checkState();
    m_isAnimated = true;

}

//-------------------------------------------------------------------//
void Table::runCloseAnimation()
{

    m_slideState = CLOSED;
    m_isAnimated = true;

}

//-------------------------------------------------------------------//
void Table::checkState()
{
    Window* window = Window::instance();
    if(m_slideType == "left")
    {
        if(m_slideState == STOPPED && m_pos.m_x !=
                window->getScreenWidth()-m_size.m_x)
        {
            m_slideState = CLOSED;
        }

        else if(m_slideState == STOPPED)
        {
            m_slideState = GO;
        }
    }
    else
    {
        if(m_slideState == STOPPED)
        {
            m_slideState = GO;
        }
    }
}
