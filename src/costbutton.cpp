#include "costbutton.h"
#include "game.h"
#include "texturelib.h"

//---------------------------------------------------------------------//
CostButton::CostButton
(
    ngl::Vec2 _pos,
    std::string _imageFile,
    std::string _name,
    std::string _type,
    int _cost,
    float _maxX,
    float _maxY
    ):

    UIButton
    (
        _pos,
        _imageFile,
        _name,
        _type,
        _maxX,
        _maxY
        ),
    m_cost(_cost)
{
    checkAffordable();
}

//---------------------------------------------------------------------//
CostButton::~CostButton()
{

}

//---------------------------------------------------------------------//
void CostButton::checkAffordable()
{
    if(Game::instance()->getPlayerCurrency()-m_cost >= 0)
    {
        m_affordable = true;
    }
    else
    {
        m_affordable = false;
    }
}

void CostButton::draw()
{


    //IN THIS FUNCTION NEED TO SET UP ISPRESSED RENDER

    glDisable(GL_DEPTH_TEST);

    Renderer *render = Renderer::instance();
    Window *window = Window::instance();
    ngl::ShaderLib *shader=ngl::ShaderLib::instance();

    GLfloat scaleX = 2.0/window->getScreenWidth();
    GLfloat scaleY = 2.0/window->getScreenHeight();


    (*shader)["UI"]->use();

    shader->setRegisteredUniform1f("xpos",m_pos.m_x);
    shader->setRegisteredUniform1f("ypos",m_pos.m_y);
    shader->setRegisteredUniform1f("scaleX",scaleX);
    shader->setRegisteredUniform1f("scaleY",scaleY);

    ngl::Vec3 c = Window::instance()->IDToColour(m_ID);
    shader->setRegisteredUniform4f("colourSelect", c.m_x/255.0f, c.m_y/255.0f, c.m_z/255.0f, 1);

    TextureLib *tex = TextureLib::instance();
    if(m_affordable)
    {
        if(m_isPressed==false)
        {
            tex->bindTexture(m_imageFile);
        }
        else if (m_type == "create")
        {
            tex->bindTexture(m_imageFile+"Creation");
        }
    }
    else
    {
        tex->bindTexture(m_imageFile+"NoMoney");
    }
    render->draw(m_IDStr, "UI");

    if(m_label)
    {
        m_label->draw();
    }

    //  glBindTexture(GL_TEXTURE_2D, m_texture);


    glEnable(GL_DEPTH_TEST);

    //  std::cout<<"drawing button "<<m_name<<" "<<m_pos<<std::endl;

}



