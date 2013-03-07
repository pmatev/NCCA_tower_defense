#include "uLayout/table.h"
#include "src/uLayout/row.cpp"
#include "createtowerbutton.h"




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
void Table::createRows(int _numRows)
{
    for(int i= 0; i < _numRows; i++)
    {
        RowPtr row = RowPtr(new Row());
        m_rows.push_back(row);
    }
}

//-------------------------------------------------------------------//
void Table::createColumns(int _row, int _numColumns)
{
    RowPtr row = m_rows[_row];

    row->createColumns(_numColumns);
}

//-------------------------------------------------------------------//
void Table::createElement(int _row, int _column, UIElementPtr _element)
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
            VAOPtr v = render->getVAObyID(m_IDStr);
            (*shader)["UI"]->use();

            float scaleX = 2.0/window->getScreenWidth();
            float scaleY = 2.0/window->getScreenHeight();

            shader->setShaderParam1f("xpos",m_pos.m_x);
            shader->setShaderParam1f("ypos",m_pos.m_y);
            shader->setShaderParam1f("scaleX",scaleX);
            shader->setShaderParam1f("scaleY",scaleY);
            shader->setShaderParam4f("colourSelect",0,0,0,0);

            glBindTexture(GL_TEXTURE_2D, m_texture);

            v->bind();
            v->draw();
            v->unbind();

        }

        //now draw all its elements
        //glDisable(GL_BLEND);

        for(std::vector<RowPtr>::iterator it=m_rows.begin(); it!=m_rows.end(); it++)
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
void Table::screenAlignment(AlignType _alignment)
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
void Table::setText(int _row, int _column, const char *_text)
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
        int _row,
        int _column,
        ngl::Vec2 _pos,
        const char *_text,
        const char *_fontFile,
        int _ptsize,
        std::string _name
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
void Table::createTowerButton
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
        )
{
    Window* window = Window::instance();

    RowPtr row = m_rows[_row];

    UIElementPtr element = CreateTowerButtonPtr
            (
                new CreateTowerButton
                (
                    _pos,
                    _imageFile,
                     _name,
                    _parent,
                     _cost,
                    _towerType,
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
        int _row,
        int _column,
        ngl::Vec2 _pos,
        std::string _imageFile,
        std::string _name,
        TablePtr _parent,
        float _maxX,
        float _maxY
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
                    _parent,
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
UIElementWPtr Table::getElement(int _row, int _column)
{
    RowPtr row = m_rows[_row];
    UIElementWPtr element = row->getElement(_column);
    return element;
}

