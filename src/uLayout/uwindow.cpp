#include "uLayout/uwindow.h"
#include "ngl/Vec2.h"

UWindow::UWindow
(
    ngl::Vec2 _pos,
    std::string _name,
    std::string _imageFile,
    UI *_parent,
    ngl::Vec2 _size
    ):

    UIElement( _pos, _name, "window",_imageFile),
    m_backgroundVisible(true),
    m_parent(_parent),
    m_isDrawable(true)

{
    m_size = _size;
}

//-------------------------------------------------------------------//
UWindow::~UWindow()
{

}

//-------------------------------------------------------------------//
void UWindow::createText
(
        const ngl::Vec2 &_pos,
        const char *_text,
        const char *_fontFile,
        const int &_ptsize,
        const std::string &_name
        )
{
    Window* window = Window::instance();

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
    m_elements.push_back(element);


}

//-------------------------------------------------------------------//
void UWindow::createCostButton
(
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
    m_elements.push_back(element);
}

//-------------------------------------------------------------------//
void UWindow::createButton
(
        const ngl::Vec2 &_pos,
        const std::string &_imageFile,
        const std::string &_name,
        const float &_maxX,
        const float &_maxY
        )
{
    Window* window = Window::instance();

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
    m_elements.push_back(element);
}

//-------------------------------------------------------------------//
void UWindow::draw()

{
    //IN THIS FUNCTION NEED TO SET UP ISPRESSED RENDER
    if(m_isDrawable == true)
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

        glEnable(GL_DEPTH_TEST);
        for(ElementVector::iterator it=m_elements.begin(); it!=m_elements.end(); it++)
        {
          (*it)->draw();
        }
    }
}

//-------------------------------------------------------------------//
void UWindow::createTable(const ngl::Vec2 &_pos,
                          const std::string &_name,
                          const std::string &_imageFile,
                          UI *_parent)
{

    Window* window = Window::instance();
    UIElementPtr menu = TablePtr(new Table(_pos,_name,_imageFile,_parent));
    if(menu)
    {
        int ID = window->getID();
        m_parent->registerID(menu, ID);
        menu->setID(ID);
        m_elements.push_back(menu);
    }
}

//-------------------------------------------------------------------//
void UWindow::alignElement(const std::string &_name,const AlignType &_alignment)
{
    UIElementPtr element;

    for(ElementVector::iterator it=m_elements.begin(); it!=m_elements.end(); it++)
    {
      UIElementPtr test = (*it);
      if(test->getName() == _name) //search for element in the vector
      {
           element = (*it);
      }
    }

    if(element)
    {
        ngl::Vec2 elPos = element->getPosition();
        ngl::Vec2 elSize = element->getSize();

        if(_alignment == RIGHT)
        {

            elPos.m_x = (m_pos.m_x+m_size.m_x)-elSize.m_x;

        }
        if(_alignment == LEFT)
        {
            elPos.m_x = m_pos.m_x;
        }

        if(_alignment == BOTTOM)
        {
            elPos.m_y = m_pos.m_y;
        }

        if(_alignment == TOP)
        {
            elPos.m_y = (m_pos.m_y+m_size.m_y)-elSize.m_y;
        }
        if(_alignment == CENTREX)
        {
            elPos.m_x = (m_size.m_x/2)-(elSize.m_x/2);
        }
        if(_alignment == CENTREY)
        {
            elPos.m_y = (m_size.m_y/2)-(elSize.m_y/2);
        }

        element->setPosition(elPos);
    }
}


//-------------------------------------------------------------------//
void UWindow::setFunction(const std::string &_name, UIButton::functionPtr _function)
{
    for(ElementVector::iterator it=m_elements.begin(); it!=m_elements.end(); it++)
    {
        UIElementPtr element = (*it);
        if(element && element->getName() == _name) //search for element in the vector
        {
            UIButtonPtr button = boost::dynamic_pointer_cast<UIButton>(element);

            if(button)
            {
                button->setFunction(_function);
                std::cout<<"function set to "<<element->getName()<<std::endl;
            }
        }
    }
}

//-------------------------------------------------------------------//
UIElementPtr UWindow::getElement(std::string _name)
{
    for(ElementVector::iterator it = m_elements.begin();
        it != m_elements.end();
        ++it)
    {
        if((*it)->getName() == _name)
        {
            return (*it);
        }
    }
    return UIElementPtr();

}

