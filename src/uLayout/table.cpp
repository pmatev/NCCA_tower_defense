#include "uLayout/table.h"
#include "src/uLayout/row.cpp"
#include "costbutton.h"
#include "texturelib.h"


Table::Table(ngl::Vec2 _pos,
             std::string _name,
             std::string _imageFile,
             UI *_parent):

    UIElement( _pos, _name, "table",_imageFile),


    m_backgroundVisible(true),
    m_parent(_parent),
    m_isDrawable(true)
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
void Table::createElement(const int &_row,const int &_column,const UIElementPtr &_element)
{
    Window* window = Window::instance();

    RowPtr row = m_rows[_row];

    int ID = window->getID();
    m_parent->registerID(_element, ID);
    _element->setID(ID);
    row->setElement(_column, _element);

}

//-------------------------------------------------------------------//
void Table::setRowPositions()
{
    ngl::Vec2 position = m_pos;
    for(RowVector::iterator it=m_rows.begin(); it!=m_rows.end(); ++it)
    {
        (*it)->setPosition(position);
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


        Renderer *render = Renderer::instance();
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
            render->draw(m_IDStr, "UI");

        }

        //now draw all its elements
        //glDisable(GL_BLEND);

        for(RowVector::iterator it=m_rows.begin(); it!=m_rows.end(); it++)
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

    setPosition(m_pos);
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
        const std::string &_type,
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
        UIButtonPtr button = boost::dynamic_pointer_cast<UIButton>(element);
        if(button)
        {
            button->setTexture(_texture);
        }
    }
}

//-------------------------------------------------------------------//
void Table::setPressed(const int &_row, const int &_column, bool _isPressed)
{
    UIElementPtr element = getElement(_row, _column).lock();

    if(element)
    {
        UIButtonPtr button = boost::dynamic_pointer_cast<UIButton>(element);
        if(button)
        {
            button->setPressed(_isPressed);
        }
    }
}
